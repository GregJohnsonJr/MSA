// MSA.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include "Alignment.h"
#include "DNADatabase.h"
#include "IOSequenceController.h"

int main()
{
    int gapScore = 0;
    int mismatchScore = 0;
    int matchScore = 0;
    int afflineGapScore = 0;
    char choice;
    IOSequence::AddToSequence(std::vector<std::string>{"gap", "mismatch", "match score", "afflinegap Score"},
        std::vector<int*>{&gapScore, &mismatchScore, &matchScore, &afflineGapScore});
    std::string filePath;
    std::cout << "Please enter the file path" << std::endl;
    std::cin >> filePath;
    DNADatabase dna = DNADatabase(filePath);
    dna.ReadFile();
    std::string outfilePath;
    std::cout << "Please enter your outfilePath" << std::endl;
    std::cin >> outfilePath;
    std::cout << "Is this a protein? (y/n)" << std::endl;
    std::cin >> choice;
    while (choice != 'y' && choice != 'n')
    {
        std::cout << "Please enter yes (y) or no (n)" << std::endl;
        std::cin >> choice;
    }
    const bool isProtein = choice == 'y' ? true : false;
    Pam pam;
    if(isProtein)
    {
        std::string path;
        std::cout << "Please enter the path to your substitution matrix" << std::endl;
        std::cin >> path;
        Pam pamTemp(path);
        pam = pamTemp;
    }
    Alignment alignment(gapScore, mismatchScore, matchScore, afflineGapScore, dna, isProtein, pam);
    alignment.MSA();
}
