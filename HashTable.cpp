// Jack Burns
// November 23, 2019
// HashTable.cpp
// Comp 15, Fall 2019

#include "HashTable.h"
#include "stringProcessing.h"

using namespace std;

HashTable::HashTable()
{
	size = 20;
	n = 0;
	for (int i = 0; i < size; i++) {
		thehash.push_back(NULL);
	}
}

HashTable::~HashTable()
{
	destroy();
}
// destroy
// Parameters: none.
// Returns: nothing.
// Does: deletes the entire hash table by calling the Word destructor
void HashTable::destroy()
{
	for (int i = 0; i < size; i++) {
		if (thehash[i] != NULL) {
			Bucket *temp = thehash[i];
			while (temp != NULL) {
				temp->value->destroy();
				delete temp->value;
				Bucket *kill = temp;
				temp = temp->next; 
				delete kill;
			}
		}
	}
	size = 0;
	n = 0;
}
// copy constructor
HashTable::HashTable(const HashTable &source)
{
	if (this == &source) {
		return;
	}
	size = source.size;
	n = source.n;
	copyHash(source.thehash);
}
// copyHash
// copies the hash table from constant reference
void HashTable::copyHash(const vector <Bucket*> array)
{
	for (int i = 0; i < size; i++) {
		thehash.push_back(array[i]);
	}
}

// operator
HashTable &HashTable::operator=(const HashTable &source)
{
	if (this != &source) {
		if (size > 0) {
			destroy();
		}
		size = source.size;
		n = source.n;
		copyHash(source.thehash);
	}
	return *this;
}
// makeBucket
// Parameters: Pointer to a newly made 'Word'
// Retuns: A pointer to a newly made 'Bucket'
// Does: creates a new bucket pointer and points the value to the word
Bucket *HashTable::makeBucket(Word *theWord)
{
	Bucket *buck = new Bucket;
	buck->value = theWord;
	buck->key = -1;
	buck->next = NULL;
	return buck;
}
// addBucket
// Parameters: pointer to a bucket, and the hashed index
// Returns: Nothing
// Does: checks if the hash table needs re=hashing and then adds the bucket
// to the index of the hash table
void HashTable::addBucket(Bucket *buck, int index)
{
	n++;
	size = thehash.size();
	if (n / size > LF) {
		expandRehash();
		index = hash<string>{}(buck->value->getLcWord()) % size;
	}
	if (thehash[index] != NULL) {
		Bucket *temp = thehash[index];
		while (temp->next != NULL) {
			temp = temp->next;
		}
		temp->next = buck;
	}
	else thehash[index] = buck;
}
// expandRehash
// Parameters: none.
// Returns: nothing
// Does: doubles the size of the vector and calls a function to rehash
void HashTable::expandRehash()
{
	vector <Bucket*> tempVector;
	for (int j = 0; j < size; j++) {
		thehash.push_back(NULL);
		tempVector.push_back(thehash[j]);
		thehash[j] = NULL;
	}
	rehashHelp(tempVector);
}
// rehashHelp
// Parameters: address of temporary vector (that is a copy of the vector 
// before expansion)
// Returns: Nothing.
// Does: Iterates through every value in the table and rehashes them, and
// adds them to the empty original (expanded) vector
void HashTable::rehashHelp(vector <Bucket*> &tempVector)
{
	for (int i = 0; i < size; i++) {
		if (tempVector[i] != NULL) {
			Bucket *temp = tempVector[i];
			Bucket *next = temp->next;
			while (temp != NULL) {
				temp->key =
				hash<string>{}(temp->value->getLcWord()) % (size * 2);
				if (thehash[temp->key] == NULL) {
					thehash[temp->key] = temp;
					thehash[temp->key]->next = NULL;
				}
				else {
					Bucket *curr = thehash[temp->key];
					while (curr->next != NULL) {
						curr = curr->next;
					} 
					curr->next = temp;
					curr->next->next = NULL;
				}
				temp = next;
				if (next != NULL) {
					next = next->next;
				}
			}
		}
	}
	size = size * 2;
}
// printWord
// Parameters: index of word to be printed
// Returns: nothing
// Does: prints the words at a given index... used for debugging 
void HashTable::printWord(int index)
{
	Bucket *temp = thehash[index];
	while (temp != NULL) {
		if (temp->value != NULL) {
			cout << temp->value->getLcWord() << endl;
		}
		temp = temp->next;
	}
	cout << " " << endl;
}

