// Matching_Game.cpp : Defines the entry point for the application.

#include "../Header/MatchingGame.h"
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

using namespace FinalProject;

bool operator==(Card x, Card y);
std::vector<Card> createDeck();
void writeToFile(std::string name, int score);
std::vector<std::string>getValuesFromFile(std::string type);

char* fileName = "topScores.txt";
nana::form fm(nana::API::make_center(600, 600));
nana::form scoresPage(fm);

int main()
{

	// Lists
	std::vector<Card> cards;
	std::vector<Image> images;
	std::vector<Card*> chosenCards;
	std::vector<std::unique_ptr<nana::picture>> pics;

	//timer
	nana::timer waitTimer{ std::chrono::milliseconds(1000) };

	// Create all images.
	images.push_back(Image("AH.jpg"));
	images.push_back(Image("2H.jpg"));
	images.push_back(Image("3H.jpg"));
	images.push_back(Image("4H.jpg"));
	images.push_back(Image("5H.jpg"));
	images.push_back(Image("6H.jpg"));
	images.push_back(Image("7H.jpg"));
	images.push_back(Image("8H.jpg"));
	images.push_back(Image("9H.jpg"));
	images.push_back(Image("10H.jpg"));
	Image backImage("back.jpg");
	Image blankImage("blank.jpg");

	// Create all sounds.
	nana::audio::player match("match.wav");
	nana::audio::player noMatch("no_match.wav");
	nana::audio::player gameOver("game_over.wav");
	nana::threads::pool pool(1);

	//display top scores.
	std::vector<std::string> names = getValuesFromFile("names");
	std::vector<std::string> scores = getValuesFromFile("scores");
	std::vector<std::unique_ptr<nana::label>> labels;

	// Create all lables.
	nana::label namelbl{ scoresPage, "NAME" };
	nana::label scorelbl{ scoresPage, "SCORE" };

	for (int i = 0; i < names.size(); i++) {
		labels.emplace_back(new nana::label{ scoresPage, names.at(i) });
		labels.emplace_back(new nana::label{ scoresPage, scores.at(i) });
	}

	nana::place scorePlace(scoresPage);
	scorePlace.div("values grid=[2,6]");
	scorePlace["values"] << namelbl;
	scorePlace["values"] << scorelbl;

	for (int i = 0; i < labels.size(); i++) {
		scorePlace["values"] << *labels.at(i);
	}
	scorePlace.collocate();

	nana::place plc(fm);
	plc.div("<cards grid=[4,5]>");
	nana::picture back(fm, true);
	Game game;
	cards = createDeck();

	// Create a grid in place and populate it.
	for (int i = 0; i < 20; i++) {
		pics.emplace_back(new nana::picture(fm));
		plc["cards"] << *pics.back();
		pics.back()->load(backImage.getPic());
		pics.back()->stretchable(5, 7, 5, 7);
	}
	plc.collocate();

	for (int i = 0; i < 20; i++) {
		pics[i]->events().click([i, &pics, &cards, &images, &chosenCards, &game, &backImage, &plc, &waitTimer] {
			if (cards[i].getState() == 0) {
				pics[i]->load(images[cards[i].getImageIndex()].getPic());
				cards[i].setFaceUp();
				if (chosenCards.size() == 1) {
					if (cards[i].getGridIndex() != chosenCards[0]->getGridIndex()) {
						chosenCards.push_back(&cards[i]);
					}
				}
				else {
					chosenCards.push_back(&cards[i]);
				}
				if (chosenCards.size() >= 2) {
					waitTimer.start();
				}
			}
		});
	}

	fm.show();
	scoresPage.show();

	waitTimer.elapse([&] () {
		Card temp1(chosenCards[0]->getImageIndex());
		Card temp2(chosenCards[1]->getImageIndex());
		if (temp1 == temp2) {
			pics[chosenCards[0]->getGridIndex()]->load(blankImage.getPic());
			pics[chosenCards[1]->getGridIndex()]->load(blankImage.getPic());
			chosenCards[0]->setMatched();
			chosenCards[1]->setMatched();
			match.play();
			game.gotMatch();
		}
		else {
			pics[chosenCards[0]->getGridIndex()]->load(backImage.getPic());
			pics[chosenCards[1]->getGridIndex()]->load(backImage.getPic());
			chosenCards[0]->setFaceDown();
			chosenCards[1]->setFaceDown();
			noMatch.play();
		}
		waitTimer.stop();
		plc.collocate();
		chosenCards.clear();
		game.takeTurn();
		if (game.isOver()) {

			gameOver.play();
			std::string name = "";
			std::cout << "Please enter your name\n>>";
			std::getline(std::cin, name);
			while (name == "") {
				std::cout << "Invalid name, please enter agian.\n>>";
				std::getline(std::cin, name);
			}

			nana::form popup(fm);
			nana::place pl(popup);
			nana::label winlbl{ popup, "Contratulations!!" };
			nana::label numTurns{ popup, "Number of turns: " + std::to_string(game.getTurns()) };
			nana::button quitBtn(popup, "Quit");
			nana::button playBtn(popup, "Play Agian");

			// Layout
			pl.div("vert <<><winlbl><>> <<><numTurns><>> <play> <quit>");
			pl["winlbl"] << winlbl;
			pl["numTurns"] << numTurns;
			pl["play"] << playBtn;
			pl["quit"] << quitBtn;
			pl.collocate();

			// button events
			quitBtn.events().click([&] {
				writeToFile(name, game.getTurns());
				fm.close();
			});
			playBtn.events().click([&] {
				writeToFile(name, game.getTurns());
				cards = createDeck();
				pics.clear();
				for (int i = 0; i < 20; i++) {
					pics.emplace_back(new nana::picture(fm));
					plc["cards"] << *pics.back();
					pics.back()->load(backImage.getPic());
					pics.back()->stretchable(5, 7, 5, 7);
				}
				for (int i = 0; i < 20; i++) {
					pics[i]->events().click([i, &pics, &cards, &images, &chosenCards, &game, &backImage, &plc, &waitTimer] {
						pics[i]->load(images[cards[i].getImageIndex()].getPic());
						if (chosenCards.size() == 1) {
							if (cards[i].getGridIndex() != chosenCards[0]->getGridIndex()) {
								chosenCards.push_back(&cards[i]);
							}
						}
						else {
							chosenCards.push_back(&cards[i]);
						}
						if (chosenCards.size() >= 2) {
							waitTimer.start();
						}
						});
				}
				plc.collocate();
				names = getValuesFromFile("names");
				scores = getValuesFromFile("scores");
				labels.clear();
				for (int i = 0; i < names.size(); i++) {
					labels.emplace_back(new nana::label{ scoresPage, names.at(i) });
					labels.emplace_back(new nana::label{ scoresPage, scores.at(i) });
				}
				nana::place scorePlace(scoresPage);
				scorePlace.div("values grid=[2,6]");
				scorePlace["values"] << namelbl;
				scorePlace["values"] << scorelbl;

				for (int i = 0; i < labels.size(); i++) {
					scorePlace["values"] << *labels.at(i);
				}
				scorePlace.collocate();
				game.reset();
				popup.close();
			});

			popup.modality();

		}
	});
	
	
	nana::exec();

	return 0;
}

