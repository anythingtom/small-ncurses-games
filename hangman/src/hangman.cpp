#include <iterator>
#include <string>
#include <vector>
#include <cstdlib>
#include <iostream>
/*
 *  -------
 *  |     |
 *  |     |
 *  |     0
 *  |    -|-
 *  |    / \
 *  |
 * ---
 * Imagine hardcoding all of this
 * height = 8
 * len = 9
 */

std::vector<std::string> hangman = {
	"",
	" -------",
	" |     |",
	" |     |",
	" |     0",
	" |    -|-",
	" |    / \\",
	" |       ",
	"---",
};

int max_mistakes = hangman.size();

/**
 * @brief clears the screen
 * 
 */
void clrscr(){
	#ifdef _WIN32
		system("cls");
	#elif __linux__
		system("clear");
	#endif 
}

/**
 * @brief making this because C++ COULD have some simple operators but cba
 *
 * @param c char for checking
 * @param s string for checking
 *
 * @return 
 */
bool charInString(char c, std::string s){
	for (char i : s){
		if (i == c){
			return true;
		}
	}
	return false;
}

int main(){
	std::string guess, display;
	int current_mistakes = 0;
	char ug; bool kt = false;
	std::cout << "Enter guess string: ";
	std::cin >> guess;
	for (int i = 0; i < guess.length(); i++){
		display += "_";
	}
	clrscr();
	while (current_mistakes < max_mistakes){
		//First output the hangman length
		for (int i = 0; i < current_mistakes; i++){
			std::cout << hangman[i] << std::endl;
		}
		std::cout << display << std::endl;
		std::cout << max_mistakes - current_mistakes << " More mistake(s) and you will lose!\nEnter char: ";
		std::cin >> ug;
		if (charInString(ug, guess)){
			for (int i = 0; i < guess.length(); i++){
				if (guess[i] == ug){	
					display[i] = ug;
				}
			}
		} else {
			current_mistakes++;
			clrscr();
		}
	}
}
