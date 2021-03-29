
namespace FinalProject
{

	class Game 
	{
		int numTurns;
		int numMatches;

	public:
		Game() {
			numTurns = 0;
			numMatches = 0;
		}

		void takeTurn() {
			this->numTurns++;
		}

		int getTurn() {
			return numTurns;
		}

		void gotMatch() {
			this->numMatches++;
		}

		bool isOver() {
			if (this->numMatches == 10) {
				return true;
			}
			else {
				return false;
			}
		}

	};

}