%option nounistd
%option noyywrap
%{

#include <stdio.h>
#include <string.h>
#include "Token.h"
void analyzeFile(char* inputFilePath, char* outputFilePath);
int line=1;


%}

PROGRAM	 "program"
END      "end"
CONST    "const"
EXCCPTION   "exception"
REAL      "real"
INTEGER   "integer"
WHEN      "when"
DO        "do"
OTHERWISE  "otherwise"
DONE       "done"
CYCLE      "cycle"
UNTIL      "until"
END_CYCLE  "end_cycle"
START      "start"
RAISE      "raise"
ID  {LETTER}({DIGIT}|{LETTER}|("_"({DIGIT}|{LETTER})+))*
REAL_NUM  [1-9]({DIGIT}+)*"."{DIGIT}+
INT_NUM  [1-9]({DIGIT}+)*
AR_OP  "+"|"-"|"mod"
REAL_OP  ">"|"<"|"<="|">="|"!="
ASSIGNMENT  "="
DIGIT [0-9]
LETTER [A-Za-z]
COMMA  ","
COLON  ":"
SEMICOLON  ";" 
LEFT_PARENTHESE  "("
RIGHT_PARENTHESE  ")"
LEFT_BRACKET  "["
RIGHT_BRACKET "]"

%%

{PROGRAM} {create_and_store_token(TOKEN_PROGRAM,yytext,line);return 1;}
{END} {create_and_store_token(TOKEN_END,yytext,line);return 1;}
{CONST} {create_and_store_token(TOKEN_CONST,yytext,line);return 1;}
{EXCCPTION} {create_and_store_token(TOKEN_EXCCPTION,yytext,line);return 1;}
{REAL} {create_and_store_token(TOKEN_REAL,yytext,line);return 1;}
{INTEGER} {create_and_store_token(TOKEN_INTEGER,yytext,line);return 1;}
{WHEN} {create_and_store_token(TOKEN_WHEN,yytext,line);return 1;}
{DO} {create_and_store_token(TOKEN_DO,yytext,line);return 1;}
{OTHERWISE} {create_and_store_token(TOKEN_OTHERWISE,yytext,line);return 1;}
{DONE} {create_and_store_token(TOKEN_DONE,yytext,line);return 1;}
{CYCLE} {create_and_store_token(TOKEN_CYCLE,yytext,line);return 1;}
{UNTIL} {create_and_store_token(TOKEN_UNTIL,yytext,line);return 1;}
{END_CYCLE} {create_and_store_token(TOKEN_END_CYCLE,yytext,line);return 1;}
{START} {create_and_store_token(TOKEN_START,yytext,line);return 1;}
{RAISE} {create_and_store_token(TOKEN_RAISE,yytext,line);return 1;}
{ID} {create_and_store_token(TOKEN_ID,yytext,line);return 1;}
{AR_OP} {create_and_store_token(TOKEN_AR_OP,yytext,line);return 1;}
{REAL_OP} {create_and_store_token(TOKEN_REAL_OP,yytext,line);return 1;}
{ASSIGNMENT} {create_and_store_token(TOKEN_ASSIGNMENT,yytext,line);return 1;}
{REAL_NUM} {create_and_store_token(TOKEN_REAL_NUM,yytext,line);return 1;}
{INT_NUM} {create_and_store_token(TOKEN_INT_NUM,yytext,line);return 1;}
{COMMA} {create_and_store_token(TOKEN_COMMA,yytext,line);return 1;}
{COLON} {create_and_store_token(TOKEN_COLON,yytext,line);return 1;}
{SEMICOLON} {create_and_store_token(TOKEN_SEMICOLON,yytext,line);return 1;}
{LEFT_PARENTHESE} {create_and_store_token(TOKEN_LEFT_PARENTHESE,yytext,line);return 1;}
{RIGHT_PARENTHESE} {create_and_store_token(TOKEN_RIGHT_PARENTHESE,yytext,line);return 1;}
{LEFT_BRACKET} {create_and_store_token(TOKEN_LEFT_BRACKET,yytext,line);return 1;}
{RIGHT_BRACKET} {create_and_store_token(TOKEN_RIGHT_BRACKET,yytext,line);return 1;}
\n  {line++;}
\/\*(.*\n)*.*\*\/   {line++;}
<<EOF>>  {create_and_store_token(TOKEN_EOF,yytext,line);return 1;}
[ \t]+  ; /* eat up whitespace  */
.	printf(yyout,"the character '%s' at line: %d does not begin any legal token in the language\n",yytext,line);



%%


void main(int argc, char* argv[])
{

	int i = 1;
	if(argv[1] && argv[2]){
		analyzeFile(argv[1], argv[2]);
		}
		   else {
		analyzeFile("C:\\temp\\test1.txt", "c:\\temp\\test1_20478667_039843271_lex.txt");
		analyzeFile("C:\\temp\\test2.txt", "c:\\temp\\test2_20478667_039843271_lex.txt");
		}	
}

void analyzeFile(char* inputFilePath, char* outputFilePath)
{   
    FILE *fr = fopen(inputFilePath,"r");
	FILE *fw = fopen(outputFilePath,"w");
	
	yyin = fr;  //input file path
	yyout = fw; //output file path
	
	currentNode = (Node*)malloc(sizeof(Node));
	currentNode->tokensArray = (Token*)malloc(sizeof(Token)*TOKEN_ARRAY_SIZE);
	while(currentNode->tokensArray[currentIndex].kind != TOKEN_EOF && currentIndex < TOKEN_ARRAY_SIZE)
	{
	   next_token();
	}
	free(currentNode->tokensArray);
	yyrestart(yyin);
	BEGIN(INITIAL);
	fclose(fr);
	fclose(fw);
    
}







