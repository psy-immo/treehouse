#ifndef lint
static const char yysccsid[] = "@(#)yaccpar	1.9 (Berkeley) 02/21/93";
#endif

#define YYBYACC 1
#define YYMAJOR 1
#define YYMINOR 9
#define YYPATCH 20110908

#define YYEMPTY        (-1)
#define yyclearin      (yychar = YYEMPTY)
#define yyerrok        (yyerrflag = 0)
#define YYRECOVERING() (yyerrflag != 0)

#define YYPREFIX "yy"

#define YYPURE 0

#line 2 "cpsp.y"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define YYSTYPE char *

#include "cprops/vector.h"
#include "cprops/str.h"

void yyerror(const char *str)
{
	fprintf(stderr, "error: %s\n",str);
}
		  
int yywrap()
{
	return 1;
} 
				    
static cp_vector *global;
static cp_vector *service;
static cp_vector *codepack;

static int entered_service = 0;
static int consumed;
static cp_string *curr_code;
					
char *strdup_escape(char *src)
{
	char *res, *dup;
	int len = strlen(src) * 2 + 1;
	dup = res = malloc(len * sizeof(char));

	while (*src)
	{
		switch (*src)
		{
			case '\n' : 
				*res++ = '\\';
				*res++ = 'n';
				src++;
				break;

			case '\\' : 
			case '\'' :
			case '\"' :
				*res++ = '\\';
				

			default :
				*res++ = *src++;
		}
	}
	*res = '\0';

	return dup;
}
				
static char *global_header = 
"#include <stdio.h>\n"
"#include \"cprops/http.h\"\n"
	;

static char *service_header = 
#ifdef _WINDOWS
"__declspec(dllexport)\n"
#endif /* _WINDOWS */
"int cpsp_service_function(cp_http_request *request, cp_http_response *response)\n"
"{\n"
"\tcp_http_session *session = cp_http_request_get_session(request, 1);\n"
"\tcp_string *content = cp_string_create(\"\", 0);\n"
"\tresponse->content = content;\n"
"\tresponse->content_type = HTML;\n"
"\t{\n"
    ;

static char *service_footer = 
"\t}\n"
"\treturn HTTP_CONNECTION_POLICY_KEEP_ALIVE;\n"
"}\n"
    ;

/* the following lines are to silence warnings */
int yylex();
extern int yyparse(void);

int main(int argc, char *argv[])
{
	int i, n;
	global = cp_vector_create(10);
	service = cp_vector_create(10);
	codepack = cp_vector_create(10);
	curr_code = cp_string_create("", 0);
	yyparse();

	printf("%s\n", global_header);
	n = cp_vector_size(global);
	for (i = 0; i < n; i++)
		printf("%s", (char *) cp_vector_element_at(global, i));

	printf("\n%s\n", service_header);
	n = cp_vector_size(service);
	for (i = 0; i < n; i++)
		printf("%s", (char *) cp_vector_element_at(service, i));

	printf("%s\n", service_footer);

	cp_vector_destroy_custom(global, free);
	cp_vector_destroy_custom(service, free);
	cp_vector_destroy_custom(codepack, free);

	return 0;
} 

#line 134 "y.tab.c"

#ifndef YYSTYPE
typedef int YYSTYPE;
#endif

/* compatibility with bison */
#ifdef YYPARSE_PARAM
/* compatibility with FreeBSD */
# ifdef YYPARSE_PARAM_TYPE
#  define YYPARSE_DECL() yyparse(YYPARSE_PARAM_TYPE YYPARSE_PARAM)
# else
#  define YYPARSE_DECL() yyparse(void *YYPARSE_PARAM)
# endif
#else
# define YYPARSE_DECL() yyparse(void)
#endif

/* Parameters sent to lex. */
#ifdef YYLEX_PARAM
# define YYLEX_DECL() yylex(void *YYLEX_PARAM)
# define YYLEX yylex(YYLEX_PARAM)
#else
# define YYLEX_DECL() yylex(void)
# define YYLEX yylex()
#endif

/* Parameters sent to yyerror. */
#define YYERROR_DECL() yyerror(const char *s)
#define YYERROR_CALL(msg) yyerror(msg)

extern int YYPARSE_DECL();

