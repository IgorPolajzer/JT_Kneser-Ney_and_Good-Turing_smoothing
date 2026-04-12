//
// Created by igork on 10/04/2026.
//

#ifndef RV2_N_GRAM_GENERATOR_H
#define RV2_N_GRAM_GENERATOR_H
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

#include "Util.h"

namespace NGramProcessor {

    inline std::string removePunctuations(std::string &s) {
        std::string result;
        for (size_t i = 0; i < s.length(); i++) {
            const char c = s[i];

            // Check for nGram tags.
            if (std::isspace(c) || c == '<' && s.length() - i >= 4) {
                std::string plausibleStartTag = s.substr(i, 4);
                std::string plausibleEndTag = s.substr(i, 5);


                if (plausibleStartTag == Util::SENTENCE_BEGIN_TAG) {
                    result += plausibleStartTag;
                    i += plausibleStartTag.length() - 1;
                } else if (plausibleEndTag == Util::SENTECE_END_TAG) {
                    result += plausibleEndTag;
                    i += plausibleEndTag.length() - 1;
                }
            }

            if (!ispunct(c)) {
                result += c;
            }
        }
        s = result;
        return s;
    }

    inline std::unordered_map<std::string, int> getAllFromSentence(const size_t &n, const std::string &sentence) {
        std::vector<std::string> words = Util::senteceToWords(sentence);

        std::unordered_map<std::string, int> nGrams;
        bool end = false;

        for (size_t i = 0; i < words.size(); ++i) {
            std::string nGram;
            for (size_t j = 0; j < n; ++j) {
                if (words.size() <= j + i) {
                    if (!nGrams.empty()) {
                        end = true;
                    }

                    break;
                }
                const std::string &word = words[j + i];
                if (nGram.empty()) nGram += word;
                else nGram += " " + word;
            }
            if (end) break;

            if (nGrams.contains(nGram)) nGrams[nGram]++;
            else nGrams[nGram] = 1;
        }

        return nGrams;
    }

    inline std::string popFirstWordOFNgram(std::string nGram) {
        std::vector<std::string> nGramWords = Util::senteceToWords(nGram);

        if (!nGramWords.empty()) {
            nGramWords.erase(nGramWords.begin());
        }

        return Util::wordsToSentence(nGramWords);
    }

    inline std::vector<std::pair<std::string, int>> getNgramFrequencies(const std::string &filePath, size_t nGramSize) {
        std::ifstream fileStream(filePath);

        if (!fileStream.is_open()) {
            std::cerr << "Unable to open file: " << filePath << std::endl;
            return {};
        }

        // Read file into a string representation.
        std::ostringstream buffer;
        buffer << fileStream.rdbuf();
        std::string stringFile = buffer.str();

        // Parse string into sentences (Splits text by \n . ! ?).
        std::vector<std::string> sentences = Util::stringToSentences(stringFile);

        // Process sentences into n-grams.
        std::unordered_map<std::string, int> nGrams;

        for (std::string &s: sentences) {
            // Remove punctuations.
            std::string strippedSentence = removePunctuations(s);

            // Generate n-grams (word n-grams).
            std::unordered_map<std::string, int> sentenceNgrams = getAllFromSentence(nGramSize, strippedSentence);
            Util::concatenateMaps(nGrams, sentenceNgrams);
        }

        return Util::mapToSortedVect(nGrams);
    }

    inline std::pair<std::string, std::vector<std::string>> splitNGramContext(const std::string &nGram) {
        auto words = Util::senteceToWords(nGram);
        if (words.empty()) return {"", {}};

        // Zadnja beseda je b_i
        std::string lastWord = words.back();

        // Kontekst so vse besede pred zadnjo (b_{i-n+1} do b_{i-1})
        words.pop_back();
        std::vector<std::string> preceedingContext = words;

        return {lastWord, preceedingContext};
    }
};

#endif //RV2_N_GRAM_GENERATOR_H
