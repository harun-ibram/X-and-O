#include <stdio.h>
#include <stdlib.h>
#include "fun.h"


Game init_game() {
	Game state = malloc(sizeof(struct game));
	state->choices = malloc(3 * sizeof(char *));
	for (int i = 0; i < 3; i++) {
		state->choices[i] = malloc(3 * sizeof(char));
		for (int j = 0; j < 3; j++) {
			state->choices[i][j] = ' ';
		}
	}
	state->turn = 0;
	state->result = -2;
	return state;
}
void turn (Game state) {
	// read the position where the player wants to place
	state->turn++;
	char player = state->turn % 2 ? 'X' : 'O';
	int x,y;
	printf("Player %c's turn. Pick a spot(line: 1-3, col: 1-3): \n", player);
	// TODO: check for valid move: spot is not already taken and is inside the table
	scanf("%d %d", &x, &y);
	while (x > 3 || x < 1 || y > 3 || y < 1 || state->choices[y-1][x-1] != ' ') {
		printf("Invalid position. Please try again!\nPick a spot(line: 1-3, col: 1-3): \n");
		scanf("%d %d", &x, &y);
	}
	state->choices[y-1][x-1] = player;
}

void draw(Game state) {
	// draw the table
	int i = 0;
	for (int j = 0; j <  3; j++) {
		printf(" %c | %c | %c \n", state->choices[0][j], state->choices[1][j], state->choices[2][j]);
		if(j < 2)
			printf("---+---+---\n");
	}
}

int check_win(char player, Game state) {
	// check if player X or O has won
	int main_diag = 0, sec_diag = 0;
	for (int i = 0; i < 3; i++) {
		int row = 0, col = 0;
		for (int j = 0; j < 3; j++) {
			if (state->choices[j][i] == player) {
				row++;
			}
			if (state->choices[i][j] == player) {
				col++;
			}
		}
		if (row == 3 || col == 3)
			return 1;
		if (state->choices[i][i] == player)
			main_diag++;
		if (state->choices[i][3 - i] == player)
			sec_diag++;
	}
	if (main_diag == 3 || sec_diag == 3) {
		return 1;
	}
	if (state->turn < 9)
		return 0;
	return -1;
	// check each line
	// check each column
	// check diagonals
	// check draw
	//
	// 0 - O win, 1 - X win, -1 - draw
}

void reset_game(Game state) {
	state->turn = 0;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			state->choices[i][j] = ' ';
		}
	}
}

Game destroy_game(Game state) {
	for (int i = 0; i < 3; i++) {
		free(state->choices[i]);
	}
	free(state->choices);
	free(state);
	return NULL;
}
void game_result (Game state) {
	char not_player = state->turn % 2 ? 'O' : 'X';
	char player = state->turn % 2 ? 'X' : 'O';
	if (state->turn < 9) {
		if(check_win(player, state) == 1) {
			printf("Player %c wins!\n", player);
			state->result = player == 'X' ? 1 : 0;
		}
	} else {
		switch(check_win(player, state)) {
			case(1):
				printf("Player %c wins!\n", player);
				state->result = 1;
				break;
			case(0):
				printf("Player %c wins\n", not_player);
				state->result = 0;
				break;
			case(-1):
				printf("It's a draw!\n");
				state->result = -1;
				break;
		}
	}
	if (state->result == -2) {
		return;
	}
	state = destroy_game(state);
	exit(1);
}
