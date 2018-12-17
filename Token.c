#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Token.h"


int currentIndex = 0;
Node* currentNode = NULL;

#define TOKEN_ARRAY_SIZE 100
char* token_name;

static char *TOKEN_STRING[]={"TOKEN_PROGRAM","TOKEN_START","TOKEN_END","TOKEN_CONST","TOKEN_EXCCPTION","TOKEN_REAL","TOKEN_INTEGER","TOKEN_WHEN",
                             "TOKEN_DO","TOKEN_OTHERWISE","TOKEN_DONE","TOKEN_CYCLE","TOKEN_UNTIL","TOKEN_END_CYCLE","TOKEN_RAISE",
                             "TOKEN_ID","TOKEN_AR_OP","TOKEN_REAL_OP","TOKEN_ASSIGNMENT","TOKEN_REAL_NUM","TOKEN_INT_NUM","TOKEN_DIGIT","TOKEN_LETTER","TOKEN_COMMA","TOKEN_COLON",
                             "TOKEN_SEMICOLON","TOKEN_LEFT_PARENTHESE","TOKEN_RIGHT_PARENTHESE","TOKEN_LEFT_BRACHET","TOKEN_RIGHT_BRACHET","TOKEN_EOF"
};
void create_and_store_token(eTOKENS kind, char* lexeme, int numOfLine)
{ 
	// case 1: there is still no tokens in the storage.
	if (currentNode == NULL)
	{
		currentNode = (Node*)malloc(sizeof(Node));

		if(currentNode == NULL)
		{
			fprintf(yyout,"\nUnable to allocate memory! \n"); 
			exit(0);
		}
		currentNode->tokensArray = (Token*)malloc(sizeof(Token)*TOKEN_ARRAY_SIZE);
		if(currentNode->tokensArray == NULL)
		{
			fprintf(yyout,"\nUnable to allocate memory! \n"); 
			exit(0);
		}
		currentNode->prev = NULL;
		currentNode->next = NULL;
	}

	// case 2: at least one token exsits in the storage.
	else
	{
		// the array (the current node) is full, need to allocate a new node
		if (currentIndex == TOKEN_ARRAY_SIZE -1)
		{
			currentIndex = 0;
			currentNode->next = (Node*)malloc(sizeof(Node));

			if(currentNode == NULL)
			{
				fprintf(yyout,"\nUnable to allocate memory! \n"); 
				exit(0);
			}
			currentNode->next->prev = currentNode;
			currentNode = currentNode->next;
			currentNode->tokensArray = (Token*)malloc(sizeof(Token)*TOKEN_ARRAY_SIZE);

			if(currentNode->tokensArray == NULL)
			{
				fprintf(yyout,"\nUnable to allocate memory! \n"); 
				exit(0);
			}
			currentNode->next = NULL;
		}

		// the array (the current node) is not full
		else
		{
			currentIndex++;
		}
	}

	currentNode->tokensArray[currentIndex].kind = kind;
	currentNode->tokensArray[currentIndex].lexeme = (char*)malloc(sizeof(char)*(strlen(lexeme)+1));
	strcpy(currentNode->tokensArray[currentIndex].lexeme, lexeme);
	currentNode->tokensArray[currentIndex].lineNumber = numOfLine;

	token_name=TOKEN_STRING[kind-1]; 
	fprintf(yyout, "Token from kind '%s' was found at line: %d, lexeme: '%s'.\n",token_name, numOfLine, lexeme);
}

/*
* This function returns the token in the storage that is stored immediately before the current token (if exsits).
*/
Token *back_token() { return NULL; }

/*
* If the next token already exists in the storage (this happens when back_token was called before this call to next_token): 
*  this function returns the next stored token.
* Else: continues to read the input file in order to identify, create and store a new token (using yylex function);
*  returns the token that was created.
*/
Token *next_token() 
{
	Token* token;
	
	//Check if yylex need to read from input file
	if (currentNode->tokensArray[currentIndex].kind != TOKEN_EOF && currentIndex < TOKEN_ARRAY_SIZE  )
	{
		yylex();
		token =currentNode->tokensArray;
	} 
    //else
	return token;
}
