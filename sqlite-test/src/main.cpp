#include <stdio.h>
#include <cstring>

#include <tuple>
#include <string>
#include <vector>
#include <thread>
#include <chrono>

#include "sqlite3.h"

static int sqlite_callback(void *not_used, int argc, char **argv, char **az_col_name)
{
    printf("got row:");
    for (int i = 0; i < argc; i++)
        printf("%s,", argv[i] ? argv[i] : "NULL");
    putchar('\n');
    return 0;
}

void exec_line(sqlite3 *db, const char *sql)
{
    printf("exec: %s\n", sql);
    char *err_msg;
    int rc = sqlite3_exec(db, sql, sqlite_callback, 0, &err_msg);
    if (rc != SQLITE_OK)
    {
        printf("sqlite error: %s\n", err_msg);
        sqlite3_free(err_msg);
    } 
}

void update_score(sqlite3_stmt *ps, const char* name, int score)
{
    puts("update_score");
    sqlite3_bind_text(ps, 1, name, strlen(name), nullptr);
    sqlite3_bind_int(ps, 2, score);
    sqlite3_bind_int(ps, 3, score);
    printf("step returned %d\n", sqlite3_step(ps));
    sqlite3_clear_bindings(ps);
    sqlite3_reset(ps);
}

std::vector<std::tuple<std::string, int, std::string>> get_scores(sqlite3_stmt *ps)
{
    puts("get_scores");

    std::vector<std::tuple<std::string, int, std::string>> result;

    bool repeat;
    do
    {
        repeat = false;
        
        int res = sqlite3_step(ps);
        switch (res)
        {
        case SQLITE_ROW:
            {
                printf("col types:");
                int col_count = sqlite3_column_count(ps);
                for (int i = 0; i < col_count; i++)
                    printf("%d,", sqlite3_column_type(ps, i));
                putchar('\n');
                result.push_back(
                    std::make_tuple(
                        std::string((const char *)sqlite3_column_text(ps, 0)),
                        sqlite3_column_int(ps, 1),
                        std::string((const char *)sqlite3_column_text(ps, 2))));
            }
            repeat = true;
            break;
        
        default:
            printf("step returned %d\n", res);
            break;

        }
    } while (repeat);

    sqlite3_reset(ps);
    return result;
}

const char insert_template[] = 
    "INSERT INTO player_scores(name,score,achievement_date) " 
    "VALUES (?,?,CURRENT_TIMESTAMP) " 
    "ON CONFLICT(name) DO " // if name already exists ...
    "UPDATE SET score=?, achievement_date=CURRENT_TIMESTAMP;"; // just update score and date.
const char select_template[] = "SELECT name,score,achievement_date FROM player_scores;";

int main()
{
    sqlite3 *db;
    int rc;

    rc = sqlite3_open("test.db", &db);
    if (rc != SQLITE_OK) return -1;

    exec_line(db, 
        "CREATE TABLE player_scores("
            "name CHAR(8) PRIMARY KEY NOT NULL,"
            "score INT NOT NULL,"
            "achievement_date TIMESTAMP NOT NULL);");

    sqlite3_stmt *insert_prep_statement, *select_prep_statement;
    sqlite3_prepare_v2(db, insert_template, sizeof(insert_template), &insert_prep_statement, nullptr);
    sqlite3_prepare_v2(db, select_template, sizeof(select_template), &select_prep_statement, nullptr);

    update_score(insert_prep_statement, "adam", 10);
    update_score(insert_prep_statement, "florian", 15);
    update_score(insert_prep_statement, "faisalhanbali", 20); // Names longer than 8 chars can still be saved, without strict mode. Turning on strict mode is probably not worth it.

    for (const auto &e : get_scores(select_prep_statement))
        printf("got row from get_scores: %s, %d, %s\n", 
            std::get<0>(e).c_str(), 
            std::get<1>(e), 
            std::get<2>(e).c_str());

    std::this_thread::sleep_for(std::chrono::seconds(2)); // Sleep to test if different timestamp is generated.

    update_score(insert_prep_statement, "adam", 25);

    puts("after update:");
    for (const auto &e : get_scores(select_prep_statement))
        printf("got row from get_scores: %s, %d, %s\n", 
            std::get<0>(e).c_str(), 
            std::get<1>(e), 
            std::get<2>(e).c_str());

    sqlite3_finalize(insert_prep_statement);
    sqlite3_finalize(select_prep_statement);
    sqlite3_close(db);
}