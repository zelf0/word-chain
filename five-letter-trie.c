#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

const int LETTERS = 5;

//constant for "spot it number" aka how many words there can be in total (n * (n-1) + 1)
const int NUMBER = 21;
//constant for how many words are in the word bank
const int WORDS = 2984;
//constant for how many words are in the special word bank (words with the higher number of letters)
const int SPCWORDS = 6773; //technically these aren't needed anymore because it could use a while loop instead since there are no dictionary arrays
//constant for the factorial of the number of letters
const int PERMUTATIONS = 120;
const int EXTRAPERMS = 720;


    typedef struct trienode
{
    struct trienode *child[26];
    bool isWord;

} trienode;

//function prototypes
void makeCards (char *card[NUMBER], char lettersArray [26]);
void swap(char* x, char* y);
void permute(char* a, int b, int c);
bool insertNode(char *input);
bool check(char *input, int length);

trienode  *createnode();


//create array to hold the permutations of the card that's being checked
char *permutedWords[EXTRAPERMS];
int countPerms = 0;

char extra[26 - NUMBER];

trienode *trie;



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
    for (int j = 0; j < EXTRAPERMS; j++)
    {
        permutedWords[j] = malloc(LETTERS + 2);
    }


    //open files
    FILE *dpoint = fopen("fiveletterwords.txt", "r");
    FILE *spoint = fopen("sixletterwords.txt", "r");
    FILE *results = fopen("results.txt", "w");

    //create trie for dictionary
    trie = createnode();

    //allocate memory for the buffer to read the dictionary
    char *buffer = malloc(LETTERS + 2);

    //read words from file into the dictionary trie
    for (int j = 0; j < WORDS; j++)
    {

        fscanf(dpoint, "%s", buffer);
        insertNode(buffer);

    }


    for (int j = 0; j < SPCWORDS; j++)
    {

        fscanf(spoint, "%s", buffer);
        insertNode(buffer);

    }

    //close words file
    fclose(dpoint);
    fclose(spoint);
    free(buffer);

    //allocate memory for cards array
     char *card[NUMBER];
    for (int j = 0; j < NUMBER; j++)
    {

        card[j] = malloc(LETTERS + 1);

    }

    //create array for the alphabet
    char lettersArray[26];

     //assign lowercase letter to each position in the array
    for (int j = 0; j < 26; j++)
    {
        lettersArray[j] = j + 97;
    }

    //move q to the second to last position
    char switchq = lettersArray[16];
    lettersArray[16] = lettersArray[24];
    lettersArray[24] = switchq;
   
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

char *special = malloc(LETTERS + 2);

//allocate buffer memory
char *printouts[NUMBER];
for (int j = 0; j < NUMBER; j++)
    {
        printouts[j] = malloc(40);
    }

//variable to know how many characters to write
int length;

