// Jack Burns
// November 23, 2019
// Variation.cpp
// Comp 15 Fall 2019

#include "Variation.h"

using namespace std;

Variation::Variation()
{
	letters = " ";
	size = 0;
}
// destroy
// deletes all data on the heap (needs to be explicitly called by other 
// functions)
void Variation::destroy()
{
	for (int i = 0; i < size; i++) {
			delete inArray[i];
	}
	size = 0;	
}
// copy constructor
Variation::Variation(const Variation &source)
{
	if (this == &source) {
		return;
	}
	letters = source.letters;
	size = source.size;
	copyVar(source.inArray);
}
// copies all of the variations from a given array
void Variation::copyVar(const vector <Instance *> array)
{
	for (int i = 0; i < size; i++) {
		inArray.push_back(array[i]);
	}
}
// assignment operator
Variation &Variation::operator=(const Variation &source)
{
	if (this != &source) {
		if (size > 0) {
			destroy();
		}
		letters = source.letters;
		size = source.size;
		copyVar(source.inArray);
	}
	return *this;
}
// createVariation
// Parameters: string of the word
// Returns: Nothing
// Does: sets the word to the letters string value in variation
void Variation::createVariation(string theWord)
{
	letters = theWord;
}
// createInstance
// Parameters: address of the filepath, file, and line number.
// Returns: Nothing
// Does: checks if instance was already taken from the same line. If not
// it creates a new instance, and adds it to the vector
void Variation::createInstance(string &path, string &file, int line)
{
	for (int i = 0; i < size; i++) {
		if (inArray[i]->line == line) {
			return;
		}
	}
	Instance *newInst = new Instance;
	newInst->filepath = path;
	newInst->file = file;
	newInst->line = line;
	inArray.push_back(newInst);
	size++;
}
// getNumInstance
// Parameters: Nothing
// Returns: integer of the size
// Does: Returns number of the instances
int Variation::getNumInstance()
{
	return size;
}
// getVar
// Parameters: Nothing
// Returns: string value of the word's variation 
// Does: Returns variation word
string Variation::getVar()
{
	return letters;
}
// getVarPath
// Parameters: index of instance
// Returns: string of the filepath of given instance
// Does: Returns fileapth of an instance
string Variation::getVarPath(int index)
{
	return inArray[index]->filepath;
}
// getVarNum
// Parameters: index of instance
// Returns: line number of an instance
// Does: Returns line number of an instance
int Variation::getVarNum(int index)
{
	return inArray[index]->line;
}
// getFilename
// Parameters: index of instance
// Returns: file name
// Does: Returns file name at gievn instance
string Variation::getFilename(int index)
{
	return inArray[index]->file;
}
