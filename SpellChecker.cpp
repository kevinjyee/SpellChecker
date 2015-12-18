/*
 * Kevin Yee
 * Spell Checker Program
 * Fall 2015
 */

#include <stdio.h> // provides declarations for printf and putchar
#include <stdint.h> // provides declarations for int32_t uint32_t and the other (new) standard C types

/* All of your code must be in this file. Please no #includes other than standard system headers (ie.., stdio.h, stdint.h)
 *
 * Many students find it helpful to declare global variables (often arrays). You are welcome to use
 * globals if you find them helfpul. Global variables are by no means necessary for this project.
 */

/* You must write this function (spellCheck). Do not change the way the function is declared (i.e., it has
 * exactly two parameters, each parameter is a standard (mundane) C string (see SpellCheck.pdf).
 * You are expected to use reasonable programming style. I *insist* that you indent
 * reasonably and consistently in your code. I strongly encourage you to avoid big functions
 * So, plan on implementing spellCheck by writing two or three other "support functions" that
 * help make the actual spell checking easier for you.
 * There are no explicit restictions on using functions from the C standard library. However,
 * for this project you should avoid using functionality from the C++ standard libary. You will
 * almost certainly find it easiest to just write everything you need from scratch!
 */

//Global Variables
char BigA= 'A';
char BigZ= 'Z';
char LittleA = 'a';
char LittleZ = 'z';
int difference = 0x20;
int length = 0;
int dupposition = 0;
char word[30] = {0};
char Noduplicates[1000] = {'\0'};


//Functions to call
int FindNewStart(int startofword, char dictionary[],int flag);
int compareStrings(char word[], char dictionary[], int startofword, int flag);
int ClearWord(char word []);
int ClearDuplicates(char duplicates[]);
void Check(char article[], char dictionary[]);
void Print();

/* Function: toLower
 * --------------------------------------------------
 * turns the entire contents to lower case
 * Points to the first memory location of array
 * Increments to see if between A and Z
 * If between A and Z  then add x20 to turn to lower
 * if greater than or equal to a, keep the same;
*/

int toLower(char *checker){

while(*checker){
if(*checker >= BigA && *checker <= BigZ){
*checker = *checker + difference;
}
checker = checker + 1;
}
return 0;
}


/*Function: isWord
 * -----------------
 * Is it between 'a' and 'z'?
 * if true, then return 1 and put it into the word array
 * if false, then return 0 and that means you've reached the end of the word array
 */

int isLetter(char letter){
	if(letter >= LittleA && letter <= LittleZ){
		return 1;
	}
	else{
		return 0;
	}
	return 0;
	}

/*Function: searchDictionary
 * -----------------------
 * Compares the first word to the first word of each dictionary value
 * If you can't find the first word, find the new start
 */


int searchDictionary(char word[],char dictionary[]){
	int startofword =0;
	int startofduplicate = 0;
	int isWord = -1; //flag
	int j=0;//designates position of word
	if(word[0] == dictionary[startofword]){
		isWord = compareStrings(word,dictionary,startofword, 0); // the start of the word matches, compare the rest of the strings
	}
	else{
		startofword = FindNewStart(startofword,dictionary,0); // find the start of a new word in the dictionary
		isWord = compareStrings(word,dictionary,startofword,0); //compare again
	}

	if (isWord != 0){
		if(compareStrings(word,Noduplicates, startofduplicate, 1) == 1){
			while(word[j] != '\0'){
			Noduplicates[dupposition] = word[j];
			dupposition = dupposition + 1;
			j = j + 1;
			}
			dupposition = dupposition +1;
			Noduplicates[dupposition] = 1;
		}


	}
	return 0;
}



/*Function: compareStrings
 * ----------------------------------
 * First word matches
 * Compare the rest of the string
 * Ends if same length
 * Ends if the while loop remains true
 */

int compareStrings(char word[], char dictionary[], int startofword, int flag){
	//flag = 0 means the the comparison is between the word and the dictionary
	//flag = 1 means the comparison is between the word and the Noduplicates array
	char end = '\n';
			if(flag == 1){
				end = '\0';
			}

	int i = 0; //used to increment through word
    int j = 0; //used to increment through dictionary
while(dictionary[j] != '\0'){

	while(word[i] == dictionary[startofword]){

		if(word[i] == '\0' || dictionary[startofword] == end){
			break;
		}
		i = i+1;
		startofword = startofword +1;
	}


		if(word[i] == '\0' && dictionary[startofword] == end){
			return 0;
		}
		else{
			i = 0;
			startofword = FindNewStart(startofword,dictionary,flag);
					j = startofword;
		}

}
return 1;
}

/*Function: FindNewStart
 * -----------------------------------
 * Finds the new start of word in the dictionary
 */

int FindNewStart(int startofword, char dictionary[],int flag){
//flag = 0 looking for dictionary
	//flag = 1 looking for no duplicates
	char end = '\n';
	if(flag == 1){
		end = '\0';
	}

	while(dictionary[startofword] != end){
		startofword = startofword + 1;
	}
	return startofword = startofword + 1;
}


/*Function: ClearWord
 * -------------------------------------
 * Clears the array holding the word in the article
 */

int ClearWord(char word []){
	int i =0;
	for (i=0; i < 30;i +=1){
	word[i] = '\0';
	}
	return 0;
}

/*Function: ClearDuplicates
 * ------------------------------------
 * Clears the array holding the duplicate values
 */

int ClearDuplicates(char duplicates[]){
	int i =0;
	for (i =0; i<300; i+=1){
		Noduplicates[i] = '\0';
	}
	return 0;
	}

/*Function: Check
 * ---------------------------------
 * Check checks to see if it's a word in the dictionary by finding the word
 *
 */
void Check(char article[], char dictionary[]){
	int i = 0; //used to increment through the article
	int wordlength=0; //used to increment through the word array
	dupposition =0;

	while(article[i] != 0){

		if(isLetter(article[i]) == 1){
			word[wordlength] = article[i]; //puts the word into an array

			wordlength = wordlength + 1;
		}

		if(isLetter(article[i]) == 0){
			if(wordlength >= 2){
			searchDictionary(word,dictionary);
			ClearWord(word);
			wordlength=0;
			}
			else{
				wordlength = 0;
			}
		}

		if (article[i + 1] == '\0' && wordlength >= 2){
				searchDictionary(word, dictionary);
			}
		i= i+1; //check next letter
	}
}

/* Function: Print
 * -----------------------
 * Prints all the words that are in the Noduplicates array
 */
void Print(){
int j =0;
int duplicatesearch = 0;
ClearWord(word);
while(Noduplicates != '\0'){
	if(Noduplicates[duplicatesearch] == 1){
		break;
	}
if(isLetter(Noduplicates[duplicatesearch]) == 1){
	word[j] = Noduplicates[duplicatesearch];
						   j = j+1;
							duplicatesearch = duplicatesearch +1;
}
else{
	printf("%s\n",word);
	ClearWord(word);
	j=0;
	duplicatesearch = duplicatesearch +1;
}
}
}
/*Function: spellCheck
 * --------------------------------------
 * main function to check if the spellings are correct
 */

void spellCheck(char article[], char dictionary[]) {


ClearWord(word);
ClearDuplicates(Noduplicates);
toLower(article);
toLower(dictionary);
Check(article,dictionary);
Print();
}







