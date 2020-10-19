// Jack Burns
// November 23, 2019
// HashTable.h
// Comp 15 Fall 2019

#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <iostream>
#include <functional>
#include <vector>
#include <fstream>
#include "Word.h"

const float LF = 0.75;

struct Bucket {
	Word *value;
	int key;
	Bucket *next;
};

class HashTable {

public:
	HashTable();
	~HashTable();

	HashTable(const HashTable &source);
	void destroy();
	void copyHash(const vector <Bucket*> array);
	HashTable &operator=(const HashTable &source);

	Bucket *makeBucket(Word *theWord);
	void addBucket(Bucket *buck, int index);
	void expandRehash();
	void rehashHelp(vector <Bucket*> &tempVector);
	void printWord(int index);
	int getSize();
	void isWord(string theWord, string &path, string &file,
	int line);
	void makeWord(string theWord, string &path, string &file, int line,
		int idex);
	void printPath(string theWord, bool anycase, ostream &out);
	void printAllPaths(int varSize, Bucket *temp, ostream &out);
	bool printOneVar(int varSize, Bucket *temp, ostream &out, string theWord);
	void printErrorMessage(bool anycase, string theWord, ostream &out);
	void printLine(Bucket *temp, int index, int varIndex, ostream &out);

private:
	int n;
	int size;
	vector <Bucket*> thehash;
};

#endif


