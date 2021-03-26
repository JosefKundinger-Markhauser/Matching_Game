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


int main()
{
	nana::form fm;
	nana::size imageSize(100, 100);

	nana::paint::graphics graphics(imageSize);
	nana::paint::image pic("../Images/back.jpg");

	pic.paste(graphics, nana::point(100,100));

	
	

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
		printf("%d \n", cards[i].getNumber());
	}

	//fm.div("vert <<00><01><02><03>> <<10><11><12><13>> <<20><21><22><23>> <<30><31><32><33>> <<40><41><42><43>>");
	
	fm.collocate();
	fm.show();
	nana::exec();

	return 0;
}
