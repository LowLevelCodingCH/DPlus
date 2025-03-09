#ifndef SCOPER_H
#define SCOPER_H

struct Scope {
    std::vector<Token> tokens;
    std::string        permisee;

    void clear() {
        this->tokens.clear();
        this->permisee = "";
    }
};

struct Scoper {
    std::vector<Scope> Scopenize(std::vector<Token> tokens){
        std::cout << "[INFO]: Scoping" << std::endl;
        std::vector<Scope> scopes;

        Scope default_scope = {};
        bool scope_begin = false;
        Scope scope;
        for(int i = 0; i < tokens.size(); i++) {
            if(tokens[i].value == "proc") {
                scope.permisee = tokens[i+1].value;
                scope_begin = true;
                i+=3;
            }
            if(tokens[i].value == "scope") {
                scope.permisee = random_string(10);
                scope_begin = true;
                i+=1;
            }
	    if(scope_begin) {
                if(tokens[i].kind == Token_Kind::CLOSED_BRACE) {
                    scope_begin = false;
                    scopes.push_back(scope);
                    scope.clear();
                }
                scope.tokens.push_back(tokens[i]);
            } else {
                default_scope.tokens.push_back(tokens[i]);
            }
        }

        return scopes;
    }
};

#endif // SCOPER_H
