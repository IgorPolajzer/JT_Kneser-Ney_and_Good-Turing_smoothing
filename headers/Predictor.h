//
// Created by igork on 12/04/2026.
//

#ifndef RV2_PREDICTOR_H
#define RV2_PREDICTOR_H
#include <optional>

#include "Model.h"
#include "NGramProcessor.h"
#include <string>

namespace Predictor {

    inline std::string predictWord(const Model& model, const std::vector<std::string>& words) {
        if (model.getN() == 0) {
            std::cout << "Model doesn't have N set." << std::endl;
            return "";
        }

        std::optional<std::pair<std::string, double>> bestCandidate;

        for (int contextSize = model.getN() - 1; contextSize >= 0; --contextSize) {
            if (contextSize > 0 && words.size() < contextSize) continue;

            const std::string context = contextSize > 0 ? Util::minusNwordsToSentece(words, contextSize) : "";

            for (const auto& nGramEntry : model.getEntries()) {
                if (nGramEntry.first == Model::UNKNOWN) continue;

                auto nGramWords = Util::senteceToWords(nGramEntry.first);
                
                if (nGramWords.size() != contextSize + 1) continue;

                std::vector prefixWords(nGramWords.begin(), nGramWords.begin() + contextSize);
                std::string prefix = Util::wordsToSentence(prefixWords);

                if (prefix == context) {
                    if (!bestCandidate || nGramEntry.second > bestCandidate->second) {
                        bestCandidate = nGramEntry;
                    }
                }
            }

            if (bestCandidate) break;
        }

        if (bestCandidate.has_value()) {
            return Util::senteceToWords(bestCandidate->first).back();
        }

        // Fallback to the most occurring word in the model.
        for (const auto& entry : model.getEntries()) {
            if (entry.first != Model::UNKNOWN) {
                return Util::senteceToWords(entry.first).back();
            }
        }
        
        return Model::UNKNOWN;
    }

    inline std::string predictWords(const Model& model, const std::string& sentence, const int M) {
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