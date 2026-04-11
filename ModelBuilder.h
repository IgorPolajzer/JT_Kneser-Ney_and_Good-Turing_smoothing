//
// Created by igork on 11/04/2026.
//

#ifndef RV2_MODELBUILDER_H
#define RV2_MODELBUILDER_H
#include <cmath>
#include <string>

#include "Model.h"
#include "NGramAnalyzer.h"

namespace ModelBuilder {
    inline Model buildKneserGlay(const std::string& corpusPath, int nGramSize) {
    }

    inline Model buildGoodTuring(const std::string& corpusPath, int nGramSize) {
        const auto nGrams = NGramAnalyzer::getNgramFrequencies(corpusPath, nGramSize);


        Model model;
        for (const auto& nGram : nGrams) {
            // N_c = število stvari, ki so se pojavile točno c-krat.
            // Za videne stvari: Pgt = C*/N; C*=((c+1) * Nc + 1) / Nc
            // Za nevidene stvari: Pgt = N1/N

            int Nc = 0;
            for (const auto& nGramCtr : nGrams) if (nGramCtr.second == nGram.second) Nc++;

            double c_star =((nGram.second + 1) * Nc + 1) / Nc;

            double frequency = log(c_star / nGrams.size());
            model.addEntry(nGram.first, frequency);
        }

        return model;
    }
}

#endif //RV2_MODELBUILDER_H