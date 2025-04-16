
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

int precedence(char op) 
{
    if (op == '+' || op == '-') 
    {
        return 1;
    }

    if (op == '*' || op == '/' || op == '%')
    {
        return 2;
    }

    if (op == '^')
    {
        return 3;
    }

    return 0; 
}

int gid = 0;

struct Tree
{
    int id;
    string op;
    string val;
    Tree * left = nullptr, * right = nullptr;

    Tree(): id(++gid) {}
    Tree(string v): id(++gid), val(v) {}
    Tree(string o, Tree * a, Tree * b): id(++gid), op(o), left(a), right(b) {}
    Tree(const Tree &) = delete;
    ~Tree() { delete left; delete right; }

    string str() const;
    string edges() const;
    string expr() const;
};


Tree * eval_expr();

Tree * eval_prim()
{
    if (peek == "(")
    {
        tok(); // Consumes the left parenthesis '('
        Tree* left = eval_expr();
        tok(); // Consumes the right parenthesis ')'
        return left;
    }

    string num = tok();
    return new Tree(num);
}

Tree * eval_powr()
{
    Tree* left = eval_prim();

    while(peek == "^")
    {
        auto op = tok();
        Tree* right = eval_prim();
        left = new Tree(op, left, right);
    }

    return left;
}

Tree * eval_term()
{
    Tree* left = eval_powr();

    while(peek == "*" || peek == "/" || peek == "%")
    {
        auto op = tok();
        Tree* right = eval_powr();
        left = new Tree(op, left, right);
    }

    return left;
}

Tree * eval_expr()
{
    Tree* left = eval_term();

    while(peek == "+" || peek == "-")
    {
        auto op = tok();
        Tree* right = eval_term();
        left = new Tree(op, left, right);
    }

    return left;
}


int main()
{
try
{
    for (string line; getline(cin, line);)
    {
        if ( line.empty() ) continue;
        if ( line[0] == '#' ) continue;
        if ( line == "end" ) break;

        istringstream is(line);
        gis = &is; // reset input stream
        gid = 0; // reset id counter
        tok(); // load peek token

        Tree * tree = eval_expr();

        cout << "```mermaid\ngraph TD\n"
             << "A(\"" << line << "\")\n"
             << "B(\"" << tree->expr() << "\")\n"
             << "A --> B\n"
             << "style A fill:#ded\n"
             << "style B fill:#dde\n"
             << tree->edges() << "```\n---\n";

        delete tree;
    }
}
    catch (string s) { cout << "Error: " << s << '\n'; }
    catch (...) { cout << "exception\n"; }
}

string Tree::str() const
{
    if ( op.empty() ) return to_string(id) + "[" + val + "]";
    return to_string(id) + "((\"" + op + "\"))";
}

string Tree::edges() const
{
    string output = "";

    if (left != nullptr)
    {
        output += str() + " --> " + left->str() + "\n";
    }

    if (right != nullptr)
    {
        output += str() + " --> " + right->str() + "\n";
    }

    if (left != nullptr)
    {
        output += left->edges();
    }

    if (right != nullptr)
    {
        output += right->edges();
    }
    
    return output;
}


string Tree::expr() const
{
    string left_str, right_str;
    
    if (op.empty())
    {
        return val;
    }

    if (left != nullptr)
    {
        left_str = left->expr();
    }

    if (right != nullptr)
    {
        right_str = right->expr();
    }


    if (left!=nullptr && !left->op.empty() && precedence(left->op[0]) < precedence(op[0]))
    {
        left_str = "( " + left_str + " )";
    }
    

    if (right != nullptr && !right->op.empty()) 
    {
        if (precedence(right->op[0]) < precedence(op[0]) || (precedence(right->op[0]) 
            == precedence(op[0]) && op[0] == '^'))
        {      
            right_str = "( " + right_str + " )";
        }
    }


    return left_str + " " + op + " " + right_str;
}
