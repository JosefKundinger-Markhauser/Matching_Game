#include "MatchingGame.h"

namespace FinalProject
{
	class Card
	{
		int row;
		int column;
		int imageIndex;
		int gridIndex;

	public:
		Card(int imageIndex) {
			this->imageIndex = imageIndex;
			this->gridIndex = 0;
			this->row = 0;
			this->column = 0;
		}

		void setRow(int row) {
			this->row = row;
		}

		int getRow() {
			return this->row;
		}

		void setColumn(int column) {
			this->column = column;
		}

		int getColumn() {
			return this->column;
		}

		int getImageIndex() {
			return this->imageIndex;
		}

		void setGridIndex(int index) {
			this->gridIndex = index;
		}

		int getGridIndex() {
			return this->gridIndex;
		}

	};

}