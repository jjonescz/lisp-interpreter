// lisp_interpreter.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <sstream>
#include <algorithm>
#include "tokens.hpp"
#include "tokenizer.hpp"
#include "parser.hpp"
#include "expressions.hpp"
#include "visitors.hpp"
#include "evaluator.hpp"
#include "common_values.hpp"

using namespace std;

int main()
{
    cout << "Lisp Interpreter by Jan Jones" << endl << endl;

    tlist tokens;
    common_values com;
    evaluator e(com);
    while (cin.good() && !cin.eof())
    {
        // tokenize user's input (until closing brackets match opening ones)
        cout << "< ";
        for (string line; getline(cin, line);) {
            stringstream ss(line);
            tokenizer(tokens).tokenize(ss);

            // check brackets' pairing
            if (count_if(tokens.begin(), tokens.end(), [](tp& t) { return t->is_left_paren(); })
                <= count_if(tokens.begin(), tokens.end(), [](tp& t) { return t->is_right_paren(); })) {
                break;
            }
            cout << ". ";
        }

        if (tokens.empty()) { continue; }

        parser p(tokens, com);
        do {
            // parse
            vp expr;
            try {
                expr = p.parse();
            }
            catch (const parser_error& e) {
                cerr << "Parsing error: " << e.what() << endl;
                break;
            }

            // evaluate
            // TODO: actually, use "eval" func from the environment (and eval this "eval" function with evaluator with parsed expr as an argument)
            vp res;
            try {
                res = e.visit(expr);
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
