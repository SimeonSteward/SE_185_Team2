//Final Project Template//
/////////////////////////
/* 
Team xx (please insert your team number instead of xx)
Team member 1 "Simeon Steward" | " 15%"
Team member 2 "Kim Phu" | "15%"
Team member 3 "Colin Kempf" | "20%"
Team member 4 "Perry Ports" | "28%"
Team member 5 "Ethan Baccam" | "22%"
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

struct timeval start, end;


// the word returned from this function is already randomized
const char *getWord(char wordArray[][15], int *numWords);
void addWord(char word[], char wordArray[][15], int *numWords);
void scanWords(char wordArray[][15], int *numWords);

void removeWord(char board[18][18], char toRemove[15], word list[]);

void addToBoard(char board[18][18], word list[], int *currWord, char wordToAdd[15]);
bool dropYaxis(char board[18][18]);

int main(){

	int *numWords;
    char wordArray[MAX_NUM_WORDS][15];
    char board[18][18];
    int *currWord;
	word list[15];
    char startGame;
    bool gameGoing = true;
    int check;
    int wordRate = 2000;

    numWords = (int*)malloc(sizeof(int));
    currWord = (int*)malloc(sizeof(int));
    *numWords = 0;
    *currWord = 0;

    // seeds random function for getting words
    srand(time(NULL));
    scanWords(wordArray, numWords);


    // populate board initially w spaces. adds bars and hyphens on the sides
    for(int y = 0; y <= 17; y++){            
        for(int x = 0; x <= 17; x++){
           board[x][y] = ' ';
           if(y == 0 || y == 17){
                board[x][y] = '-';
            } else if(x == 0 || x == 17){
                board[x][y] = '-';
            }
        }
    }

    // asks user if they would like to play the game
    printf("Start game? ");
    scanf("%c", &startGame);


    if(startGame == 'y' || startGame == 'Y'){
        // asks user if they would like to add a word
        while(1){
        char word[15];
        
        printf("Would you like to add word?\n");
	    printf("1. Continue\n");
	    printf("2. Exit\n");

        scanf("%d", &check);

        if(check == 1){
            printf("Enter word: ");
            scanf("%s", word);

	        addWord(word, wordArray, numWords);

        } else{
            break;
        }
        }


        // game loop
        while(gameGoing){
			int difference;
			int timePrint;
            char userInput[20];
            char tmpWord[20];

            if(wordRate == 2000){
                strcpy(tmpWord, getWord(wordArray, numWords));
				addToBoard(board, list, currWord, tmpWord);
            }

            // display board
            for(int y = 0; y < 17; y++){
            for(int x = 0; x <= 17; x++){
            if(x == 17){
                printf("%c\n", board[x][y]);
            }else{
                printf("%c", board[x][y]);
            } 
            }
            }




			gettimeofday(&start, NULL);
            printf("Enter a word: ");
            scanf("%s", userInput);
			gettimeofday(&end, NULL);
			difference = fabs((end.tv_sec - start.tv_sec)) * 1000 + fabs((end.tv_usec - start.tv_usec)) / 1000.0;
			timePrint = difference / wordRate; 

            removeWord(board, userInput, list);

            while(timePrint > 1){

            gameGoing = dropYaxis(board);
            strcpy(tmpWord, getWord(wordArray, numWords));
	        addToBoard(board, list, currWord, tmpWord);

            timePrint--;
            }
			wordRate = wordRate - 200;
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

void addToBoard(char board[18][18], word list[], int *currWord, char wordToAdd[15]){
    // this function adds a new word to the board 

    int len = strlen(wordToAdd);

    // determines where on the board the word can legally go
    list[*currWord].x = rand() % (15 - strlen(wordToAdd)) + 1; 

    // ensures the first line is clear
    for(int x = 1; x < 16; x++){
        board[x][1] = ' ';
    }

    // adds to board and to the word list
    // adds word to the board;
    for(int i = 0; i < (len + 1); ++i){
        if(i == len +1){
            board[i + list[*currWord].x][1] = '\0';
        } else{
        board[i + list[*currWord].x][1] = wordToAdd[i];
        }
    }


    strcpy(list[*currWord].name, wordToAdd);

    // ensures that the word list doesn't overflow
    *currWord++;
    if(*currWord == 16 ){
        *currWord = 0;
    }

}


bool dropYaxis(char board[18][18]){

    char tempLine[18];
    char tempLine2[18];

    for(int i = 1; i < 15; i++){
            if(i == 1){
                //strcpy(tempLine, board[i]);
                for(int j = 0; j <= 17; j++){                        
                    if(j == 17){
                        tempLine[j] = '\0';
                    }
                    if(board[j][i] == '\0'){
                        board[j][i] = ' ';
                    }
                    tempLine[j] = board[j][i];
                }
            }

            //strcpy(tempLine2, board[i + 1]);
            for(int j = 0; j <= 17; j++){
                if(j == 17){
                        tempLine2[j] = '\0';
                    }
                    if(board[j][i] == '\0'){
                        board[j][i] = ' ';
                    }
                    tempLine2[j] = board[j][i];
            }

            //strcpy(board[i + 1], tempLine);
            for(int j = 0; j <= 17; j++){
                    if(board[j][i] == '\0'){
                        board[j][i] = ' ';
                    }
                    board[j][i +1] = tempLine[j];
                    if(j == 17){
                        board[j][i] = '\0';
                    }
            }

            //strcpy(tempLine, tempLine2);
            for(int j = 0; j < 17; j++){
                if(j == 17){
                    tempLine[j] = '\0';
                } else if(tempLine[j] == '\0'){
                    tempLine[j] = ' ';
                }
                tempLine[j] = tempLine2[j];
            }
    }

    // check for failure
    for(int i = 1; i< 16; i++){
        if(board[i][16] != ' '){
        return false;
        }
    }

    return true;
}


void removeWord(char board[18][18], char toRemove[15], word list[]){

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
        // populates the temp string in each line to compare with the word to remove
        for(int i = 0; i <= (len +1); i++){
            if(i = (len +1)){
                tempStr[i] = '\0';
           }
           tempStr[i] = board[xAxis + i][y];
        }

        // if the string is the correct one it removes it
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
