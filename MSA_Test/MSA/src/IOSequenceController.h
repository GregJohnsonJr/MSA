#pragma once
#include <string>
#include <vector>
#include <iostream>

namespace IOSequence
{
    template <typename T> class IOSequenceController;
    template <typename T> void AddToSequence(std::vector<std::string> variableNames, std::vector<T*> outputValues)
    {
        int a = 0;
        for(auto i : outputValues)
        {
            std:: cout << "Input the value for " << variableNames[a] << ": " << std::endl;
            std::cin >> *i;
            a++;
        }
    }
};
