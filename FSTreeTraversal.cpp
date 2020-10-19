// Jack Burns
// 18th November, 2019
// treetraversal.cpp
// Comp 15 Fall 2019

#include <iostream>
#include "FSTree.h"

using namespace std;

string find_path(DirNode *root, string dir, int numDir, string path, int files);
void print_one_path(DirNode *root, string dir, int numDir);

int main(int argc, char *argv[])
{
	if (argc != 2) {
		cout << "Usage:  gerp directory\n";
		return 0;
	}
	string rootFile = argv[1];
	FSTree searchTree(rootFile);
	if (searchTree.isEmpty()) {
		cout << "Empty tree\n";
		return 0;
	}
	DirNode *root = searchTree.getRoot();
	string dir = root->getName();
	int numDir = root->numSubDirs();
	string path = dir + "/";
	int files = root->numFiles();
	string thePath = find_path(root, dir, numDir, path, files);
	return 0;
}
// find_path
// Parameters: the current directory, the name of the current directory, the
// number of sub-directories in current directory, the current string repre-
// sentation of the path, and the number of files in current directory. 
// Returns: nothing.
// Does: recursively builds upon a string (path) until it reaches files, and
// then prints out those files
string find_path(DirNode *root, string dir, int numDir, string path, int files)
{
	for (int i = 0; i <  files; i++) {
		path += root->getFile(i);
	}
	if (numDir == 0) {
		return path;
	}
	DirNode *temp = root->getSubDir(numDir - 1);
	int num = temp->numSubDirs();
	string directory = temp->getName();
	int numFiles = temp->numFiles();
	cerr << path << endl;
	find_path(temp, directory, num, path + directory + "/", numFiles);
	find_path(root, dir, numDir - 1, path, 0);
	return " ";
}