#include "DNADatabase.h"
#include <fstream>
#include <iostream>
#include <vector>
std::vector<DNADatabase::Sequences> DNADatabase::ReadFile()
{
    std::vector<std::string> n;
    std::ifstream dnaFile;
    std::string line;
    dnaFile.open(filePath);
    while (!dnaFile.is_open())
    {
        std::cout << "Could not find file, Re enter file" << std::endl;
        std::cin >> filePath;
        dnaFile.open(filePath);
    }
    int j = -1;
    while (std::getline(dnaFile, line))
    {
        if (line.find('>') != std::string::npos)
        {
            j++;
            DNADatabase::Sequences sequences;
            line.erase(line.begin());
            sequences.name = line;
            dnaSequences.emplace_back(sequences);
            continue;
        }
        dnaSequences[j].sequence += line;
    }
    for(auto i : dnaSequences)
    {
        sequenceMap.insert({i.name, i});
    }
    return dnaSequences;
}
