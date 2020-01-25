#include "dic.h"


/**/
void spellerCorrector(double value, double* hashTable)
{
	char str[WORD_LENGTH];
	char temp[WORD_LENGTH];
	int i , c, r;
	double x=0;
	
	
	value2string26base(value,str);
	strcpy(temp, str);
	
	printf("\n\n misspelled \"%s\"  -> Did you mean:\n",temp);
	
	
	for(i=0 ; temp[i]!='\0' ; i++)
		for(c=0; c<26; c++)
		{
		temp[i] = (char)(c+97);
		
		for(r=0; r<NUM_RUNS; r++)
	     	{
	    	x = hashFun(string2value26base(temp), M, r);

			if(*(hashTable + (int)x) == string2value26base(temp) )
				{
				printf(" %s ",temp);
				r=NUM_RUNS;
				}
			}
			
		strcpy(temp, str);
		}
	


missingChar(str, hashTable);
	
spairChar(str, hashTable);
	
			/*i is in '/0' index here*/
edgeErrors(str,hashTable,i,i+1);
		
		/*i is in '/0' index here*/
edgeErrors(str,hashTable,i-2,i-1);
	
}


void inorderSpellerIterator(node n, void(*func)(double,double*), double* hashTable)
{

	if (n == NULL)
		return;
	else{
		inorderSpellerIterator(n->left, func, hashTable);
		func(n->value,hashTable);
		inorderSpellerIterator(n->right, func, hashTable);
		}
}

void inorderSpellerPrint(tree t, double* hashTable)
{

	printf("\n\n Misspelling review:\n");
	printf(" -------------------\n");

	inorderSpellerIterator(*t, spellerCorrector,hashTable);
	printf("\n");
}

void edgeErrors(char* str, double* hashTable, int i, int end)
{

	char temp[WORD_LENGTH];
	int  c, r;
	double x=0;

strcpy(temp, str);

	for(c=0; c<26; c++)			/*i is in '/0' index here*/
		{
		temp[i] = (char)(c+97);
		temp[end] = '\0';
		
		for(r=0; r<NUM_RUNS; r++)
	     	{
	    	x = hashFun(string2value26base(temp), M, r);

			if(*(hashTable + (int)x) == string2value26base(temp) )
				{
				printf(" %s ",temp);
				r=NUM_RUNS;
				}
			}
		strcpy(temp, str);
		}
}

void missingChar(char* str, double* hashTable)
{
	char src[WORD_LENGTH];
    char temp[WORD_LENGTH];


	double x=0;
    int i,j,k , c,r;
   
   
   
   strcpy(src,str);

 for(i=1; src[i]!='\0'; i++)
 	 {
 	 
 	 for(c=0; c<26; c++)			/*i is in '/0' index here*/
		{
 	 	for(j=0; j!=i; j++)
 			temp[j] = src[j];
		temp[j] = (char)(c+97);	
		k=i;
		j++;
		for(; src[k]!='\0'; k++,j++)	
			temp[j] = src[k];
		
		temp[j] = '\0';
		
		
		for(r=0; r<NUM_RUNS; r++)
	     	{
	    	x = hashFun(string2value26base(temp), M, r);

			if(*(hashTable + (int)x) == string2value26base(temp) )
				{
				printf(" %s ",temp);
				r=NUM_RUNS;
				}
			}
		}
	}
}


void spairChar(char* str, double* hashTable)
{
	char src[WORD_LENGTH];
    char temp[WORD_LENGTH];


	double x=0;
    int i,j,k ,r;
   
   
   
   strcpy(src,str);

 for(i=0; src[i]!='\0'; i++)
 	 {
 	 	if(src[i] == src[i+1])		/*skip one check for double chars*/
 	 		i++;
 	 	for(j=0; j!=i; j++)
 			temp[j] = src[j];
		k=i+1;
		for(; src[k]!='\0'; k++,j++)	
			temp[j] = src[k];
		
		temp[j] = '\0';
		
		
		for(r=0; r<NUM_RUNS; r++)
	     	{
	    	x = hashFun(string2value26base(temp), M, r);

			if(*(hashTable + (int)x) == string2value26base(temp) )
				{
				printf(" %s ",temp);
				r=NUM_RUNS;
				}
			}
		}
		
	
}
