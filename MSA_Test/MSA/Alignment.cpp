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
		std::reverse(alignment.begin(), alignment.end());
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
			//std::cout << key <<" : " << " Best Score: " << _alignmentScores[key].first << " Best Alignment: " << _alignmentScores[key].second << std::endl;
		}
	}
	CreateGuideTree();
}

void Alignment::CreateGuideTree()
{
	_distanceMatrix = new Matrix(_sequences.size() + 1, _sequences.size() + 2);
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
		for(int j = i + 1; j < _distanceMatrix->matrix[0].size() - 1; j++)
		{
			std::string currentName = _distanceMatrix->matrix[0][j]->_val;
			std::string key = nameOne + "+" +(currentName);
			float val = distances[key];
			float approxVal = ApproximateGuideTree(val);
			_distanceMatrix->matrix[i][j] = new Matrix::MatrixNode();
			_distanceMatrix->matrix[i][j]->_val = std::to_string(approxVal);
			_distanceMatrix->matrix[j][i] = new Matrix::MatrixNode();
			_distanceMatrix->matrix[j][i]->_val = std::to_string(approxVal);
		}
	}
	//GUIDE TREE CREATED!!!!
	// Jukes cantor then create outgroups
	//OutGroups
	_alignmentScores.clear(); // To make room for new alignments
	CreateOutGroups();
	
}

float Alignment::ApproximateGuideTree(float val) const
{
	float newValue = (1 - ((4/3) * val ));
	newValue = std::abs(newValue);
	newValue = std::log(newValue);
	newValue = (-0.75) * newValue;
	return newValue;
}

void Alignment::CreateOutGroups() 
{
	for(int i = 1; i < _distanceMatrix->matrix.size(); i++)
	{
		float outgroup = 0.0;
		for(int j = 1; j < _distanceMatrix->matrix[0].size(); j++)
		{
			if(_distanceMatrix->matrix[i][j] == nullptr)
				continue;
			outgroup += std::stof(_distanceMatrix->matrix[i][j]->_val);
		}
		int divideSize = (_distanceMatrix->matrix.size() - 1) - 2;
		divideSize = std::max(divideSize, 1);
		outgroup = outgroup/(float)divideSize;
		Matrix::MatrixNode* node = new Matrix::MatrixNode();
		node ->_val = std::to_string(outgroup);
		_distanceMatrix->matrix[i][_distanceMatrix->matrix[0].size() - 1] = node;
	}
	TransformMatrix();
}

void Alignment::TransformMatrix() 
{
	std::pair<int, int> smallestValue = FindSmallestMatrixValue(); // the value to transform
	int rowLength = _distanceMatrix->matrix[0].size();
	int columnLength = _distanceMatrix->matrix.size();

	
	if(columnLength <= 2)
	{
		OutputInformation();
		return;
	}
	std::string columnSequence = _distanceMatrix->matrix[smallestValue.first][0]->_val;
	std::string columnSequenceTwo = _distanceMatrix->matrix[0][smallestValue.second]->_val;
	float outgroupOfFirstValue = std::stof(_distanceMatrix->matrix[smallestValue.first][rowLength - 1]->_val);
	float outgroupOfSecondValue = std::stof(_distanceMatrix->matrix[smallestValue.second][rowLength - 1]->_val);
	float valOfIndexes =  std::stof(_distanceMatrix->matrix[smallestValue.first][smallestValue.second]->_val);

	float averageOutGroup = 0.0;
	for(int i = 1; i < _distanceMatrix->matrix.size(); i++)
	{
		averageOutGroup += std::stof(_distanceMatrix->matrix[i][_distanceMatrix->matrix[0].size() - 1]->_val);
	}
	averageOutGroup = averageOutGroup / (float)(_distanceMatrix->matrix.size() - 1);
	//(Dab - dAD - dBD) /2 + dD(average of all outgroups)
	float newValue = (valOfIndexes - outgroupOfFirstValue - outgroupOfSecondValue)/(float)(2.0);
	newValue = newValue + averageOutGroup;
	_distanceMatrix->matrix[smallestValue.first][smallestValue.second]->_val = std::to_string(newValue);
	for(int i = 1; i < columnLength; i++)
	{
		//Replace all values in column
		if(_distanceMatrix->matrix[smallestValue.first][i] == nullptr || _distanceMatrix->matrix[i][smallestValue.second] == nullptr)
			continue;
		float newVal = std::stof(_distanceMatrix->matrix[smallestValue.first][i]->_val) + std::stof(_distanceMatrix->matrix[i][smallestValue.second]->_val)
			- std::stof(_distanceMatrix->matrix[smallestValue.first][smallestValue.second]->_val);
		newVal/=(float)2;
		_distanceMatrix->matrix[smallestValue.first][i]->_val = std::to_string(newVal);
	}
	
	_distanceMatrix->matrix.erase(_distanceMatrix->matrix.begin() + smallestValue.second);
	for(int i = 0; i < columnLength - 1; i++)
	{
		_distanceMatrix->matrix[i].erase(_distanceMatrix->matrix[i].begin() + smallestValue.second);
	}
	DNADatabase::Sequences seq = _sequenceFile.sequenceMap.at(columnSequence); // need a function for this
	DNADatabase::Sequences seq2 = _sequenceFile.sequenceMap.at(columnSequenceTwo);
	std::vector<std::string> seqVector= seq.SequenceToVector();
	std::vector<std::string> seqVector2 = seq2.SequenceToVector();
	Matrix::MatrixNode* node = GlobalAlignment(seqVector, seqVector2);
	ScoreSequence(node, 0, "", false, seq.name, seq2.name);
	if(initialSeqName == " ") // only the first one
	{
		initialSeqName = columnSequenceTwo;
		Matrix::MatrixNode* node2 = GlobalAlignment(seqVector2, seqVector);
		ScoreSequence(node, 0, "", false, seq2.name, seq.name);
		std::string keyN = seq2.name + "+" + seq.name;
		//std::cout << "Alignment: " << _alignmentScores[keyN].second << std::endl;
		alignedSequences.emplace_back(_alignmentScores[keyN].second);
		_consensusSequence = _alignmentScores[keyN].second;
	}
	std::string key = seq.name + "+" + seq2.name;
	//std::cout << "Alignment: " << _alignmentScores[key].second << std::endl;
	alignedSequences.emplace_back(_alignmentScores[key].second);
	ConsensusSequence(_alignmentScores[key].second);
	GenerateNewickTree(std::pair<std::string, std::string>(seq.name, seq2.name));
	CreateOutGroups(); //indirect recursion 
	//Transform other values
	
}

