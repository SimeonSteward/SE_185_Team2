//Final Project Template//
/////////////////////////
/* 
Team xx (please insert your team number instead of xx)
Team member 1 "Simeon Steward" | "Percentage of Contribution to The Project"
Team member 2 "Name" | "Percentage of Contribution to The Project"
Team member 3 "Name" | "Percentage of Contribution to The Project"
Team member 4 "Name" | "Percentage of Contribution to The Project"
Team member 4 "Name" | "Percentage of Contribution to The Project"
*/

////////////////////
#include<stdio.h>//
//add more here////

//////////////////////
//Struct Definition//
typedef word {
	char name[];
	int x;//represents how far right the word is with 0 being the furthest left side of the board
}word;
////////////////////


/////////////////////////////////////
//User Defined Functions Prototype//
 char* fileReader(char file[]);
 void fileWriter(char file[], char words[][]);
 void displayBoard(word board[]);
 void removeWord(word board[], char toRemove[15]);
//List prototypes here and define//
//tehm below the main function////
const int MAX_NUM_WORDS = 2000;
/////////////////////////////////

int main(){
	char* words = (char*)malloc(sizeof(char)*15*MAX_NUM_WORDS);
	words = fileReader("(File Adress");
	//prompt user to see if they want to add words to the file
	//loop until the user says no
	word board[];
	while(){
		displayBoard(board);
		


	}
	//write to file new list of words
	//prompt the user to begin game
	//loop through the game script
	
	
	
	
	
	
	return 0;
}

///////////////////////////////////////
//User Defined Functions' Definition//
/////////////////////////////////////
