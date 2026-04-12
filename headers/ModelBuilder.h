// ModelBuilder.h
#ifndef RV2_MODELBUILDER_H
#define RV2_MODELBUILDER_H
#include <string>

#include "Model.h"
#include "NGramAnalyzer.h"

namespace ModelBuilder {

    inline Model buildKneserNey(const std::string& corpusPath, int nGramSize) {
    }

    inline Model buildGoodTuring(const std::string& corpusPath, int nGramSize) {
        const auto nGrams = NGramAnalyzer::getNgramFrequencies(corpusPath, nGramSize);

        long N = 0;
        for (const auto& ng : nGrams) N += ng.second;

        // Build frequency-of-frequency map (O(n) instead of O(n^2))
        std::unordered_map<int, int> freqOfFreq;
        for (const auto& ng : nGrams) freqOfFreq[ng.second]++;

        // Compute unseen probability: N1 / N
        const int N1 = freqOfFreq.count(1) ? freqOfFreq[1] : 0;
        const double unseenProbability = static_cast<double>(N1) / N;

        Model model(nGramSize);
        model.setUnseenProbability(unseenProbability);

        for (const auto& nGram : nGrams) {
            const int c = nGram.second;
            const int Nc       = freqOfFreq.count(c)     ? freqOfFreq[c]     : 0;
            const int Nc_plus1 = freqOfFreq.count(c + 1) ? freqOfFreq[c + 1] : 0;

            double c_star;
            if (Nc_plus1 == 0)
                c_star = c;
            else
                c_star = static_cast<double>(c + 1) * Nc_plus1 / Nc;

            const double frequency = c_star / N;
            model.addEntry(nGram.first, frequency);
        }

        model.sort();
        return model;
    }
}

#endif //RV2_MODELBUILDER_H