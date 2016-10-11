#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

typedef enum {
    UNKNOWN, END_OF_FILE,
    PLUS, MULT,
    LPAREN, RPAREN,
    NUM
} TokenType;

#define MAX_LENGTH 100

TokenType ttype = UNKNOWN;
char token[MAX_LENGTH];
int line = 1;
bool active_token = false;

static void skip_spaces()
{
    char c = ' ';
    while (isspace(c) && !feof(stdin))
    {
        line += (c == '\n');
        c = getchar();
    }
    if (!feof(stdin))
        ungetc(c, stdin);
}

static int scan_number()
{
    int len = 0;
    char c;

    c = getchar();
    if (isdigit(c))
    {
        if (c == '0')
        {
            token[len++] = c;
        }
        else
        {
            while (isdigit(c) && !feof(stdin) && len < MAX_LENGTH)
            {
                token[len++] = c;
                c = getchar();
            }
            if (!feof(stdin))
                ungetc(c, stdin);
        }
        token[len++] = '\0';
        return NUM;
    }
    else
    {
        return UNKNOWN;
    }
}

TokenType next_token()
{
    char c;

    if (active_token)
    {
        active_token = false;
        return ttype;
    }

    skip_spaces();
    token[0] = 0;
    c = getchar();

    switch(c)
    {
        case '+': ttype = PLUS;   return ttype;
        case '*': ttype = MULT;   return ttype;
        case '(': ttype = LPAREN; return ttype;
        case ')': ttype = RPAREN; return ttype;
        default:
            if (isdigit(c))
            {
                ungetc(c, stdin);
                ttype = scan_number();
                return ttype;
            }
            else if (c == EOF)
            {
                ttype = END_OF_FILE;
                return ttype;
            }
            else
            {
                ttype = UNKNOWN;
                return ttype;
            }
    }
}

void unget_token()
{
    active_token = true;
}

// -----------------------------------------------------------------------------

void syntax_error(const char* func, const char* msg)
{
    fprintf(stderr, "Syntax error in %s: %s, line %d\n", func, msg, line);
    exit(1);
}

void do_expect(TokenType desired_type, const char* func, const char* msg)
{
    next_token();
    if (ttype != desired_type)
        syntax_error(func, msg);
}

void peek_token()
{
    next_token();
    unget_token();
}

#define expect(token) do_expect(token, __func__, "expected " #token)

// -----------------------------------------------------------------------------

void parse_e();
void parse_e1();
void parse_t();
void parse_t1();
void parse_f();

void parse_e()
{
    puts("e -> t e1");
    parse_t();
    parse_e1();
}

void parse_e1()
{
    next_token();
    if (ttype == PLUS)
    {
        puts("e1 -> PLUS e");
        parse_e();
    }
    else if (ttype == RPAREN || ttype == END_OF_FILE)
    {
        puts("e1 -> epsilon");
        unget_token();
    }
    else
    {
        syntax_error(__func__, "expected PLUS, RPAREN or $");
    }
}

void parse_t()
{
    puts("t -> f t1");
    parse_f();
    parse_t1();
}

void parse_t1()
{
    next_token();
    if (ttype == MULT)
    {
        puts("t1 -> MULT t");
        parse_t();
    }
    else if (ttype == PLUS || ttype == RPAREN || ttype == END_OF_FILE)
    {
        puts("t1 -> epsilon");
        unget_token();
    }
    else
    {
        syntax_error(__func__, "expected MULT, PLUS, RPAREN or $");
    }
}

void parse_f()
{
    next_token();
    if (ttype == NUM)
    {
        puts("f -> NUM");
    }
    else if (ttype == LPAREN)
    {
        puts("f -> LPAREN e RPAREN");
        parse_e();
        expect(RPAREN);
    }
    else
    {
        syntax_error(__func__, "expected NUM or LPAREN");
    }
}

void parse_input()
{
    parse_e();
    expect(END_OF_FILE);
}

// -----------------------------------------------------------------------------

int main()
{
    parse_input();
    return 0;
}

