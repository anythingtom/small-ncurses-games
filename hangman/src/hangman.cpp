#include <list>
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
	" -------",
	" |     |",
	" |     |",
	" |     0",
	" |    -|-",
	" |    / \\",
	" |       ",
	"---",
};

const int max_mistakes = hangman.size();

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
	while (current_mistakes < max_mistakes){
		//First output the hangman length
		for (int i = 0; i < current_mistakes; i++){
			std::cout << hangman[i] << std::endl;
		}
	}
}
