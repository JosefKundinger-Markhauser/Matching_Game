#include "MatchingGame.h"

namespace FinalProject
{

	class Image
	{
		nana::paint::image image;

	public:
		Image() {

		}

		Image(char* pathToPic) {
			this->image = nana::paint::image(pathToPic);
		}

		auto getPic() {
			return this->image;
		}
	};

}