#include "Alignment.h"

Matrix::MatrixNode* Alignment::GlobalAlignment(const std::vector<std::string> arr1, const std::vector<std::string> arr2)//TODO Change chars to strings to account for negatives, Switch i and J value to fix location of next values
{
	Matrix* matrix = new Matrix(arr2.size() + 2, arr1.size() + 2);
	std::string firstSequence;
	for (auto i : arr1)
	{
		firstSequence.append(i);
	}
	// Fill in  matrix
	
	matrix->SetMatrixValueAtPosition(1,1, new Matrix::MatrixNode());
	for (int i = 2; i < matrix->matrix[0].size(); i++)
	{
		Matrix::MatrixNode* node = new Matrix::MatrixNode();
		node->_val = arr1[i - 2];
		Matrix::MatrixNode* node2 = new Matrix::MatrixNode();
		node2->_val = std::to_string((i - 1) * _gapScore);
		matrix->SetMatrixValueAtPosition(0, i, node);
		matrix->SetMatrixValueAtPosition(1, i, node2);
		node2->_parent = matrix->matrix[1][i - 1];
		node2->_left = matrix->matrix[1][i - 1];
		node2->_seqLetter = arr2[0];
	}
	for (int i = 2; i < matrix->matrix.size(); i++)
	{
		Matrix::MatrixNode* node = new Matrix::MatrixNode();
		node->_val = arr2[i - 2];
		Matrix::MatrixNode* node2 = new Matrix::MatrixNode();
		node2->_val = std::to_string((i - 1) * _gapScore);
		matrix->SetMatrixValueAtPosition(i, 0, node);
		matrix->SetMatrixValueAtPosition(i, 1, node2);
		node2->_parent = matrix->matrix[i - 1][1];
		node2->_left = matrix->matrix[i - 1][1];
		node2->_seqLetter = arr2[i - 2];
	}
	matrix->matrix[1][1]->_seqLetter = matrix->matrix[2][0]->_val;
	matrix->DisplayMatrix();
	
	for (int i = 2; i < matrix->matrix.size(); i++) //y
	{
		for (int j = 2; j < matrix->matrix[0].size(); j++)//x
		{
			Matrix::MatrixNode* node = matrix->matrix[i][j];
			std::string topLetter = matrix->matrix[0][j]->_val;
			std::string otherSeqLetter = matrix->matrix[i][0]->_val;
			int topVal = std::stoi(matrix->matrix[i - 1][j]->_val);
			int leftVal = std::stoi(matrix->matrix[i][j - 1]->_val);
			int middleVal = std::stoi(matrix->matrix[i - 1][j - 1]->_val);
			node->_left = matrix->matrix[i][j - 1];
			node->_middle = matrix->matrix[i - 1][j - 1];
			node->_top = matrix->matrix[i - 1][j];
			topVal += _gapScore;
			leftVal += _gapScore;
			middleVal = topLetter == otherSeqLetter ? middleVal + _matchScore : middleVal + _mismatchScore;
			node->_seqLetter = otherSeqLetter;
			if (topVal > leftVal)
			{
				if (topVal > middleVal)
				{
					node->_val = std::to_string(topVal);
					node->_parent = matrix->matrix[i - 1][j];
					node->isGap = true;
				}
				else
				{
					node->_val = std::to_string(middleVal);
					node->_parent = matrix->matrix[i - 1][j - 1];
				}
			}
			else if (middleVal > leftVal)
			{
				if (middleVal > topVal)
				{
					node->_val = std::to_string(middleVal);
					node->_parent = matrix->matrix[i - 1][j - 1];
				}
				else
				{
					node->_val = std::to_string(topVal);
					node->_parent = matrix->matrix[i - 1][j];
					node->isGap = true;
				}
			}
			else
			{
				node->_val = std::to_string(leftVal);
				node->_parent = matrix->matrix[i][j - 1];
				node->isGap = true;
			}
			if (_isProtein)
			{
				node->_val = _substitutionMatrix.GetSubstitutionValue(topLetter, otherSeqLetter);
			}
		}
	}
	//std::string str = FindAlignmentPath(matrix); //Affline gaps are when we decrease gap scores as we continously gap
	//osOutFile << str << std::endl;
	return matrix->matrix[matrix->matrix.size() - 1][matrix->matrix[0].size() - 1]; // Returns last node
}

