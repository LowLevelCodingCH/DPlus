#ifndef OPT_H_
#define OPT_H_

struct Opt {
    std::vector<Token> Optimize(std::vector<Token> tokens) {
        std::cout << "[INFO]: Optimizing" << std::endl;
        std::vector<Token> result;

        for(int i = 0; i < tokens.size(); i++) {
            result.push_back(tokens[i]);
        }

        return result;
    }
};

#endif
