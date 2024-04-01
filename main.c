#include "fun.h"

int main() {

	Game state = init_game();
	turn(state);
	draw(state);
	for (int i = 0; i < 8; i++) {
		turn(state);
		draw(state);
		game_result(state);
	}
	return 0;
}
