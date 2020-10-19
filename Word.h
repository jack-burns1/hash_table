// Jack Burns
// November 23, 2019
// Word.h
// Comp 15 Fall 2019

#ifndef WORD_H
#define WORD_H

#include <iostream>
#include <string>
#include "Variation.h"

using namespace std;

class Word {

public:

	Word();
	~Word();
	void destroy();

	Word(const Word &source);
	void copyWord(const vector <Variation> array);
	Word &operator=(const Word &source);

	void createNewWord(string &file, int line, string &path, string theWord);
	bool isVariation(string theWord);
	void addVariation(string &path, string &file, string theWord, int line);
	void addInstance(string &path, string &file, int line, Variation *var);

	string getLcWord();
	string getPath(int index, int varIndex);
	int getLineNum(int index, int varIndex);
	string getFileName(int index, int varIndex);
	Variation *getVariation(int index);
	int getSize();



private:

	string lcWord;
	vector <Variation> varList;
	int size;
};

#endif