
namespace FinalProject
{

	class Game 
	{
		int numTurns;

	public:
		Game() {
			numTurns = 0;
		}

		void take_turn() {
			numTurns++;
		}

		int get_turn() {
			return numTurns;
		}

	};

}