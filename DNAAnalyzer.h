#ifndef DNA_ANALYZER_H
#define DNA_ANALYZER_H

#include "UnrolledLinkedList.h"
#include "SuffixArray.h"
#include "IntervalTree.h"
#include <string>

class DNAAnalyzer {
private:
    UnrolledLinkedList dnaSequence;
    SuffixArray* index;
    IntervalTree geneTracker;
    bool indexNeedsUpdate;

public:
    DNAAnalyzer();
    ~DNAAnalyzer();

    // Sequence Operations (Unrolled Linked List)
    void loadSequence(const std::string& seq);
    void insertSequence(int index, const std::string& seq);
    void deleteSequence(int index, int length);
    void displaySequence() const;
    std::string getSequenceString() const;

    // Pattern Matching (Suffix Array)
    void buildIndex();
    void searchPattern(const std::string& pattern);
    void findLongestRepeating();

    // Gene Tracking (Interval Tree)
    void addGeneMarker(int start, int end, const std::string& name);
    void queryGenes(int start, int end) const;
    void displayGenes() const;
};

#endif // DNA_ANALYZER_H
