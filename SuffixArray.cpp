#include "SuffixArray.h"
#include <algorithm>
#include <iostream>

struct Suffix {
    int index;
    int rank[2];
};

// Compare two suffixes according to their first and second ranks
int cmp(struct Suffix a, struct Suffix b) {
    return (a.rank[0] == b.rank[0]) ? (a.rank[1] < b.rank[1] ? 1 : 0) :
           (a.rank[0] < b.rank[0] ? 1 : 0);
}

SuffixArray::SuffixArray(const std::string& text) : text(text) {
    buildSuffixArray();
}

void SuffixArray::updateText(const std::string& newText) {
    text = newText;
    buildSuffixArray();
}

void SuffixArray::buildSuffixArray() {
    int n = text.length();
    if (n == 0) {
        suffixArr.clear();
        return;
    }

    std::vector<Suffix> suffixes(n);

    // Initial ranks (based on first character)
    for (int i = 0; i < n; i++) {
        suffixes[i].index = i;
        suffixes[i].rank[0] = text[i];
        suffixes[i].rank[1] = ((i + 1) < n) ? text[i + 1] : -1;
    }

    // Sort based on first 2 characters
    std::sort(suffixes.begin(), suffixes.end(), cmp);

    std::vector<int> ind(n);

    // Sort based on first 4, 8, 16... characters (Prefix Doubling: O(N log^2 N))
    for (int k = 4; k < 2 * n; k = k * 2) {
        int rank = 0;
        int prev_rank = suffixes[0].rank[0];
        suffixes[0].rank[0] = rank;
        ind[suffixes[0].index] = 0;

        for (int i = 1; i < n; i++) {
            if (suffixes[i].rank[0] == prev_rank &&
                suffixes[i].rank[1] == suffixes[i - 1].rank[1]) {
                prev_rank = suffixes[i].rank[0];
                suffixes[i].rank[0] = rank;
            } else {
                prev_rank = suffixes[i].rank[0];
                suffixes[i].rank[0] = ++rank;
            }
            ind[suffixes[i].index] = i;
        }

        for (int i = 0; i < n; i++) {
            int nextindex = suffixes[i].index + k / 2;
            suffixes[i].rank[1] = (nextindex < n) ?
                                  suffixes[ind[nextindex]].rank[0] : -1;
        }

        std::sort(suffixes.begin(), suffixes.end(), cmp);
    }

    suffixArr.resize(n);
    for (int i = 0; i < n; i++)
        suffixArr[i] = suffixes[i].index;
}

std::vector<int> SuffixArray::search(const std::string& pattern) const {
    std::vector<int> results;
    if (pattern.empty() || text.empty()) return results;

    int n = text.length();
    int m = pattern.length();
    
    int l = 0, r = n - 1;
    int first_match = -1;
    
    // Binary Search to find the FIRST occurrence of the pattern
    while (l <= r) {
        int mid = l + (r - l) / 2;
        int res = text.compare(suffixArr[mid], m, pattern);
        
        if (res == 0) {
            first_match = mid;
            r = mid - 1; // Look left for earlier occurrences
        } else if (res < 0) { // Suffix is smaller than pattern
            l = mid + 1;
        } else { // Suffix is larger than pattern
            r = mid - 1;
        }
    }
    
    // If we found a match, collect all identical prefix matches
    if (first_match != -1) {
        for (int i = first_match; i < n; ++i) {
            if (text.compare(suffixArr[i], m, pattern) == 0) {
                results.push_back(suffixArr[i]);
            } else {
                break;
            }
        }
    }
    
    // Sort results by index in text for better readability
    std::sort(results.begin(), results.end());
    
    return results;
}

std::string SuffixArray::longestRepeatingSubstring() const {
    if (text.empty() || suffixArr.empty()) return "";
    
    int n = text.length();
    int maxLen = 0;
    int maxIdx = 0;
    
    // Build LCP (Longest Common Prefix) array using Kasai's algorithm
    std::vector<int> lcp(n, 0);
    std::vector<int> invSuff(n, 0);
    
    for (int i = 0; i < n; i++) {
        invSuff[suffixArr[i]] = i;
    }
    
    int k = 0;
    for (int i = 0; i < n; i++) {
        if (invSuff[i] == n - 1) {
            k = 0;
            continue;
        }
        
        int j = suffixArr[invSuff[i] + 1];
        while (i + k < n && j + k < n && text[i + k] == text[j + k]) {
            k++;
        }
        
        lcp[invSuff[i]] = k;
        
        if (k > maxLen) {
            maxLen = k;
            maxIdx = i;
        }
        
        if (k > 0) {
            k--;
        }
    }
    
    return maxLen > 0 ? text.substr(maxIdx, maxLen) : "";
}
