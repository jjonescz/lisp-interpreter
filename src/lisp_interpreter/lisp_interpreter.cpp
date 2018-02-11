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
    cout << "Lisp Interpreter by Jan Jones (2018)" << endl << endl;

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
            vp value;
            try {
                value = p.parse();
            }
            catch (const parser_error& e) {
                cerr << "Parsing error: " << e.what() << endl;
                break;
            }

            // wrap expression inside eval call, so that evaluation
            // can be effectively overwritten by the running program
            value = make_shared<e_pair>(com.eval_token, make_shared<e_pair>(
                make_shared<e_pair>(com.quote_token, make_shared<e_pair>(move(value), com.nil_token)), com.nil_token));

            // evaluate
            try {
                value = e.visit(move(value));
            }
            catch (const eval_error& e) {
                cerr << "Evaluation error: " << e.what() << endl;
                break;
            }

            // print
            printer(cout).visit(move(value));
            cout << endl;
        } while (!tokens.empty());

        tokens.clear();
    }

    cout << endl;
    return 0;
}
