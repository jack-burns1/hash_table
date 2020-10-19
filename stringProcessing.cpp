// Jack Burns
// November 18, 2019
// stringProcessing.h

#include "stringProcessing.h"

// stripNonAlphaNum
// Parameters: string that needs to be stripped
// Returns: stripped version of original string
// Does: removes all non-alphanumeric characters from a string
string stripNonAlphaNum(string word)
{
	int i = 0;
	int j = word.length();
	while (word[i] < 48 || (word[i] < 97 && word[i] > 90) || (word[i] < 65
		&& word[i] > 57) || word[i] > 122) {
		i++;
		if (i == j) {
			return " ";
		}
	}
	
	while (word[j] < 48 || (word[j] < 97 && word[j] > 90) || (word[j] < 65
		&& word[j] > 57) || word[j] > 122) {
		j--;
	}
	string newWord;
	while (i <= j) {
		newWord += word[i];
		i++;
	}
	return newWord;
}
