#pragma once
#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>

class ConsensusSequenceCreator
{
public:
    //std::string GenerateConsensusSequence(std::string, std::string);
    std::string ConsensusSequenceGenerator(std::string seq, std::string other)
    {
        int length = 0;
        int addGaps = 0;
        InitInterpreter();
        if( seq.size() > other.size())
        {
            length = other.size();
            addGaps = seq.size() - length;
        }
        else
        {
            length = seq.size();
            addGaps = other.size() - length;
        }
        std::string conensusString = "";
        for(int i = 0; i < length; i++)
        {
            std::string temp = std::string(1,other[i]);
            std::string temp2 = std::string(1,seq[i]);
            if(temp == temp2)
            {
                conensusString.append(temp);
                continue;
            }
            if(temp == "_")
            {
                conensusString.append(temp2);
                continue;
            }
            if(temp2 == "-")
            {
                conensusString.append(temp);
                continue;
            }
            std::string eqString(temp);
            eqString.append(temp2);
            if(languageInterpreter.find(eqString) == languageInterpreter.end())
            {
                std::reverse(eqString.begin(), eqString.end());
                conensusString.append(languageInterpreter[eqString]);
            }
            else
                conensusString.append(languageInterpreter[eqString]);
        }
        return conensusString;
    }
    void InitInterpreter()
    {
        languageInterpreter.insert({"AG", "R"}); //purinines
        languageInterpreter.insert({"AC", "M"});
        languageInterpreter.insert({"TG", "K"});
        languageInterpreter.insert({"TC", "Y"}); //pyrimidinies
        languageInterpreter.insert({"GC", "S"});
        //Same bases will just be equal to themselves
        languageInterpreter.insert({"RG", "G"});
        languageInterpreter.insert({"RA", "A"});
        languageInterpreter.insert({"YT", "T"});
        languageInterpreter.insert({"YC", "C"});
        languageInterpreter.insert({"YR", "N"});
        languageInterpreter.insert({"MC", "C"});
        languageInterpreter.insert({"MA", "A"});
        languageInterpreter.insert({"MG", "V"});
        languageInterpreter.insert({"MT", "H"});
        languageInterpreter.insert({"MR", "A"});
        languageInterpreter.insert({"MY", "C"});
        languageInterpreter.insert({"BD", "K"});
        
        languageInterpreter.insert({"BD", "K"});
        //
        languageInterpreter.insert({"KC", "B"});
        languageInterpreter.insert({"KA", "D"});
        languageInterpreter.insert({"KG", "G"});
        languageInterpreter.insert({"KT", "T"});
        languageInterpreter.insert({"KR", "G"});
        languageInterpreter.insert({"KY", "T"});
        //
        languageInterpreter.insert({"SC", "C"});
        languageInterpreter.insert({"SA", "V"});
        languageInterpreter.insert({"SG", "G"});
        languageInterpreter.insert({"ST", "B"});
        languageInterpreter.insert({"SR", "V"});
        languageInterpreter.insert({"SY", "C"});
        //
        languageInterpreter.insert({"-G", "G"});
        languageInterpreter.insert({"-A", "A"});
        languageInterpreter.insert({"-T", "T"});
        languageInterpreter.insert({"-C", "C"});
    }
private:
    std::vector<std::vector<std::string>> consensusValues;
    std::unordered_map<std::string, std::string> languageInterpreter;
};
