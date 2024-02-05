
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.4.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Copy the first part of user declarations.  */

/* Line 189 of yacc.c  */
#line 2 "Yacc.y"

    #include <stdio.h>
    #include <stdlib.h>
	#include <string.h>
	#include <ctype.h>

	//#include "lex.yy.c"
	int yylex();
	int yydebug = 0;
	void yyerror(const char*);
	extern int yylineno;
	extern int st[100];
	extern int top;
	extern int count;
	extern void display();
	extern void insert_in_st(char*, char*, int, char*);
	char st1[100][100];
	char i_[2]="0";
	int temp_i = 0;				//current available temporary number
	char tmp_i[10];				//an array to hold temporary variable number as string. We assume this is below 999999999				
	char temp[10]="";			//an array to hold temporary varialbe name as string. We assume this is below T999999999	
	int label[20];
	int lnum = 0;				//current available label number.
	int ltop = 0;
	int abcd = 0;
	int l_while=0;
	int l_for=0;
	int flag_set = 1;
	int stop = -1;				//top of stack
	char G_val[10];
	FILE* ast_tree_output;


	typedef struct quadruples
  	{
  	  char *op;
  	  char *arg1;
  	  char *arg2;
  	  char *res;
  	}quad;
  	int quadindex = 0;			//current index of Q to store the quadruple in.
	quad Q[100];

	void push(char *a)			//push to top of stack
	{
		strcpy(st1[++stop],a);
	}

	// Statements -helper
	void TAC()				//to be called after any expression. say expr is b*c -> pop top three , ti = b*c and insert ti.
	{
	    strcpy(temp,"T");
	    sprintf(tmp_i, "%d", temp_i);
	    strcat(temp,tmp_i);
	    printf("%s = %s %s %s\n",temp,st1[stop-2],st1[stop],st1[stop - 1]);
	    Q[quadindex].op = (char*)malloc(sizeof(char)*strlen(st1[stop]));
	    Q[quadindex].arg1 = (char*)malloc(sizeof(char)*strlen(st1[stop-2]));
	    Q[quadindex].arg2 = (char*)malloc(sizeof(char)*strlen(st1[stop - 1]));
	    Q[quadindex].res = (char*)malloc(sizeof(char)*strlen(temp));
	    strcpy(Q[quadindex].op,st1[stop]);
	    strcpy(Q[quadindex].arg1,st1[stop-2]);
	    strcpy(Q[quadindex].arg2,st1[stop - 1]);
	    strcpy(Q[quadindex].res,temp);
	    quadindex++;
	    stop-=2;
	    strcpy(st1[stop],temp);
		temp_i++;
	}

	// Assignment Operations need a different TAC function as the operation performed is different
	void TAC_assign()
	{
	    printf("%s = %s\n",st1[stop-2],st1[stop - 1]);
	    Q[quadindex].op = (char*)malloc(sizeof(char));
	    Q[quadindex].arg1 = (char*)malloc(sizeof(char)*strlen(st1[stop - 1]));
	    Q[quadindex].arg2 = NULL;
	    Q[quadindex].res = (char*)malloc(sizeof(char)*strlen(st1[stop-2]));
	    strcpy(Q[quadindex].op,"=");
	    strcpy(Q[quadindex].arg1,st1[stop - 1]);
	    strcpy(Q[quadindex].res,st1[stop-2]);
	    quadindex++;
	    stop-=2;
	}

	void TAC_assign_back()
	{
		temp_i--;
	    strcpy(temp,"T");
	    sprintf(tmp_i, "%d", temp_i);
	    strcat(temp,tmp_i);
		temp_i++;
		printf("%s = %s\n",G_val,temp);
	    Q[quadindex].op = (char*)malloc(sizeof(char));
	    Q[quadindex].arg1 = (char*)malloc(sizeof(char)*strlen(temp));
	    Q[quadindex].arg2 = NULL;
	    Q[quadindex].res = (char*)malloc(sizeof(char)*strlen(G_val));
	    strcpy(Q[quadindex].op,"=");
		strcpy(Q[quadindex].arg1,temp);
	    strcpy(Q[quadindex].res,G_val);
		quadindex++;
	}
	// ICG - While

	// Create label for while
	void While_Loop_Label()
	{
	
	    label[ltop++] = lnum++;			
	    printf("L%d: \n", label[ltop - 1]);			// print label and increase label number for next use	
	    Q[quadindex].op = (char*)malloc(sizeof(char)*6);		//a label's quad 	
	    Q[quadindex].arg1 = NULL;
	    Q[quadindex].arg2 = NULL;
	    Q[quadindex].res = (char*)malloc(sizeof(char)*(lnum + 2));   //lum + 2 is a safe way to have enough space for L0, L1, ... etc. 
	    strcpy(Q[quadindex].op,"Label");
	    char x[10];
		x[0] = '0' + label[ltop - 1];
	    char l[]="L";
	    strcpy(Q[quadindex].res,strcat(l,x));
	    quadindex++;
	}

	// While Loop Condition
	void While_loop_cond()
	{
	 	strcpy(temp,"T");			
	 	sprintf(tmp_i, "%d", temp_i);		//if temp_i = 0, tmp_i has "0"		
	 	strcat(temp,tmp_i);					//temp has "T0"
	 	printf("%s = not %s\n",temp,st1[stop]);		//T0 has not of condition

		//since this is a unary operator, one of the operands is NULL
	    Q[quadindex].op = (char*)malloc(sizeof(char)*4);
	    Q[quadindex].arg1 = (char*)malloc(sizeof(char)*strlen(st1[stop]));
	    Q[quadindex].arg2 = NULL;
	    Q[quadindex].res = (char*)malloc(sizeof(char)*strlen(temp));
	    strcpy(Q[quadindex].op,"not");
	    strcpy(Q[quadindex].arg1,st1[stop]);
	    strcpy(Q[quadindex].res,temp);
	    quadindex++;

		//if T0 goto label which will be placed after body
		//in this case op -> if, arg1 -> T0 , res -> L1
	    printf("if %s goto L%d\n",temp,lnum);
	    Q[quadindex].op = (char*)malloc(sizeof(char)*3);
	    Q[quadindex].arg1 = (char*)malloc(sizeof(char)*strlen(temp));
	    Q[quadindex].arg2 = NULL;
	    Q[quadindex].res = (char*)malloc(sizeof(char)*(lnum+2));
	    strcpy(Q[quadindex].op,"if");
	    strcpy(Q[quadindex].arg1,temp);
	    char x[10];
	    sprintf(x,"%d",lnum);char l[]="L";
	    strcpy(Q[quadindex].res,strcat(l,x));
	    quadindex++;
	 	temp_i++;
		
		label[ltop++] = lnum;
		lnum++;
	}

	// End While loop
	void While_END()			// in the end insert goto label and also insert the label which should be branched to if condition fails
	{
		printf("goto L%d \n",label[ltop - 2]);	//ltop - 2 contains the label to be branched if true
		Q[quadindex].op = (char*)malloc(sizeof(char)*5);
	    Q[quadindex].arg1 = NULL;
	    Q[quadindex].arg2 = NULL;
	    Q[quadindex].res = (char*)malloc(sizeof(char)*(l_while+2));
	    strcpy(Q[quadindex].op,"goto");
	    char x[10];
	    sprintf(x,"%d",label[ltop]);
	    char l[]="L";
	    strcpy(Q[quadindex].res,strcat(l,x));
	    quadindex++;

	    printf("L%d: \n", label[ltop - 1]);		//ltop - 1 contains the label to be branched if false
	    Q[quadindex].op = (char*)malloc(sizeof(char)*6);
	    Q[quadindex].arg1 = NULL;
	    Q[quadindex].arg2 = NULL;
	    Q[quadindex].res = (char*)malloc(sizeof(char)*(lnum+2));
	    strcpy(Q[quadindex].op,"Label");
	    char x1[10];
	    sprintf(x1,"%d", label[ltop - 1]);
	    char l1[]="L";
	    strcpy(Q[quadindex].res,strcat(l1,x1));
	    quadindex++;
		ltop -= 2;							//since these labels have been used, decrease ltop by two 
	}

	// ICG - IF

	// Handle Initial IF as well as else if
	void IFSTMT()
	{

	    strcpy(temp,"T");
	    sprintf(tmp_i, "%d", temp_i);
	    strcat(temp,tmp_i);
	    printf("%s = not %s\n",temp,st1[stop]);
	    Q[quadindex].op = (char*)malloc(sizeof(char)*4);
	    Q[quadindex].arg1 = (char*)malloc(sizeof(char)*strlen(st1[stop]));
	    Q[quadindex].arg2 = NULL;
	    Q[quadindex].res = (char*)malloc(sizeof(char)*strlen(temp));
	    strcpy(Q[quadindex].op,"not");
	    strcpy(Q[quadindex].arg1,st1[stop]);
	    strcpy(Q[quadindex].res,temp);
	    quadindex++;

	    printf("if %s goto L%d\n",temp,lnum);
	    Q[quadindex].op = (char*)malloc(sizeof(char)*3);
	    Q[quadindex].arg1 = (char*)malloc(sizeof(char)*strlen(temp));
	    Q[quadindex].arg2 = NULL;
	    Q[quadindex].res = (char*)malloc(sizeof(char)*(lnum+2));
	    strcpy(Q[quadindex].op,"if");
	    strcpy(Q[quadindex].arg1,temp);
	    char x[10];
	    sprintf(x,"%d",lnum);
	    char l[]="L";
	    strcpy(Q[quadindex].res,strcat(l,x));
	    quadindex++;
	    temp_i++;
		
	    label[ltop++] = lnum;
		++lnum;									//increase lnum for next needed label.
		
	}

	void Elif()
	{
		printf("L%d: \n",label[--ltop]);		//print the top in label stack as this is where runtime should come if cond is false
	    										//increase lable for the next time										
		

	    strcpy(temp,"T");
	    sprintf(tmp_i, "%d", temp_i);
	    strcat(temp,tmp_i);
	    printf("%s = not %s\n",temp,st1[stop]);
	    Q[quadindex].op = (char*)malloc(sizeof(char)*4);
	    Q[quadindex].arg1 = (char*)malloc(sizeof(char)*strlen(st1[stop]));
	    Q[quadindex].arg2 = NULL;
	    Q[quadindex].res = (char*)malloc(sizeof(char)*strlen(temp));
	    strcpy(Q[quadindex].op,"not");
	    strcpy(Q[quadindex].arg1,st1[stop]);
	    strcpy(Q[quadindex].res,temp);
	    quadindex++;
		

	    printf("if %s goto L%d\n",temp,lnum);
	    Q[quadindex].op = (char*)malloc(sizeof(char)*3);
	    Q[quadindex].arg1 = (char*)malloc(sizeof(char)*strlen(temp));
	    Q[quadindex].arg2 = NULL;
	    Q[quadindex].res = (char*)malloc(sizeof(char)*(lnum+2));
	    strcpy(Q[quadindex].op,"if");
	    strcpy(Q[quadindex].arg1,temp);
	    char x[10];
	    sprintf(x,"%d",lnum);
	    char l[]="L";
	    strcpy(Q[quadindex].res,strcat(l,x));
	    quadindex++;
	    temp_i++;

	    label[ltop++] = lnum;							//store this as top of label stack and increase ltop
		++lnum;										//increase lnum for next needed label.
	}


	// Handle cleanup

	void if_else_cleanup()
	{
		int y;
		y = label[--ltop];
		printf("L%d: \n",y);
		Q[quadindex].op = (char*)malloc(sizeof(char)*6);
	    Q[quadindex].arg1 = NULL;
	    Q[quadindex].arg2 = NULL;
	    Q[quadindex].res = (char*)malloc(sizeof(char)*(y+2));
	    strcpy(Q[quadindex].op,"Label");
	    char x[10];
	    sprintf(x,"%d",y);
	    char l[]="L";
	    strcpy(Q[quadindex].res,strcat(l,x));
	    quadindex++;
	}

	// ICG - For

	//Define Label for "FOR"
	void FOR_label()
	{
		label[ltop++] = lnum++;						//label stack is used for nested loops. Increase lnum for next label use
	    // l_for = lnum;
	    printf("L%d: \n", label[ltop - 1]);
	    Q[quadindex].op = (char*)malloc(sizeof(char)*6);
	    Q[quadindex].arg1 = NULL;
	    Q[quadindex].arg2 = NULL;
	    Q[quadindex].res = (char*)malloc(sizeof(char)*(lnum+2));
	    strcpy(Q[quadindex].op,"Label");
	    char x[10];
	    sprintf(x,"%d", label[ltop - 1]);
	    char l[]="L";
	    strcpy(Q[quadindex].res,strcat(l,x));
	    quadindex++;
	}

	// Handle Loop Condition
	void FOR_Condition()
	{

	    strcpy(temp,"T");						//lets take condition as b < 4. This effectively says T1 = not T0. Note that expr would have made T0 = b < 4
	    sprintf(tmp_i, "%d", temp_i);
	    strcat(temp,tmp_i);
	    printf("%s = not %s\n",temp,st1[stop]);
	    Q[quadindex].op = (char*)malloc(sizeof(char)*4);
	    Q[quadindex].arg1 = (char*)malloc(sizeof(char)*strlen(st1[stop]));
	    Q[quadindex].arg2 = NULL;
	    Q[quadindex].res = (char*)malloc(sizeof(char)*strlen(temp));
	    strcpy(Q[quadindex].op,"not");
	    strcpy(Q[quadindex].arg1,st1[stop]);
	    strcpy(Q[quadindex].res,temp);
	    quadindex++;

	    printf("if %s goto L%d\n",temp,lnum);				// if T1 goto L1. Increase labele
	    Q[quadindex].op = (char*)malloc(sizeof(char)*3);
	    Q[quadindex].arg1 = (char*)malloc(sizeof(char)*strlen(temp));
	    Q[quadindex].arg2 = NULL;
	    Q[quadindex].res = (char*)malloc(sizeof(char)*(lnum+2));
	    strcpy(Q[quadindex].op,"if");
	    strcpy(Q[quadindex].arg1,temp);
	    char x[10];
	    sprintf(x,"%d",lnum);
	    char l[]="L";
	    strcpy(Q[quadindex].res,strcat(l,x));
	    quadindex++;
	    temp_i++;
	    label[ltop++] = lnum;								//store label in stack and increase lnum.
	    lnum++;

	    printf("goto L%d\n",lnum);							//goto body part. goto L2
	    Q[quadindex].op = (char*)malloc(sizeof(char)*5);
	    Q[quadindex].arg1 = NULL;
	    Q[quadindex].arg2 = NULL;
	    Q[quadindex].res = (char*)malloc(sizeof(char)*(lnum+2));
	    strcpy(Q[quadindex].op,"goto");
	    char x1[10];
	    sprintf(x1,"%d",lnum);
	    char l1[]="L";
	    strcpy(Q[quadindex].res,strcat(l1,x1));
	    quadindex++;
	    label[ltop++] = lnum++;							//store label in stack and increase lnum.


	
	    printf("L%d: \n",lnum);							//L3:
	    Q[quadindex].op = (char*)malloc(sizeof(char)*6);
	    Q[quadindex].arg1 = NULL;
	    Q[quadindex].arg2 = NULL;
	    Q[quadindex].res = (char*)malloc(sizeof(char)*(lnum+2));
	    strcpy(Q[quadindex].op,"Label");
	    char x2[10];
	    sprintf(x2,"%d",lnum);
	    char l2[]="L";
	    strcpy(Q[quadindex].res,strcat(l2,x2));
	    quadindex++;
		label[ltop++] = lnum++;
	}

	// Increment
	void FOR_INC_Cond()
	{
	    int x;
	    x = label[ltop - 4];							//after processing increment, should go and evaluate condition again. goto L0
	    printf("goto L%d \n",x);
	    Q[quadindex].op = (char*)malloc(sizeof(char)*5);
	    Q[quadindex].arg1 = NULL;
	    Q[quadindex].arg2 = NULL;
	    Q[quadindex].res = (char*)malloc(sizeof(char)*strlen(temp));
	    strcpy(Q[quadindex].op,"goto");
	    char jug[10];
	    sprintf(jug,"%d",x);
	    char l[]="L";
	    strcpy(Q[quadindex].res,strcat(l,jug));
	    quadindex++;

	    printf("L%d: \n",label[ltop - 2]);							//this is where after processing condition you should come to . L2:
	    Q[quadindex].op = (char*)malloc(sizeof(char)*6);
	    Q[quadindex].arg1 = NULL;
	    Q[quadindex].arg2 = NULL;
	    Q[quadindex].res = (char*)malloc(sizeof(char)*(x+2));
	    strcpy(Q[quadindex].op,"Label");
	    char jug1[10];
	    sprintf(jug1,"%d", label[ltop - 2]);
	    char l1[]="L";
	    strcpy(Q[quadindex].res,strcat(l1,jug1));
	    quadindex++;
	}

	// Ending of for
	void FOR_End()
	{
	    int x;
	    x = label[ltop - 1];								//goto L3 (increment condition)
	    printf("goto L%d \n",x);

	    Q[quadindex].op = (char*)malloc(sizeof(char)*5);
	    Q[quadindex].arg1 = NULL;
	    Q[quadindex].arg2 = NULL;
	    Q[quadindex].res = (char*)malloc(sizeof(char)*strlen(temp));
	    strcpy(Q[quadindex].op,"goto");
	    char jug[10];
	    sprintf(jug,"%d",x);
	    char l[]="L";
	    strcpy(Q[quadindex].res,strcat(l,jug));
	    quadindex++;

	    printf("L%d: \n",label[ltop - 3]);							//L1:
	    Q[quadindex].op = (char*)malloc(sizeof(char)*6);
	    Q[quadindex].arg1 = NULL;
	    Q[quadindex].arg2 = NULL;
	    Q[quadindex].res = (char*)malloc(sizeof(char)*(x+2));
	    strcpy(Q[quadindex].op,"Label");
	    char jug1[10];
	    sprintf(jug1,"%d", label[ltop - 3]);
	    char l1[]="L";
	    strcpy(Q[quadindex].res,strcat(l1,jug1));
	    quadindex++;
		ltop -= 4;	
	}

	char LineBreaker[] = "\n_______________________________________________________________________________________________________\n";
	
	//node in AST
	typedef struct ASTNode
	{
		struct ASTNode *left;
		struct ASTNode *right;
		char *token;
	} node;
	
	node *Construct_AST(node *left, node *right, char *token)
	{
		node *newnode = (node *)malloc(sizeof(node));
		char *newstr = (char *)malloc(strlen(token)+1);
		strcpy(newstr, token);
		newnode->left = left;
		newnode->right = right;
		newnode->token = newstr;
		return(newnode); 
	}
	
	void Display_tree(node *tree)
	{
		// if (tree->left || tree->right)
		// 	fprintf(ast_tree_output, "%s", "(");
		// fprintf(ast_tree_output, " %s ", tree->token);
		// if (tree->left)
		// 	Display_tree(tree->left);
		// if (tree->right)
		// 	Display_tree(tree->right);
		// if (tree->left || tree->right)
		// 	fprintf(ast_tree_output, "%s", ")");
	}


