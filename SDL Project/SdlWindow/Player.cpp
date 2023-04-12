#include "Player.h"

void Player::GetCard(Card* CardtoGet) {

	if(CardtoGet->isValid){

				if (ChosenCard1 != NULL && ChosenCard1 == CardtoGet ) {

					std::cout << "Card1Unselected\n";
					ChosenCard1->FlipCard();
					ChosenCard1 = NULL;
				}

				else if (ChosenCard2 != NULL && ChosenCard2 == CardtoGet) {

					std::cout << "Card2Unselected\n";
					ChosenCard2->FlipCard();
					ChosenCard2 = NULL;
				}
				else if (ChosenCard1 == NULL) {
					ChosenCard1 = CardtoGet;
					std::cout << "Card1Selected\n";
					ChosenCard1->FlipCard();
					std::cout << ChosenCard1;
				}
				else if (ChosenCard2 == NULL) {
					ChosenCard2 = CardtoGet;
					std::cout << "Card2Selected\n";
					ChosenCard2->FlipCard();
					// std::cout << ChosenCard2;
				}
				else if (ChosenCard1 != NULL && ChosenCard2 != NULL) {

					ChosenCard1->FlipCard();
					ChosenCard1 = CardtoGet;
					ChosenCard1->FlipCard();
				}

	}
}

void Player::CheckCards() {

	if (ChosenCard1 != NULL && ChosenCard2 != NULL && ChosenCard1->CardId == ChosenCard2->CardId) {
		ChosenCard1->isValid = false;
		ChosenCard2->isValid = false;
		//std::cout << ChosenCard1->CardId;
		//std::cout << ChosenCard2->CardId;
		//Grid.CardsLeft -= 2;
		Score += 10;
		ChosenCard1 = NULL;
		ChosenCard2 = NULL;
	}
}