#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

const int LETTERS = 4;
//constant for "spot it number" aka how many words there can be in total (n * (n-1) + 1)
const int NUMBER = 13;
//constant for how many words are in the word bank
const int WORDS = 1941;
//constant for the factorial of the number of letters
const int PERMUTATIONS = 24;

//function prototypes
void makeCards (char *card[NUMBER], char lettersArray [26]);
void swap(char* x, char* y);
char *makeDictionary (void);
bool checkWord (char *word, char *bank[WORDS]);
void permute(char* a, int b, int c);

//create array to hold the permutations of the card that's being checked
char *permutedWords[PERMUTATIONS];
int countPerms = 0;

    
int main(int argc,  char *argv[])
{
    // Check command-line arguments
    if (argc != 3)
    {
        printf("Usage: ./spotit loops minimum\n");
        return 1;
    }
   
    //create variables for number of loops and minimum set size based on command line arguments
    int loops = atoi(argv[1]);
    int minimum = atoi(argv[2]);
    
    //make sure minimum set size is in the appropriate range
    if (minimum < 2 || minimum > NUMBER)
    {
        printf("minimum must be at least 2 and no higher than %i\n", NUMBER);
        return 1;
    }
    
    
    
    
    
    //allocate memory for the permutations array
    for (int j = 0; j < PERMUTATIONS; j++)
    {
        permutedWords[j] = malloc(LETTERS + 1);
    }


    //open files
    FILE *dpoint = fopen("fourletterwords.txt", "r");
    FILE *results = fopen("results.txt", "w");

    //allocate memory for the dictionary
    char *dictionary[WORDS];
    for (int j = 0; j < WORDS; j++)
    {

        dictionary[j] = malloc(LETTERS + 1);

    }

    //allocate memory for the buffer to read the dictionary
    char *buffer = malloc(LETTERS + 1);
    
    //read words from file into the dictionary array
    for (int j = 0; j < WORDS; j++)
    {

        fscanf(dpoint, "%s", buffer);
        sprintf(dictionary[j], "%s", buffer);
    }
    
    //close words file
    fclose(dpoint);


    //allocate memory for cards array
     char *card[NUMBER];
    for (int j = 0; j < NUMBER; j++)
    {

        card[j] = malloc(LETTERS+ 1);

    }
    
    //create array for the alphabet
    char lettersArray[26];
    
     //assign lowercase letter to each position in the array
    for (int j = 0; j < 26; j++)
    {
        lettersArray[j] = j + 97;
    }
    
    //create variables to store characters
    char a;
    char b;
    char c;
    char d;
    char e;
    char f;
    char g;
    char h;
    char i;
    char l;
    char m;
    char n;
    char o;
    
    //change seed for rand function so it's not the same every time 
    srand(time(NULL));
    
//make variables to use to check each permutation of each card
char *currentWord;
int cardCounter = 0;
bool isItAWord;

//allocate buffer memory
char *printouts[NUMBER];
for (int j = 0; j < NUMBER; j++)
    {
        printouts[j] = malloc(30);
    }

//variable to know how many characters to write
int length;

//make new cards to check as many times as loops variable
for(int j = 0; j < loops; j++)
    {
        cardCounter = 0;
        makeCards(card, lettersArray);
        countPerms = 0;
        permute(card[cardCounter], 0, 3);
        
        //for each set, iterate through every permutation of each card
        for (int q = 0; q < PERMUTATIONS && cardCounter < NUMBER; q++)
        {
            currentWord = permutedWords[q];
            isItAWord = checkWord(currentWord, dictionary);
            if (isItAWord)
            {
                /*if less than minimum set, only print to the buffer. 
                if it's the minimum, write all the previous buffers and the current one. 
                if it's more, print and write the current one*/
                if (cardCounter < minimum - 1)
                {
                    if (cardCounter == 0)
                    {
                        sprintf(printouts[cardCounter], "\nLoop %i: Word %i is %s   ", j, cardCounter, currentWord);
                    }
                    else
                    {
                        sprintf(printouts[cardCounter], "Word %i is %s   ", cardCounter, currentWord);
                    }
                }

            else if (cardCounter == minimum - 1)
            {
                sprintf(printouts[cardCounter], "Word %i is %s     ", cardCounter, currentWord);
                for (int k = 0; k < minimum; k++)
                {
                length = strlen(printouts[k]);
                fwrite(printouts[k], sizeof(char), length, results);
                }
            }

            else
            {
                sprintf(printouts[cardCounter], "Word %i is %s   ", cardCounter, currentWord);
                length = strlen(printouts[cardCounter]);
                fwrite(printouts[cardCounter], sizeof(char), length, results);
            }
                //if it's a word, increase counter to look at the next card, permute the new card, and reset q so we check all permutations
                cardCounter++;
                countPerms = 0;
                if (cardCounter < NUMBER)
                {
                    permute(card[cardCounter], 0, LETTERS - 1);
                }
                q = 0;
                
            }

        }

    }

    //free all mallocs
    for (int j = 0; j < NUMBER; j++)
    {

        free(card[j]);

    }
    for (int j = 0; j < PERMUTATIONS; j++)
    {
        free (permutedWords[j]);
    }

    for (int j = 0; j < WORDS; j++)
    {
        free (dictionary[j]);
    }

    for (int j = 0; j < NUMBER; j++)
    {
        free (printouts[j]);
    }


    fclose(results);
}


