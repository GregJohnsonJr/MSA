#pragma once
#include "DNADatabase.h"
#include <vector>
#include <fstream>
#include <unordered_map>
#include "Matrix.h"
#include "Pam.h"
using namespace Matrices;
class Alignment
{
public:
	Alignment(int gap, int mismatch, int match, int afflineGap, DNADatabase dataFile, bool isProtein, Pam pam)
	{
		_gapScore = gap;
		_matchScore = match;
		_mismatchScore = mismatch;
		_afflineGapScore = afflineGap;
		_sequenceFile = dataFile;
		_isProtein = isProtein;
		_substitutionMatrix = pam;
	}
	Matrix::MatrixNode* GlobalAlignment(const std::vector<std::string> arr1, const std::vector<std::string>);
	void ScoreSequence(const Matrix::MatrixNode*, int, std::string, bool, std::string, std::string);
	void MSA();
	void CreateGuideTree();
	void ApproximateGuideTree();
	void TransformMatrix();
	void ConsensusSequence();
	void GenerateNewickTree();
	void FindSmallestMatrixValue(Matrix*);
private:
	DNADatabase _sequenceFile;
	std::vector<DNADatabase::Sequences> _sequences;
	std::ifstream _outputFile;
	std::unordered_map<std::string, int> _alignmentScores;
	std::string _consensusSequence;
	Matrix* _distanceMatrix = nullptr;
	Pam _substitutionMatrix;
	int _gapScore, _matchScore, _mismatchScore, _afflineGapScore;
	bool _isProtein;
};
