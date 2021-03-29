// Matching_Game.cpp : Defines the entry point for the application.

#include "../Header/MatchingGame.h"
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

using namespace FinalProject;

bool operator==(Card x, Card y) {
	if (x.getImageIndex() == y.getImageIndex()) {
		return true;
	}
	else
		return false;
}

std::vector<Card> createDeck();


int main()
{

	// Lists
	std::vector<Card> cards;
	std::vector<Image> images;
	std::vector<Card> chosenCards;
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
	
	nana::form fm(nana::API::make_center(600,600));
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
			pics[i]->load(images[cards[i].getImageIndex()].getPic());
			if (chosenCards.size() == 1) {
				if (cards[i].getGridIndex() != chosenCards[0].getGridIndex()) {
					chosenCards.push_back(cards[i]);
				}
			}
			else {
				chosenCards.push_back(cards[i]);
			}
			if (chosenCards.size() >= 2) {
				waitTimer.start();
			}
		});
	}

	waitTimer.elapse([&] {
		if (chosenCards[0] == chosenCards[1]) {
			pics[chosenCards[0].getGridIndex()]->load(blankImage.getPic());
			pics[chosenCards[1].getGridIndex()]->load(blankImage.getPic());
			match.play();
			game.gotMatch();
		}
		else {
			pics[chosenCards[0].getGridIndex()]->load(backImage.getPic());
			pics[chosenCards[1].getGridIndex()]->load(backImage.getPic());
			noMatch.play();
		}
		waitTimer.stop();
		plc.collocate();
		chosenCards.clear();
		game.takeTurn();
		if (game.isOver()) {
			nana::form popup(fm, { 300,200 });
			popup.modality();
		}
	});
	
	fm.show();
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

