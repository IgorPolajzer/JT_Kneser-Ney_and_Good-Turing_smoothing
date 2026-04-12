//
// Created by igork on 11/04/2026.
//

#ifndef RV2_UTIL_H
#define RV2_UTIL_H
#include <algorithm>
#include <regex>
#include <string>
#include <unordered_map>
#include <vector>
#include <sstream>

namespace Util {
    static constexpr std::string SENTENCE_BEGIN_TAG = "<s> ";
    static constexpr std::string SENTECE_END_TAG = " </s>";

    template<typename T>
    bool cmp(const std::pair<std::string, T>& a, const std::pair<std::string, T>& b) {
        return a.second > b.second;
    }

    inline std::vector<std::pair<std::string, int>> mapToSortedVect(const std::unordered_map<std::string, int>& map) {
        std::vector<std::pair<std::string, int>> sorted(map.begin(), map.end());
        std::ranges::sort(sorted, cmp<int>);
        return sorted;
    }

    inline void concatenateMaps(std::unordered_map<std::string, int>& map1, const std::unordered_map<std::string, int>& map2) {
        for (const auto& [key, value] : map2) {
            map1[key] += value; // default-initializes missing keys to 0
        }
    }

    inline std::vector<std::string> stringToSentences(const std::string &s) {
        static const std::regex sentenceRegex(R"((\n+|[.!?]\s+))");
        std::sregex_token_iterator iter(s.begin(), s.end(), sentenceRegex, -1);
        std::sregex_token_iterator end;
        std::vector<std::string> sentences = {iter, end};

        for (std::string &sentence: sentences) {
            std::string taggedSentece = SENTENCE_BEGIN_TAG + sentence + SENTECE_END_TAG;
            sentence = taggedSentece;
        }

        return sentences;
    }

    inline std::vector<std::string> senteceToWords(const std::string& sentence) {
        std::stringstream ss(sentence);
        std::vector<std::string> words;
        std::string word;

        while (ss >> word) {
            words.push_back(word);
        }

        return words;
    }

    inline std::string wordsToSentence(const std::vector<std::string> &words) {
        std::string sentence;
        for (const std::string &word: words) {
            if (!sentence.empty()) sentence += " ";
            sentence += word;
        }

        return sentence;
    }

    inline std::vector<std::string> fileToSentecences(const std::string& filePath) {
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
        return stringToSentences(stringFile);
    }

    inline std::vector<std::string> fileToWords(const std::string& filePath) {
        std::vector<std::string> senteces = fileToSentecences(filePath);
        std::vector<std::string> words;

        for (const std::string &sentence: senteces) {
            std::vector<std::string> sentenceWords = senteceToWords(sentence);
            words.insert(words.end(), sentenceWords.begin(), sentenceWords.end());
        }

        return words;
    }

    inline std::string minusNwordsToSentece(const std::vector<std::string>& words, const int& N) {
        std::vector sentenceWords(words.end() - N, words.end());
        return wordsToSentence(sentenceWords);
    }
}

#endif //RV2_UTIL_H