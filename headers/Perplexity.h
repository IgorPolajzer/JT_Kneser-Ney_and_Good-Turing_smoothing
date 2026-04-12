//
// Created by igork on 12/04/2026.
//

#ifndef RV2_PERPLEXITY_H
#define RV2_PERPLEXITY_H
#include <string>
#include <cmath>

#include "Model.h"
#include "NGramProcessor.h"
#include "Util.h"

namespace Perplexity {
    inline double compute(const Model &model, const std::string &corpusPath) {
        // S - poved ali stavek
        // P(b1, ..., b2) - skupna verjetnost celotnega zaporedja besed
        // -1/N - normalizacija
        std::vector<std::string> sentences = Util::fileToSentecences(corpusPath);
        
        double logProbSum = 0.0;
        int totalNGrams = 0;
        int n = model.getN();

        if (n <= 0) return 0.0;

        for (std::string sentence : sentences) {
            std::string strippedSentence = NGramProcessor::removePunctuations(sentence);
            std::vector<std::string> words = Util::senteceToWords(strippedSentence);

            if (words.size() < n) continue;

            for (size_t i = 0; i <= words.size() - n; ++i) {
                std::string nGram = words[i];
                for (size_t j = 1; j < n; ++j) {
                    nGram += " " + words[i + j];
                }

                double prob = model.getEntityProbability(nGram);
                if (prob == 0.0) {
                    prob = model.getUnseenProbability();
                }

                // Protect against log(0) if model has 0 unseen probability
                if (prob > 0.0) {
                    logProbSum += std::log2(prob);
                    totalNGrams++;
                }
            }
        }

        if (totalNGrams == 0) return 0.0;

        // Perplexity = 2^(-1/N * sum(log2(P)))
        return std::pow(2.0, -logProbSum / totalNGrams);
    }
}

#endif //RV2_PERPLEXITY_H
