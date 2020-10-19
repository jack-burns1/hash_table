// Jack Burns
// November 23, 2019
// Variation.h
// Comp 15 Fall 2019

#ifndef VARIATION_H
#define VARIATION_H

#include <iostream>
#include <functional>
#include <vector>

using namespace std;

struct Instance {
	string filepath;
	string file;
	int line;
};

class Variation {

public:

	Variation();
	// ~Variation();

	Variation(const Variation &source);
	void destroy();
	void copyVar(const vector <Instance*> array);
	Variation &operator=(const Variation &source);
	void createVariation(string theWord);
	void createInstance(string &path, string &file, int line);

	int getNumInstance();
	string getVar();
	string getVarPath(int index);
	int getVarNum(int index);
	string getFilename(int index);

private:
	string letters;
	vector <Instance*> inArray;
	int size;
};

#endif