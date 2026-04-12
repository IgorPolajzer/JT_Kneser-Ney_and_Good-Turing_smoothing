//
// Created by igork on 11/04/2026.
//

#ifndef RV2_UTIL_H
#define RV2_UTIL_H
#include <algorithm>
#include <string>
#include <unordered_map>
#include <vector>

namespace Util {

    template<typename T>
    inline bool cmp(const std::pair<std::string, T>& a, const std::pair<std::string, T>& b) {
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

}

#endif //RV2_UTIL_H