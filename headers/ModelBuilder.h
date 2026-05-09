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

        long N = 0;
        for (const auto& ng : nGrams) N += ng.second;

        // Calculate Vocabulary Size (V) to find N0 (number of unseen n-grams)
        std::set<std::string> vocabulary;
        for (const auto& ng : nGrams) {
            auto words = Util::senteceToWords(ng.first);
            for (const auto& w : words) {
                vocabulary.insert(w);
            }
        }
        
        double N0 = 1;

        Model model(nGramSize);
        int N1 = 0;
        for (const auto& nGram : nGrams) {
            const int c = nGram.second;

            // Count items which occur once.
            if (c == 1) {
                N1++;
            }

            // Count n-grams with frequency c (Nc) and c+1 (Nc+1).
            int Nc = 0, Nc_plus_1 = 0;
            for (const auto& other : nGrams) {
                if (other.second == c)     Nc++;
                if (other.second == c + 1) Nc_plus_1++;
            }

            double c_star;
            if (Nc_plus_1 == 0) {
                c_star = c;
            }
            else {
                c_star = static_cast<double>(c + 1) * Nc_plus_1 / Nc;
            }

            double frequency = c_star / N;
            model.addEntry(nGram.first, frequency);
        }

        // Add probability for <UNK> to the end.
        // Unseen mass (N1/N) is divided by N0 (number of unseen n-grams) 
        // to get the probability of a SINGLE unseen n-gram.
        const double totalUnseenProbMass = static_cast<double>(N1) / static_cast<double>(N);
        const double unkProb = totalUnseenProbMass / N0;
        
        model.addEntry(Model::UNKNOWN, unkProb);
        model.setUnseenProbability(unkProb);

        model.sort();
        return model;
    }
}

#endif //RV2_MODELBUILDER_H