std::vector<Card> createDeck() {
	std::vector<Card> cards;

	// Create vector of cards with their image identifying number.
	for (int i = 0; i < 10; i++) {
		cards.push_back(Card(i));
	}
	for (int i = 0; i < 10; i++) {
		cards.push_back(cards[i]);
	}

	// Shuffle cards.
	std::random_shuffle(cards.begin(), cards.end());

	// Assing grid index.
	for (int i = 0; i < 20; i++) {
		cards[i].setGridIndex(i);
	}

	return cards;
}

void writeToFile(std::string name, int score) {
	std::vector<std::string> names;
	std::vector<std::string> scores;
	std::string line;

	names.push_back(name);
	scores.push_back(std::to_string(score));

	// input
	std::ifstream inFile;
	inFile.open(fileName);

	if (inFile.is_open()) {
		int temp = 0;
		while (getline(inFile, line)) {
			if (temp == 0) {
				names.push_back(line);
				temp = 1;
			}
			else {
				scores.push_back(line);
				temp = 0;
			}
		}
		inFile.close();
	}

	std::string tempName;
	std::string tempScore;

	for (int i = 0; i < names.size(); i++) {
		for (int j = i + 1; j < names.size(); j++) {
			if (std::stoi(scores.at(j)) < std::stoi(scores.at(i))) {
				tempName = names.at(i);
				tempScore = scores.at(i);
				
				names.at(i) = names.at(j);
				scores.at(i) = scores.at(j);

				names.at(j) = tempName;
				scores.at(j) = tempScore;
			}
		}
	}
	
	// output
	std::ofstream outFile;
	outFile.open(fileName);
	if (outFile.is_open()) {
		if (names.size() >= 5) {
			for (int i = 0; i < 5; i++) {
				outFile << names.at(i) + "\n" + scores.at(i) + "\n";
			}
		}
		else {
			for (int i = 0; i < names.size(); i++) {
				outFile << names.at(i) + "\n" + scores.at(i) + "\n";
			}
		}
		outFile.close();
	}
}

std::vector<std::string>getValuesFromFile(std::string type) {
	std::string line;
	std::vector<std::string> names;
	std::vector<std::string> scores;

	std::ifstream inFile;
	inFile.open(fileName);

	if (inFile.is_open()) {
		int temp = 0;
		while (getline(inFile, line)) {
			if (temp == 0) {
				names.push_back(line);
				temp = 1;
			}
			else {
				scores.push_back(line);
				temp = 0;
			}
		}
		inFile.close();
	}
	if (type == "names") {
		return names;
	}
	else {
		return scores;
	}
}

bool operator==(Card x, Card y) {
	if (x.getImageIndex() == y.getImageIndex()) {
		return true;
	}
	else
		return false;
}



