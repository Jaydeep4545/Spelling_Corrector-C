#include "dic.h"

/*reads word into a hashing table(word for each line)*/
void fillHash(double* hashTable,FILE* fp1)
{

char str[WORD_LENGTH];
int colcount[NUM_RUNS]={0};
int i=0, sec=0, t=0;
int  value=0;
char* p;


while (fgets(str, WORD_LENGTH, fp1)!=NULL)
{
	p=cleaner(str);
	for(i=0; i<NUM_RUNS; i++)
		{
		value = hashFun(string2value26base(p), M, i);		
		if(value>=0 && value<M)
		{
				if( *(hashTable+value) != 0)
					{
					colcount[i]++;
					}
				else {
						*(hashTable+value) = string2value26base(p);
						sec++;
						i=NUM_RUNS;
					}
		}else printf("\nthe error string is: '%s' '%d'",p,value);
		}
t++;	
}

	printf("\n Hash Table status:\n");
	printf(" -------------------\n");

	/*counting iteretions for hash function*/
	for(i=0; i<NUM_RUNS && colcount[i]!=0 ; i++)
		;
		
		
		printf("\n Maximum number of collusion iteretions (double hashing):\n %d\n",i);
		printf("\n Number of seccsess:\n %d\n",sec);
		printf("\n Number of words:\n %d\n",t);	

}

/*reads word into a hashing table(word for each line)*/
void fillRBT(node* tree,FILE* fp2)
{


char temp[WORD_LENGTH];
char line[LINE_LENGTH];
const char cc[2] = " ";
double x=0;

char* token=temp;

 	printf("\n\n Red Black Tree status:\n");
 	printf(" -----------------------\n");
 	
   /*open second file to insert to a Red Black Tree*/	
	while (fgets(line, LINE_LENGTH, fp2)!=NULL)
       {	

	
        /* get the first token */
	    token = strtok(line,cc);
	
   
        /* insert the tokens to a Red-Black tree. */
        while( token != NULL )
     	  {
     	   token = cleaner(token);
     	   x=string2value26base(token);
           printf( "\n '%s' -> ", token );
           
           if( treeSearch(*tree, x) ==NULL)
          	 {
          	 insertNode(tree, x);
         	 value2string26base(x,temp);
         	 printf("inserted.\n");
         	 }
          else printf("already in tree!\n");
                  
          token = strtok(NULL, cc);
          }
     }

}



/*second file reading to delete from the tree femiliar words*/
void clearMisspelledRBT(double* hashTable,node* tree,FILE* fp2)
{


char temp[WORD_LENGTH];
char line[LINE_LENGTH];
const char cc[2] = " ";
double x=0;
int i=0, value=0;

char* token=temp;

    
    printf("\n\n Deletion status of the words that spelled correctly:\n ----------------------------------------------------\n");

	while (fgets(line, LINE_LENGTH, fp2)!=NULL)
{	

	
   /* get the first token */
	token = strtok(line,cc);
	
   
   /* insert the tokens to a Red-Black tree. */
    while( token != NULL )
     	 {
     	  token = cleaner(token);
     	  x=string2value26base(token);
          
          if( treeSearch(*tree, x) ==NULL)
         	 ;
          else 
          {
          for(i=0; i<NUM_RUNS; i++)
	     	{
	    	value = hashFun(string2value26base(token), M, i);		
		    if(value>=0 && value<M)
		      {
			     	if( *(hashTable+value) == x )
				 	{    
					printf("\n '%s' -> FOUND in hashTable[%d] on the: #%d hash function iteretion.\n",token,value,i+1);
					removeNode(tree, x);
					i=NUM_RUNS;
					printf("\tDELETED!\n");
					}
		      }else printf("\nthe error string is: '%s' '%.0f'",token,x);
		    }
          }
                  
          token = strtok(NULL, cc);
        }
}

}
