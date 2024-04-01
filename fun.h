typedef struct game {
	char **choices;
	int turn;
	int result;
} *Game;

Game init_game();

void turn(Game);

void draw(Game);

int check_win(char, Game);

void game_result(Game);

void reset_game(Game);