void makeCards (char *card[NUMBER], char lettersArray [26])
{



  char temp;
  int randomPos;

    //shuffles letters randomly
    for (int j = 0; j < 26; j++)
    {

        temp = lettersArray[j];
        randomPos = rand() % 25;
        lettersArray[j] = lettersArray[(int) randomPos];
        lettersArray [(int) randomPos] = temp;

    }

    //assign variables to a unique now randomized character
    char a = lettersArray[0];
    char b = lettersArray[1];
    char c = lettersArray[2];
    char d = lettersArray[3];
    char e = lettersArray[4];
    char f = lettersArray[5];
    char g = lettersArray[6];
    char h = lettersArray[7];
    char i = lettersArray[8];
    char l = lettersArray[9];
    char m = lettersArray[10];
    char n = lettersArray[11];
    char o = lettersArray[12];
    
    //plug random characters into the cards
    sprintf(card[0], "%c%c%c%c", a, b, c, d);
    sprintf(card[1], "%c%c%c%c", a, e, f, g);
    sprintf(card[2], "%c%c%c%c", c, e, i, o);
    sprintf(card[3], "%c%c%c%c", o, d, f, h);
    sprintf(card[4], "%c%c%c%c", b, e, h, m);
    sprintf(card[5], "%c%c%c%c", b, f, i, n);
    sprintf(card[6], "%c%c%c%c", a, h, i, l);
    sprintf(card[7], "%c%c%c%c", b, g, l, o);
    sprintf(card[8], "%c%c%c%c", c, g, h, n);
    sprintf(card[9], "%c%c%c%c", c, f, l, m);
    sprintf(card[10], "%c%c%c%c", l, d, e, n);
    sprintf(card[11], "%c%c%c%c", m, d, g, i);
    sprintf(card[12], "%c%c%c%c", a, m, n, o);
}


bool checkWord (char *word, char *bank[WORDS])
{
    //use binary search to look through each word in the dictionary and compare with the given word
    int  change = WORDS / 2;
    char *dictionaryWord;
    int dictionaryPosition = change;


    while (change > 0)
    {
        dictionaryWord = bank[dictionaryPosition];

        if (strcmp(word, dictionaryWord) == 0)
        {

            return true;
        }

        if (strcmp(word, dictionaryWord) > 0)
        {
          change = change / 2;
          dictionaryPosition = dictionaryPosition + change;
        }

        if (strcmp(word, dictionaryWord) < 0)
        {
          change = change / 2;
          dictionaryPosition = dictionaryPosition - change;
        }

    }

    return false;
}


//function to swap characters to be used for permutations
void swap(char* x, char* y)
{
    char temp;
    temp = *x;
    *x = *y;
    *y = temp;
}

// permute the string and print every permutation into the array
void permute(char* a, int b, int c)
{

    int i;
    if (b == c)
    {
        sprintf(permutedWords[countPerms], "%s", a);
        countPerms++;
    }
     else {
        for (i = b; i <= c; i++)
            {
                swap((a + b), (a + i));
                permute(a, b + 1, c);
                swap((a + b), (a + i)); // backtrack
            }
        }
}