/* Line 189 of yacc.c  */
#line 536 "Yacc.tab.c"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     T_keyword = 258,
     T_int = 259,
     T_main = 260,
     T_type = 261,
     T_return = 262,
     T_for = 263,
     T_if = 264,
     T_else = 265,
     T_while = 266,
     T_InputStream = 267,
     T_OutputStream = 268,
     T_openParenthesis = 269,
     T_closedParanthesis = 270,
     T_openFlowerBracket = 271,
     T_closedFlowerBracket = 272,
     T_RelationalOperator = 273,
     T_LogicalOperator = 274,
     T_UnaryOperator = 275,
     T_AssignmentOperator = 276,
     T_Semicolon = 277,
     T_identifier = 278,
     T_numericConstants = 279,
     T_stringLiteral = 280,
     T_character = 281,
     T_plus = 282,
     T_minus = 283,
     T_mod = 284,
     T_divide = 285,
     T_multiply = 286,
     T_whiteSpace = 287,
     T_shortHand = 288,
     T_LogicalOr = 289,
     T_LogicalAnd = 290,
     T_not_equal = 291,
     T_equal_equal = 292,
     T_greater_equal = 293,
     T_greater = 294,
     T_less_equal = 295,
     T_less = 296
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 214 of yacc.c  */
#line 464 "Yacc.y"

    char *str;
	struct ASTNode *NODE;



