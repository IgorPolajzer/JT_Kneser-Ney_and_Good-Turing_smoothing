#include <iostream>

#include "ModelBuilder.h"
#include "NGramAnalyzer.h"

int main(int argc, char* argv[]) {

    if (argc < 3) {
        std::cout << "Usage: -gt/-kn [n] [corpus-file-path]";
        return 0;
    }

    std::string modelStrategy = argv[1];
    size_t n = std::stoi(argv[2]);
    std::string corpusPath = argv[3];



    if (modelStrategy == "-gt") {
        ModelBuilder::buildKneserGlay(corpusPath, n);
    } else if (modelStrategy == "-kn") {

    } else {
        std::cout << "Smoothing '" << modelStrategy << "'not supported. Pick Good Turing '-gt' or Kneser-Nay '-kn'" << std::endl;
    }


    return 0;
}
