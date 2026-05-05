#ifndef INTERVAL_TREE_H
#define INTERVAL_TREE_H

#include <vector>
#include <string>
#include <iostream>

struct Interval {
    int low, high;
    std::string geneName;
};

struct ITNode {
    Interval* i;
    int max;
    ITNode *left, *right;
};

class IntervalTree {
private:
    ITNode* root;

    ITNode* insert(ITNode* root, Interval i);
    void inorder(ITNode* root) const;
    bool doOverlap(Interval i1, Interval i2) const;
    void searchOverlapping(ITNode* root, Interval i, std::vector<Interval>& result) const;
    void destroy(ITNode* root);

public:
    IntervalTree();
    ~IntervalTree();

    // Add a new gene interval
    void addInterval(int low, int high, const std::string& name);
    
    // Find all genes overlapping with a specific range
    std::vector<Interval> findOverlapping(int low, int high) const;
    
    // Debug method to print the tree
    void display() const;
};

#endif // INTERVAL_TREE_H
