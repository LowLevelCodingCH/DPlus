#ifndef SYNA_H_
#define SYNA_H_

/* NOTE: Rules
 *
 * procedure declaration (keyword: "proc") must follow a word                                       //NOTE: Finished
 * return shall not follow any value                                                                //NOTE: Finished
 * exit MUST return an integer                                                                      //NOTE: Finished
 * Structure of vars must be TYPE NAME = VALUE;                                                     //NOTE: Finished
 * CALL must have 1 arg                                                                             //NOTE: Finished
 * Inside of "alloc();" there must be an integer and also in PUSH() and pushptr;                    //NOTE: Finished
 * POP doesnt take any args                                                                         //NOTE: Finished
 * parenthesis "[]{}()" should have a closing partner that should be calculated
*/

struct Syna{
  std::vector<Token> Analyze(std::vector<Token> tokens) {
    std::cout << "[INFO]: Analyzing" << std::endl;
    std::vector<Token> result;
    for(size_t i = 0; i < tokens.size(); ++i) {
      if (tokens[i].kind == Token_Kind::KEYWORD) {
        if(tokens[i].value == "external") {
          if(tokens[i+1].kind != Token_Kind::WORD) {
            std::cerr << "[SYNA-ERROR]: {At: " << i << "} External reference to `not` word" << std::endl;
            exit(1);
          }
        }

        if(tokens[i].value == "sof"){
            if(tokens[i+1].kind != Token_Kind::OPEN_PARENTHESIS ||
            tokens[i+3].kind != Token_Kind::COMMA ||
            tokens[i+2].kind != Token_Kind::WORD ||
            tokens[i+4].kind != Token_Kind::WORD) {
              std::cerr << "[SYNA-ERROR] {At: " << i << "} SOF doesnt follow: `sof(var count, char* buffer)`" << std::endl;
              exit(1);
            }
        }

        if(tokens[i].value == "loop") {
          if(tokens[i+1].value != "do") {
            std::cerr << "[SYNA-ERROR]: {At: " << i << "} no `do` after `loop` statement" << std::endl;
            exit(1);
          }
        }

        if(tokens[i].value == "while"){
          if(tokens[i+1].value != "repeat") {
            std::cerr << "[SYNA-ERROR]: {At: " << i << "} no `repeat` after `while` statement" << std::endl;
            exit(1);
          }
        }

        if(tokens[i].value == "endwhile"){
          if(!IsAssertion(tokens[i+2].kind, tokens[i+3].kind)){
              std::cerr << "[SYNA-ERROR]: {At: " << i << "} `endwhile` does not follow: `endwhile X <assertion> Y`" << std::endl;
              exit(1);
          }
        }

        if(tokens[i].value == "if"){
          if(tokens[i+1].value != "do") {
            std::cerr << "[SYNA-ERROR]: {At: " << i << "} no `do` after `if`" << std::endl;
            exit(1);
          }
        }

        if(tokens[i].value == "endif"){
          if(!IsAssertion(tokens[i+2].kind, tokens[i+3].kind)){
            std::cerr << "[SYNA-ERROR]: {At: " << i << "} `endif` does not follow: `endif X <assertion> Y`" << std::endl;
            exit(1);
          }
        }

        if(tokens[i].value == "times"){
          if(tokens[i+2].value != "repeat") {
            std::cerr << "[SYNA-ERROR]: {At: " << i << "} `times` keyword does not follow integer and `repeat`" << std::endl;
            exit(1);
          }
        }

        // Rule 7: * POP doesnt take any args

        if(tokens[i].value == "pop"){
          if(tokens[i+1].kind != Token_Kind::OPEN_PARENTHESIS ||
          tokens[i+2].kind != Token_Kind::CLOSED_PARENTHESIS) {
            std::cerr << "[SYNA-ERROR]: {At: " << i << "} POP does not equal: `pop()`" << std::endl;
            exit(1);
          }
        }

        // Rule 6: * Inside of "alloc();" there must be an integer and also in PUSH(); and pushptr

        if(tokens[i].value == "alloc") {
          if(tokens[i+2].kind != Token_Kind::INTEGER_LITERAL){
            std::cerr << "[SYNA-ERROR]: {At: " << i << "} Allocation does not have integer argument" << std::endl;
            exit(1);
          }
        }

        if(tokens[i].value == "push") {
          if(tokens[i+2].kind != Token_Kind::INTEGER_LITERAL && tokens[i+2].kind != Token_Kind::WORD){
            std::cerr << "[SYNA-ERROR]: {At: " << i << "} Pushing does not have integer or var argument" << std::endl;
            exit(1);
          }
        }

        if(tokens[i].value == "pushptr") {
          if(tokens[i+2].kind != Token_Kind::WORD){
            std::cerr << "[SYNA-ERROR]: {At: " << i << "} Pushing a pointer does not have var argument" << std::endl;
            exit(1);
          }
        }

        // Rule 5: * CALL must have 1 arg

        if (tokens[i].value == "call") {
          if (tokens[i+2].kind != Token_Kind::WORD ||
              tokens[i+1].kind != Token_Kind::OPEN_PARENTHESIS ||
              tokens[i+3].kind != Token_Kind::CLOSED_PARENTHESIS) {
              std::cerr << "[SYNA-ERROR]: {At: " << i << "} Call does not have structure: call(PROC)" << std::endl;
              exit(1);
            }
        }

        // Rule 1: * procedure declaration (keyword: "proc") must follow a word

        if (tokens[i].value == "proc") {
          if (tokens[i+1].kind != Token_Kind::WORD) {
            std::cerr << "[SYNA-ERROR]: {At: " << i << "} Procedure declaration does not follow a word" << std::endl;
            exit(1);
          }
        }

        // Rule 2: * return shall not follow any value

        if (tokens[i].value == "return") {
          if (tokens[i+1].value != "") {
            std::cerr << "[SYNA-ERROR]: {At: " << i << "} Value cannot be after a Return statement" << std::endl;
            exit(1);
          }
        }

        // Rule 3: * exit MUST return an integer

        if (tokens[i].value == "exit") {
          if(tokens[i+1].kind != Token_Kind::OPEN_PARENTHESIS ||
             tokens[i+3].kind != Token_Kind::CLOSED_PARENTHESIS) {
            std::cerr << "[SYNA-ERROR]: {At: " << i << "} Exit must follow this: `(`, integer/variable (int), `)`" << std::endl;
            exit(1);
          }
        }
      }

      // Rule 4: * Structure of vars must be TYPE NAME = VALUE;

      if (tokens[i].kind == Token_Kind::TYPE) {
        if (tokens[i+1].kind != Token_Kind::WORD ||
            tokens[i+2].kind != Token_Kind::EQUAL) {
          std::cerr << "[SYNA-ERROR]: {At: " << i << "} Type must follow this:\n  type name = value" << std::endl;
          exit(1);
        }
      }

      if (tokens[i].kind == Token_Kind::TYPE && tokens[i].value == "Bool") {
        if (tokens[i+1].kind != Token_Kind::WORD ||
            tokens[i+2].kind != Token_Kind::EQUAL) {
          std::cerr << "[SYNA-ERROR]: {At: " << i << "} Type must follow this: type, name, `=`, value" << std::endl;
          exit(1);
            }
      }


      result.push_back(tokens[i]);
    }
    return result;
  }
};

#endif // SYNA_H_
