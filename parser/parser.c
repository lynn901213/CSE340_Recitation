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

enum Tag
{
    TAG_PLUS,
    TAG_MULT,
    TAG_NUM
};

struct Expression
{
    enum Tag tag;
    int value;                  // meaningful if tag == TAG_NUM
    struct Expression * left;   // meaningful if tag == TAG_PLUS or TAG_MULT
    struct Expression * right;  // meaningful if tag == TAG_PLUS or TAG_MULT
};

#define ALLOC(t) (t*) calloc(sizeof(t), 1)

// -----------------------------------------------------------------------------

struct Expression * parse_e();
struct Expression * parse_t();
struct Expression * parse_f();

struct Expression * parse_e()
{
    struct Expression * t = parse_t();
    next_token();
    if (ttype == PLUS)
    {
        struct Expression * e = parse_e();
        struct Expression * node = ALLOC(struct Expression);
        node->tag = TAG_PLUS;
        node->left = t;
        node->right = e;
        return node;
    }
    else if (ttype == RPAREN || ttype == END_OF_FILE)
    {
        unget_token();
        return t;
    }
    else
    {
        syntax_error(__func__, "expected PLUS, RPAREN or $");
        return NULL;
    }
}

struct Expression * parse_t()
{
    struct Expression * f = parse_f();
    next_token();
    if (ttype == MULT)
    {
        struct Expression * t = parse_t();
        struct Expression * node = ALLOC(struct Expression);
        node->tag = TAG_MULT;
        node->left = f;
        node->right = t;
        return node;
    }
    else if (ttype == PLUS || ttype == RPAREN || ttype == END_OF_FILE)
    {
        unget_token();
        return f;
    }
    else
    {
        syntax_error(__func__, "expected MULT, PLUS, RPAREN or $");
        return NULL;
    }
}

struct Expression * parse_f()
{
    next_token();
    if (ttype == NUM)
    {
        struct Expression * node = ALLOC(struct Expression);
        node->tag = TAG_NUM;
        node->value = atoi(token);
        return node;
    }
    else if (ttype == LPAREN)
    {
        struct Expression * e = parse_e();
        expect(RPAREN);
        return e;
    }
    else
    {
        syntax_error(__func__, "expected NUM or LPAREN");
        return NULL;
    }
}

struct Expression * parse_input()
{
    struct Expression * e = parse_e();
    expect(END_OF_FILE);
    return e;
}

// -----------------------------------------------------------------------------

void print_expression_prefix(struct Expression * e)
{
    switch (e->tag)
    {
        case TAG_PLUS:
            printf("+ ");
            print_expression_prefix(e->left);
            print_expression_prefix(e->right);
            break;
        case TAG_MULT:
            printf("* ");
            print_expression_prefix(e->left);
            print_expression_prefix(e->right);
            break;
        case TAG_NUM:
            printf("%d ", e->value);
            break;
    }
}

int evaluate_expression(struct Expression * e)
{
    switch (e->tag)
    {
        case TAG_PLUS:
            {
                int left = evaluate_expression(e->left);
                int right = evaluate_expression(e->right);
                return left + right;
            }
        case TAG_MULT:
            {
                int left = evaluate_expression(e->left);
                int right = evaluate_expression(e->right);
                return left * right;
            }
        case TAG_NUM:
            return e->value;
        default:
            return 0;
    }

}

int main()
{
    struct Expression * e = parse_input();
    print_expression_prefix(e);
    printf("\n");
    printf("Result = %d\n", evaluate_expression(e));
    return 0;
}