// getSize
// Parameters: nothing.
// Returns: an integer size
// Does: returns the size of the array
int HashTable::getSize()
{
	return size;
}
// isWord
// Parameters: string of word to be added, adddress of the path to the file,
// filename, and line number of the instance of that file.
// Returns: nothing.
// Does: indexes the word, and iterates through the hash table. Will add a new
// bucket if the index is empty, chain the word to the end of an index if the 
// word is not there and a collision occurs, and adds an instance if the word 
// exists
void HashTable::isWord(string theWord, string &path, string &file,
	int line)
{
	int length = theWord.length();
	string lowerWord;
	for (int i = 0; i < length; i++) {
		lowerWord += tolower(theWord[i]);  //makes lowercase
	}
	int index = hash<string>{}(lowerWord) % size;
	if (thehash[index] == NULL) {    // checks if anything in index
		makeWord(theWord, path, file, line, index);
		return;
	}
	Bucket *temp = thehash[index];
	while (temp != NULL && temp->value->getLcWord() != lowerWord) {
		temp = temp->next;   // iterates until word is reached or end of list
	}
	if (temp == NULL) {
		makeWord(theWord, path, file, line, index);
		return;
	}
	int varSize = temp->value->getSize(); // # of variations
	for (int i = 0; i < varSize; i++) {
		if (temp->value->getVariation(i)->getVar() == theWord) {
			Variation *var = temp->value->getVariation(i);
			temp->value->addInstance(path, file, line, var); // add instance to variation
			return;  
		}
	}
	temp->value->addVariation(path, file, theWord, line);
}
// makeWord
// Parameters: string of word to be added, adddress of the path to the file,
// filename, and line number of the instance of that file, index number.
// Returns: nothing.
// Does: creates a new Word type and calls functions from the Word class to 
// fully initialize.
void HashTable::makeWord(string theWord, string &path, string &file, int line,
	int index)
{
	Word *newWord = new Word;
	newWord->createNewWord(file, line, path, theWord);
	addBucket(makeBucket(newWord), index);
}
// printPath
// Parameters: string of the word, boolean anycase (true = case insensitive)
// and address of outfile
// Returns: Nothing
// Does: Searches for the word in a similar way that isWord does, and prints
// corrosponding messages to the output file.
void HashTable::printPath(string theWord, bool anycase, ostream &out)
{
	int length = theWord.length();
	string lowerWord;
	for (int i = 0; i < length; i++) {
		lowerWord += tolower(theWord[i]);  //makes lowercase
	}
	int index = hash<string>{}(lowerWord) % size;
	if (thehash[index] == NULL) {
		printErrorMessage(anycase, theWord, out);
		return;
	}
	Bucket *temp = thehash[index];
	while (temp != NULL && temp->value->getLcWord() != lowerWord) {
		temp = temp->next;
	}
	if (temp == NULL) {
		printErrorMessage(anycase, theWord, out);
		return;
	}
	int varSize = temp->value->getSize();
	if (anycase) {
		printAllPaths(varSize, temp, out);
		return;
	}
	bool found = printOneVar(varSize, temp, out, theWord);
	if (!found) {
		out << theWord << " does not appear in this directory\n";
	}
}
// printAllPaths
// Parameters: Number of variations of the word, temp value of this word's
// bucket, address of output file
// Returns: nothing
// Does: prints all of the instances for all of the variations of a word
void HashTable::printAllPaths(int varSize, Bucket *temp, ostream &out)
{
	for (int i = 0; i < varSize; i++) {
		int inst = temp->value->getVariation(i)->getNumInstance();
		for (int k = 0; k < inst; k++) {
			string thePath = temp->value->getPath(i, k);
			int len = thePath.size();
			for (int j = 0; j < len - 1; j++){
				out << thePath[j];
			}
			out << ":";
			out << temp->value->getLineNum(i, k) << ":";
			printLine(temp, i, k, out);
		}
	}
}
// printOneVar
// Parameters: Number of variations of the word, temp value of this word's
// bucket, address of output file, string of the word to find
// Returns: nothing.
// Does: prints all of the instances of one variation of a word
bool HashTable::printOneVar(int varSize, Bucket *temp, ostream &out,
	string theWord)
{
	bool found = false;
	for (int i = 0; i < varSize; i++) { 
		if (temp->value->getVariation(i)->getVar() == theWord) {
			int numInst = temp->value->getVariation(i)->getNumInstance();
			for (int k = 0; k < numInst; k++) {
				string thePath = temp->value->getPath(i, k);
				int len = thePath.size();
				for (int j = 0; j < len - 1; j++){
					out << thePath[j];
				}
				out << ":";
				out << temp->value->getLineNum(i, k) << ":";
				found = true;
				printLine(temp, i, k, out);
			}
		}
	}
	return found;
}
// printErrorMessage
// Parameters: boolean anycase (true if using insensitive)
// Returns: nothing
// Does: prints the correct message if the word is not found
void HashTable::printErrorMessage(bool anycase, string theWord, ostream &out)
{
	if (!anycase) {
		out << theWord << " Not Found. Try with @insensitive or @i.\n";
	}
	else out << theWord << " Not Found.\n";
}
// printLine
// Parameters: temp Bucket of the word, the index of its variation, the index
// of its instance and the address of the output file.
// Returns: Nothing
// Does: using the line number, it opens the file and prints the line the word
// appears on
void HashTable::printLine(Bucket *temp, int index, int varIndex, ostream &out)
{
	string fileName;
	int length = temp->value->getPath(index, varIndex).length();
	for (int i = 0; i < length - 1; i++) {
		fileName += temp->value->getPath(index, varIndex)[i];
	}
	int lineNum = temp->value->getLineNum(index, varIndex);
	ifstream infile;
	infile.open(fileName);
	if (!infile) {
		cout << "Cannot open " << fileName << endl;
	}
	int counter = 0;
	string line;
	while (counter != lineNum) {
		counter++;
		string templine;
		getline(infile, templine);
		line = templine;
	}
	out << " " << line << endl;
}










