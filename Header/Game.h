
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

		int getTurns() {
			return this->numTurns;
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

		void reset() {
			this->numMatches = 0;
			this->numTurns = 0;
		}

	};

}