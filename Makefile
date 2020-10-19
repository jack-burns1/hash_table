  
CC = clang++
CFLAGS = -Wall -Wextra -c -std=c++11 -O2
DEPS = DirNode.h FSTree.h HashTable.h Variation.h stringProcessing.h Word.h

%.o: %.cpp $(DEPS)
	$(CC) -o $@ $< $(CFLAGS)

gerp: gerp.o FSTree.o DirNode.o FSTreeTraversal.o HashTable.o StringProcessing.o Variation.o Word.o
	$(CC) -o FSTree.o DirNode.o FSTreeTraversal.o HashTable.o StringProcessing.o Variation.o Word.o


clean:
	rm -f *.o core* *~ gerp