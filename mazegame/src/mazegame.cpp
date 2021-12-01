/**
 * @file mazegame.cpp
 * @author Hoàng Minh Đức
 * @brief Maze-solving game written in C++
 * @version 1.0
 * @date 2021-10-23
 * 
 * @copyright Copyright (c) 2021
 */
#include <ncurses.h>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <cctype>
#include <cstdio>
using std::vector;
/**
 * @brief the Maze class
 * 
 */
class Maze{
	private:
		unsigned int len, width, mode;
		int lives;
		vector<vector<unsigned char>> maze;
		unsigned int lenc, widthc; char mov;
	public:
		/**
		 * @brief initialize things
		 * 
		 * @param width Length of maze
		 * @param len Width of maze
		 * @param lives Number of lives
		 * @param mode Difficulty
		 */
		Maze(unsigned int width, unsigned int len, unsigned int lives, unsigned int mode){
			srand(time(NULL));
			maze.clear();
			lenc = 0; widthc = 0;
			this->len = len;
			this->width = width;
			this->lives = lives;
			this->mode = 7 - mode;
			for (unsigned int i = 0; i < len; i++){
				vector<unsigned char> current;
				for (unsigned int j = 0; j < width; j++){
					current.push_back(rand() % 4);
				}
				maze.push_back(current);
			}
			maze[0][0] = 1;
			maze[len-1][width-1] = 1;
			initscr();
			timeout(-1);
			noecho();
			start_color();
			init_pair(1, COLOR_RED, COLOR_BLACK);
			init_pair(2, COLOR_YELLOW, COLOR_BLACK);
			init_pair(3, COLOR_WHITE, COLOR_BLACK);
			attron(A_BOLD);
		}
		/**
		 * @brief Ends the game
		 * 
		 */
		~Maze(){
			endwin();
		}
		/**
		 * @brief draws the maze
		 * 
		 * Draws the maze and some other things as well
		 */
		void draw(){
			for (vector<unsigned char> vch : maze){
				for (unsigned char c : vch){
					if (c != 0){
						printw(" ");
					}
					else {
						attron(COLOR_PAIR(1));
						printw("#");
						attroff(COLOR_PAIR(1));
					}
				}
				printw("\n");
			}
			printw("Use the W, A, S, D keys to move around. Press Q to exit.\n");
			printw("Don't run into the red traps! You\'ll lose a life and have to start over!\n");
			printw("Enter the white X to win.\n");
			printw("If the maze is unsolvable, exit and re-enter to generate a new one\n");
			printw("Lives: %d", lives);
			move(len - 1, width - 1);
			attron(COLOR_PAIR(3));
			addch('X');
			attroff(COLOR_PAIR(3));
			move(0, 0);
		}
		/**
		 * @brief game execution
		 * 
		 * Should be handled better tbh
		 */
		void exec(){
			while ((lenc != len-1 || widthc != width-1) && lives > 0){
				mov = getch();
				switch(tolower(mov)){
					case 'a':
						widthc--;
						if (widthc < 0){widthc = 0;}
						break;
					case 'd':
						widthc++;
						if (widthc > width-1){widthc = width-1;}
						break;
					case 's':
						lenc++;
						if (lenc > len-1){lenc = len-1;}
						break;
					case 'w':
						lenc--;
						if (lenc < 0){lenc = 0;}
						break;
					case 'q':
						return;
				}	
				move(lenc, widthc);
				if (mvinch(lenc, widthc) == 2097443){
					lives--;
					mvprintw(len + 4, 0, "Lives: %d", lives);
					lenc = 0; widthc = 0;
					move(0, 0);
				}
			}
			if (lives == 0){
				attron(COLOR_PAIR(1));
				mvprintw(len + 5, 0, "GAME OVER! Press any key to continue...");
				attron(COLOR_PAIR(1));
				getch();
				return;
			}
			attron(COLOR_PAIR(2));
			mvprintw(len + 5, 0, "YOU WIN! Press any key to continue...");
			attroff(COLOR_PAIR(2));
			getch();
		}
};

/**
 * @brief Main function 
 * 
 * @return int 
 */
int main(){
	unsigned int l, w, p, mode;
	printf("=========WELCOME TO MAZE GAME!!=========\n");
	printf("Enter the length, width, and the amount of lives you want: ");
	scanf("%u %u %u", &l, &w, &p);
	while(l <= 0 && w <= 0 && p <= 0){
		printf("Your input is invalid. Please try again: ");
		scanf("%u %u %u", &l, &w, &p);
	}
	printf("Which mode do you want to play? Press 1 for easy, 2 for medium, 3 for hard, and 4 for extra hard: ");
	scanf("%u", &mode);
	while(mode < 1 || mode > 4){ 
		printf("Your input is invalid. Please try again: ");
		scanf("%u", &mode);
	}
	printf("=========GAME START!=========\n");
	printf("Press enter to start...\n"); getchar(); getchar();
	Maze m = Maze(l, w, p, mode); 
	m.draw();
	m.exec();
	return 0;
}
