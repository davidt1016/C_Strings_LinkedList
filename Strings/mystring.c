#include "mystring.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
/*
 *  mystrlen() calculates the length of the string s, 
 *  not including the terminating character '\0'.
 *  Returns: length of s.
 */
int mystrlen (const char *s) 
{
	//Length of the string and initialize to zero to prevent from random number
	int lengthofString = 0;
	int i = 0;
	//Calculating the string length of a string excluding the terminating character
	while( s[i] != '\0' )
	{
		//For every valid non terminating string, length of the string will be incremented by one
		lengthofString++;
		i++;
	}
	//Returning the length of the string
	return lengthofString;
}

/*
 *  mystrcpy()  copies the string pointed to by src (including the terminating 
 *  character '\0') to the array pointed to by dst.
 *  Returns: a  pointer to the destination string dst.
 */
char  *mystrcpy (char *dst, const char *src)
{
	/* Complete the body of the function */
	//Copying the string from char variable src and store it into dst array
	//Copying src string into an array src
	int len = 0;
	for ( int i = 0; src[i] != '\0' ; i++)
	{
		dst[i] = src[i];
		len = i;
	}
	//Inlcuding the terminating character at the end of the string of dst
	dst[len+1] = '\0';
	//returning the dst pointer
	return dst;
}

/*
 * mystrcmp() compares two strings alphabetically
 * Returns: 
 * 	-1 if s1  < s2
 *  	0 if s1 == s2
 *  	1 if s1 > s2
 */
int mystrcmp(const char *s1, const char *s2)
{
	//Variables decalaration 
	int comparisonOutput = 0;
	//Variables for storing the sum of the ASCII for both s1 and s2
	int sumS1 = 0;
	int sumS2 = 0;
	
	//Computing the result of the sum of all the strings in s1 in ASCII code
	for ( int i = 0; s1[i] != '\0' ;i ++)
	{
		sumS1 += s1[i];
	} 	
	//Computing the result of the sum of all the strings in s2 in ASCII code
	for( int j = 0; s2[j] != '\0'; j++  )
	{
		sumS2 += s2[j];
	} 

	//Comparison of the ASCII CODE 
	// s1 < s2, => ouptut -1
	if ( sumS1 < sumS2 )
	{
		comparisonOutput = -1;
	}
	// s1 = s2, => ouptut -0
	else if ( sumS1 == sumS2 )
	{
		comparisonOutput = 0;
	}
	// s1 > s2, => ouptut 1
	else if ( s1 > s2 )
	{
		comparisonOutput = 1;
	}
	//Returning the compared result to the main function
	return comparisonOutput;
}

/*
 * mystrdup() creates a duplicate of the string pointed to by s. 
 * The space for the new string is obtained using malloc.  
 * If the new string can not be created, a null pointer is returned.
 * Returns:  a pointer to a new string (the duplicate) 
 	     or null If the new string could not be created for 
	     any reason such as insufficient memory.
 */
//Reference from: https://c-for-dummies.com/blog/?p=1699
char *mystrdup(const char *s1)
{
	//Variables initialization
	int length;
    static char *duplicate;
    char *dup;
    /* Allocate memory for duplicate */
    length = mystrlen(s1);
    duplicate = (char *)malloc(sizeof(char)*length+1);
    //If it cannot be created, return NULL
    if( duplicate == NULL)
    {
    	//Returning NULL if duplicate space cannot be allocated
        return NULL;
    }
    /* Copying string */
    dup = duplicate;
    //Copying the original string into the duplicate in the while loop
    while(*s1)
    {
    	//Copying the address of s1 into dup to maintain the original address of s1
        *dup = *s1;
        //incrementing each address by one everytime 
        dup++;
        s1++;
     }
    //Copying the duplicate in and add terminating '\0'
    *dup = '\0';
    //returning the duplicate 
    return duplicate;
}

int main()
{
	const int SIZE = 100;
	char buffer[SIZE];

	printf("\n--------Testing Implemented String Functions--------\n");
	
	//Self testing of different conditions to see if it passes with different input
	assert(mystrlen("Hello World!") == 12);
	assert(mystrlen("111@") == 4);
	//Indication of the task passed 
	printf("\nTest 1:strelen PASSED!\n");
	mystrcpy(buffer, "Testing String Functions!");
	//Testing my mystrcmp function 
	printf("\nTest 2:Testing buffer\n");
	//Printing out the size of the testing string
	printf ("Size of the buffer string is %d", mystrlen(buffer)); //strlen: 32
	printf("\nsize of actual string is %d\n", mystrlen("Testing String Functions!")); //strlen: 33

	assert(strcmp(buffer, "Testing String Functions!") == 0);
	printf("\nTest 3:mystrcpy passed!\n");

	//Testing different conditions
	assert(mystrcmp ("Coding is fun!", "Coding is fun") >= 0);
    assert(mystrcmp ("Coding is fun", "Coding is fun!") <= 0);
	assert(mystrcmp ("Coding is fun", "Coding is fun") == 0);
	printf("\nTest 4:mystrcpy passed!\n");

	//Testing the mystrdup functions
	char *dupStr = mystrdup(buffer);
	assert (!strcmp(buffer, dupStr));
	assert (buffer != dupStr);

	if (dupStr != NULL)
		free (dupStr);

	printf ("\n--------END OF THE TEST--------\n");

	return 0;
}




