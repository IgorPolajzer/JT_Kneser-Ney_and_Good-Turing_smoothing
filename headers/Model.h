//
// Created by igork on 11/04/2026.
//

#ifndef RV2_MODEL_H
#define RV2_MODEL_H
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>

#include "Util.h"

class Model {
    /* Example:
        "I am" → {
            "happy": 0.5,
            "tired": 0.3,
            "here": 0.2
        }
    */
    std::vector<std::pair<std::string, double>> entries;


    public:

    void sort() {
        std::ranges::sort(entries, Util::cmp<double>);
    }

    void addEntry(const std::string& name, const double value) {
        entries.emplace_back(name, value);
    }

    void saveToFile(const std::string& modelPath) const {
        std::ofstream file(modelPath);

        if (!file.is_open()) {
            std::cout << "Could not open file " << modelPath << std::endl;
        }

        for (const auto& entry : entries) {
            file << entry.first << ":" << std::fixed << std::setprecision(20) << entry.second << "\n";
        }
    }

    static Model loadFromFile(const std::string& modelPath) {
        std::ifstream file(modelPath);

        if (!file.is_open()) {
            std::cout << "Could not open file " << modelPath << std::endl;
        }


        Model model;
        std::string line;
        while (std::getline(file, line)) {
            const int delimitIndex = line.find(':');

            std::string nGram = line.substr(0, delimitIndex);
            const double frequency = std::stod(line.substr(delimitIndex + 1));

            model.addEntry(nGram, frequency);
        }

        return model;
    }
};

#endif //RV2_MODEL_H