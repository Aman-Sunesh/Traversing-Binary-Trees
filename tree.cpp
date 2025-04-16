
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
    // FIXME
    return nullptr;
}

Tree * eval_powr()
{
    // FIXME
    return nullptr;
}

Tree * eval_term()
{
    // FIXME
    return nullptr;
}

Tree * eval_expr()
{
    // FIXME
    return nullptr;
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
    // FIXME
    return "";
}


string Tree::expr() const
{
    // FIXME
    return "";
}
