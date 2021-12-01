/**
 * @file tic.cpp
 * @brief 
 * @version 0.1
 * @date 2021-10-19
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <vector>
#include <cctype>
#include <ncurses.h>

const int Player1Wins = 1;
const int Player2Wins = -1;
/**
 * @brief Init the game components. Function initially in main() but moved
 * 
 */
void init(){
    initscr();
    timeout(-1);
	noecho();
	if (has_colors()){
		start_color();
		init_pair(1, COLOR_RED, COLOR_BLACK);
		init_pair(2, COLOR_BLUE, COLOR_BLACK);
		init_pair(3, COLOR_WHITE, COLOR_BLACK);
		init_pair(4, COLOR_YELLOW, COLOR_BLACK);
		attron(COLOR_PAIR(3));
		attroff(COLOR_PAIR(1)); attroff(COLOR_PAIR(2));
	}
    mvprintw(0, 0, "----------");
	mvprintw(1, 0, "|  |  |  |");
	mvprintw(2, 0, "----------");
	mvprintw(3, 0, "|  |  |  |");
	mvprintw(4, 0, "----------");
	mvprintw(5, 0, "|  |  |  |");
	mvprintw(6, 0, "----------");
	mvprintw(7, 0, "Use W, A, S, D to move around the cells");
	mvprintw(8, 0, "Use Q to input to the selected cell. Input will auto switch between X and O");
    move(1, 1);
	attroff(3);
	attron(A_BOLD);
}

/**
 * @brief just checking
 * 
 * @param c1 
 * @param c2 
 * @param c3 
 * @return short int 
 */

short int check_winner(char c1, char c2, char c3){
	if(c1 == c2 && c2 == c3 && c3 == 'X'){
		return Player1Wins;
	}
	else if (c1 == c2 && c2 == c3 && c3 == 'O'){
		return Player2Wins;
	}
	return 0;
}

/**
 * @brief return winner player
 * 
 * @param play 
 */

void check_and_exit(short int play){
	attron(COLOR_PAIR(4));
	if (play > 0){
		mvprintw(9, 0,  "*******************************");
		mvprintw(10, 0, "*                             *");
		mvprintw(11, 0, "*       PLAYER 1 WINS!!       *");
		mvprintw(12, 0, "*       PLAYER 2 LOSES!!      *");
		mvprintw(13, 0, "*                             *");
		mvprintw(14, 0, "*******************************");
		mvprintw(15, 0, "Press any key to exit.");
	}
	else if (play < 0){
		mvprintw(9, 0,  "*******************************");
		mvprintw(10, 0, "*                             *");
		mvprintw(11, 0, "*       PLAYER 2 WINS!!       *");
		mvprintw(12, 0, "*       PLAYER 1 LOSES!!      *");
		mvprintw(13, 0, "*                             *");
		mvprintw(14, 0, "*******************************");
		mvprintw(15, 0, "Press any key to exit.");
	}
	else {
		mvprintw(9, 0,  "*******************************");
		mvprintw(10, 0, "*                             *");
		mvprintw(11, 0, "*             TIE!            *");
		mvprintw(12, 0, "*                             *");
		mvprintw(13, 0, "*                             *");
		mvprintw(14, 0, "*******************************");
		mvprintw(15, 0, "Press any key to exit.");
	}
	attroff(COLOR_PAIR(4));
}

/**
 * @brief check if cell grid is not full
 * 
 * @param cell 
 * @return true 
 * @return false 
 */

bool is_not_full(char cell[3][3]){
	for (int i = 0; i < 3; i++){
		for (int j = 0; j < 3; j++){
			if (cell[j][i] == '\0' || cell[i][j] == '\0'){
				return true;
			}
		}
	}
	return false;
}

/**
 * @brief 
 * 
 * @return int 
 */
int main(){
    short int pl = 0, kx = 0, ky = 0;
    char cell[3][3];
    bool inp = true;
    std::vector<short int> vx = {1, 4, 7}; auto x = vx.begin();
    std::vector<short int> vy = {1, 3, 5}; auto y = vy.begin();
    for (int i = 0; i < 3; i++){
		for (int j = 0; j < 3; j++){
			cell[i][j] = '\0';
		}
	}
	init();
	do{
		switch(tolower(getch())){
			case 'a':
				kx -= 1; x -= 1;
				if (x - vx.begin() < 0) x = vx.begin();
				if (kx < 0) kx = 0;
				break;
			case 'd':
				kx += 1; x += 1;
				if (x - vx.begin() > 2) x = vx.begin() + 2;
				if (kx > 2) kx = 2;
				break;
			case 'w':
				ky -= 1; y -= 1;
				if (y - vy.begin() < 0) y = vy.begin();
				if (ky < 0) ky = 0;
				break;
			case 's':
				ky += 1; y += 1;
				if (y - vy.begin() > 2) y = vy.begin() + 2;
				if (ky > 2) ky = 2;
				break;
			case 'q': //let's blow some colors into this thing
				attroff(COLOR_PAIR(inp + 1);
				attron(COLOR_PAIR(inp + 1));
				echo(); addch(inp ? 'X' : 'O');
				cell[ky][kx] = inp ? 'X' : 'O';
				inp = !inp;
				noecho(); break;
			default:
				continue;
		}
		move(*y, *x);
		pl += check_winner(cell[0][0], cell[0][1], cell[0][2]);
		pl += check_winner(cell[1][0], cell[1][1], cell[1][2]);
		pl += check_winner(cell[2][0], cell[2][1], cell[2][2]);
		pl += check_winner(cell[0][0], cell[1][0], cell[2][0]);
		pl += check_winner(cell[0][1], cell[1][1], cell[2][1]);
		pl += check_winner(cell[0][2], cell[1][2], cell[2][2]);
		pl += check_winner(cell[0][0], cell[1][1], cell[2][2]);
		pl += check_winner(cell[2][0], cell[1][1], cell[0][2]);
	} while (pl == 0 && is_not_full(cell));
	attroff(COLOR_PAIR(1)); attroff(COLOR_PAIR(2));
	check_and_exit(pl); attroff(A_BOLD);
	getch();
	endwin(); return 0;
}
