#include <iostream>
#include <stack>
#include "post.h"
using namespace std;

bool Token::operator==(char b)
{
    return len == 1 && str[0] ==b;
}
bool Token::operator!= (char b)
{
    return len != 1 || str[0] != b;
}
Token::Token() {}
Token::Token(char c):len(1), type(c)
{ 
    str = new char[1]; 
    str[0] = c;
}
Token::Token(char c, char c2, int ty): len(2), type(ty)
{ 
    str = new char[2];
    str[0] = c;
    str[1] = c2;
}
Token::Token(char* arr, int l, int ty = ID):len(l), type(ty)
{
    str = new char[len + 1];
    for(int i = 0; i < len; i++)
        str[i] = arr[i];
    str[len] = '\0';
    if(type == NUM)
    {
        ival = arr[0] - '0';
        for(int i = 1; i<len; i++)
            ival = ival * 10 + arr[i] -'0';
    }
    else if(type == ID)
        ival = 0;
    else
        throw "must be ID or NUM";
}

bool Token::IsOperand()
{
    return type == ID || type == NUM;
}

ostream& operator<<(ostream& os, Token t)
{
    if(t.type == UMINUS)
        os<<"-u";
    else if(t.type == NUM)
        os<<t.ival;
    else
        for(int i = 0; i<t.len; i++)
            os<<t.str[i];
    os<<" ";
    return os;
}

bool GetID(Expression& e, Token& tok)
{
    char arr[MAXLEN];
    int idlen = 0;
    char c = e.str[e.pos];
    if(!(c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z'))
        return false;
    arr[idlen++] = c;
    e.pos++;
    while((c = e.str[e.pos]) >= 'a' && c<= 'z' || c >= 'A' && c <= 'Z' || c >= '0' && c <= '9')
            {
                arr[idlen++] = c;
                e.pos++;
            }
    arr[idlen] = '\0';
    tok = Token(arr, idlen, ID);
    return true;
}
bool GetInt(Expression& e, Token& tok)
{
    char arr[MAXLEN];
    int numlen = 0;
    char c = e.str[e.pos];
    if(!(c >= '0' && c <= '9'))
        return false;
    arr[numlen++] = c;
    e.pos++;
    while((c = e.str[e.pos]) >= '0' && c<= '9')
    {
        arr[numlen++] = c;
        e.pos++;
    }
    arr[numlen] = '\0';
    tok = Token(arr, numlen, NUM);
    return true;
}

void SkipBlanks(Expression& e)
{
    char c;
    while(e.pos < e.len && ((c = e.str[e.pos]) == ' '|| c == '\t'))
        e.pos++;
}


bool TwoCharOp(Expression& e, Token& tok)
{
    char c = e.str[e.pos];
    char c2 = e.str[e.pos + 1];
    int op;
    if(c == '<' && c2 == '=') op = LE;
    else if(c == '>' && c2 == '=') op = GE;
    else if(c == '=' && c2 == '=') op = EQ;
    else if(c == '!' && c2 == '=') op = NE;
    else if(c == '&' && c2 == '&') op = AND;
    else if(c == '|' && c2 == '|') op = OR;
    else if(c == '-' && c2 == 'u') op = UMINUS;
    else return false;
    tok = Token(c, c2, op);
    e.pos += 2;
    return true;
}
bool OneCharOp(Expression& e, Token& tok)
{
    char c = e.str[e.pos];
    if(c == '-'||c == '!' ||c == '*' ||c == '/' ||c == '%' ||
    c == '+' ||c == '<' ||c == '>'||c == '('||c == ')'||c == '=')
    {
        tok = Token(c);
        e.pos++;
        return true;
    }
    return false;
}

Token NextToken(Expression& e)
{
    static bool oprrFound = true; //종전에 연산자 발견되었다고 가정
    Token tok;
    SkipBlanks(e);
    if(e.pos == e.len)
    {
        oprrFound = true;
        return Token('#');
    }
    if(GetID(e,tok) || GetInt(e,tok))
    {
        oprrFound = false;
        return tok;
    }
    if (TwoCharOp(e, tok) || OneCharOp(e, tok))
    {
        if((tok.type == '-' && e.pos == 1) || (tok.type == '-' && oprrFound))
            tok = Token('-', 'u', UMINUS);
        oprrFound = true;
        return tok;
    }

    throw "Illegal Character Found";
}

int icp(Token& t)
{
    int ty = t.type;
    if (ty == '(') return 0;
    else if (ty == UMINUS || ty == '!') return 1;
    else if (ty == '*' || ty == '/' || ty == '%') return 2;
    else if (ty == '+' || ty == '-') return 3;
    else if (ty == '<' || ty == '>' || ty == LE || ty == GE) return 4;
    else if (ty == EQ || ty == NE) return 5;
    else if (ty == AND) return 6;
    else if (ty == OR) return 7;
    else if (ty == '=') return 8;
    else if (ty == '#') return 9;
}
int isp(Token &t)
{
    int ty = t.type;
    if (ty == '(') return 9;
    else if (ty == UMINUS || ty == '!') return 1;
    else if (ty == '*' || ty == '/' || ty == '%') return 2;
    else if (ty == '+' || ty == '-') return 3;
    else if (ty == '<' || ty == '>' || ty == LE || ty == GE) return 4;
    else if (ty == EQ || ty == NE) return 5;
    else if (ty == AND) return 6;
    else if (ty == OR) return 7;
    else if (ty == '=') return 8;
    else if (ty == '#') return 9;
}

void Postfix(Expression e)
{
    stack<Token>stack;
    stack.push('#');
    for(Token x = NextToken(e); x != '#'; x = NextToken(e))
    {
        if(x.IsOperand())
            cout << x;
        else if(x == ')')
        {
            for(;stack.top() != '('; stack.pop())
                cout << stack.top();
            stack.pop();
        }
        else
        {
            for(;isp(stack.top()) <= icp(x); stack.pop())
            {
                if(x == '=' && stack.top() == '=')
                    break;
                cout << stack.top();
            }
            stack.push(x);
        }
    }
    for(;stack.top() != '#'; cout << stack.top(), stack.pop());
    cout << endl;
}