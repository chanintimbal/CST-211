#include "../GameOfLife/GameOfLife.hpp"
#include "../DataStructures/array2d.hpp"

using namespace data_structures;

int main()
{
	GameOfLife game(10, 10);
	game.run();

	return 0;
}