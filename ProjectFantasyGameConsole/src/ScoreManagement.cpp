#include <stdio.h>
#include <cstring>

#include <tuple>
#include <string>
#include <vector>

#include "sqlite3.h"

#include "ScoreManagement.hpp"

namespace FantasyGameEngine 
{
    constexpr char insert_template[] =
        "INSERT INTO player_scores(name,score,achievement_date) "
        "VALUES (?,?,CURRENT_TIMESTAMP) "
        "ON CONFLICT(name) DO " // if name already exists ...
        "UPDATE SET score=?, achievement_date=CURRENT_TIMESTAMP;"; // just update score and date.
    constexpr char select_template[] = "SELECT name,score,achievement_date FROM player_scores;";

    int rc;
    sqlite3 *db;
    sqlite3_stmt 
        *insert_prep_statement, 
        *select_prep_statement;

    static int sqlite_callback(void* _, int argc, char** argv, char** az_col_name)
    {
        printf("got row:");
        for (int i = 0; i < argc; i++)
            printf("%s,", argv[i] ? argv[i] : "NULL");
        putchar('\n');
        return 0;
    }

    void exec_line(sqlite3* db, const char* sql)
    {
        printf("exec: %s\n", sql);
        char* err_msg;
        int rc = sqlite3_exec(db, sql, sqlite_callback, 0, &err_msg);
        if (rc != SQLITE_OK)
        {
            printf("sqlite error: %s\n", err_msg);
            sqlite3_free(err_msg);
        }
    }

    void update_score(const char* name, int score)
    {
        puts("update_score");
        sqlite3_bind_text(insert_prep_statement, 1, name, strlen(name), nullptr);
        sqlite3_bind_int(insert_prep_statement, 2, score);
        sqlite3_bind_int(insert_prep_statement, 3, score);
        printf("step returned %d\n", sqlite3_step(insert_prep_statement));
        sqlite3_clear_bindings(insert_prep_statement);
        sqlite3_reset(insert_prep_statement);
    }

    std::vector<std::tuple<std::string, int, std::string>> get_scores()
    {
        puts("get_scores");

        std::vector<std::tuple<std::string, int, std::string>> result;

        bool repeat;
        do
        {
            repeat = false;

            int res = sqlite3_step(select_prep_statement);
            switch (res)
            {
            case SQLITE_ROW:
            {
                printf("col types:");
                int col_count = sqlite3_column_count(select_prep_statement);
                for (int i = 0; i < col_count; i++)
                    printf("%d,", sqlite3_column_type(select_prep_statement, i));
                putchar('\n');
                result.push_back(
                    std::make_tuple(
                        std::string((const char*)sqlite3_column_text(select_prep_statement, 0)),
                        sqlite3_column_int(select_prep_statement, 1),
                        std::string((const char*)sqlite3_column_text(select_prep_statement, 2))));
            }
            repeat = true;
            break;

            default:
                printf("step returned %d\n", res);
                break;

            }
        } while (repeat);

        sqlite3_reset(select_prep_statement);
        return result;
    }

    bool score_system_init()
    {
        rc = sqlite3_open("score.db", &db);
        if (rc != SQLITE_OK)
        {
            return false;
        }

        exec_line(db,
            "DROP TABLE IF EXISTS `player_scores`;"
            "CREATE TABLE player_scores("
                "name CHAR(8) PRIMARY KEY NOT NULL,"
                "score INT NOT NULL,"
                "achievement_date TIMESTAMP NOT NULL);");

        sqlite3_prepare_v2(db, insert_template, sizeof(insert_template), &insert_prep_statement, nullptr);
        sqlite3_prepare_v2(db, select_template, sizeof(select_template), &select_prep_statement, nullptr);

        return true;
    }

    void score_system_close()
    {
        sqlite3_finalize(insert_prep_statement);
        sqlite3_finalize(select_prep_statement);
        sqlite3_close(db);
    }
}