//make new cards to check as many times as loops variable
for(int j = 0; j < loops; j++)
    {
        cardCounter = 0;
        makeCards(card, lettersArray);
        countPerms = 0;
        permute(card[cardCounter], 0, (LETTERS - 1));

        //for each set, iterate through every permutation of each card
        for (int q = 0; q < PERMUTATIONS && cardCounter < NUMBER; q++)
        {
            currentWord = permutedWords[q];
            isItAWord = check(currentWord, LETTERS);


            //if this card is not a word in any permutation, try adding an extra letter
            if (q == PERMUTATIONS - 1 && cardCounter > 1)
            {
                //print to a new string the current card plus one extra letter that hasn't been used yet
                for (int k = 0; k < (26 - NUMBER) && !isItAWord; k++)
                {
                    if (extra[k] && extra[k] != '0')
                    {
                        //check the special card to see if any permutation is a word
                        sprintf(special, "%s%c", card[cardCounter], extra[k]);
                        countPerms = 0;
                        permute(special, 0, LETTERS);
                        for (int z = 0; z < EXTRAPERMS && !isItAWord; z++)
                        {
                            currentWord = permutedWords[z];
                            isItAWord = check(currentWord, LETTERS + 1);
                            if (isItAWord)
                            {
                                sprintf(&extra[k], "%c", '0');
                            }
                        }
                    }
                }
            }




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
    for (int j = 0; j < EXTRAPERMS; j++)
    {
        free (permutedWords[j]);
    }


    for (int j = 0; j < NUMBER; j++)
    {
        free (printouts[j]);
    }

    free(special);

    fclose(results);
}


void makeCards (char *card[NUMBER], char lettersArray [26])
{



  char temp;
  int randomPos;

    //shuffles non-q letters randomly
    for (int j = 0; j < 23; j++)
    {

        temp = lettersArray[j];
        randomPos = rand() % 22;
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

    //plug random characters into the cards which are formatted so every card has one letter in common
    sprintf(card[0], "%c%c%c%c%c", a, b, c, d, e);
    sprintf(card[1], "%c%c%c%c%c", a, l, m, n, o);
    sprintf(card[2], "%c%c%c%c%c", s, e, i, l, v);
    sprintf(card[3], "%c%c%c%c%c", i, d, w, p, m);
    sprintf(card[4], "%c%c%c%c%c", b, h, n, s, w); 
    sprintf(card[5], "%c%c%c%c%c", a, f, g, h, i);
    sprintf(card[6], "%c%c%c%c%c", a, u, v, w, y);
    sprintf(card[7], "%c%c%c%c%c", b, f, l, p, u);
    sprintf(card[8], "%c%c%c%c%c", b, g, m, r, v);
    sprintf(card[9], "%c%c%c%c%c", a, p, r, s, t);
    sprintf(card[10], "%c%c%c%c%c", b, i, o, t, y); 
    sprintf(card[11], "%c%c%c%c%c", s, c, f, m, y);
    sprintf(card[12], "%c%c%c%c%c", s, d, g, o, u);   
    sprintf(card[13], "%c%c%c%c%c", u, m, e, t, h);  
    sprintf(card[15], "%c%c%c%c%c", p, h, o, v, c);
    sprintf(card[14], "%c%c%c%c%c", i, c, u, r, n);
    sprintf(card[16], "%c%c%c%c%c", y, d, h, l, r);
    sprintf(card[17], "%c%c%c%c%c", p, g, e, y, n);
    sprintf(card[18], "%c%c%c%c%c", o, e, f, r, w);
    sprintf(card[19], "%c%c%c%c%c", w, c, g, l, t);
    sprintf(card[20], "%c%c%c%c%c", v, f, d, n, t);


    //make extras
    for (int k = 0; k < (26 - NUMBER); k++)
    {
      sprintf(&extra[k], "%c", lettersArray[NUMBER + k]);
    }



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


bool insertNode(char *input)
{
    // if (*root == NULL)
    // {
    //     *root = createnode();
    // }

    //type word to be unsigned
    unsigned char *word = (unsigned char *)input;

    trienode *tmp = trie;

    int inputLength = strlen(input);

    //go through each letter of the word and add nodes if there aren't any yet
    for (int i = 0; i < inputLength; i++)
    {
        if (tmp->child[word[i] - 97] == NULL)
        {
            tmp->child[word[i] - 97] = createnode();
        }

        tmp = tmp->child[word[i] - 97];

    }

    //now that nodes are created at each letter, indicate that this is a word if it isn't already
    if (tmp->isWord)
    {
        //return false bc it's already a word
        return false;
    }

    else
    {
        tmp->isWord = true;
        return true;
    }

}

bool check(char *input, int inputLength)
{
    unsigned char *word = (unsigned char *)input;

    trienode *tmp = trie;

    // if (inputLength != strlen(input))
    // {
    //     printf("%i\n%lu\n%s\n", inputLength, strlen(input), input);
    // }

    //go through each letter of the word until the final letter
    for (int i = 0; i < inputLength; i++)
    {
        if (tmp->child[word[i] - 97] == NULL)
        {
            //printf("%s is not a word\n", input);
            return false;
        }

        tmp = tmp->child[word[i] - 97];

    }


    if (tmp->isWord)
    {

        //printf("%s is a word\n", input);
        return true;
    }

    else
    {
        //printf("%s is not a word\n", input);
        return false;
    }
}

trienode  *createnode()
{
    trienode *newnode = malloc(sizeof(trienode));

    //initialize children to null
    for (int i = 0; i < 26; i++)
    {
        newnode->child[i] = NULL;
    }

    newnode->isWord = false;

    return newnode;

}
