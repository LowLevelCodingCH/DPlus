#ifndef SHORTENIZER_H_
#define SHORTENIZER_H_

#include <vector>

using namespace std;

struct Shortenizer{
    vector<Scope> Shortenize(vector<Scope> scopes) {
        vector<Scope> result;

        for(Scope scope : scopes) {
            if(scope.tokens[1].kind == Token_Kind::CLOSED_BRACE) {
                scope.tokens[1].value == "";
            }
            result.push_back(scope);
        }

        return result;
    }
};

#endif // SHORTENIZER_H_
