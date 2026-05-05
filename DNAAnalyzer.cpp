#include "DNAAnalyzer.h"
#include <iostream>

DNAAnalyzer::DNAAnalyzer() : index(nullptr), indexNeedsUpdate(true) {}

DNAAnalyzer::~DNAAnalyzer() {
    if (index != nullptr) {
        delete index;
    }
}

void DNAAnalyzer::loadSequence(const std::string& seq) {
    dnaSequence.insertString(0, seq);
    indexNeedsUpdate = true;
    std::cout << "Successfully loaded sequence of length " << seq.length() << ".\n";
}

void DNAAnalyzer::insertSequence(int idx, const std::string& seq) {
    try {
        dnaSequence.insertString(idx, seq);
        indexNeedsUpdate = true;
        std::cout << "Inserted " << seq.length() << " bases at index " << idx << ".\n";
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }
}

void DNAAnalyzer::deleteSequence(int idx, int length) {
    try {
        dnaSequence.remove(idx, length);
        indexNeedsUpdate = true;
        std::cout << "Deleted " << length << " bases starting at index " << idx << ".\n";
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }
}

void DNAAnalyzer::displaySequence() const {
    std::cout << "Current DNA Sequence (Internal Structure):\n";
    dnaSequence.display();
    std::cout << "Raw string: " << dnaSequence.toString() << "\n";
}

std::string DNAAnalyzer::getSequenceString() const {
    return dnaSequence.toString();
}

void DNAAnalyzer::buildIndex() {
    std::string fullSeq = dnaSequence.toString();
    if (fullSeq.empty()) {
        std::cout << "Sequence is empty. Nothing to index.\n";
        return;
    }

    if (index != nullptr) {
        delete index;
    }

    std::cout << "Building Suffix Array index...\n";
    index = new SuffixArray(fullSeq);
    indexNeedsUpdate = false;
    std::cout << "Index built successfully for " << fullSeq.length() << " bases.\n";
}

void DNAAnalyzer::searchPattern(const std::string& pattern) {
    if (indexNeedsUpdate || index == nullptr) {
        std::cout << "Warning: Index is missing or outdated. Building index now...\n";
        buildIndex();
    }
    
    if (index == nullptr) return;

    std::vector<int> results = index->search(pattern);
    if (results.empty()) {
        std::cout << "Pattern '" << pattern << "' not found in the sequence.\n";
    } else {
        std::cout << "Found " << results.size() << " occurrences of '" << pattern << "' at indices:\n";
        for (int idx : results) {
            std::cout << idx << " ";
        }
        std::cout << "\n";
    }
}

void DNAAnalyzer::findLongestRepeating() {
    if (indexNeedsUpdate || index == nullptr) {
        std::cout << "Warning: Index is missing or outdated. Building index now...\n";
        buildIndex();
    }
    
    if (index == nullptr) return;

    std::string repeating = index->longestRepeatingSubstring();
    if (repeating.empty()) {
        std::cout << "No repeating sequence found.\n";
    } else {
        std::cout << "Longest Repeating Sequence (Length " << repeating.length() << "):\n";
        std::cout << repeating << "\n";
    }
}

void DNAAnalyzer::addGeneMarker(int start, int end, const std::string& name) {
    geneTracker.addInterval(start, end, name);
    std::cout << "Added gene marker '" << name << "' at interval [" << start << ", " << end << "].\n";
}

void DNAAnalyzer::queryGenes(int start, int end) const {
    std::vector<Interval> overlaps = geneTracker.findOverlapping(start, end);
    if (overlaps.empty()) {
        std::cout << "No genes or markers found overlapping with interval [" << start << ", " << end << "].\n";
    } else {
        std::cout << "Found " << overlaps.size() << " overlapping genes/markers:\n";
        for (const auto& gene : overlaps) {
            std::cout << "- " << gene.geneName << " [" << gene.low << ", " << gene.high << "]\n";
        }
    }
}

void DNAAnalyzer::displayGenes() const {
    std::cout << "All tracked genes/markers:\n";
    geneTracker.display();
}
