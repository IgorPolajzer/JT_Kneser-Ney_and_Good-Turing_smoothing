//
// Created by igork on 10/04/2026.
//

#ifndef RV2_N_GRAM_GENERATOR_H
#define RV2_N_GRAM_GENERATOR_H
#include <fstream>
#include <iostream>
#include <regex>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

#include "Util.h"

namespace NGramAnalyzer {
    static constexpr std::string N_GRAM_BEGIN_TAG = "<s> ";
    static constexpr std::string N_GRAM_END_TAG = " </s>";

    inline std::string removePunctuations(std::string &s) {
        std::string result;
        for (size_t i = 0; i < s.length(); i++) {
            const char c = s[i];

            // Check for nGram tags.
            if (std::isspace(c) || c == '<' && s.length() - i >= 4) {
                std::string plausibleStartTag = s.substr(i, 4);
                std::string plausibleEndTag = s.substr(i, 5);


                if (plausibleStartTag == N_GRAM_BEGIN_TAG) {
                    result += plausibleStartTag;
                    i += plausibleStartTag.length() - 1;
                } else if (plausibleEndTag == N_GRAM_END_TAG) {
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

    inline std::vector<std::string> parseSentences(const std::string &s) {
        static const std::regex sentenceRegex(R"((\n+|[.!?]\s+))");
        std::sregex_token_iterator iter(s.begin(), s.end(), sentenceRegex, -1);
        std::sregex_token_iterator end;
        std::vector<std::string> sentences = {iter, end};

        for (std::string &sentence: sentences) {
            std::string taggedSentece = N_GRAM_BEGIN_TAG + sentence + N_GRAM_END_TAG;
            sentence = taggedSentece;
        }

        return sentences;
    }

    inline std::unordered_map<std::string, int> getNgrams(const size_t &n, const std::string &sentence) {
        std::vector<std::string> tokens;

        std::stringstream ss(sentence);
        std::vector<std::string> words;
        std::string word;

        while (ss >> word) {
            words.push_back(word);
        }

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

            if (nGrams.find(nGram) != nGrams.end()) nGrams[nGram] = 1;
            else nGrams[nGram]++;
        }

        return nGrams;
    }

    inline std::vector<std::pair<std::string, int>> getNgramFrequencies(const std::string &filePath, size_t n) {
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
        std::vector<std::string> sentences = parseSentences(stringFile);

        // Process sentences into n-grams.
       std::unordered_map<std::string, int> nGrams;

        for (std::string &s: sentences) {
            // Remove punctuations.
            std::string strippedSentence = removePunctuations(s);

            // Generate n-grams (word n-grams).
            std::unordered_map<std::string, int> sentenceNgrams = getNgrams(n, strippedSentence);
            Util::concatenateMaps(nGrams, sentenceNgrams);
        }

        return  Util::mapToSortedVect(nGrams);
    }
};

#endif //RV2_N_GRAM_GENERATOR_H
