#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define WORD_LENGTH 30
#define LINE_LENGTH 300

#define M 11587	
#define NUM_RUNS 50
#define BASE 26

#if defined(_WIN32) && defined(_MSC_VER)
#pragma warning (disable : 4996)
#endif

enum { RED, BLACK };

typedef int COLOR;
typedef double valueType;

/*rbtree nodes*/
typedef struct Node {
	valueType value;					/*26 base value represents the string*/
	COLOR color;
	struct Node *right, *left, *parent;
}*node;

typedef node* tree;


/*declarations*/
 int char2index(char c);
 char index2char(int i);
 double string2value26base(char* str);
 char* cleaner(char* token);
 int hashFun(double k, double m, int i);
 void value2string26base(double value,char* str);

/*RB declarations*/
node initilize(node, valueType);
node grandparent(node);
node uncle(node);
node sibling(node);
node treeSearch(node x, valueType k);
node treeMinimum(node x);
node treeSeccessor(node x);

void insertNode(tree, valueType);
void insertUtil(tree, node);
void removeNode(tree, valueType);
void removeUtil(tree, node);
void rightRotate(tree, node);
void leftRotate(tree, node);
void replaceNode(tree, node, node);
void printNode(node n);
void inorderIterator(node n, void(*func)(node));
void preorderIterator(node n, void(*func)(node));
void inorderPrint(tree t);
void preorderPrint(tree t);
void destroy(node);


/*speller declarations*/
void inorderSpellerIterator(node n, void(*func)(double,double*), double*);
void inorderSpellerPrint(tree t, double* hashTable);
void spellerCorrector(double value, double*);
void edgeErrors(char* str, double* hashTable, int i, int end);
void missingChar(char* str, double* hashTable);
void spairChar(char* str, double* hashTable);

/*hashing functions*/
void fillHash(double* hashTable,FILE* fp1);
void fillRBT(node* tree,FILE* fp2);
void clearMisspelledRBT(double* hashTable, node* tree,FILE* fp2);
