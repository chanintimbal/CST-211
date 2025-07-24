#include "../GameOfLife/GameOfLife.hpp"
#include "../DataStructures/array2d.hpp"

using namespace data_structures;

int main()
{
	GameOfLife game(50, 50);
	game.run();

	return 0;
}