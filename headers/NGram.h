//
// Created by igork on 12/04/2026.
//

#ifndef RV2_NGRAM_H
#define RV2_NGRAM_H
#include <string>

class NGram {
    std::string value;
    double frequency;

public:
    NGram(std::string value, double frequency);
};

#endif //RV2_NGRAM_H