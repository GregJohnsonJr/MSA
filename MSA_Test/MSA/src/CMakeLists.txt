cmake_minimum_required(VERSION 3.3)
add_executable(core MSA.cpp
        ConsensusSequenceCreator.cpp
        ConsensusSequenceCreator.h
        DNADatabase.cpp
        DNADatabase.h
        IOSequenceController.cpp
        IOSequenceController.h
        Matrix.cpp
        Matrix.h
        MSA.cpp
        Pam.cpp
        Pam.h
        Alignment.h
        Alignment.cpp)