
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

istream * gis;
string peek;
string tok() 
{ 
    auto r = peek; peek = ""; 
    if (*gis) 
        (*gis) >> peek; 
    return r; 
}

string eval_expr();

string eval_prim()
{
    if ( peek == "(" )
    {
        tok();
        return eval_expr();
    }

    return ' ' + tok();
}

string eval_powr()
{

    string result = eval_prim();

    for (;;)
    {
        if ( peek == "^" )
        {
            auto op = tok();
            auto b = eval_prim();
            result += b + ' ' + op;
        }
        else break;
    }
    return result;
}

string eval_term()
{
    auto result = eval_powr();
    for (;;)
    {
        if ( peek == "*" || peek == "/" || peek == "%" )
        {
            auto op = tok();
            auto b = eval_powr();
            result += b + ' ' + op;
        }
        else break;
    }
    return result;
}

string eval_expr()
{
    string result = eval_term();
    for (;;)
    {
        if ( peek == "+" || peek == "-" )
        {
            auto op = tok();
            auto b = eval_term();
            result += b + ' ' + op;
        }
        else if (peek.empty()) break;
        else if (peek == ")") { tok(); break; }
        else throw "bad operator [" + peek + "]";
    }
    return result;
}

int main()
try
{
    for (string line; getline(cin, line);)
    {
        if ( line.empty() ) continue;
        if ( line[0] == '#' ) continue;
        if ( line == "end" ) break;
        istringstream is(line);
        gis = &is;
        tok(); // load peek token
        cout << eval_expr() << '\n';
    }
}
catch (string s) 
{ 
    cout << "Error: " << s << '\n'; 
}
catch (...) 
{ 
    cout << "exception\n"; 
}