/* Line 214 of yacc.c  */
#line 620 "Yacc.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 632 "Yacc.tab.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  4
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   442

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  42
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  32
/* YYNRULES -- Number of rules.  */
#define YYNRULES  85
/* YYNRULES -- Number of states.  */
#define YYNSTATES  160

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   296

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,    10,    13,    15,    18,    20,    22,    25,
      27,    30,    32,    34,    36,    39,    42,    43,    44,    45,
      55,    56,    57,    65,    66,    74,    75,    84,    85,    89,
      90,    95,    96,    99,   101,   104,   107,   109,   111,   115,
     119,   124,   129,   134,   139,   144,   146,   150,   154,   158,
     162,   166,   170,   174,   178,   182,   186,   190,   194,   198,
     200,   202,   204,   208,   212,   216,   220,   224,   228,   232,
     236,   240,   244,   248,   252,   256,   259,   262,   265,   268,
     270,   272,   274,   276,   277,   279
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      43,     0,    -1,     4,     5,    14,    15,    72,    44,    -1,
      47,    46,    -1,    73,    -1,    72,    44,    -1,    47,    -1,
      22,    -1,    47,    46,    -1,    73,    -1,    65,    22,    -1,
      55,    -1,    52,    -1,    48,    -1,    63,    22,    -1,     1,
      22,    -1,    -1,    -1,    -1,     8,    14,    66,    49,    66,
      50,    67,    51,    45,    -1,    -1,    -1,    11,    53,    14,
      65,    15,    54,    45,    -1,    -1,     9,    14,    65,    15,
      56,    45,    57,    -1,    -1,    10,     9,    14,    65,    15,
      58,    45,    57,    -1,    -1,    10,    59,    61,    -1,    -1,
      10,    60,    72,    44,    -1,    -1,    62,    46,    -1,    22,
      -1,    65,    22,    -1,    63,    22,    -1,    52,    -1,    48,
      -1,    68,    21,    65,    -1,    68,    33,    65,    -1,     6,
      68,    21,    64,    -1,     6,    68,    21,    69,    -1,     6,
      68,    21,    70,    -1,     4,    68,    21,    64,    -1,     4,
      68,    21,    70,    -1,    68,    -1,    65,    27,    65,    -1,
      65,    28,    65,    -1,    65,    30,    65,    -1,    65,    31,
      65,    -1,    65,    29,    65,    -1,    65,    35,    65,    -1,
      65,    34,    65,    -1,    65,    41,    65,    -1,    65,    40,
      65,    -1,    65,    39,    65,    -1,    65,    38,    65,    -1,
      65,    37,    65,    -1,    65,    36,    65,    -1,    70,    -1,
      69,    -1,    68,    -1,    65,    27,    65,    -1,    65,    28,
      65,    -1,    65,    30,    65,    -1,    65,    31,    65,    -1,
      65,    29,    65,    -1,    65,    35,    65,    -1,    65,    34,
      65,    -1,    65,    41,    65,    -1,    65,    40,    65,    -1,
      65,    39,    65,    -1,    65,    38,    65,    -1,    65,    37,
      65,    -1,    65,    36,    65,    -1,    71,    22,    -1,    63,
      22,    -1,    71,    15,    -1,    63,    15,    -1,    23,    -1,
      25,    -1,    24,    -1,    65,    -1,    -1,    16,    -1,    17,
      -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   498,   498,   502,   503,   508,   509,   510,   522,   523,
     530,   531,   532,   533,   534,   535,   541,   541,   541,   541,
     552,   552,   552,   556,   556,   558,   558,   559,   559,   560,
     560,   561,   564,   565,   568,   569,   570,   571,   574,   575,
     576,   577,   578,   579,   580,   585,   586,   587,   588,   589,
     590,   591,   592,   593,   594,   595,   596,   597,   598,   602,
     603,   604,   605,   606,   607,   608,   609,   610,   611,   612,
     613,   614,   615,   616,   617,   620,   621,   623,   624,   626,
     628,   630,   633,   634,   637,   638
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "T_keyword", "T_int", "T_main", "T_type",
  "T_return", "T_for", "T_if", "T_else", "T_while", "T_InputStream",
  "T_OutputStream", "T_openParenthesis", "T_closedParanthesis",
  "T_openFlowerBracket", "T_closedFlowerBracket", "T_RelationalOperator",
  "T_LogicalOperator", "T_UnaryOperator", "T_AssignmentOperator",
  "T_Semicolon", "T_identifier", "T_numericConstants", "T_stringLiteral",
  "T_character", "T_plus", "T_minus", "T_mod", "T_divide", "T_multiply",
  "T_whiteSpace", "T_shortHand", "T_LogicalOr", "T_LogicalAnd",
  "T_not_equal", "T_equal_equal", "T_greater_equal", "T_greater",
  "T_less_equal", "T_less", "$accept", "Start", "block_end_flower",
  "block", "Multiple_stmts", "stmt", "for_stmt", "$@1", "$@2", "$@3",
  "while_stmt", "$@4", "$@5", "if_stmt", "$@6", "elseif_else_empty", "$@7",
  "$@8", "$@9", "Multiple_stmts_not_if", "stmt_without_if",
  "Assignment_stmt", "expr_without_constants", "expr",
  "expr_or_empty_with_semicolon_and_assignment",
  "expr_or_empty_with_assignment_and_closed_parent", "idid", "sc", "nc",
  "expr_or_empty", "openflower", "closeflower", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    42,    43,    44,    44,    45,    45,    45,    46,    46,
      47,    47,    47,    47,    47,    47,    49,    50,    51,    48,
      53,    54,    52,    56,    55,    58,    57,    59,    57,    60,
      57,    57,    61,    61,    62,    62,    62,    62,    63,    63,
      63,    63,    63,    63,    63,    64,    64,    64,    64,    64,
      64,    64,    64,    64,    64,    64,    64,    64,    64,    65,
      65,    65,    65,    65,    65,    65,    65,    65,    65,    65,
      65,    65,    65,    65,    65,    66,    66,    67,    67,    68,
      69,    70,    71,    71,    72,    73
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     6,     2,     1,     2,     1,     1,     2,     1,
       2,     1,     1,     1,     2,     2,     0,     0,     0,     9,
       0,     0,     7,     0,     7,     0,     8,     0,     3,     0,
       4,     0,     2,     1,     2,     2,     1,     1,     3,     3,
       4,     4,     4,     4,     4,     1,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     1,
       1,     1,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     2,     2,     2,     2,     1,
       1,     1,     1,     0,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     1,     0,     0,    84,     0,     0,
       0,     0,     0,     0,    20,    85,    79,    81,    80,     2,
       0,    13,    12,    11,     0,     0,    61,    60,    59,     4,
      15,     0,     0,    83,     0,     0,     3,     0,     9,    14,
      10,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    82,
      16,     0,     0,    61,     0,     8,    62,    63,    66,    64,
      65,    68,    67,    74,    73,    72,    71,    70,    69,    38,
      39,    43,     0,    61,    59,    40,    60,    59,    76,    83,
      75,    23,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    17,     0,    21,    62,
      63,    66,    64,    65,    52,    51,    74,    73,    72,    71,
      70,    69,    83,     7,    31,     6,     0,     0,     0,    18,
       0,    27,    24,     5,    22,    78,     0,    77,     0,     0,
       0,    19,     0,    33,    37,    36,    28,     0,     0,     0,
       0,     0,    32,    35,    34,    30,    25,     0,    31,    26
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,    19,   124,    36,   125,    21,    89,   122,   136,
      22,    35,   127,    23,   107,   132,   157,   139,   140,   146,
     147,    24,    81,    25,    60,   129,    63,    27,    28,    61,
     126,    29
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -120
static const yytype_int16 yypact[] =
{
       5,    10,    19,    18,  -120,     9,    11,  -120,   217,    14,
      52,    52,    25,    68,  -120,  -120,  -120,  -120,  -120,  -120,
     217,  -120,  -120,  -120,    78,   239,    -7,  -120,  -120,  -120,
    -120,    80,    82,    17,   113,    90,  -120,   217,  -120,  -120,
    -120,   113,   113,   113,   113,   113,   113,   113,   113,   113,
     113,   113,   113,   113,   113,   113,   113,   113,    84,   341,
    -120,    86,    16,  -120,   113,  -120,   141,   141,  -120,  -120,
    -120,   401,   401,    64,    64,    64,    64,    64,    64,   341,
     341,  -120,   356,    -2,    13,  -120,    15,    44,  -120,    17,
    -120,  -120,    49,   113,   113,   113,   113,   113,   113,   113,
     113,   113,   113,   113,   113,   113,  -120,   101,  -120,   207,
     336,    45,    46,    47,   371,   386,    43,   286,   296,   306,
     316,   326,    17,  -120,   105,  -120,   217,   101,    96,  -120,
     106,     2,  -120,  -120,  -120,  -120,   101,  -120,   115,   240,
      11,  -120,   113,  -120,  -120,  -120,  -120,   217,    98,   259,
     217,   154,  -120,  -120,  -120,  -120,  -120,   101,   105,  -120
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
    -120,  -120,  -116,  -119,   -31,    -4,   -12,  -120,  -120,  -120,
      -9,  -120,  -120,  -120,  -120,   -25,  -120,  -120,  -120,  -120,
    -120,   -26,    77,   111,    51,  -120,    -8,    91,    41,    28,
      -5,   -15
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -69
static const yytype_int16 yytable[] =
{
      26,     8,    31,    32,    20,    38,    65,    58,   134,     1,
     133,   138,    26,   -45,    54,     3,    37,   141,   -29,     4,
     -45,    10,    38,    11,     6,    26,    55,     7,   -44,    26,
     -41,    91,     5,    37,   155,   -44,    30,   -41,   158,    33,
      16,    17,    18,    41,    42,    43,    44,    45,    83,    83,
      46,    47,    48,    49,    50,    51,    52,    53,   -58,   -42,
     -50,   -48,   -49,    58,   108,   -58,   -42,   -50,   -48,   -49,
      41,    42,    43,    44,    45,    16,    41,    42,    43,    44,
      45,    26,    34,    46,    47,    48,    49,    50,    51,    52,
      53,    41,    42,    43,    44,    45,   128,    84,    87,    26,
      39,    56,     9,    57,    64,    10,    88,    11,    90,    12,
      13,   135,    14,   148,    26,   131,   152,     7,    26,    26,
     153,   137,    20,   123,    16,    17,    18,   144,    26,   142,
     145,    26,    38,   159,    85,   150,    16,    17,    18,    26,
     106,     0,    26,    37,    59,    62,    20,     0,    86,    26,
     130,     0,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    82,    82,   156,
      43,    44,    45,     0,     0,    92,     0,     0,     0,     0,
       0,    41,    42,    43,    44,    45,     0,     0,    46,    47,
      48,    49,    50,    51,    52,    53,     0,     0,     0,     0,
      59,     0,     0,     0,   109,   110,   111,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   121,     0,     9,     0,
       0,    10,   -46,    11,     0,    12,    13,     0,    14,   -46,
       0,     0,     0,    59,    15,     0,    43,    44,    45,     0,
      16,    17,    18,     0,    10,     0,    11,     0,    12,     0,
     149,    14,     0,   151,     0,     0,     0,     0,     0,     0,
       0,    40,   143,    16,    17,    18,    41,    42,    43,    44,
      45,     0,     0,    46,    47,    48,    49,    50,    51,    52,
      53,   154,     0,     0,     0,     0,    41,    42,    43,    44,
      45,     0,     0,    46,    47,    48,    49,    50,    51,    52,
      53,   -57,     0,     0,     0,     0,     0,     0,   -57,     0,
       0,   -56,     0,    41,    42,    43,    44,    45,   -56,     0,
       0,   -55,     0,    41,    42,    43,    44,    45,   -55,     0,
       0,   -54,     0,    41,    42,    43,    44,    45,   -54,     0,
       0,   -53,     0,    41,    42,    43,    44,    45,   -53,     0,
       0,   -47,     0,    41,    42,    43,    44,    45,   -47,     0,
       0,     0,     0,     0,     0,    43,    44,    45,    41,    42,
      43,    44,    45,     0,     0,    46,    47,    48,    49,    50,
      51,    52,    53,    93,    94,    95,    96,    97,     0,     0,
      98,    99,   100,   101,   102,   103,   104,   105,    41,    42,
      43,    44,    45,     0,     0,   -68,   -68,    48,    49,    50,
      51,    52,    53,    41,    42,    43,    44,    45,     0,     0,
     -67,   -67,    48,    49,    50,    51,    52,    53,    41,    42,
      43,    44,    45,     0,     0,     0,     0,    48,    49,    50,
      51,    52,    53
};

static const yytype_int16 yycheck[] =
{
       8,     6,    10,    11,     8,    20,    37,    33,   127,     4,
     126,     9,    20,    15,    21,     5,    20,   136,    16,     0,
      22,     4,    37,     6,    15,    33,    33,    16,    15,    37,
      15,    15,    14,    37,   150,    22,    22,    22,   157,    14,
      23,    24,    25,    27,    28,    29,    30,    31,    56,    57,
      34,    35,    36,    37,    38,    39,    40,    41,    15,    15,
      15,    15,    15,    89,    15,    22,    22,    22,    22,    22,
      27,    28,    29,    30,    31,    23,    27,    28,    29,    30,
      31,    89,    14,    34,    35,    36,    37,    38,    39,    40,
      41,    27,    28,    29,    30,    31,   122,    56,    57,   107,
      22,    21,     1,    21,    14,     4,    22,     6,    22,     8,
       9,    15,    11,   139,   122,    10,   147,    16,   126,   127,
      22,    15,   126,    22,    23,    24,    25,   139,   136,    14,
     139,   139,   147,   158,    57,   140,    23,    24,    25,   147,
      89,    -1,   150,   147,    33,    34,   150,    -1,    57,   157,
     122,    -1,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    15,
      29,    30,    31,    -1,    -1,    64,    -1,    -1,    -1,    -1,
      -1,    27,    28,    29,    30,    31,    -1,    -1,    34,    35,
      36,    37,    38,    39,    40,    41,    -1,    -1,    -1,    -1,
      89,    -1,    -1,    -1,    93,    94,    95,    96,    97,    98,
      99,   100,   101,   102,   103,   104,   105,    -1,     1,    -1,
      -1,     4,    15,     6,    -1,     8,     9,    -1,    11,    22,
      -1,    -1,    -1,   122,    17,    -1,    29,    30,    31,    -1,
      23,    24,    25,    -1,     4,    -1,     6,    -1,     8,    -1,
     139,    11,    -1,   142,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    22,    22,    23,    24,    25,    27,    28,    29,    30,
      31,    -1,    -1,    34,    35,    36,    37,    38,    39,    40,
      41,    22,    -1,    -1,    -1,    -1,    27,    28,    29,    30,
      31,    -1,    -1,    34,    35,    36,    37,    38,    39,    40,
      41,    15,    -1,    -1,    -1,    -1,    -1,    -1,    22,    -1,
      -1,    15,    -1,    27,    28,    29,    30,    31,    22,    -1,
      -1,    15,    -1,    27,    28,    29,    30,    31,    22,    -1,
      -1,    15,    -1,    27,    28,    29,    30,    31,    22,    -1,
      -1,    15,    -1,    27,    28,    29,    30,    31,    22,    -1,
      -1,    15,    -1,    27,    28,    29,    30,    31,    22,    -1,
      -1,    -1,    -1,    -1,    -1,    29,    30,    31,    27,    28,
      29,    30,    31,    -1,    -1,    34,    35,    36,    37,    38,
      39,    40,    41,    27,    28,    29,    30,    31,    -1,    -1,
      34,    35,    36,    37,    38,    39,    40,    41,    27,    28,
      29,    30,    31,    -1,    -1,    34,    35,    36,    37,    38,
      39,    40,    41,    27,    28,    29,    30,    31,    -1,    -1,
      34,    35,    36,    37,    38,    39,    40,    41,    27,    28,
      29,    30,    31,    -1,    -1,    -1,    -1,    36,    37,    38,
      39,    40,    41
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     4,    43,     5,     0,    14,    15,    16,    72,     1,
       4,     6,     8,     9,    11,    17,    23,    24,    25,    44,
      47,    48,    52,    55,    63,    65,    68,    69,    70,    73,
      22,    68,    68,    14,    14,    53,    46,    47,    73,    22,
      22,    27,    28,    29,    30,    31,    34,    35,    36,    37,
      38,    39,    40,    41,    21,    33,    21,    21,    63,    65,
      66,    71,    65,    68,    14,    46,    65,    65,    65,    65,
      65,    65,    65,    65,    65,    65,    65,    65,    65,    65,
      65,    64,    65,    68,    70,    64,    69,    70,    22,    49,
      22,    15,    65,    27,    28,    29,    30,    31,    34,    35,
      36,    37,    38,    39,    40,    41,    66,    56,    15,    65,
      65,    65,    65,    65,    65,    65,    65,    65,    65,    65,
      65,    65,    50,    22,    45,    47,    72,    54,    63,    67,
      71,    10,    57,    44,    45,    15,    51,    15,     9,    59,
      60,    45,    14,    22,    48,    52,    61,    62,    63,    65,
      72,    65,    46,    22,    22,    44,    15,    58,    45,    57
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}

/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*-------------------------.
| yyparse or yypush_parse.  |
`-------------------------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{


    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks thru separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:

/* Line 1455 of yacc.c  */
#line 498 "Yacc.y"
    {(yyval.NODE) = (yyvsp[(6) - (6)].NODE);;}
    break;

  case 3:

/* Line 1455 of yacc.c  */
#line 502 "Yacc.y"
    {(yyval.NODE) = (yyvsp[(1) - (2)].NODE);;}
    break;

  case 4:

/* Line 1455 of yacc.c  */
#line 503 "Yacc.y"
    {(yyval.NODE) = Construct_AST(NULL, NULL, ";"); ;}
    break;

  case 5:

/* Line 1455 of yacc.c  */
#line 508 "Yacc.y"
    {(yyval.NODE) = (yyvsp[(2) - (2)].NODE);;}
    break;

  case 6:

/* Line 1455 of yacc.c  */
#line 509 "Yacc.y"
    {(yyval.NODE) = (yyvsp[(1) - (1)].NODE);;}
    break;

  case 7:

/* Line 1455 of yacc.c  */
#line 510 "Yacc.y"
    {(yyval.NODE) = Construct_AST(NULL, NULL, ";"); ;}
    break;

  case 8:

/* Line 1455 of yacc.c  */
#line 522 "Yacc.y"
    {(yyval.NODE) = (yyvsp[(1) - (2)].NODE);;}
    break;

  case 9:

/* Line 1455 of yacc.c  */
#line 523 "Yacc.y"
    {(yyval.NODE) = Construct_AST(NULL, NULL, ";"); ;}
    break;

  case 10:

/* Line 1455 of yacc.c  */
#line 530 "Yacc.y"
    {(yyval.NODE) = (yyvsp[(1) - (2)].NODE); Display_tree((yyval.NODE)); fprintf(ast_tree_output, "\n");;}
    break;

  case 11:

/* Line 1455 of yacc.c  */
#line 531 "Yacc.y"
    {(yyval.NODE) = (yyvsp[(1) - (1)].NODE); Display_tree((yyval.NODE)); fprintf(ast_tree_output, "\n");;}
    break;

  case 12:

/* Line 1455 of yacc.c  */
#line 532 "Yacc.y"
    {(yyval.NODE) = (yyvsp[(1) - (1)].NODE); Display_tree((yyval.NODE));fprintf(ast_tree_output, "\n");;}
    break;

  case 13:

/* Line 1455 of yacc.c  */
#line 533 "Yacc.y"
    {(yyval.NODE) = (yyvsp[(1) - (1)].NODE); Display_tree((yyval.NODE)); fprintf(ast_tree_output, "\n");;}
    break;

  case 14:

/* Line 1455 of yacc.c  */
#line 534 "Yacc.y"
    {(yyval.NODE) = (yyvsp[(1) - (2)].NODE); Display_tree((yyval.NODE)); fprintf(ast_tree_output, "\n");;}
    break;

  case 15:

/* Line 1455 of yacc.c  */
#line 535 "Yacc.y"
    {(yyval.NODE) = Construct_AST(NULL, NULL, ";"); ;}
    break;

  case 16:

/* Line 1455 of yacc.c  */
#line 541 "Yacc.y"
    {FOR_label();;}
    break;

  case 17:

/* Line 1455 of yacc.c  */
#line 541 "Yacc.y"
    {FOR_Condition();;}
    break;

  case 18:

/* Line 1455 of yacc.c  */
#line 541 "Yacc.y"
    {FOR_INC_Cond();;}
    break;

  case 19:

/* Line 1455 of yacc.c  */
#line 541 "Yacc.y"
    {{ 	FOR_End();node* left;
																																	node* right;
																																	left = Construct_AST((yyvsp[(5) - (9)].NODE), (yyvsp[(7) - (9)].NODE), "Cond_Loopstmts");
																																	right = Construct_AST((yyvsp[(3) - (9)].NODE),(yyvsp[(5) - (9)].NODE),"Init_&_Increment");
																																	(yyval.NODE) = Construct_AST(left,right,"FOR");
																																	};}
    break;

  case 20:

/* Line 1455 of yacc.c  */
#line 552 "Yacc.y"
    {While_Loop_Label();;}
    break;

  case 21:

/* Line 1455 of yacc.c  */
#line 552 "Yacc.y"
    {While_loop_cond();;}
    break;

  case 22:

/* Line 1455 of yacc.c  */
#line 552 "Yacc.y"
    {While_END();(yyval.NODE) = Construct_AST((yyvsp[(3) - (7)].str), (yyvsp[(5) - (7)].str), "While"); ;}
    break;

  case 23:

/* Line 1455 of yacc.c  */
#line 556 "Yacc.y"
    {IFSTMT();;}
    break;

  case 24:

/* Line 1455 of yacc.c  */
#line 556 "Yacc.y"
    {(yyval.NODE) = Construct_AST((yyvsp[(3) - (7)].NODE), (yyvsp[(6) - (7)].NODE), "IF");;}
    break;

  case 25:

/* Line 1455 of yacc.c  */
#line 558 "Yacc.y"
    {;Elif();;}
    break;

  case 26:

/* Line 1455 of yacc.c  */
#line 558 "Yacc.y"
    {(yyval.NODE) = Construct_AST((yyvsp[(4) - (8)].NODE), (yyvsp[(7) - (8)].NODE), "ELSEIF"); ;}
    break;

  case 27:

/* Line 1455 of yacc.c  */
#line 559 "Yacc.y"
    {if_else_cleanup();;}
    break;

  case 28:

/* Line 1455 of yacc.c  */
#line 559 "Yacc.y"
    {(yyval.NODE) = (yyvsp[(3) - (3)].NODE);;}
    break;

  case 29:

/* Line 1455 of yacc.c  */
#line 560 "Yacc.y"
    {if_else_cleanup();;}
    break;

  case 30:

/* Line 1455 of yacc.c  */
#line 560 "Yacc.y"
    {(yyval.NODE) = (yyvsp[(4) - (4)].NODE);;}
    break;

  case 31:

/* Line 1455 of yacc.c  */
#line 561 "Yacc.y"
    {if_else_cleanup(); (yyval.NODE) = Construct_AST(NULL, NULL, ";"); ;}
    break;

  case 32:

/* Line 1455 of yacc.c  */
#line 564 "Yacc.y"
    {(yyval.NODE) = (yyvsp[(1) - (2)].NODE);;}
    break;

  case 33:

/* Line 1455 of yacc.c  */
#line 565 "Yacc.y"
    {(yyval.NODE) = Construct_AST(NULL, NULL, ";"); ;}
    break;

  case 34:

/* Line 1455 of yacc.c  */
#line 568 "Yacc.y"
    {(yyval.NODE) = (yyvsp[(1) - (2)].NODE);;}
    break;

  case 35:

/* Line 1455 of yacc.c  */
#line 569 "Yacc.y"
    {(yyval.NODE) = (yyvsp[(1) - (2)].NODE);Display_tree((yyval.NODE));fprintf(ast_tree_output, "\n");;}
    break;

  case 36:

/* Line 1455 of yacc.c  */
#line 570 "Yacc.y"
    {(yyval.NODE) = (yyvsp[(1) - (1)].NODE);;}
    break;

  case 37:

/* Line 1455 of yacc.c  */
#line 571 "Yacc.y"
    {(yyval.NODE) = (yyvsp[(1) - (1)].NODE);;}
    break;

  case 38:

/* Line 1455 of yacc.c  */
#line 574 "Yacc.y"
    {push("=");TAC_assign();(yyval.NODE) = Construct_AST((yyvsp[(1) - (3)].NODE),(yyvsp[(3) - (3)].NODE),"=");;}
    break;

  case 39:

/* Line 1455 of yacc.c  */
#line 575 "Yacc.y"
    {push("se");TAC_assign();(yyval.NODE) = Construct_AST((yyvsp[(1) - (3)].NODE),(yyvsp[(3) - (3)].NODE),"SE"); ;}
    break;

  case 40:

/* Line 1455 of yacc.c  */
#line 576 "Yacc.y"
    {push("=");strcpy(G_val,(yyvsp[(2) - (4)].NODE)->token);TAC_assign_back();insert_in_st((yyvsp[(1) - (4)].str), (yyvsp[(2) - (4)].NODE)->token, st[top], "j");(yyval.NODE) = Construct_AST((yyvsp[(2) - (4)].NODE),(yyvsp[(4) - (4)].NODE),"=");;}
    break;

  case 41:

/* Line 1455 of yacc.c  */
#line 577 "Yacc.y"
    {push("=");TAC_assign();insert_in_st((yyvsp[(1) - (4)].str), (yyvsp[(2) - (4)].NODE)->token, st[top], (yyvsp[(4) - (4)].NODE)->token);(yyval.NODE) = Construct_AST((yyvsp[(2) - (4)].NODE),(yyvsp[(4) - (4)].NODE),"=");;}
    break;

  case 42:

/* Line 1455 of yacc.c  */
#line 578 "Yacc.y"
    {push("=");TAC_assign();insert_in_st((yyvsp[(1) - (4)].str), (yyvsp[(2) - (4)].NODE)->token, st[top], (yyvsp[(4) - (4)].NODE)->token);(yyval.NODE) = Construct_AST((yyvsp[(2) - (4)].NODE),(yyvsp[(4) - (4)].NODE),"=");;}
    break;

  case 43:

/* Line 1455 of yacc.c  */
#line 579 "Yacc.y"
    {push("=");strcpy(G_val,(yyvsp[(2) - (4)].NODE)->token);TAC_assign_back();insert_in_st((yyvsp[(1) - (4)].str), (yyvsp[(2) - (4)].NODE)->token, st[top], "j");(yyval.NODE) = Construct_AST((yyvsp[(2) - (4)].NODE),(yyvsp[(4) - (4)].NODE),"=");;}
    break;

  case 44:

/* Line 1455 of yacc.c  */
#line 580 "Yacc.y"
    {push("=");TAC_assign();insert_in_st((yyvsp[(1) - (4)].str), (yyvsp[(2) - (4)].NODE)->token, st[top], (yyvsp[(4) - (4)].NODE)->token);(yyval.NODE) = Construct_AST((yyvsp[(2) - (4)].NODE),(yyvsp[(4) - (4)].NODE),"=");;}
    break;

  case 45:

/* Line 1455 of yacc.c  */
#line 585 "Yacc.y"
    {(yyval.NODE) = (yyvsp[(1) - (1)].NODE);;}
    break;

  case 46:

/* Line 1455 of yacc.c  */
#line 586 "Yacc.y"
    {push("+");TAC();(yyval.NODE) = Construct_AST((yyvsp[(1) - (3)].NODE), (yyvsp[(3) - (3)].NODE), "+");;}
    break;

  case 47:

/* Line 1455 of yacc.c  */
#line 587 "Yacc.y"
    {push("-");TAC();(yyval.NODE) = Construct_AST((yyvsp[(1) - (3)].NODE), (yyvsp[(3) - (3)].NODE), "-");;}
    break;

  case 48:

/* Line 1455 of yacc.c  */
#line 588 "Yacc.y"
    {push("/");TAC();(yyval.NODE) = Construct_AST((yyvsp[(1) - (3)].NODE), (yyvsp[(3) - (3)].NODE), "/");;}
    break;

  case 49:

/* Line 1455 of yacc.c  */
#line 589 "Yacc.y"
    {push("*");TAC();(yyval.NODE) = Construct_AST((yyvsp[(1) - (3)].NODE), (yyvsp[(3) - (3)].NODE), "*");;}
    break;

  case 50:

/* Line 1455 of yacc.c  */
#line 590 "Yacc.y"
    {push("%");TAC();(yyval.NODE) = Construct_AST((yyvsp[(1) - (3)].NODE), (yyvsp[(3) - (3)].NODE), "%");;}
    break;

  case 51:

/* Line 1455 of yacc.c  */
#line 591 "Yacc.y"
    {push("&");TAC();(yyval.NODE) = Construct_AST((yyvsp[(1) - (3)].NODE), (yyvsp[(3) - (3)].NODE), "&");;}
    break;

  case 52:

/* Line 1455 of yacc.c  */
#line 592 "Yacc.y"
    {push("|");TAC();(yyval.NODE) = Construct_AST((yyvsp[(1) - (3)].NODE), (yyvsp[(3) - (3)].NODE), "|");;}
    break;

  case 53:

/* Line 1455 of yacc.c  */
#line 593 "Yacc.y"
    {push("<");TAC();(yyval.NODE) = Construct_AST((yyvsp[(1) - (3)].NODE), (yyvsp[(3) - (3)].NODE), "<");;}
    break;

  case 54:

/* Line 1455 of yacc.c  */
#line 594 "Yacc.y"
    {push("<=");TAC();(yyval.NODE) = Construct_AST((yyvsp[(1) - (3)].NODE), (yyvsp[(3) - (3)].NODE), "<=");;}
    break;

  case 55:

/* Line 1455 of yacc.c  */
#line 595 "Yacc.y"
    {push(">");TAC();(yyval.NODE) = Construct_AST((yyvsp[(1) - (3)].NODE), (yyvsp[(3) - (3)].NODE), ">");;}
    break;

  case 56:

/* Line 1455 of yacc.c  */
#line 596 "Yacc.y"
    {push(">=");TAC();(yyval.NODE) = Construct_AST((yyvsp[(1) - (3)].NODE), (yyvsp[(3) - (3)].NODE), ">=");;}
    break;

  case 57:

/* Line 1455 of yacc.c  */
#line 597 "Yacc.y"
    {push("==");TAC();(yyval.NODE) = Construct_AST((yyvsp[(1) - (3)].NODE), (yyvsp[(3) - (3)].NODE), "==");;}
    break;

  case 58:

/* Line 1455 of yacc.c  */
#line 598 "Yacc.y"
    {push("!=");TAC();(yyval.NODE) = Construct_AST((yyvsp[(1) - (3)].NODE), (yyvsp[(3) - (3)].NODE), "!=");;}
    break;

  case 59:

/* Line 1455 of yacc.c  */
#line 602 "Yacc.y"
    {(yyval.NODE) = (yyvsp[(1) - (1)].NODE);;}
    break;

  case 60:

/* Line 1455 of yacc.c  */
#line 603 "Yacc.y"
    {(yyval.NODE) = (yyvsp[(1) - (1)].NODE);;}
    break;

  case 61:

/* Line 1455 of yacc.c  */
#line 604 "Yacc.y"
    {(yyval.NODE) = (yyvsp[(1) - (1)].NODE);;}
    break;

  case 62:

/* Line 1455 of yacc.c  */
#line 605 "Yacc.y"
    {push("+");TAC();(yyval.NODE) = Construct_AST((yyvsp[(1) - (3)].NODE), (yyvsp[(3) - (3)].NODE), "+");;}
    break;

  case 63:

/* Line 1455 of yacc.c  */
#line 606 "Yacc.y"
    {push("-");TAC();(yyval.NODE) = Construct_AST((yyvsp[(1) - (3)].NODE), (yyvsp[(3) - (3)].NODE), "-");;}
    break;

  case 64:

/* Line 1455 of yacc.c  */
#line 607 "Yacc.y"
    {push("/");TAC();(yyval.NODE) = Construct_AST((yyvsp[(1) - (3)].NODE), (yyvsp[(3) - (3)].NODE), "/");;}
    break;

  case 65:

/* Line 1455 of yacc.c  */
#line 608 "Yacc.y"
    {push("*");TAC();(yyval.NODE) = Construct_AST((yyvsp[(1) - (3)].NODE), (yyvsp[(3) - (3)].NODE), "*");;}
    break;

  case 66:

/* Line 1455 of yacc.c  */
#line 609 "Yacc.y"
    {push("%");TAC();(yyval.NODE) = Construct_AST((yyvsp[(1) - (3)].NODE), (yyvsp[(3) - (3)].NODE), "%");;}
    break;

  case 67:

/* Line 1455 of yacc.c  */
#line 610 "Yacc.y"
    {push("&");TAC();(yyval.NODE) = Construct_AST((yyvsp[(1) - (3)].NODE), (yyvsp[(3) - (3)].NODE), "&");;}
    break;

  case 68:

/* Line 1455 of yacc.c  */
#line 611 "Yacc.y"
    {push("|");TAC();(yyval.NODE) = Construct_AST((yyvsp[(1) - (3)].NODE), (yyvsp[(3) - (3)].NODE), "|");;}
    break;

  case 69:

/* Line 1455 of yacc.c  */
#line 612 "Yacc.y"
    {push("<");TAC();(yyval.NODE) = Construct_AST((yyvsp[(1) - (3)].NODE), (yyvsp[(3) - (3)].NODE), "<");;}
    break;

  case 70:

/* Line 1455 of yacc.c  */
#line 613 "Yacc.y"
    {push("<=");TAC();(yyval.NODE) = Construct_AST((yyvsp[(1) - (3)].NODE), (yyvsp[(3) - (3)].NODE), "<=");;}
    break;

  case 71:

/* Line 1455 of yacc.c  */
#line 614 "Yacc.y"
    {push(">");TAC();(yyval.NODE) = Construct_AST((yyvsp[(1) - (3)].NODE), (yyvsp[(3) - (3)].NODE), ">");;}
    break;

  case 72:

/* Line 1455 of yacc.c  */
#line 615 "Yacc.y"
    {push(">=");TAC();(yyval.NODE) = Construct_AST((yyvsp[(1) - (3)].NODE), (yyvsp[(3) - (3)].NODE), ">=");;}
    break;

  case 73:

/* Line 1455 of yacc.c  */
#line 616 "Yacc.y"
    {push("==");TAC();(yyval.NODE) = Construct_AST((yyvsp[(1) - (3)].NODE), (yyvsp[(3) - (3)].NODE), "==");;}
    break;

  case 74:

/* Line 1455 of yacc.c  */
#line 617 "Yacc.y"
    {push("!=");TAC();(yyval.NODE) = Construct_AST((yyvsp[(1) - (3)].NODE), (yyvsp[(3) - (3)].NODE), "!=");;}
    break;

  case 75:

/* Line 1455 of yacc.c  */
#line 620 "Yacc.y"
    {(yyval.NODE) = (yyvsp[(1) - (2)].NODE);;}
    break;

  case 76:

/* Line 1455 of yacc.c  */
#line 621 "Yacc.y"
    {(yyval.NODE) = (yyvsp[(1) - (2)].NODE);;}
    break;

  case 77:

/* Line 1455 of yacc.c  */
#line 623 "Yacc.y"
    {(yyval.NODE) = (yyvsp[(1) - (2)].NODE);;}
    break;

  case 78:

/* Line 1455 of yacc.c  */
#line 624 "Yacc.y"
    {(yyval.NODE) = (yyvsp[(1) - (2)].NODE);;}
    break;

  case 79:

/* Line 1455 of yacc.c  */
#line 626 "Yacc.y"
    {push((char*)yylval.str);(yyval.NODE) = Construct_AST(NULL, NULL, (char*)yylval.str); ;}
    break;

  case 80:

/* Line 1455 of yacc.c  */
#line 628 "Yacc.y"
    {push((char*)yylval.str);(yyval.NODE) = Construct_AST(NULL, NULL, (char*)yylval.str); ;}
    break;

  case 81:

/* Line 1455 of yacc.c  */
#line 630 "Yacc.y"
    {push((char*)yylval.str);(yyval.NODE) = Construct_AST(NULL, NULL, (char*)yylval.str); ;}
    break;

  case 82:

/* Line 1455 of yacc.c  */
#line 633 "Yacc.y"
    {(yyval.NODE) = (yyvsp[(1) - (1)].NODE);;}
    break;

  case 83:

/* Line 1455 of yacc.c  */
#line 634 "Yacc.y"
    {(yyval.NODE) = Construct_AST(NULL, NULL, ";"); ;}
    break;

  case 84:

/* Line 1455 of yacc.c  */
#line 637 "Yacc.y"
    {;}
    break;

  case 85:

/* Line 1455 of yacc.c  */
#line 638 "Yacc.y"
    {;}
    break;



/* Line 1455 of yacc.c  */
#line 2624 "Yacc.tab.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined(yyoverflow) || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}



/* Line 1675 of yacc.c  */
#line 641 "Yacc.y"


void yyerror(const char *str) 
{ 
	printf("Error | Line: %d\n%s\n",yylineno,str);
} 

void symboldisplay()
{
	//printf("Hi");
	//printf("%s",LineBreaker);
	//for (int i = 0;i < stop;i++)
	//{
	//	printf("%s\t",st1[i]);
	//}

	// Display Quads
	printf("%s",LineBreaker);
	//printf("Quadruplets\n");
	for(int i=0;i<quadindex;i++)
    {
        printf("%-8s \t %-8s \t %-8s \t %-6s \n",Q[i].op,Q[i].arg1,Q[i].arg2,Q[i].res);
    }
	printf("%s",LineBreaker);
}

int isDigit(char* in)
{
	for(int i = 0; i < strlen(in); ++i)
	{
		if(!isdigit(in[i])) return 0;
	}
	return 1;
}

void icg_optimize()
{
	
	for(int i = 0; i < quadindex; ++i)
	{
		if((strcmp(Q[i].op, "+") == 0 || strcmp(Q[i].op, "-") == 0 || strcmp(Q[i].op, "*") == 0 || strcmp(Q[i].op, "/") == 0
		|| strcmp(Q[i].op, "%") == 0 || strcmp(Q[i].op, "&") == 0 || strcmp(Q[i].op, "|") == 0 || strcmp(Q[i].op, "^") == 0)
		&& isDigit(Q[i].arg1) && isDigit(Q[i].arg2))
		{
			
			int res;
			if(strcmp(Q[i].op, "+") == 0)
				res = atoi(Q[i].arg1) + atoi(Q[i].arg2);
			else if(strcmp(Q[i].op, "-") == 0)
				res = atoi(Q[i].arg1) - atoi(Q[i].arg2);
			else if(strcmp(Q[i].op, "*") == 0)
				res = atoi(Q[i].arg1) * atoi(Q[i].arg2);
			else if(strcmp(Q[i].op, "/") == 0)
				res = atoi(Q[i].arg1) / atoi(Q[i].arg2);
			else if(strcmp(Q[i].op, "%") == 0)
				res = atoi(Q[i].arg1) % atoi(Q[i].arg2);
			else if(strcmp(Q[i].op, "&") == 0)
				res = atoi(Q[i].arg1) & atoi(Q[i].arg2);
			else if(strcmp(Q[i].op, "|") == 0)
				res = atoi(Q[i].arg1) | atoi(Q[i].arg2);
			else if(strcmp(Q[i].op, "^") == 0)
				res = atoi(Q[i].arg1) ^ atoi(Q[i].arg2);

			strcpy(Q[i].op, "=");
			sprintf(Q[i].arg1, "%d", res);

			Q[i].arg2 = NULL;

		}
	}
}

int main()
{
 	ast_tree_output = fopen("ast_tree_output.txt", "w");
	if(ast_tree_output == NULL)
	{
		printf("Could not open output file, aborting\n");
		exit(1);
	}
	yyparse();				//parse through the input. This step effectively also fills the symbol table, generates the AST and computes & prints ICG.
	
	printf("\n**************************************Symbol Table****************************************\n");
	
	display();				//display the symbol table. The function is defined in lex.l
	
	printf("\n*************************************************************************************************\n");
	
	printf("Intermediate Code Generation (Quadraple Form):\n");
	symboldisplay();

	/*icg_optimize();

	printf("After Optimization:\n");
	symboldisplay();*/
	fclose(ast_tree_output);
	return 0;
}