void Alignment::ConsensusSequence(std::string other)
{
	ConsensusSequenceCreator creator;
	_consensusSequence = creator.ConsensusSequenceGenerator(_consensusSequence, other);
}

void Alignment::GenerateNewickTree(std::pair<std::string, std::string> pairString) // I have to prepare for the case where another sequence may create a pair...
{
	bool hasFirst = false, hasSecond = false;
	std::string first = pairString.first;
	std::string second = pairString.second;
	for(int i = 0; i < containedTrees.size(); i++)
	{
		if(first == containedTrees[i])
		{
			hasFirst = true;
		}
		if(second == containedTrees[i])
		{
			hasSecond = true;
		}
	}
	if( !hasFirst && !hasSecond)
	{
		newWick.insert(0, "(");
		newWick.append(first).append(",").append(second).append(")");
		containedTrees.emplace_back(first);
		containedTrees.emplace_back(second);
	}
	else if(!hasFirst)
	{
		newWick.insert(0, "(");
		newWick.append(first).append(")");
		containedTrees.emplace_back(first);
	}
	else if(!hasSecond)
	{
		newWick.insert(0, "(");
		newWick.append(second).append(")");
		containedTrees.emplace_back(second);
	}
	std::cout << newWick << std::endl;
	
}


std::pair<int, int> Alignment::FindSmallestMatrixValue() const // make unit testable later if possible
{
	float val = 0.0;
	std::pair<int, int> smallestValIndex(-1,-1);
	for(int i = 1; i < _distanceMatrix->matrix.size() ; i++)
	{
		for(int j = 1; j < _distanceMatrix->matrix[0].size() - 1; j++) // -1 to avoid outgroups
		{
			if(_distanceMatrix->matrix[i][j] == nullptr)
				continue;
			float newValue = std::stof(_distanceMatrix->matrix[i][j]->_val);
			if(smallestValIndex.first == -1)
			{
				val = newValue;
				smallestValIndex = std::pair<int,int>(i,j);
				continue;
			}
			if(val > newValue) // the smallest value
			{
				val = newValue;
				smallestValIndex = std::pair<int,int>(i,j);
			}
		}
	}
	return smallestValIndex;
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

void Alignment::OutputInformation()
{
	_outputFile << "Sequences: " << std::endl;
	for(auto i : alignedSequences)
	{
		_outputFile << i << std::endl;
	}
	_outputFile << std::endl;
	_outputFile << "Consensus Sequence: " << std::endl;
	_outputFile << _consensusSequence << std::endl;
	_outputFile << std::endl;
	_outputFile << "Newick tree file: " <<std::endl;
	_outputFile << newWick << std::endl;
}
