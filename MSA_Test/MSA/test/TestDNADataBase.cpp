//
// Created by gregj on 10/13/2024.
//

 #include "../src/DNADatabase.h"
 #include "gtest/gtest.h"
 #include <string>

TEST(DNADatabase, ReadFile) {
    // This test is named "Negative", and belongs to the "FactorialTest"
    // test case.
    const std::string filePath = "../Alignmentsamplesequences/pairwise_nucleotide_1.fasta";
    DNADatabase database(filePath);
    const std::vector<DNADatabase::Sequences> sequences = database.ReadFile();
    EXPECT_EQ(sequences.size(), 2);
}

