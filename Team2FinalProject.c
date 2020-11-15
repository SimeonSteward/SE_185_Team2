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
#include <sys/time.h>

#define MAX_NUM_WORDS 1500


typedef struct word{
	char name[15];
	int x;//represents how far right the word is with 0 being the furthest left side of the board
}word;

// the word returned from this function is already randomized
const char *getWord(char wordArray[][15], int *numWords);
void addWord(char word[], char wordArray[][15], int *numWords);
void scanWords(char wordArray[][15], int *numWords);

void displayBoard(char board[17][17]);
void removeWord(char board[17][17], char toRemove[15], word list[]);

void addToBoard(char board[17][17], word list[], int *currWord, char wordToAdd[15]);
bool dropYaxis(char board[17][17]);

int main(){

	int *numWords;
    char wordArray[MAX_NUM_WORDS][15];
    char board[17][17];
    int *currWord;
	word list[15];
    char startGame;
    bool gameGoing = true;

    numWords = (int*)malloc(sizeof(int));
    currWord = (int*)malloc(sizeof(int));
    *numWords = 0;
    *currWord = 0;

    // seeds random function for getting words
    srand(time(NULL));
    scanWords(wordArray, numWords);


    // populate board initially w spaces. adds bars and hyphens on the sides
    for(int x = 0; x < 17; x++){            
        for(int y = 0; y < 17; y++){
            if(y == 0){
                board[x][y] = '-';
            } else if(x == 0 || x == 17){
                board[x][y] = '|';
            }
           board[x][y] = ' ';
        }
    }

    // asks user if they would like to play the game

    printf("Start game? ");
    scanf("%c", &startGame);
     
    if(startGame == 'y' || 'Y'){
        // add ethans stuff

        while(gameGoing){
            // if iter == 1 // add word
            // else drop words
            // add word
            // those should be in a for loop based on how many times the time fucntion returns
        }

    }




	
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

void addToBoard(char board[17][17], word list[], int *currWord, char wordToAdd[15]){
    // this function adds a new word to the board 

    // determines where on the board the word can legally go
    list[*currWord].x = rand() % (15 - strlen(wordToAdd)) + 1; 

    // ensures the first line is clear
    for(int x = 1; x < 16; x++){
        board[x][1] = ' ';
    }

    // adds to board and to the word list
    strcpy(board[list[*currWord].x][1], wordToAdd);
    strcpy(list[*currWord].name, wordToAdd);

    // ensures that the word list doesn't overflow
    *currWord++;
    if(*currWord == 16 ){
        *currWord = 0;
    }

}


bool dropYaxis(char board[17][17]){

    char tempLine[15];
    char tempLine2[15];


    for(int i = 1; i < 15; i++){
            if(i == 1){
                strcpy(tempLine, board[i]);
            }

            strcpy(tempLine2, board[i + 1]);
            strcpy(board[i + 1], tempLine);
            strcpy(tempLine, tempLine2);
    }

    // check for failure
    for(int i = 1; i< 16; i++){
        if(board[i][16] != ' '){
        return false;
        }
    }

    return true;
}

void displayBoard(char board[17][17]){
    // prints out the board

    for(int y = 0; y < 17; y++){
        for(int x = 0; x < 18; x++){
            if(x == 18){
                printf("\n");
            }else{
            printf("%c", board[x][y]);
            } 
        }
    }
}

void removeWord(char board[17][17], char toRemove[15], word list[]){

     
    int len = strlen(toRemove);
    int xAxis = 1;
    char tempStr[15];
    int listNum = 0;

    // finds if input sring toRemove matches possible word on the baord

    for(int i = 0; i < 15; i++){
        if(strcmp(list[i].name, toRemove) == 0){
            xAxis = list[i].x;
            listNum = i;
        }
    }

    // finds the string on the board and sets it to spaces
    
    for(int y = 1; y < 16; y++){
        strncpy(tempStr, board[xAxis][y], len);
        if(strcmp(tempStr, toRemove) == 0){
            for(int i = 0; i < (len + 1); i++){
                board[i + xAxis][y] = ' ';
            }
            // removes word on the list
            strcpy(list[listNum].name, "  ");
            return;
        }
    }
}
