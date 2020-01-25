#include "dic.h"

/*this class responsible for the dictionary operations.*/

/*converting a string of alphabetic letters to a value by 26 base.*/
double string2value26base(char* str)
{

char temp[WORD_LENGTH];
double sum=0;
int i;

strcpy(temp, str);

for(i=0; i<strlen(temp); i++)
	{
	sum += char2index(temp[i]) * pow((double)BASE,(double)i);
	}
return sum;
}

/*converting a value by 26 base to string of alphabetic letters to .*/
void value2string26base(double value,char* str)
{
int i=0;

while(value!=0)
	{
	*(str+i)= index2char( (int)(fmod(value,BASE)) );
	value=floor(value/BASE);
	i++;
	}
*(str+i)='\0';	/*end of string*/
}

/*converts a charecter to a integer between 1-26(or -1 if fails).*/
int char2index(char c)
{
	if(!isalpha(c))
		{
		printf("\n#Error: unvalid charecter '%c'\n",c);
		return -1;
		}
	if(isupper(c))
		return (int)c - 64;
	else return (int)c - 96;
}

/*converts a integer to a char between a-z(or -1 if fails).*/
char index2char(int i)
{
	return (char)(i+96);
}

		
/*method for cleaning the begining of a string of spaces and tabs.*/
char* cleaner(char* token)
{
char* temp=token;

	/*clean the input from tabs and spaces*/
	while( ((int)*temp==9)  ||  ((int)*temp==32) )
			temp++;
   	token=temp;
  	
  	/*approving the word*/
  	while(isalpha(*(temp)))
   		temp++;
   		
   	/*ends the string*/
   	*(temp)='\0'; 
   	 return token;
}		

int hashFun(double k, double m, int i)
{
return (int)( fmod( fmod(k,m) + i*(1+ fmod(k,m-1)) , m) );
}


