#include "Matrix.h"
#include <iostream>
#include <cmath>
namespace Matrices
{
	bool Matrix::SetMatrixValueAtPosition(int y, int x, MatrixNode* node)
	{
		if (matrix.size() < y || matrix[0].size() < x)
			return false;
		matrix[y][x] = node;
		return true;
	}
	void Matrix::DisplayMatrix()
	{
		for (int i = 0; i < matrix.size(); i++)
		{
			for (int j = 0; j < matrix[0].size(); j++)
			{
				if (matrix[i][j] == nullptr)
				{
					MatrixNode* node = new MatrixNode();
					matrix[i][j] = node;
				}
				std::string val = matrix[i][j]->_val;
				if (val == "")
				{
					val = "0";
					matrix[i][j]->_val = val;
				}
				//	std::cout << val << std::string(4 - val.length(),' ');
			}
			//	std::cout << std::endl;
		}
		//	std::cout << std::endl;
		//	std::cout << std::endl;
	}
}