void Alignment::ScoreSequence(const Matrix::MatrixNode* lastVal, int score, std::string alignment, bool isCurrentlyAfflineGap, std::string seqOne, std::string seqTwo) // The traceback + score
{
	if(lastVal != nullptr)
	{
		std::string alignedVal = lastVal->_seqLetter;
		if (lastVal->_parent == lastVal->_left || lastVal->_parent == lastVal->_top)
		{
			alignedVal = "-";
		}
		alignment.append(alignedVal);
		if (lastVal->_top != nullptr &&  lastVal->_parent->_val == lastVal->_top->_val) // gap
		{
			if(isCurrentlyAfflineGap)
			{
				score += _gapScore;
			}
			else
			{
				score = score + _afflineGapScore + _gapScore;
				isCurrentlyAfflineGap = true;
			}
			ScoreSequence(lastVal->_top, score ,alignment, isCurrentlyAfflineGap, seqOne, seqTwo);
		}
		if (lastVal->_left != nullptr &&lastVal->_parent->_val == lastVal->_left->_val) // gap
		{
			if(isCurrentlyAfflineGap)
			{
				score += _gapScore;
			}
			else
			{
				score = score + _afflineGapScore + _gapScore;
				isCurrentlyAfflineGap = true;
			}
			ScoreSequence(lastVal->_left, score , alignment, isCurrentlyAfflineGap, seqOne, seqTwo);
		}
		if (lastVal->_middle != nullptr &&lastVal->_parent->_val == lastVal->_middle->_val) //middle match
		{
			isCurrentlyAfflineGap = false;
			ScoreSequence(lastVal->_middle, score + _matchScore, alignment, isCurrentlyAfflineGap, seqOne, seqTwo);
		}
		if(lastVal->_parent == nullptr)
		{
			ScoreSequence(lastVal->_parent, score, alignment, isCurrentlyAfflineGap, seqOne, seqTwo);
		}
	}
	else
	{
		std::string key = seqOne + "+" + seqTwo;
		if (!(_alignmentScores.find(key) == _alignmentScores.end())) // if we do have the key
		{
			if(_alignmentScores[key].first < score) //It means this is a better alignment
			{
				_alignmentScores[key] = std::pair<int, std::string>(score, alignment);
			} // otherwise nothing happens
		}
		else // we do not contain the key insert
			_alignmentScores.insert({key, std::pair<int, std::string>(score, alignment)});
	}
}

void Alignment::MSA()
{
	//Continuously Align Sequences
	for(int i = 0; i < _sequences.size(); i++)
	{
		for(int j = i + 1; j < _sequences.size(); j++) // start at the next sequence
		{
			Matrix::MatrixNode* node = GlobalAlignment(_sequences[i].SequenceToVector(), _sequences[j].SequenceToVector());
			ScoreSequence(node, 0, "", false, _sequences[i].name, _sequences[j].name);
			std::string key = _sequences[i].name + "+" + _sequences[j].name;
			std::cout << key <<" : " << " Best Score: " << _alignmentScores[key].first << " Best Alignment: " << _alignmentScores[key].second << std::endl;
		}
	}
	CreateGuideTree();
}

void Alignment::CreateGuideTree()
{
	_distanceMatrix = new Matrix(_sequences.size() + 1, _sequences.size() + 1);
	for(int i = 1; i < _distanceMatrix->matrix.size(); i++)
	{
		_distanceMatrix->matrix[i][0] = new Matrix::MatrixNode();
		_distanceMatrix->matrix[0][i] = new Matrix::MatrixNode();
		_distanceMatrix->matrix[i][0]->_val = _sequences[i - 1].name;
		_distanceMatrix->matrix[0][i]->_val = _sequences[i - 1].name;
	}
	std::unordered_map<std::string, float> distances;
	for(const auto &i : _alignmentScores)
	{
		std::string delimiter = "+";
		std::string token = i.first.substr(0, i.first.find(delimiter));
		std::string initialSequence = _sequenceFile.sequenceMap.at(token).sequence;
		std::string otherSequence = i.second.second;
		//now find the hamming distance with the aligned Sequence
		int length = otherSequence.length() < initialSequence.length() ? otherSequence.size() : initialSequence.size();
		int matches = 0;
		float hammingDistance = 0;
		for(int i = 0; i < length; i++)
		{
			if(otherSequence[i] == initialSequence[i])
				matches++;
		}
		hammingDistance = (float)(length - matches)/(float)length;
		distances.insert({i.first, hammingDistance});
	}
	for(int i = 1; i < _distanceMatrix->matrix.size(); i++)
	{
		std::string nameOne = _distanceMatrix->matrix[i][0]->_val;
		for(int j = i + 1; j < _distanceMatrix->matrix[0].size(); j++)
		{
			std::string currentName = _distanceMatrix->matrix[0][j]->_val;
			std::string key = nameOne + "+" +(currentName);
			float val = distances[key];
			_distanceMatrix->matrix[i][j] = new Matrix::MatrixNode();
			_distanceMatrix->matrix[i][j]->_val = std::to_string(ApproximateGuideTree(val));
		}
	}
	//GUIDE TREE CREATED!!!!
	// Jukes cantor then create outgroups
	
}

float Alignment::ApproximateGuideTree(float val)
{
	float newValue = (1 - ((4/3) * val ));
	newValue = std::abs(newValue);
	newValue = std::log(newValue);
	newValue = (-0.75) * newValue;
	return newValue;
}

std::string Alignment::FindLargestScoreInTable() const
{
	std::string key = " ";
	int val = 0;
	for(const auto &i : _alignmentScores)
	{
		if(key == " ")
		{
			key = i.first;
			val = i.second.first;
		}
		else if(val < i.second.first)
		{
			val = i.second.first;
			key = i.first;
		}
	}
	return key;
}
