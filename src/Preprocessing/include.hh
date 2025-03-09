#ifndef INCLUDE_HH
#define INCLUDE_HH

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

std::string HandleInclude(std::string file){
    ifstream inputFile(file);

    if (!inputFile.is_open()) {
        cerr << "[ERROR]: No such file: " << file << endl;
        exit(1);
    }

    stringstream outstr;

    string line;

    while (getline(inputFile, line)) {
        outstr << line;
        outstr << "\n";
    }

    inputFile.close();

    return outstr.str();
}

#endif // INCLUDE_HH
