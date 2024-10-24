//
// Created by gregj on 10/18/2024.
//

#ifndef MULTIPLESEQUENCEALIGNMENT_H
#define MULTIPLESEQUENCEALIGNMENT_H
#include <vector>
#include <string>


class MultipleSequenceAlignment final {
public:
    MultipleSequenceAlignment(const int gap_score, const int match_score,
        const int mismatch_score, const int affline_gap_score)
        : gapScore(gap_score),
          matchScore(match_score),
          mismatchScore(mismatch_score),
          afflineGapScore(affline_gap_score) {
    }
    std::vector<std::vector<std::string>> GlobalAlignment(const std::string&, const std::string&);

private:
    int gapScore, matchScore, mismatchScore, afflineGapScore;
};



#endif //MULTIPLESEQUENCEALIGNMENT_H
