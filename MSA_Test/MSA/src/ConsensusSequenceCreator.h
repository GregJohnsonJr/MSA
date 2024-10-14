#pragma once
#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <iostream>

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
            if(temp == "-")
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
            {
                std::string val = (languageInterpreter[eqString] == " " ? "-"
                    : languageInterpreter[eqString]);
                conensusString.append(languageInterpreter[eqString] == " " ? "-"
                    : languageInterpreter[eqString]);
            }
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
        languageInterpreter.insert({"TA", "W"});
        //Same bases will just be equal to themselves
        languageInterpreter.insert({"RG", "G"});
        languageInterpreter.insert({"RA", "A"});
        languageInterpreter.insert({"YT", "T"});
        languageInterpreter.insert({"YC", "C"});
        languageInterpreter.insert({"YR", "N"});
       //
        languageInterpreter.insert({"RT", "A"});
        languageInterpreter.insert({"YA", "H"});
        languageInterpreter.insert({"RC", "V"});
        //
        
        languageInterpreter.insert({"BD", "N"});
        languageInterpreter.insert({"BA", "N"});
        languageInterpreter.insert({"BT", "T"});
        languageInterpreter.insert({"BG", "G"});
        languageInterpreter.insert({"BC", "C"});
        languageInterpreter.insert({"BR", "N"});
        languageInterpreter.insert({"BS", "S"});
        languageInterpreter.insert({"BW", "N"});
        languageInterpreter.insert({"BK", "K"});
        languageInterpreter.insert({"BM", "N"});
        languageInterpreter.insert({"BH", "N"});
        languageInterpreter.insert({"BV", "N"});
        languageInterpreter.insert({"BN", "N"});
        languageInterpreter.insert({"BY", "Y"});
        // G or T
        languageInterpreter.insert({"KC", "B"});
        languageInterpreter.insert({"KA", "D"});
        languageInterpreter.insert({"KG", "G"});
        languageInterpreter.insert({"KT", "T"});
        languageInterpreter.insert({"KR", "G"});
        languageInterpreter.insert({"KY", "T"});
        languageInterpreter.insert({"KS", "G"});
        languageInterpreter.insert({"KW", "T"});
        languageInterpreter.insert({"KM", "N"});
        languageInterpreter.insert({"KB", "K"});
        languageInterpreter.insert({"KD", "K"});
        languageInterpreter.insert({"KH", "T"});
        languageInterpreter.insert({"KV", "T"});
        languageInterpreter.insert({"KN", "K"});
        //
        languageInterpreter.insert({"SC", "C"});
        languageInterpreter.insert({"SA", "V"});
        languageInterpreter.insert({"SG", "G"});
        languageInterpreter.insert({"ST", "B"});
        languageInterpreter.insert({"SR", "V"});
        languageInterpreter.insert({"SY", "C"});
        languageInterpreter.insert({"SW", "N"});
        languageInterpreter.insert({"SK", "G"});
        languageInterpreter.insert({"SM", "C"});
        languageInterpreter.insert({"SB", "S"});
        languageInterpreter.insert({"SD", "G"});
        languageInterpreter.insert({"SH", "C"});
        languageInterpreter.insert({"SV", "S"});
        languageInterpreter.insert({"SN", "S"});
        // A or T
        languageInterpreter.insert({"WC", "D"});
        languageInterpreter.insert({"WA", "A"});
        languageInterpreter.insert({"WG", "D"});
        languageInterpreter.insert({"WT", "T"});
        languageInterpreter.insert({"WR", "A"});
        languageInterpreter.insert({"WY", "T"});
        languageInterpreter.insert({"WS", "N"});
        languageInterpreter.insert({"WK", "T"});
        languageInterpreter.insert({"WM", "N"});
        languageInterpreter.insert({"WB", "T"});
        languageInterpreter.insert({"WD", "W"});
        languageInterpreter.insert({"WH", "W"});
        languageInterpreter.insert({"WV", "A"});
        languageInterpreter.insert({"WN", "W"});
        // G or T
        languageInterpreter.insert({"KC", "B"});
        languageInterpreter.insert({"KA", "D"});
        languageInterpreter.insert({"KG", "G"});
        languageInterpreter.insert({"KT", "T"});
        languageInterpreter.insert({"KR", "G"});
        languageInterpreter.insert({"KS", "G"});
        languageInterpreter.insert({"KW", "T"});
        languageInterpreter.insert({"KY", "T"});
        languageInterpreter.insert({"KM", "N"});
        languageInterpreter.insert({"KB", "K"});
        languageInterpreter.insert({"KD", "K"});
        languageInterpreter.insert({"KH", "T"});
        languageInterpreter.insert({"KV", "G"});
        languageInterpreter.insert({"KN", "K"});
        // A or C
        languageInterpreter.insert({"MC", "C"});
        languageInterpreter.insert({"MA", "A"});
        languageInterpreter.insert({"MG", "V"});
        languageInterpreter.insert({"MT", "H"});
        languageInterpreter.insert({"MR", "A"});
        languageInterpreter.insert({"MY", "C"});
        languageInterpreter.insert({"MB", "C"});
        languageInterpreter.insert({"MS", "C"});
        languageInterpreter.insert({"MK", "N"});
        languageInterpreter.insert({"MD", "A"});
        languageInterpreter.insert({"MH", "M"});
        languageInterpreter.insert({"MV", "M"});
        languageInterpreter.insert({"MN", "M"});
        // A or G or T
        languageInterpreter.insert({"DA", "A"});
        languageInterpreter.insert({"DT", "T"});
        languageInterpreter.insert({"DG", "G"});
        languageInterpreter.insert({"DC", "N"});
        languageInterpreter.insert({"DR", "R"});
        languageInterpreter.insert({"DS", "G"});
        languageInterpreter.insert({"DW", "W"});
        languageInterpreter.insert({"DK", "K"});
        languageInterpreter.insert({"DM", "A"});
        languageInterpreter.insert({"DH", "W"});
        languageInterpreter.insert({"DB", "K"});
        languageInterpreter.insert({"DH", "W"});
        languageInterpreter.insert({"DV", "R"});
        languageInterpreter.insert({"DN", "D"});
        languageInterpreter.insert({"DY", "T"});
        // A or C or T
        languageInterpreter.insert({"HA", "A"});
        languageInterpreter.insert({"HT", "T"});
        languageInterpreter.insert({"HG", "N"});
        languageInterpreter.insert({"HC", "C"});
        languageInterpreter.insert({"HR", "A"});
        languageInterpreter.insert({"HS", "C"});
        languageInterpreter.insert({"HW", "W"});
        languageInterpreter.insert({"HK", "T"});
        languageInterpreter.insert({"HM", "M"});
        languageInterpreter.insert({"HB", "C"});
        languageInterpreter.insert({"HD", "W"});
        languageInterpreter.insert({"HV", "M"});
        languageInterpreter.insert({"HN", "H"});
        languageInterpreter.insert({"HY", "Y"});
        //A or C or G
        languageInterpreter.insert({"VA", "A"});
        languageInterpreter.insert({"VT", "N"});
        languageInterpreter.insert({"VG", "G"});
        languageInterpreter.insert({"VC", "C"});
        languageInterpreter.insert({"VR", "R"});
        languageInterpreter.insert({"VS", "S"});
        languageInterpreter.insert({"VW", "A"});
        languageInterpreter.insert({"VK", "G"});
        languageInterpreter.insert({"VM", "M"});
        languageInterpreter.insert({"VB", "S"});
        languageInterpreter.insert({"VD", "R"});
        languageInterpreter.insert({"VH", "M"});
        languageInterpreter.insert({"VN", "N"});
        languageInterpreter.insert({"VY", "Y"});
        //

        languageInterpreter.insert({"NA", "A"});
        languageInterpreter.insert({"NT", "T"});
        languageInterpreter.insert({"NG", "G"});
        languageInterpreter.insert({"NC", "C"});
        languageInterpreter.insert({"NR", "R"});
        languageInterpreter.insert({"NS", "S"});
        languageInterpreter.insert({"NW", "W"});
        languageInterpreter.insert({"NK", "K"});
        languageInterpreter.insert({"NM", "M"});
        languageInterpreter.insert({"NB", "B"});
        languageInterpreter.insert({"ND", "D"});
        languageInterpreter.insert({"NH", "H"});
        languageInterpreter.insert({"NN", "N"});
        languageInterpreter.insert({"NY", "Y"});
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
