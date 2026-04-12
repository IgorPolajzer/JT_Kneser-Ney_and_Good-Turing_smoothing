#include <iostream>

#include "headers/ModelBuilder.h"
#include "headers/Predictor.h"

int main(int argc, char* argv[]) {

    if (argc < 2) {
        std::cout << "Usage: -g/-p";
        return 0;
    }

    const std::string mode = argv[1];

    // Generate.
    if (mode == "-g") {
        if (argc < 5) {
            std::cout << "Usage: -g -gt/-kn [n] [corpus-file-path] [model-save-path]";
            return 0;
        }

        const std::string modelStrategy = argv[2];
        const int n = std::stoi(argv[3]);
        const std::string corpusPath = argv[4];
        const std::string modelSavePath = argv[5];

        Model model;
        if (modelStrategy == "-gt") {
            model = ModelBuilder::buildGoodTuring(corpusPath, n);
        } else if (modelStrategy == "-kn") {

        } else {
            std::cout << "Smoothing '" << modelStrategy << "'not supported. Pick Good Turing '-gt' or Kneser-Nay '-kn'" << std::endl;
            return 0;
        }

        model.saveToFile(modelSavePath);

    // Predict.
    } else if (mode == "-p") {
        if (argc < 3) {
            std::cout << "Usage: -p [model-save-path]";
            return 0;
        }

        const std::string modelPath = argv[2];
        const int M = 5;
        std::string sentece;

        std::cout << "Input sentence: ";
        std::cin >> sentece;

        Model model = Model::loadFromFile(modelPath);
        Predictor::predict(model, sentece, M);
    }

    return 0;
}
