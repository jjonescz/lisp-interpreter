// lisp_interpreter.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <sstream>
#include "tokens.hpp"
#include "tokenizer.hpp"
#include "parser.hpp"
#include "expressions.hpp"
#include "visitors.hpp"
#include "evaluator.hpp"

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
        evaluator e;
        do {
            // parse
            vp expr;
            try {
                expr = move(p.parse());
            }
            catch (const parser_error& e) {
                cerr << "Parsing error: " << e.what() << endl;
                break;
            }

            // evaluate
            // TODO: actually, use "eval" func from the environment (and eval this "eval" function with evaluator with parsed expr as an argument)
            vp res;
            try {
                res = move(e.visit(expr));
            }
            catch (const eval_error& e) {
                cerr << "Evaluation error: " << e.what() << endl;
                break;
            }

            // print
            printer(cout).visit(res);
            cout << endl;
        } while (!tokens.empty());

        tokens.clear();
    }
    return 0;
}
