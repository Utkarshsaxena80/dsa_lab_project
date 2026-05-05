#include "DNAAnalyzer.h"
#include <iostream>
#include <string>

void displayMenu() {
    std::cout << "\n============================================\n";
    std::cout << "   BIOINFORMATICS / DNA SEQUENCE ANALYZER   \n";
    std::cout << "============================================\n";
    std::cout << "1. Load Initial DNA Sequence\n";
    std::cout << "2. Gene Editing (Insert/Delete)\n";
    std::cout << "3. Build/Update Suffix Index\n";
    std::cout << "4. Search for Genetic Marker (Substring)\n";
    std::cout << "5. Find Longest Repeating Sequence\n";
    std::cout << "6. Add Gene/Mutation Marker (Interval)\n";
    std::cout << "7. Query Overlapping Genes\n";
    std::cout << "8. Display Current DNA State\n";
    std::cout << "0. Exit\n";
    std::cout << "============================================\n";
    std::cout << "Enter your choice: ";
}

int main() {
    DNAAnalyzer analyzer;
    int choice;

    // Load sample data for testing purposes
    std::cout << "Initializing with sample DNA sequence...\n";
    analyzer.loadSequence("ATGCGTACGTTAGCTAGCTAGCGT");
    analyzer.addGeneMarker(0, 5, "Gene_Alpha");
    analyzer.addGeneMarker(10, 15, "Mutation_Beta");
    analyzer.buildIndex();

    do {
        displayMenu();
        if (!(std::cin >> choice)) {
            std::cout << "Invalid input. Please enter a number.\n";
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            continue;
        }

        switch (choice) {
            case 1: {
                std::string seq;
                std::cout << "Enter DNA sequence (A, C, G, T): ";
                std::cin >> seq;
                analyzer.loadSequence(seq);
                break;
            }
            case 2: {
                int editChoice;
                std::cout << "1. Insert\n2. Delete\nChoice: ";
                std::cin >> editChoice;
                if (editChoice == 1) {
                    int idx;
                    std::string seq;
                    std::cout << "Enter index to insert at: ";
                    std::cin >> idx;
                    std::cout << "Enter sequence to insert: ";
                    std::cin >> seq;
                    analyzer.insertSequence(idx, seq);
                } else if (editChoice == 2) {
                    int idx, len;
                    std::cout << "Enter start index: ";
                    std::cin >> idx;
                    std::cout << "Enter length to delete: ";
                    std::cin >> len;
                    analyzer.deleteSequence(idx, len);
                }
                break;
            }
            case 3:
                analyzer.buildIndex();
                break;
            case 4: {
                std::string pattern;
                std::cout << "Enter genetic marker to search for: ";
                std::cin >> pattern;
                analyzer.searchPattern(pattern);
                break;
            }
            case 5:
                analyzer.findLongestRepeating();
                break;
            case 6: {
                int start, end;
                std::string name;
                std::cout << "Enter start index: ";
                std::cin >> start;
                std::cout << "Enter end index: ";
                std::cin >> end;
                std::cout << "Enter marker name (no spaces): ";
                std::cin >> name;
                analyzer.addGeneMarker(start, end, name);
                break;
            }
            case 7: {
                int start, end;
                std::cout << "Enter query start index: ";
                std::cin >> start;
                std::cout << "Enter query end index: ";
                std::cin >> end;
                analyzer.queryGenes(start, end);
                break;
            }
            case 8:
                analyzer.displaySequence();
                analyzer.displayGenes();
                break;
            case 0:
                std::cout << "Exiting DNA Analyzer. Goodbye!\n";
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 0);

    return 0;
}
