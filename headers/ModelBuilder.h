//
// Created by igork on 11/04/2026.
//

#ifndef RV2_MODELBUILDER_H
#define RV2_MODELBUILDER_H
#include <string>

#include "Model.h"
#include "NGramAnalyzer.h"

namespace ModelBuilder {

    inline Model buildKneserGlay(const std::string& corpusPath, int nGramSize) {
    }

    inline Model buildGoodTuring(const std::string& corpusPath, int nGramSize) {
        const auto nGrams = NGramAnalyzer::getNgramFrequencies(corpusPath, nGramSize);

        // Total token count (N).
        long N = 0;
        for (const auto& ng : nGrams) N += ng.second;

        Model model(nGramSize);
        for (const auto& nGram : nGrams) {
            const int c = nGram.second;

            // Count n-grams with frequency c (Nc) and c+1 (Nc+1).
            int Nc = 0, Nc_plus_1 = 0;
            for (const auto& other : nGrams) {
                if (other.second == c)     Nc++;
                if (other.second == c + 1) Nc_plus_1++;
            }

            double c_star;
            if (Nc_plus_1 == 0)
                c_star = c; // fallback, no smoothing if Nc+1 is zero
            else
                c_star = static_cast<double>(c + 1) * Nc_plus_1 / Nc;

            double frequency = c_star / N;
            model.addEntry(nGram.first, frequency);
        }

        model.sort();

        return model;
    }
}

#endif //RV2_MODELBUILDER_H