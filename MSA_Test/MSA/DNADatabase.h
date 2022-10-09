#pragma once
#include <string>
#include <vector>

class DNADatabase
{
public:

	struct Sequences
	{
	public:
		Sequences(){}
		std::string name;
		std::string sequence;
		bool operator==(const DNADatabase::Sequences& seq) const
		{
			return seq.name == this->name && seq.sequence == this->sequence;
		}
		std::vector<std::string> SequenceToVector() const
		{
			if(!sequenceVector.empty())
				return sequenceVector;
			std::vector<std::string> seq;
			for (const auto s : sequence)
			{
				seq.emplace_back(std::string(1, s));
			}
			return seq;
		}
		std::vector<std::string> sequenceVector;
	};
	DNADatabase() {}
	DNADatabase(const std::string _filePath)
	{
		filePath = _filePath;
	}
	std::vector<DNADatabase::Sequences> ReadFile(); //Either force the user to input the directory or inform them to place to file inside of the solution...
	std::vector<DNADatabase::Sequences> dnaSequences;
private:
	std::string filePath;
};

