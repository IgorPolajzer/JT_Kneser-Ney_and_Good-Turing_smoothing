//
// Created by igork on 12/04/2026.
//

#ifndef RV2_PREDICTOR_H
#define RV2_PREDICTOR_H
#include <optional>

#include "Model.h"
#include "NGramAnalyzer.h"
#include <string>

namespace Predictor {

    /*Step 1:  context = "Mariboru"          → predicts "fakulteta"
         sentence = "Univerza v Mariboru fakulteta"

    Step 2:  context = "fakulteta"         → predicts "za"
             sentence = "Univerza v Mariboru fakulteta za"

    Step 3:  context = "za"                → predicts "elektrotehniko"
             sentence = "Univerza v Mariboru fakulteta za elektrotehniko"*/

    inline void predict(const Model& model, const std::string& sentence, int M) {

        for (int i = 0; i < M; i++) {
            std::string
        }
    }

    inline std::string predictWord(const Model& model, const std::vector<std::string>& words) {
        if (!model.getN()) {
            std::cout << "Thr provided model doesn't have the N set." << std::endl;
            return;
        }

        int NMinusOne = model.getN() - 1;
        std::optional<std::pair<std::string, double>> bestCandidate;

        while (!bestCandidate && NMinusOne > 0) {
            const std::string& lastWords = Util::minusNwordsToSentece(words, NMinusOne);

            for (const std::pair nGram : model.getEntries()) {
                const std::string nMinusOneWords = NGramAnalyzer::constructNMinusOneGrams(nGram);

                if (nMinusOneWords == lastWords && (!bestCandidate || bestCandidate->second < nGram.second)) {
                    bestCandidate = nGram;
                }
            }

            NMinusOne--;
        }

        if (bestCandidate.has_value()) {
            std::cout << bestCandidate.value().first << ":" << bestCandidate.value().second << std::endl;
        } else {
            //bestCandidate = ;
        }

        return bestCandidate.value();
    }
}

#endif //RV2_PREDICTOR_H