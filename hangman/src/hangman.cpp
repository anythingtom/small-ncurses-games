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
	std::string guess;
	std::cout << "Enter input string: ";
	std::cin >> guess;
	std::string display;
	for (int i = 0; i < guess.length(); i++){
		display += "_"; 
	}
	char c;
	int mistakes = hangman.size();
	while (mistakes > 0){
		system("clear");
		std::cout << "Enter character: ";
		std::cin >> c;
		for (int i = 0; i < guess.length(); i++){
			if (charInString(c, guess)){
				for (int i = 0; i < )
			}
		}
	}
}
