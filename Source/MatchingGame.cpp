// Matching_Game.cpp : Defines the entry point for the application.

#include "../Header/MatchingGame.h"
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

using namespace FinalProject;

// Lists
std::vector<Card> cards;
std::vector<Image> images;
std::vector<nana::picture> pics;


int main()
{
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
	
	nana::form fm;
	nana::place plc(fm);
	nana::picture back(fm);

	// Create vector of cards with their identifying number.
	int number = 0;
	for (int i = 0; i < 10; i++) {
		cards.push_back(Card(number++));
	}
	for (int i = 0; i < 10; i++) {
		cards.push_back(cards[i]);
	}

	// Shuffle cards.
	std::random_shuffle(cards.begin(), cards.end());

	// Put them in rows and columns.
	for (int i = 0; i < 20; i++) {
		pics.push_back(nana::picture(fm));
		printf("%d \n", cards[i].getNumber());
	}

	plc.div("<cards grid=[4,5]>");
	for (int i = 0; i < 20; i++) {
		plc["cards"] << pics[i];
	}
	plc.collocate();

	for (int i = 0; i < 20; i++) {
		pics[i].load(backImage.getPic());
		pics[i].stretchable(5, 5, 5, 5);
	}

	//back.load(backImage.getPic());
	//back.stretchable(5, 5, 5, 5);
	
	
	fm.show();
	nana::exec();

	return 0;
}
