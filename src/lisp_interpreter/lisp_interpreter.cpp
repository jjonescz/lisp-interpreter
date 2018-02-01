// lisp_interpreter.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <sstream>
#include "tokenizer.hpp"
#include "parser.hpp"
#include "visitors.hpp"

using namespace std;

int main()
{
    tlist tokens;
    for (string line; getline(cin, line);)
    {
        // tokenize
        stringstream ss(line);
        tokenizer(tokens).tokenize(ss);

        parser p(tokens);
        do {
            // parse
            ep expr;
            try {
                expr = p.parse();
            }
            catch (const parser_error& e) {
                cerr << "Parsing error: " << e.what() << endl;
                break;
            }

            // evaluate
            // TODO.
            printer(cout).visit(*expr);
            cout << endl;
        } while (!tokens.empty());

        tokens.clear();
    }
    return 0;
}
