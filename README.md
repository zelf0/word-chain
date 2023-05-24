# word-chain
## C application that finds lists of words which adhere to a special rule.

## A few examples of valid lists: 

**Mauve, molds, curly, lent, hymn, using, trim, deify, thud, hers, hail, darn, stay**

**fonts, scamp, verbs, chord, afield, dusky, cubit, thyme**

**Nasty, befit, drips, bravo, decoy, hijack, folks, ampule**

Feel free to try and spot the special rule! Scroll down for the solution.















The rule is that each word has precisely letter in common with every other word in the list. In other words, every pair of words shares no more or less than one letter.

It's similar to the card game Spot It, where every two cards has one picture in common between them.

![image](https://github.com/zelf0/word-chain/assets/84274405/c31ffc2e-ef1b-4798-8c34-00db9661950d)



The files are named with the minimum number of letters, and the data structure used to search a list of valid English words. The programs using a trie run the most time-efficently compared to the programs using a hash table or of course an array. (I plan to revisit this to see if a more perfect hash function runs even faster than the trie)

The four-letter versions can only make lists up to 13 words long because it is impossible for a set to follow the rule past 13. The words will be a mix of 4 and 5 letter words (a previous commit makes lists of only 4 letter words). The five-letter version makes lists up to 21 words, but a set that long is extremely rare so the proram is unlikely to find one that long with its current efficiency. The words will be a mix of 5 and 6 letter words (and in a previous commit, only 5).

After you run the program, the results will be written to a file called results.txt.




To run the program, choose the file to run, followed by 2 command-line arguments. The first argument is for the number of iterations to generate and check new list (most lists are invalid). My mac takes about a minute to do 5,000,000 loops with four-letter-trie.c. The second argument is for the minimum size of list you want to print. For example, if your minimum size is 7, only lists containing 7 or more words will be written to results.txt.

Example usage: ./four-letter-trie 10000000 10 (Runs four-letter-trie, running 10000000 iterations, and printing lists of at least 10)


*Dictionary used is http://www.mieliestronk.com/corncob_lowercase.txt*




The rule is that each word has precisely letter in common with every other word in the list. In other words, every pair of words shares no more or less than one letter.
