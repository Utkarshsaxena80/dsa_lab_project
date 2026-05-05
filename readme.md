# Bioinformatics / DNA Sequence Analyzer

This project is an advanced Data Structures and Algorithms (DSA) laboratory project in C++. It simulates a bioinformatics environment for storing, searching, and mutating massive DNA sequences. 

To solve real-world genomics problems, it leverages three specialized and highly-optimized data structures:

## Core Data Structures

1. **Unrolled Linked List (`UnrolledLinkedList`)**
   - **Purpose:** Massive Text Storage & Gene Editing.
   - **Why:** Storing a 200-million base chromosome in an array makes insertions/deletions (mutations) terribly slow ($O(N)$). Storing it in a standard Linked List wastes massive amounts of memory on pointers. 
   - **How:** An Unrolled Linked List is a hybrid approach. It stores "chunks" of DNA arrays (e.g., 64 bases per node) inside linked list nodes. This reduces memory overhead by ~95% while keeping insertions/deletions very fast.

2. **Suffix Array (`SuffixArray`)**
   - **Purpose:** Lightning-Fast Substring Searching & Pattern Matching.
   - **Why:** Searching for a specific genetic marker (like `TAGCT`) across a massive DNA strand usually takes $O(N \times M)$ time.
   - **How:** The Suffix Array sorts all possible suffixes of the DNA strand alphabetically using the **Prefix Doubling** algorithm in $O(N \log^2 N)$ time. Once sorted, a simple Binary Search can instantly find any pattern in $O(M \log N)$ time. It also uses **Kasai's Algorithm** to compute the Longest Common Prefix (LCP), which instantly identifies the longest repeating genetic sequence (useful for finding anomalies like Huntington's disease).

3. **Interval Tree (`IntervalTree`)**
   - **Purpose:** Gene & Mutation Tracking.
   - **Why:** Genes and mutations are not single points; they span ranges (e.g., from index 10,000 to 15,000). Finding overlapping traits across a genome can be painfully slow.
   - **How:** An Interval Tree is an augmented Binary Search Tree. Each node stores an interval `[start, end]` and also the maximum `end` value in its entire sub-tree. This allows the system to prune paths and query overlapping genes in blisteringly fast $O(\log N + K)$ time.

---

## How to Run

### Compilation
Open your terminal in this directory and run the following command to compile the C++ source files into an executable:

```bash
g++ -std=c++17 -O3 *.cpp -o DNAAnalyzer
```

### Execution
Run the compiled executable:

```bash
.\DNAAnalyzer.exe
```

*(Note: On Linux/macOS, use `./DNAAnalyzer` instead)*

---

## Features (CLI Menu)
Once the application is running, you can interact with the DNA sequence using the following menu options:

1. **Load Initial DNA Sequence:** Overwrite the current genome with a new string.
2. **Gene Editing:** Insert or Delete bases (demonstrates the Unrolled Linked List block splitting/shifting).
3. **Build/Update Index:** Rebuilds the Suffix Array after major edits.
4. **Search for Genetic Marker:** Uses Binary Search on the Suffix Array to find substring positions.
5. **Find Longest Repeating Sequence:** Uses Kasai's LCP algorithm.
6. **Add Gene Marker:** Adds an interval to the Interval Tree.
7. **Query Overlapping Genes:** Queries the Interval Tree for traits overlapping a given region.
8. **Display State:** Visualizes the raw DNA string, the Unrolled Linked List's internal array chunks, and all tracked genes.

---

## C++ Architecture: Why use `.h` and `.cpp` files?

In this project, you will notice that every data structure is split into two files (e.g., `IntervalTree.h` and `IntervalTree.cpp`). This is the standard best practice in C++ for organizing code. Here is the difference:

### 1. The Header File (`.h`) -> "The Blueprint"
- **What it does:** It acts as a menu or blueprint. It tells the compiler *what* classes exist, *what* variables they hold, and *what* functions they can perform.
- **Why it is useful:** If `main.cpp` wants to use an `IntervalTree`, it only needs to `#include "IntervalTree.h"`. It doesn't need to read the thousands of lines of complex logic; it just looks at the header to know what functions are available to call (like `addInterval`). 

### 2. The Source File (`.cpp`) -> "The Implementation"
- **What it does:** It contains the actual logic and algorithms. It takes the functions promised in the header file and actually writes the code for them.
- **Why it is useful:** This keeps compilation fast and code clean. If you change a bug deep inside the `IntervalTree.cpp` logic, `main.cpp` does not need to be re-notified because the "Blueprint" (`.h` file) didn't change! 

**Analogy:** 
The Header file (`.h`) is the restaurant menu—it tells you what dishes you can order. The Source file (`.cpp`) is the kitchen—it contains the complex recipes to actually make the food. The user (`main.cpp`) only needs to see the menu!
