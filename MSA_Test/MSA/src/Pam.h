#include <string>
#include <vector>
#include <cstring>
#include <fstream>
#include <iostream>

class Pam
{
private: //PAM NEEDS TO BE USER DEFINED
	std::vector<std::vector<std::string>> PAM100;
public:
	Pam(std::string filePath) // Get the conensus sequence, and then re-compare it to the other sequences
	{// Continue doing this until you have no sequences left
		// tends to be an empty space at 0,0 in a matrix
		PAM100.emplace_back(std::vector<std::string>());
		PAM100[0].emplace_back("");
		Init(filePath);

	}
	Pam() {}
	void Init(std::string filePath)
	{
		std::ifstream file;
		std::string line = "";
		file.open(filePath);
		while (!file.is_open())
		{
			std::cout << "Could not find file, Re enter file" << std::endl;
			std::cin >> filePath;
			file.open(filePath);
		}
		int j = 0;
		while (getline(file, line))
		{
			for (int i = 0; i < line.size(); i++)
			{
				std::string val;
				if (line[i] == ' ')
				{
					continue;
				}
				if (line[i] == '-')
				{
					char temp = line[i];
					val.append(std::string(1, temp));
					while (line[++i] != ' ')
					{
						if (i >= line.size())
							break;
						temp = line[i];
						val.append(std::string(1, temp));
					}
				}
				else
				{
					val.append(std::string(1, line[i]));
				}
				PAM100[j].emplace_back(val);

			}
			PAM100.emplace_back(std::vector<std::string>());
			j++;
		}
		PAM100.erase(PAM100.end() - 1);
		COLUMN_SIZE = PAM100.size();
		ROW_SIZE = PAM100[0].size();
	}
	std::string GetSubstitutionValue(std::string first, std::string second)
	{
		int xIndex = 0;
		int yIndex = 0;

		for (int i = 0; i < ROW_SIZE; i++)
		{
			if (PAM100[0][i][0] == (std::toupper(first[0])))
			{
				xIndex = i;
				break;
			}
		}
		for (int i = 0; i < COLUMN_SIZE; i++)
		{
			if (PAM100[0][i][0] == (std::toupper(second[0])))
			{
				yIndex = i;
				break;
			}
		}
		//Chance it could not exist
		return PAM100[xIndex][yIndex];
	}
private:
	int ROW_SIZE = 21;
	int COLUMN_SIZE = 21;
};