#define OPENPAGEBLOCK 257
#define OPENGLOBALBLOCK 258
#define OPENSVCBLOCK 259
#define OPENVALBLOCK 260
#define CLOSEBLOCK 261
#define CODE 262
#define YYERRCODE 256
static const short yylhs[] = {                           -1,
    0,    0,    1,    1,    1,    1,    1,    2,    3,    4,
    5,    6,    6,    7,
};
static const short yylen[] = {                            2,
    0,    2,    1,    1,    1,    1,    1,    3,    3,    3,
    3,    0,    2,    1,
};
static const short yydefred[] = {                         1,
    0,   12,   12,   12,   12,    2,    3,    4,    5,    6,
    0,    0,    0,    0,    0,   14,   13,    8,    9,   10,
   11,
};
static const short yydgoto[] = {                          1,
    6,    7,    8,    9,   10,   11,   17,
};
static const short yysindex[] = {                         0,
 -254,    0,    0,    0,    0,    0,    0,    0,    0,    0,
 -262, -250, -248, -246, -244,    0,    0,    0,    0,    0,
    0,
};
static const short yyrindex[] = {                         0,
    1,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    2,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,
};
static const short yygindex[] = {                         0,
    0,    0,    0,    0,    0,    5,    0,
};
#define YYTABLESIZE 263
static const short yytable[] = {                         16,
   12,    7,    2,    3,    4,    5,   12,   13,   14,   15,
   18,   16,   19,   16,   20,   16,   21,   16,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    7,    7,
    7,    7,   12,
};
static const short yycheck[] = {                        262,
    0,    0,  257,  258,  259,  260,    2,    3,    4,    5,
  261,  262,  261,  262,  261,  262,  261,  262,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  257,  258,
  259,  260,  262,
};
#define YYFINAL 1
#ifndef YYDEBUG
#define YYDEBUG 0
#endif
#define YYMAXTOKEN 262
#if YYDEBUG
static const char *yyname[] = {

"end-of-file",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"OPENPAGEBLOCK","OPENGLOBALBLOCK",
"OPENSVCBLOCK","OPENVALBLOCK","CLOSEBLOCK","CODE",
};
static const char *yyrule[] = {
"$accept : statements",
"statements :",
"statements : statements statement",
"statement : pageblock",
"statement : globalblock",
"statement : svcblock",
"statement : valblock",
"statement : code",
"pageblock : OPENPAGEBLOCK code CLOSEBLOCK",
"globalblock : OPENGLOBALBLOCK code CLOSEBLOCK",
"svcblock : OPENSVCBLOCK code CLOSEBLOCK",
"valblock : OPENVALBLOCK code CLOSEBLOCK",
"code :",
"code : code raw",
"raw : CODE",

};
#endif

int      yydebug;
int      yynerrs;

int      yyerrflag;
int      yychar;
YYSTYPE  yyval;
YYSTYPE  yylval;

/* define the initial stack-sizes */
#ifdef YYSTACKSIZE
#undef YYMAXDEPTH
#define YYMAXDEPTH  YYSTACKSIZE
#else
#ifdef YYMAXDEPTH
#define YYSTACKSIZE YYMAXDEPTH
#else
#define YYSTACKSIZE 500
#define YYMAXDEPTH  500
#endif
#endif

#define YYINITSTACKSIZE 500

typedef struct {
    unsigned stacksize;
    short    *s_base;
    short    *s_mark;
    short    *s_last;
    YYSTYPE  *l_base;
    YYSTYPE  *l_mark;
} YYSTACKDATA;
/* variables for the parser stack */
static YYSTACKDATA yystack;

#if YYDEBUG
#include <stdio.h>		/* needed for printf */
#endif

#include <stdlib.h>	/* needed for malloc, etc */
#include <string.h>	/* needed for memset */

/* allocate initial stack or double stack size, up to YYMAXDEPTH */
static int yygrowstack(YYSTACKDATA *data)
{
    int i;
    unsigned newsize;
    short *newss;
    YYSTYPE *newvs;

    if ((newsize = data->stacksize) == 0)
        newsize = YYINITSTACKSIZE;
    else if (newsize >= YYMAXDEPTH)
        return -1;
    else if ((newsize *= 2) > YYMAXDEPTH)
        newsize = YYMAXDEPTH;

    i = data->s_mark - data->s_base;
    newss = (short *)realloc(data->s_base, newsize * sizeof(*newss));
    if (newss == 0)
        return -1;

    data->s_base = newss;
    data->s_mark = newss + i;

    newvs = (YYSTYPE *)realloc(data->l_base, newsize * sizeof(*newvs));
    if (newvs == 0)
        return -1;

    data->l_base = newvs;
    data->l_mark = newvs + i;

    data->stacksize = newsize;
    data->s_last = data->s_base + newsize - 1;
    return 0;
}

