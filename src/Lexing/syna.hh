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
 * POKE takes args and these are ADR and TO_SET
 * parenthesis "[]{}()" should have a closing partner that should be calculated
*/

struct Syna {
  std::vector<Token> Analyze(std::vector<Token> tokens) {
    std::cout << "[INFO]: Analyzing" << std::endl;
    return tokens;
  }
};

#endif // SYNA_H_
