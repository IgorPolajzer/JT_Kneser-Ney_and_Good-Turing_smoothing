//
// Created by igork on 11/04/2026.
//

#ifndef RV2_MODEL_H
#define RV2_MODEL_H
#include <string>
#include <vector>

class Model {
    /* Example:
        "I am" → {
            "happy": 0.5,
            "tired": 0.3,
            "here": 0.2
        }
    */
    std::unordered_map<
        std::string,
        std::unordered_map<std::string, double>
    > entries;

    public:

    void addEntry(const std::string& name, double& value) {
        entries[name] = value;
    }
};

#endif //RV2_MODEL_H