#if YYPURE || defined(YY_NO_LEAKS)
static void yyfreestack(YYSTACKDATA *data)
{
    free(data->s_base);
    free(data->l_base);
    memset(data, 0, sizeof(*data));
}
#else
#define yyfreestack(data) /* nothing */
#endif

#define YYABORT  goto yyabort
#define YYREJECT goto yyabort
#define YYACCEPT goto yyaccept
#define YYERROR  goto yyerrlab

int
YYPARSE_DECL()
{
    int yym, yyn, yystate;
#if YYDEBUG
    const char *yys;

    if ((yys = getenv("YYDEBUG")) != 0)
    {
        yyn = *yys;
        if (yyn >= '0' && yyn <= '9')
            yydebug = yyn - '0';
    }
#endif

    yynerrs = 0;
    yyerrflag = 0;
    yychar = YYEMPTY;
    yystate = 0;

#if YYPURE
    memset(&yystack, 0, sizeof(yystack));
#endif

    if (yystack.s_base == NULL && yygrowstack(&yystack)) goto yyoverflow;
    yystack.s_mark = yystack.s_base;
    yystack.l_mark = yystack.l_base;
    yystate = 0;
    *yystack.s_mark = 0;

yyloop:
    if ((yyn = yydefred[yystate]) != 0) goto yyreduce;
    if (yychar < 0)
    {
        if ((yychar = YYLEX) < 0) yychar = 0;
#if YYDEBUG
        if (yydebug)
        {
            yys = 0;
            if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
            if (!yys) yys = "illegal-symbol";
            printf("%sdebug: state %d, reading %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
    }
    if ((yyn = yysindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: state %d, shifting to state %d\n",
                    YYPREFIX, yystate, yytable[yyn]);
#endif
        if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack))
        {
            goto yyoverflow;
        }
        yystate = yytable[yyn];
        *++yystack.s_mark = yytable[yyn];
        *++yystack.l_mark = yylval;
        yychar = YYEMPTY;
        if (yyerrflag > 0)  --yyerrflag;
        goto yyloop;
    }
    if ((yyn = yyrindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
        yyn = yytable[yyn];
        goto yyreduce;
    }
    if (yyerrflag) goto yyinrecovery;

    yyerror("syntax error");

    goto yyerrlab;

yyerrlab:
    ++yynerrs;

yyinrecovery:
    if (yyerrflag < 3)
    {
        yyerrflag = 3;
        for (;;)
        {
            if ((yyn = yysindex[*yystack.s_mark]) && (yyn += YYERRCODE) >= 0 &&
                    yyn <= YYTABLESIZE && yycheck[yyn] == YYERRCODE)
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: state %d, error recovery shifting\
 to state %d\n", YYPREFIX, *yystack.s_mark, yytable[yyn]);
#endif
                if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack))
                {
                    goto yyoverflow;
                }
                yystate = yytable[yyn];
                *++yystack.s_mark = yytable[yyn];
                *++yystack.l_mark = yylval;
                goto yyloop;
            }
            else
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: error recovery discarding state %d\n",
                            YYPREFIX, *yystack.s_mark);
