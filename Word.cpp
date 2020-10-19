// Jack Burns
// November 23, 2019
// Word.cpp
// Comp 15 Fall 2019

#include "Word.h"

Word::Word()
{
	size = 0;
}

Word::~Word()
{
	destroy();
}
// frees up all heap memory
void Word::destroy()
{
	for (int i = 0; i < size; i++) {
		varList[i].destroy();
	}
	size = 0;
}

// copy constructor
Word::Word(const Word &source)
{
	if (this == &source) {
		return;
	}
	lcWord = source.lcWord;
	size = source.size;
	copyWord(source.varList);
}
// copies array of variations given
void Word::copyWord(const vector <Variation> array)
{
	for (int i = 0; i < size; i++) {
		varList.push_back(array[i]);
	}
}
// assignment operator
Word &Word::operator=(const Word &source)
{
	if (this != &source) {
		if (size > 0) {
			destroy();
		}
	lcWord = source.lcWord;
	size = source.size;
	copyWord(source.varList);
	}
	return *this;
}
// createNewWord
// Parameters: address of filename, line umber, address of path, string of the
// word
// Returns: nothing
// Does: calls addVariation after converting the word to lowercase
void Word::createNewWord(string &file, int line, string &path, string theWord)
{
	int length = theWord.size();
	for (int i = 0; i < length; i++) {
		lcWord += tolower(theWord[i]);
	}
	addVariation(path, file, theWord, line);
}
// isVariation
// Parameters: string value of the word
// Returns: boolean of whether the given word is a variation
// Does: iterates through variation vector to check if word is there
bool Word::isVariation(string theWord)
{
	for (int i = 0; i < size; i++) { //     Check if this gets last elem
		if (varList[i].getVar() == theWord) {
			return true;
		}
	}
	return false;
}
// addVariation
// Parameters: address of filepath, filename, the word, and the line number
// Returns: nothing
// Does: uses variation class functions to create a new variation and add it
// to the variation vector
void Word::addVariation(string &path, string &file, string theWord, int line) // returned var pointer... idk why
{
	Variation theVar;
	theVar.createVariation(theWord);
	theVar.createInstance(path, file, line);
	varList.push_back(theVar);
	size++;
}
// addInstance
// Parameters: address of filepath, address of filename, the line number, and
// pointer to a variation
// Returns: nothing
// Does: uses the variation class to add an instance
void Word::addInstance(string &path, string &file, int line, Variation *var)
{
	var->createInstance(path, file, line);
}
// getLcWord
// Parameters: none
// Returns: string to the lowercase word
// Does: returns the value of the Word's lowercase value
string Word::getLcWord()
{
	return lcWord;
}
// getPath
// Parameters: index of the variation and index of instance
// Returns: string of the filepath
// Does: retuerns the filepath of a given instance
string Word::getPath(int index, int varIndex)
{
	return varList[index].getVarPath(varIndex);
}
// getLineNum
// Parameters: index of the variation and index of instance
// Returns: integer of the line number
// Does: returns the line number of a given instance
int Word::getLineNum(int index, int varIndex)
{
	return varList[index].getVarNum(varIndex);
}
// getFilename
// Parameters: index of the variation and index of instance
// Returns: string of the file's name
// Does: returns the filename of a given instance
string Word::getFileName(int index, int varIndex)
{
	return varList[index].getFilename(varIndex);
}
// getVariation
// Parameters: index of variation
// Returns: variation pointer
// Does: returns the variation address at a given index
Variation *Word::getVariation(int index)
{
	return &varList[index];
}
// getSize
// Parameters: none
// Returns: integer of the size of the vector
// Does: returns the number of variations
int Word::getSize()
{
	return size;
}





