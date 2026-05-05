#include "IntervalTree.h"
#include <algorithm>

IntervalTree::IntervalTree() : root(nullptr) {}

IntervalTree::~IntervalTree() {
    destroy(root);
}

void IntervalTree::destroy(ITNode* node) {
    if (node != nullptr) {
        destroy(node->left);
        destroy(node->right);
        delete node->i;
        delete node;
    }
}

ITNode* IntervalTree::insert(ITNode* node, Interval i) {
    // Base case: empty tree
    if (node == nullptr) {
        ITNode* temp = new ITNode();
        temp->i = new Interval(i);
        temp->max = i.high;
        temp->left = temp->right = nullptr;
        return temp;
    }

    // Get low value of root's interval
    int l = node->i->low;

    // If new interval's low is smaller, go to left subtree
    if (i.low < l)
        node->left = insert(node->left, i);
    // Else, go to right subtree
    else
        node->right = insert(node->right, i);

    // Update the max value of this ancestor if needed
    if (node->max < i.high)
        node->max = i.high;

    // Return the (unchanged) node pointer
    return node;
}

void IntervalTree::addInterval(int low, int high, const std::string& name) {
    Interval i = {low, high, name};
    root = insert(root, i);
}

bool IntervalTree::doOverlap(Interval i1, Interval i2) const {
    if (i1.low <= i2.high && i2.low <= i1.high)
        return true;
    return false;
}

void IntervalTree::searchOverlapping(ITNode* node, Interval i, std::vector<Interval>& result) const {
    // Base Case
    if (node == nullptr) return;

    // If this node overlaps with given interval, add it to result
    if (doOverlap(*(node->i), i)) {
        result.push_back(*(node->i));
    }

    // If left child of root is present and max of left child is
    // greater than or equal to given interval, then i may
    // overlap with an interval in left subtree
    if (node->left != nullptr && node->left->max >= i.low) {
        searchOverlapping(node->left, i, result);
    }

    // Also check right subtree (we don't have a strict bound to avoid it here unless we add more checks,
    // but in a standard interval tree, we usually just go right if we can't rule it out)
    // Actually, we can rule out the right subtree if node's low > i.high, because all nodes in right 
    // subtree will have low >= node's low > i.high.
    if (node->right != nullptr && node->i->low <= i.high) {
        searchOverlapping(node->right, i, result);
    }
}

std::vector<Interval> IntervalTree::findOverlapping(int low, int high) const {
    std::vector<Interval> result;
    Interval i = {low, high, ""};
    searchOverlapping(root, i, result);
    return result;
}

void IntervalTree::inorder(ITNode* node) const {
    if (node == nullptr) return;

    inorder(node->left);

    std::cout << "[" << node->i->low << ", " << node->i->high << "] "
              << "Gene: " << node->i->geneName << " (max = " << node->max << ")" << std::endl;

    inorder(node->right);
}

void IntervalTree::display() const {
    if (root == nullptr) {
        std::cout << "No genes tracked.\n";
        return;
    }
    inorder(root);
}
