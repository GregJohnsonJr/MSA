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
        int offset = 0;
        for(int i = 0; i < length; i++)
        {
            std::string temp = std::string(1,other[i]);
            std::string temp2 = std::string(1,seq[i - offset]);
            if(temp == "[")
            {
                temp.append(other.begin() +(i + 1), other.begin() + (i + 4));
                i+=4;
                offset +=4;
            }
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
        languageInterpreter.insert({"AC", "[AC]"});
        languageInterpreter.insert({"TG", "[TG]"});
        languageInterpreter.insert({"TC", "Y"}); //pyrimidinies
        languageInterpreter.insert({"GC", "[GC]"});
        //Same bases will just be equal to themselves
        languageInterpreter.insert({"RG", "G"});
        languageInterpreter.insert({"RA", "A"});
        languageInterpreter.insert({"YT", "T"});
        languageInterpreter.insert({"YC", "C"});
        languageInterpreter.insert({"[AC]C", "C"});
        languageInterpreter.insert({"[AC]A", "A"});
        languageInterpreter.insert({"[AC]G", "R"});
        languageInterpreter.insert({"[AC]T", "Y"});
        languageInterpreter.insert({"[AC]R", "A"});
        languageInterpreter.insert({"[AC]Y", "C"});
        //
        languageInterpreter.insert({"[TG]C", "Y"});
        languageInterpreter.insert({"[TG]A", "R"});
        languageInterpreter.insert({"[TG]G", "G"});
        languageInterpreter.insert({"[TG]T", "T"});
        languageInterpreter.insert({"[TG]R", "R"});
        languageInterpreter.insert({"[TG]Y", "T"});
        //
        languageInterpreter.insert({"[GC]C", "C"});
        languageInterpreter.insert({"[GC]A", "R"});
        languageInterpreter.insert({"[GC]G", "G"});
        languageInterpreter.insert({"[GC]T", "Y"});
        languageInterpreter.insert({"[GC]R", "R"});
        languageInterpreter.insert({"[GC]Y", "C"});
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
