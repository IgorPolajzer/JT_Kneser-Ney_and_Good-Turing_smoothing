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

#include "NGramProcessor.h"
#include "Util.h"

class Model {
    // "I am" → { "happy": 0.5, "tired": 0.3, "here": 0.2 }
    std::vector<std::pair<std::string, double> > entries;

    // word1 word2 word3 -> word3 : { word1, word2 }
    std::unordered_map<std::string, std::vector<std::string>> entriesContext;

    // For faster lookups.
    std::unordered_map<std::string, double> entitiesProbabilities;

    int n;
    double unseenProbability = 0.0;

    std::pair<std::string, std::vector<std::string> > mapWordToContext(const std::string &word) {
        std::pair<std::string, std::vector<std::string> > result;
        std::vector<std::string> words = Util::senteceToWords(word);

        if (!words.empty()) {
            std::string contextWord = words.front();
            words.erase(words.begin());
            result = std::pair(contextWord, words);
        }

        return result;
    }

public:
    static constexpr std::string UNKNOWN = "<UNK>";

    Model(const int n=0) : n(n) {}

    [[nodiscard]] std::vector<std::pair<std::string, double>> getEntries() const { return entries; }
    [[nodiscard]] int getN() const { return n; }
    [[nodiscard]] double getUnseenProbability() const { return unseenProbability; }

    [[nodiscard]] double getEntityProbability(const std::string &nGram) const {
        auto it = entitiesProbabilities.find(nGram);
        if (it == entitiesProbabilities.end()) return 0.0;
        return it->second;
    }

    void setN(const int n) { this->n = n; }
    void setUnseenProbability(const double p) { unseenProbability = p; }

    static Model loadFromFile(const std::string &modelPath) {
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

            if (nGram == UNKNOWN) {
                model.setUnseenProbability(frequency);
            }
        }

        return model;
    }
    void saveToFile(const std::string &modelPath) const {
        std::ofstream file(modelPath);
        if (!file.is_open()) {
            std::cout << "Could not open file " << modelPath << std::endl;
            return;
        }

        for (const auto &entry: entries) {
            file << entry.first << ":" << std::fixed << std::setprecision(20) << entry.second << "\n";
        }
    }
    void sort() {
        std::ranges::sort(entries, Util::cmp<double>);
    }

    std::pair<std::string, double> findNGram(std::string nGram) const {
        for (const auto &entry: entries) {
            if (entry.first == nGram) {
                return entry;
            }
        }

        return {"", -1.0};
    }

    void addEntry(const std::string &nGram, const double frequency) {
        if (getN() == 0 && nGram != UNKNOWN) {
            int nGramSize = Util::senteceToWords(nGram).size();
            if (nGramSize > getN()) setN(nGramSize);
        }

        if (nGram == UNKNOWN) {
            setUnseenProbability(frequency);
        }

        entries.emplace_back(nGram, frequency);
        auto nGramContext = NGramProcessor::splitNGramContext(nGram);
        entriesContext[nGramContext.first] = nGramContext.second;
        entitiesProbabilities[nGram] = frequency;
    }
};

#endif //RV2_MODEL_H