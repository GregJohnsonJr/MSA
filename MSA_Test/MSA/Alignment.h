#pragma once
#include "DNADatabase.h"
#include <vector>
#include <fstream>
#include <unordered_map>
#include "Matrix.h"
#include "Pam.h"
#include "ConsensusSequenceCreator.h"
#include <cmath>
using namespace Matrices;

/**
 * Remover Pointers.... Causing memory leaks *sigh*
 */
class Alignment
{
public:
	Alignment(int gap, int mismatch, int match, int afflineGap, DNADatabase dataFile, bool isProtein, Pam pam, std::string filePath)
	{
		_gapScore = gap;
		_matchScore = match;
		_mismatchScore = mismatch;
		_afflineGapScore = afflineGap;
		_sequenceFile = dataFile;
		_isProtein = isProtein;
		_substitutionMatrix = pam;
		_sequences = dataFile.dnaSequences;
		_outputFile.open(filePath);
		while(!_outputFile.is_open())
		{
			std::cout << "Please enter a new path for the outfile";
			std::cin >> filePath;
			_outputFile.open(filePath);
		}
	}
	Matrix GlobalAlignment(const std::vector<std::string> arr1, const std::vector<std::string>);
	void ScoreSequence(const Matrix,int,int, int, std::string, bool, std::string, std::string);
	void MSA();
	void CreateGuideTree();// Think i need a rebuild tree function
	float ApproximateGuideTree(float) const;
	void CreateOutGroups();
	void TransformMatrix();
	void ConsensusSequence(std::string);
	void GenerateNewickTree(std::pair<std::string, std::string>);
	void OutputInformation();
	void ConstructNewickTree();
	std::pair<int,int> FindSmallestMatrixValue() const; // returns index
	std::string FindLargestScoreInTable() const;
private:
	std::vector<std::string> containedTrees;
	DNADatabase _sequenceFile;
	std::vector<DNADatabase::Sequences> _sequences;
	std::string newWick;
	std::vector<std::string> alignedSequences;
	std::ofstream _outputFile;
	std::unordered_map<std::string, std::pair<int, std::string>> _alignmentScores;
	std::string _consensusSequence;
	Matrix _distanceMatrix;
	int largestLength = 0;
	Pam _substitutionMatrix;
	std::string initialSeqName =" ";
	int _gapScore, _matchScore, _mismatchScore, _afflineGapScore;
	bool _isProtein;
	std::vector<std::string> _treeConstructionPath;
	std::unordered_map<std::string, float> _transformedDistances;
};

