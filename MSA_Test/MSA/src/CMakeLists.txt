cmake_minimum_required(VERSION 3.3)
add_library(core_lib MSA.cpp
        ConsensusSequenceCreator.cpp
        DNADatabase.cpp
        IOSequenceController.cpp
        Matrix.cpp
        MSA.cpp
        Pam.cpp
        Alignment.cpp)


target_include_directories(core_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

set(HEADER_FILES
        ConsensusSequenceCreator.h
        DNADatabase.h
        IOSequenceController.h
        Matrix.h
        Pam.h
        Alignment.h
)

target_sources(core_lib PRIVATE ${HEADER_FILES})

add_executable(core_exec
        MSA.cpp  # Your main source file for the executable
)

target_link_libraries(core_exec PRIVATE core_lib)