#endif
                if (yystack.s_mark <= yystack.s_base) goto yyabort;
                --yystack.s_mark;
                --yystack.l_mark;
            }
        }
    }
    else
    {
        if (yychar == 0) goto yyabort;
#if YYDEBUG
        if (yydebug)
        {
            yys = 0;
            if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
            if (!yys) yys = "illegal-symbol";
            printf("%sdebug: state %d, error recovery discards token %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
        yychar = YYEMPTY;
        goto yyloop;
    }

yyreduce:
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: state %d, reducing by rule %d (%s)\n",
                YYPREFIX, yystate, yyn, yyrule[yyn]);
#endif
    yym = yylen[yyn];
    if (yym)
        yyval = yystack.l_mark[1-yym];
    else
        memset(&yyval, 0, sizeof yyval);
    switch (yyn)
    {
case 7:
#line 127 "cpsp.y"
	{
		if (!consumed)
		{
			char *curr_code_ptr = cp_string_tocstr(curr_code);
			if (!entered_service)
			{
				while (*curr_code_ptr == '\n') curr_code_ptr++;
				if (*curr_code_ptr) entered_service = 1;
			}
				
			if (*curr_code_ptr)
			{
				char *escaped = strdup_escape(curr_code_ptr);
				cp_string *g = cp_string_cstrdup("\tcp_string_cstrcat(content, \"");
				cp_string_cstrcat(g, escaped);
				free(escaped);
				cp_string_cstrcat(g, "\");\n");
				cp_vector_add_element(service, strdup(cp_string_tocstr(g)));
				cp_string_delete(g);
			}

			cp_string_reset(curr_code);
			consumed = 5;
		}
	}
break;
case 8:
#line 156 "cpsp.y"
	{
		cp_string *g = cp_string_cstrdup("//%@");
		cp_string_cat(g, curr_code);
		cp_string_cstrcat(g, "\n");
		cp_vector_add_element(global, strdup(cp_string_tocstr(g)));
		cp_string_delete(g);
		cp_string_reset(curr_code);
		consumed = 1;
	}
break;
case 9:
#line 170 "cpsp.y"
	{
		cp_string_cstrcat(curr_code, "\n");
		cp_vector_add_element(global, strdup(cp_string_tocstr(curr_code)));
		cp_string_reset(curr_code);
		consumed = 2;
	}
break;
case 10:
#line 180 "cpsp.y"
	{
		cp_string_cstrcat(curr_code, "\n");
		cp_vector_add_element(service, strdup(cp_string_tocstr(curr_code)));
		cp_vector_add_element(service, strdup("\n"));
		cp_string_reset(curr_code);
		consumed = 3;
	}
break;
case 11:
#line 191 "cpsp.y"
	{
		cp_string *g = cp_string_cstrdup("\tcp_string_cstrcat(content, ");
		cp_string_cat(g, curr_code);
		cp_string_cstrcat(g, ");\n");
		cp_vector_add_element(service, strdup(cp_string_tocstr(g)));
		cp_string_delete(g);
		cp_string_reset(curr_code);
		consumed = 4;
	}
break;
case 13:
#line 204 "cpsp.y"
	{
		yyval = yystack.l_mark[0];
	}
break;
case 14:
#line 211 "cpsp.y"
	{
		consumed = 0;
		if (yystack.l_mark[0])
			cp_string_cstrcat(curr_code, yystack.l_mark[0]);
	}
break;
#line 622 "y.tab.c"
    }
    yystack.s_mark -= yym;
    yystate = *yystack.s_mark;
    yystack.l_mark -= yym;
    yym = yylhs[yyn];
    if (yystate == 0 && yym == 0)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: after reduction, shifting from state 0 to\
 state %d\n", YYPREFIX, YYFINAL);
#endif
        yystate = YYFINAL;
        *++yystack.s_mark = YYFINAL;
        *++yystack.l_mark = yyval;
        if (yychar < 0)
        {
            if ((yychar = YYLEX) < 0) yychar = 0;
#if YYDEBUG
            if (yydebug)
            {
                yys = 0;
                if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
                if (!yys) yys = "illegal-symbol";
                printf("%sdebug: state %d, reading %d (%s)\n",
                        YYPREFIX, YYFINAL, yychar, yys);
            }
#endif
        }
        if (yychar == 0) goto yyaccept;
        goto yyloop;
    }
    if ((yyn = yygindex[yym]) && (yyn += yystate) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yystate)
        yystate = yytable[yyn];
    else
        yystate = yydgoto[yym];
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: after reduction, shifting from state %d \
to state %d\n", YYPREFIX, *yystack.s_mark, yystate);
#endif
    if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack))
    {
        goto yyoverflow;
    }
    *++yystack.s_mark = (short) yystate;
    *++yystack.l_mark = yyval;
    goto yyloop;

yyoverflow:
    yyerror("yacc stack overflow");

yyabort:
    yyfreestack(&yystack);
    return (1);

yyaccept:
    yyfreestack(&yystack);
    return (0);
}
