#ifndef TOKEN_H
#define TOKEN_H

extern FILE *yyin, *yyout;

typedef enum eTOKENS
{

     TOKEN_PROGRAM=1,
     TOKEN_START,
     TOKEN_END,
     TOKEN_CONST,
     TOKEN_EXCCPTION,
     TOKEN_REAL,
     TOKEN_INTEGER,
     TOKEN_WHEN,
     TOKEN_DO,
     TOKEN_OTHERWISE,
     TOKEN_DONE,
     TOKEN_CYCLE,
     TOKEN_UNTIL,
     TOKEN_END_CYCLE,
     TOKEN_RAISE,
     TOKEN_ID,
     TOKEN_AR_OP,
     TOKEN_REAL_OP,
     TOKEN_ASSIGNMENT,
	 TOKEN_REAL_NUM,
	 TOKEN_INT_NUM,
     TOKEN_DIGIT,
     TOKEN_LETTER,
     TOKEN_COMMA,
     TOKEN_COLON,
     TOKEN_SEMICOLON,
     TOKEN_LEFT_PARENTHESE, 
     TOKEN_RIGHT_PARENTHESE,
     TOKEN_LEFT_BRACKET,
     TOKEN_RIGHT_BRACKET,
     TOKEN_EOF
}eTOKENS;

typedef struct Token
{
	eTOKENS kind;
	char *lexeme;
	int lineNumber;
}Token;

typedef struct Node
{
	Token *tokensArray;
	struct Node *prev;
	struct Node *next;
} Node;

void create_and_store_token(eTOKENS kind, char* lexeme, int numOfLine);
Token *next_token();
Token *back_token();

extern Node* currentNode;
extern int currentIndex;
#define TOKEN_ARRAY_SIZE 100

#endif