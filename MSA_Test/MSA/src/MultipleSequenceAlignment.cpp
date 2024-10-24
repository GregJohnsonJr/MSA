//
// Created by gregj on 10/18/2024.
//

#include "MultipleSequenceAlignment.h"

#include <algorithm>
#include <iostream>

std::vector<std::vector<std::string>> MultipleSequenceAlignment::GlobalAlignment(const std::string& firstSequence,
                                                                                 const std::string& otherSequence) {
    const int firstSeqSize = static_cast<int>(firstSequence.size());
    const int otherSeqSize = static_cast<int>(otherSequence.size());
    std::vector<std::vector<int>> matrix(firstSeqSize,
        std::vector<int>(otherSeqSize));

    for(int i = 0; i < firstSeqSize; i++) {
        matrix[i][0] = -i;
    }
    for(int i = 0; i < otherSeqSize; i++) {
        matrix[0][i] = -i;
    }
    for(int i = 1; i < firstSeqSize; i++) {
        for(int j = 1; j < otherSeqSize; j++) {
            const bool match = firstSequence[i] == otherSequence[i];
            int left = matrix[i][j - 1];
            int middle = matrix[i - 1][j - 1];
            int top = matrix[i - 1][j];
            top += gapScore;
            left += gapScore;
            middle = match ? middle + matchScore : middle + mismatchScore;
            const int highestScore = std::max(middle, std::max(left, top));
            matrix[i][j] = highestScore;
        }
    }
    for(const auto& vec : matrix) {
        for(const auto& val: vec) {
            std::cout << val << "  ";
        }
        std::cout << std::endl;
    }
    return {};
}
