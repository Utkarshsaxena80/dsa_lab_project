#ifndef SUFFIX_ARRAY_H
#define SUFFIX_ARRAY_H

#include <string>
#include <vector>

class SuffixArray {
private:
    std::string text;
    std::vector<int> suffixArr;

    void buildSuffixArray();

public:
    SuffixArray(const std::string& text);
    void updateText(const std::string& newText);

    // Search for a pattern, returns all starting indices of the pattern in the text
    std::vector<int> search(const std::string& pattern) const;
    
    // Find longest repeating substring (useful for finding genetic anomalies)
    std::string longestRepeatingSubstring() const;
};

#endif // SUFFIX_ARRAY_H
