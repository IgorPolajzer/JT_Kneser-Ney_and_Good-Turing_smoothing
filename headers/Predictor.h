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

    inline std::string predictWord(const Model& model, const std::vector<std::string>& words) {
        if (!model.getN()) {
            std::cout << "Model doesn't have N set." << std::endl;
            return "";
        }

        int NMinusOne = model.getN() - 1;
        std::optional<std::pair<std::string, double>> bestCandidate;

        while (!bestCandidate && NMinusOne > 0) {
            const std::string lastWords = Util::minusNwordsToSentece(words, NMinusOne);

            for (const auto& nGram : model.getEntries()) {
                const std::string nMinusOneWords = NGramAnalyzer::constructNMinusOneGrams(nGram);
                if (nMinusOneWords == lastWords && (!bestCandidate || bestCandidate->second < nGram.second)) {
                    bestCandidate = nGram;
                }
            }
            NMinusOne--;
        }

        if (bestCandidate.has_value()) {
            return Util::senteceToWords(bestCandidate->first).back();
        }

        // Unseen value <UNK>. Fallback to the most occurring word.
        return Util::senteceToWords(model.getEntries().front().first).back();
    }

    inline std::string predictWords(const Model& model, const std::string& sentence, int M) {
        std::cout << "Vhod: " << sentence << std::endl;
        std::cout << "Vmesni rezultati: " << std::endl;
        std::vector<std::string> words = Util::senteceToWords(sentence);

        for (int i = 0; i < M; i++) {
            const std::string nextWord = predictWord(model, words);
            if (nextWord.empty()) break;
            words.push_back(nextWord);
            std::cout << words.back() << std::endl;
        }

        return Util::wordsToSentence(words);
    }
}

#endif //RV2_PREDICTOR_H