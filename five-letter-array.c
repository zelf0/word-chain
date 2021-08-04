#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>


//constant for "spot it number" aka how many words there can be in total (n * (n-1) + 1)
const int NUMBER = 21;
//constant for how many words are in the word bank
const int WORDS = 9636;
//constant for the factorial of the number of letters
const int PERMUTATIONS = 120;

//function prototypes
void makeCards (char *card[NUMBER], char lettersArray [26]);
void swap(char* x, char* y);
char *makeDictionary (void);
bool checkWord (char *word, char *bank[WORDS]);
void permute(char* a, int l, int r);

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
        permutedWords[j] = malloc(6);
    }


    //open files
    FILE *dpoint = fopen("fiveletterwords.txt", "r");
    FILE *results = fopen("results.txt", "w");

    //allocate memory for the dictionary
    char *dictionary[WORDS];
    for (int j = 0; j < WORDS; j++)
    {

        dictionary[j] = malloc(6);

    }

    //allocate memory for the buffer to read the dictionary
    char *buffer = malloc(6);
    
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

        card[j] = malloc(6);

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
    char p;
    char r;
    char s;
    char t;
    char u;
    char v;
    char w;
    char y;
    
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
        permute(card[cardCounter], 0, 4);
        
        //for each set, iterate through every permutation of each card
        for (int q = 0; q < PERMUTATIONS; q++)
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
                permute(card[cardCounter], 0, 4);
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
    char p = lettersArray[13];
    char r = lettersArray[14];
    char s = lettersArray[15];
    char t = lettersArray[16];
    char u = lettersArray[17];
    char v = lettersArray[18];
    char w = lettersArray[19];
    char y = lettersArray[20];
    
    //plug random characters into the cards
    sprintf(card[0], "%c%c%c%c%c", a, b, c, d, e);
    sprintf(card[1], "%c%c%c%c%c", a, f, g, h, i);
    sprintf(card[2], "%c%c%c%c%c", a, l, m, n, o);
    sprintf(card[3], "%c%c%c%c%c", a, p, r, s, t);
    sprintf(card[4], "%c%c%c%c%c", a, u, v, w, y);
    sprintf(card[5], "%c%c%c%c%c", b, f, l, p, u);
    sprintf(card[6], "%c%c%c%c%c", b, g, m, r, v);
    sprintf(card[7], "%c%c%c%c%c", b, i, o, t, y);
    sprintf(card[8], "%c%c%c%c%c", b, h, n, s, w);
    sprintf(card[9], "%c%c%c%c%c", s, c, f, m, y);
    sprintf(card[10], "%c%c%c%c%c", s, d, g, o, u);
    sprintf(card[11], "%c%c%c%c%c", s, e, i, l, v);
    sprintf(card[12], "%c%c%c%c%c", u, m, e, t, h);
    sprintf(card[13], "%c%c%c%c%c", i, d, w, p, m);
    sprintf(card[14], "%c%c%c%c%c", i, c, u, r, n);
    sprintf(card[15], "%c%c%c%c%c", p, h, o, v, c);
    sprintf(card[16], "%c%c%c%c%c", y, d, h, l, r);
    sprintf(card[17], "%c%c%c%c%c", p, g, e, y, n);
    sprintf(card[18], "%c%c%c%c%c", o, e, f, r, w);
    sprintf(card[19], "%c%c%c%c%c", w, c, g, l, t);
    sprintf(card[20], "%c%c%c%c%c", v, f, d, n, t);
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
void permute(char* a, int l, int r)
{

    int i;
    if (l == r)
    {
        sprintf(permutedWords[countPerms], "%s", a);
        countPerms++;
    }
     else {
        for (i = l; i <= r; i++)
            {
                swap((a + l), (a + i));
                permute(a, l + 1, r);
                swap((a + l), (a + i)); // backtrack
            }
        }
}