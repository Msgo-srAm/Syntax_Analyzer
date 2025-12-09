#include <iostream>
#include <fstream>
#include "Parser.hpp"

int main(int argc, char *argv[]) {
    if (argc < 3) {
        std::cout << "Usage: " << argv[0] << " <input_file> <output_file>" << std::endl;
        return 1;
    }
    Parser parser(argv[1]);
    if (parser.parse()) parser.printReduceStack(argv[2]);
    return 0;
}