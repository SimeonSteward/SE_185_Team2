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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <stdbool.h>

#define MAX_NUM_WORDS 1500


typedef struct word {
	char name[15];
	int x;//represents how far right the word is with 0 being the furthest left side of the board
}word;

// the word returned from this function is already randomized
const char *getWord(char wordArray[][15], int *numWords);
void addWord(char word[], char wordArray[][15], int *numWords);
void scanWords(char wordArray[][15], int *numWords);
void displayBoard(word board[]);
void removeWord(word board[], char toRemove[15]);



int main(){

	int *numWords;
    char wordArray[MAX_NUM_WORDS][15];

    numWords = (int*)malloc(sizeof(int));
    *numWords = 0;

    srand(time(NULL));
    scanWords(wordArray, numWords);
	
	char word[50];
	int check;
	
	
	while(1) {
		
	printf("Type the word you would like to print.\n");
	scanf("%s", word);
	
	addWord(word, wordArray, numWords);
	
	printf("Would you like to add another word?\n");
	printf("1. Continue\n");
	printf("2. Exit\n");
	
	scanf("%d", &check);
	
	if (check == 2) {
		break;
	} 
	}


	//prompt user to see if they want to add words to the file
	//loop until the user says no
    
	word board[16] = {};
    word empty ={"",0};
    int i;
    for(i = 0;i<16;i++);{
        board[i] = empty;
    }

	while(strcmp(board[15].name,"")==0){
        word w = {wordArray[rand()%*numWords],rand()%15};
        for(i = 15;i>0;){
            board[i] = board[--i];
        }
        board[0] = w;
        char input[15];
        scanf("%s",&input);
        for(i = 0;i<16;i++){
            if(strcpr(input,board[i].name)==0){
                board[i] = empty;
            }
        }

		displayBoard(board);


	}
	//write to file new list of words
	//prompt the user to begin game
	//loop through the game script
	
	
	
	
	
	free(numWords);
	return 0;
}


void scanWords(char wordArray[][15], int *numWords){
	// this function populates an array with all of the words in the wordList.txt file

    char line[15];
    int count = 0;
    FILE *textFile;
    textFile = fopen("wordList.txt", "r");

    if(textFile == NULL){
        printf("Error opening file.");
        exit(1);
    }

    while(fgets(line, 15, textFile) != NULL){
            sscanf(line , "%s ", &wordArray[count]);
            count++;
        }

    *numWords = count;
    fclose(textFile);
}

void addWord(char word[], char wordArray[][15], int *numWords){
	// adds word to the array

    int tmp = (*numWords)++;
    FILE *textFile;
    textFile = fopen("wordList.txt", "a");

    fprintf(textFile, "\n%s", word);

    strcpy(wordArray[tmp], word);
    *numWords = tmp;
    fclose(textFile);
}


const char *getWord(char wordArray[][15], int *numWords){
	// gets a random word from the array

    int rNum;
    char *randWord;
    randWord = (char*)malloc(15 * sizeof(char));

    rNum = (rand() % *numWords);

    strcpy(randWord, wordArray[rNum]);
    return randWord; 
}
