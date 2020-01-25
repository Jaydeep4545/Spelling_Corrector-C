/*
program: speller corrector.
author: nir nicole.
summary: the program will receive 2 text files containing vocabulary and a text with only cahrs and blanks.
the program will use the vocabulary to determine which word is misspelled and offer correction suggestions.
*/

#include "dic.h"

int main()
{
 	double hashTable[M]={0};

	 FILE *fp1;							  /*dictionary*/
 	FILE *fp2;							  /*text*/
 
	node rbtree = NULL;					  /*initiate red-bleck tree.*/
	
	node* prbt = &rbtree; 

	/*wellcome note*/
	printf("\n #Speller Corrector\n\n Wellcome,\n This program's purpose is to find misspelled words in a text and suggest improvments.\n");


    fp1 = fopen("dictionary.txt", "r");  /*Open file for reading.*/
    
	fillHash(hashTable,fp1);			 /*creating a dictionary.*/
	
    fclose(fp1);						 /*close dictionery*/

    fp2 = fopen("text.txt", "r");        /*Open text file for reading.*/
    
	fillRBT(prbt,fp2);					 /*creating a R-B tree.*/
	
	fclose(fp2);					     /*close text*/
	 
    fp2 = fopen("text.txt", "r");     /*Open  again text file for reading word by word.*/
	
	clearMisspelledRBT(hashTable,prbt ,fp2);  /*keep only misspelled words.*/
                    	
    inorderSpellerPrint(prbt, hashTable);     /*print misspelled with corrections.*/		
    
	 fclose(fp2);					/*close dictionery*/
	
	/*end note*/
	printf("\n\n Thank you for using this program, goodbye!\n");
	
return 0;
}

