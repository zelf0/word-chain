# word-chain
## C application that finds lists of words which adhere to a predefined rule.

An example of a valid list is: **sting, funky, hours, fired, podgy, coven, prawn** 

Another example is: **hail, trim, hers, mauve, curly, lent, hymn, deify, molds, using, thud, stay, darn**

Feel free to try and spot the rule, or scroll to the bottom of the readme.


The files are named with the minimum number of letters, and the data structure used to search a list of valid English words. The trie is the most efficient of the three data structures.

The four-letter versions can only make lists up to 13 words long because it is impossible for a set to follow the rule past 13. The words will be a mix of 4 and 5 letter words (a previous commit makes lists of only 4 letter words). The five-letter version makes lists up to 21 words, but a set that long is extremely rare so the proram is unlikely to find one that long with its current efficiency. The words will be a mix of 5 and 6 letter words (and in a previous commit, only 5).

After you run the program, the results will be written to a file called results.txt.

There are 2 command-line arguments. The first is for the number of times you want to generate and check a new list (most are invalid). My mac takes about a minute to do 5,000,000 loops with four-letter-trie.c. The second argument is for the minimum size of list you want to print. For example, if your minimum size is 7, only lists containing 7 or more words will be written to results.txt.

Example usage: ./four-letter-trie 10000000 10


*Dictionary used is http://www.mieliestronk.com/corncob_lowercase.txt*




The rule is that each word has precisely letter in common with every other word in the list. In other words, every pair of words shares no more or less than one letter.
