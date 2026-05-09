//
// Created by igork on 11/04/2026.
//

#ifndef RV2_MODELBUILDER_H
#define RV2_MODELBUILDER_H
#include <cmath>
#include <set>
#include <string>

#include "Model.h"
#include "NGramProcessor.h"

namespace ModelBuilder {

    constexpr double D = 0.75;

    inline double calculateKneserNeyProbability(const std::string& nGram,
                                                const std::unordered_map<std::string, int>& allNGrams,
                                                const std::unordered_map<std::string, std::set<std::string>>& historyFollowers,
                                                const std::unordered_map<std::string, std::set<std::string>>& contextHistory,
                                                int totalUniqueBigrams,
                                                int nGramSize) {
        if (nGramSize == 1) {
            auto it = contextHistory.find(nGram);
            double uniqueContextsForWord = it != contextHistory.end() ? it->second.size() : 0.0;
            return std::max(uniqueContextsForWord, 0.1) / (totalUniqueBigrams > 0 ? totalUniqueBigrams : 1.0);
        }

        auto nGramContext = NGramProcessor::splitNGramContext(nGram);

        double numerator = std::max(static_cast<double>(allNGrams.at(nGram)) - D, 0.0);

        std::string history = Util::wordsToSentence(nGramContext.second);
        double lambda = D / allNGrams.at(history) * historyFollowers.at(history).size();

        std::string nMinusOneGram = NGramProcessor::popFirstWordOFNgram(nGram);

        return numerator / allNGrams.at(history) + lambda *
            calculateKneserNeyProbability(nMinusOneGram, allNGrams, historyFollowers, contextHistory, totalUniqueBigrams, nGramSize - 1);
    }

    inline Model buildKneserNey(const std::string& corpusPath, int nGramSize) {
        std::unordered_map<std::string, int> allNGrams;
        Model model(nGramSize);

        // Compute the necessary values for all n grams.
        std::unordered_map<std::string, std::set<std::string>> contextHistory;
        std::unordered_map<std::string, std::set<std::string>> historyFollowers;

        for (int i = 1; i <= nGramSize; i++) {
            const auto nGrams = NGramProcessor::getNgramFrequencies(corpusPath, i);

            for (const auto& nGram : nGrams) {
                auto nGramContext = NGramProcessor::splitNGramContext(nGram.first);

                if (!nGramContext.second.empty()) {
                    contextHistory[nGramContext.first].emplace(nGramContext.second.back());
                    std::string history = Util::wordsToSentence(nGramContext.second);
                    historyFollowers[history].emplace(nGramContext.first);
                }

                allNGrams[nGram.first] = nGram.second;
            }
        }

        int totalUniqueBigrams = 0;
        for (const auto& [key, val] : contextHistory) {
            totalUniqueBigrams += val.size();
        }

        for (const auto& [nGram, freq] : allNGrams) {
            int currentN = Util::senteceToWords(nGram).size();
            double probability = calculateKneserNeyProbability(nGram, allNGrams, historyFollowers, contextHistory, totalUniqueBigrams, currentN);
            model.addEntry(nGram, probability);
        }

        model.sort();
        return model;
    }

    inline Model buildGoodTuring(const std::string& corpusPath, const int nGramSize) {
        const auto nGrams = NGramProcessor::getNgramFrequencies(corpusPath, nGramSize);

        double N = 0; // Total n-gram count (sum of frequencies).
        for (const auto& ng : nGrams) N += ng.second;

        Model model(nGramSize);
        int N1 = 0;
        for (const auto& nGram : nGrams) {
            const int c = nGram.second; // nGram Frequency.

            // Count items which occur once.
            if (c == 1) N1++;

            double c_star = static_cast<double>(c) - D;
            double Pgt = c_star / N;
            model.addEntry(nGram.first, Pgt);
        }

        // Probability for unknown tokens.
        const double Pgt_unk = static_cast<double>(N1) / N;

        model.addEntry(Model::UNKNOWN, Pgt_unk);
        model.setUnseenProbability(Pgt_unk);

        model.sort();
        return model;
    }
}

#endif //RV2_MODELBUILDER_H