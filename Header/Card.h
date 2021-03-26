
namespace FinalProject
{
	class Card
	{
		int row;
		int column;
		int number;

	public:
		Card(int number) {
			this->number = number;
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

		int getNumber() {
			return this->number;
		}

	};

}