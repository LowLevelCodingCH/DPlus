#include <unordered_map>
#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <fstream>
#include <cstdlib>
#include <stdio.h>
#include <string>
#include <random>

/*
 * KEYWORDS:
 *
 * "proc" "return" "exit" "write" "call" "alloc" "push" "pop"
 * "loop" "endloop" "times" "endtimes" "repeat" "do" "String"
 * "Int" "Bool" "true" "false" "read" "external" "open" "close"
 * "NString" "fwrite" "fread" "sof" "while" "endwhile" "if" "endif"
 * "scope" "mexpr" "pushptr"
 *
*/

std::string random_string(std::size_t length)
{
    const std::string CHARACTERS = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

    std::random_device random_device;
    std::mt19937 generator(random_device());
    std::uniform_int_distribution<> distribution(0, CHARACTERS.size() - 1);

    std::string random_string;

    for (std::size_t i = 0; i < length; ++i)
    {
        random_string += CHARACTERS[distribution(generator)];
    }

    return random_string;
}

#include "Lexing/lexer.hh"
#include "Lexing/syna.hh"
#include "Lexing/opt.hh"
#include "Lexing/scoper.hh"
#include "Lexing/shortenizer.hh"
#include "Parsing/parser.hh"
#include "Generating/agen.hh"
#include "Preprocessing/include.hh"

std::string dpgen = "DPLUS: db 1";

int main(int argc, char** argv){
  if(argc == 4){
	 if(strcmp(argv[2], "-o") != 0) exit(EXIT_FAILURE);
    Lexer*       lexer       = new Lexer();
    Syna*        syna        = new Syna();
    Agen*        agen        = new Agen();
    Opt*         opt         = new Opt();
    Scoper*      scoper      = new Scoper();
    Shortenizer* shortenizer = new Shortenizer();

    std::ifstream file(argv[1]);
    std::stringstream program;
    if (!file.is_open()) {
        std::cerr << "[DPC-ERROR]: Error opening file." << std::endl;
        exit(1);
    }
    std::string line;
    while (std::getline(file, line)) {
       size_t lp = line.find_first_not_of(" \t");
       std::string lineN = (lp == std::string::npos) ? "" : line.substr(lp);
       if (lineN.rfind("#import ", 0) == 0) {
           program << HandleInclude(lineN.substr(8)) + "\n";
       } else if (lineN.rfind("//", 0) == 0) {} else {
           program << lineN << "\n";
       }
    }

    std::string code = program.str();

    if(0 == 0) {
      std::ofstream ofile(argv[3]);
      if (!ofile.is_open()) {
          std::cerr << "[DPC-ERROR]: Error opening file." << std::endl;
          exit(1);
      }
      // Lex, Analyze, Optimize, Scope, Parse, Generate, Shorten


      std::string assembly = agen->Generate(
        shortenizer->Shortenize(
            scoper->Scopenize(
                syna->Analyze(
                    opt->Optimize(
                        lexer->Lex(code)
                    )
                )
            )
        )
      );

	    ofile << "; D+ ASSEMBLY GENERATED\n";
      ofile << assembly << "\n";
      ofile << dpgen << "\n";

      ofile.close();
    } else {
      std::cerr << "[DPC-ERROR]: Wrong usage" << std::endl;
      std::cerr << "[USAGE]:     dpc <file>.dp -o <file>.s" << std::endl;
      std::cout << "[INFO]:      Prerequisites: nasm, cbuild" << std::endl;
    }
    delete lexer;
    delete syna;
    delete opt;
    delete shortenizer;
    delete agen;
    delete scoper;
    file.close();
  } else {
      std::cerr << "[DPC-ERROR]: Wrong usage" << std::endl;
      std::cerr << "[USAGE]:     dpc <file>.dp -o <file>.s" << std::endl;
      std::cout << "[INFO]:      Prerequisites: nasm, cbuild" << std::endl;
  }
}
