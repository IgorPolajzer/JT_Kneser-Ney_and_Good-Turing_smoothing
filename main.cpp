#include <iostream>

#include "headers/ModelBuilder.h"
#include "headers/Perplexity.h"
#include "headers/Predictor.h"

int main(int argc, char* argv[]) {

    if (argc < 2) {
        std::cout << "Usage: -g/-p/-mp";
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
            model = ModelBuilder::buildKneserNey(corpusPath, n);
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

        std::string sentence;
        std::cout << "Input sentence: ";
        std::getline(std::cin, sentence);

        const Model model = Model::loadFromFile(modelPath);
        std::string predictedSentence = Predictor::predictWords(model, sentence, M);
        std::cout << "Izhod: " << predictedSentence << std::endl;

    // Model perplexity.
    } else if (mode == "-mp") {
        if (argc < 4) {
            std::cout << "Usage: -mp [model-path] [corpus-path]";
            return 0;
        }

        std::string modelPath = argv[2];
        std::string corpusPath = argv[3];

        Model model = Model::loadFromFile(modelPath);
        const double perplexity = Perplexity::compute(model, corpusPath);
        std::cout << "Perplexity: " << std::fixed << std::setprecision(20) << perplexity << std::endl;
    }

    return 0;
}
