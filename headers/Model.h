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
    int n;
    double unseenProbability = 0.0;

    static constexpr std::string_view HEADER_N = "#N:";
    static constexpr std::string_view HEADER_UNSEEN = "#UNSEEN:";

    public:
    static constexpr std::string UNKNOWN = "<UNK>";

    Model(const int n) : n(n) {}
    Model() = default;

    [[nodiscard]] std::vector<std::pair<std::string, double>> getEntries() const { return entries; }
    [[nodiscard]] int getN() const { return n; }
    [[nodiscard]] double getUnseenProbability() const { return unseenProbability; }

    void setN(const int n) { this->n = n; }
    void setUnseenProbability(const double p) { unseenProbability = p; }

    void addEntry(const std::string& nGram, const double frequency) {
        if (getN() && nGram != UNKNOWN) {
            setN(Util::senteceToWords(nGram).size());
        }
        entries.emplace_back(nGram, frequency);
    }

    void sort() {
        std::ranges::sort(entries, Util::cmp<double>);
    }

    void saveToFile(const std::string& modelPath) const {
        std::ofstream file(modelPath);
        if (!file.is_open()) {
            std::cout << "Could not open file " << modelPath << std::endl;
            return;
        }

        for (const auto& entry : entries) {
            file << entry.first << ":" << std::fixed << std::setprecision(20) << entry.second << "\n";
        }
    }

    static Model loadFromFile(const std::string& modelPath) {
        std::ifstream file(modelPath);
        if (!file.is_open()) {
            std::cout << "Could not open file " << modelPath << std::endl;
            return {};
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