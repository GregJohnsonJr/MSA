#pragma once
#include <vector>
#include <string>
namespace Matrices
{
	class Matrix
	{
	private:

	public:
		struct MatrixNode
		{
			MatrixNode() {} // 48bytes * 3600 
			MatrixNode(std::string val, std::string seqLetter)
			{
				_val = val;
				_seqLetter = seqLetter;
			}
			std::string _val = "";
			std::string _seqLetter = "";
			bool isGap = false;
		};
		std::vector<std::vector<MatrixNode>> matrix;
		Matrix() {};
		Matrix(int ySize, int xSize)
		{
			std::vector <std::vector<MatrixNode>> sMatrix(ySize, std::vector<MatrixNode>(xSize));
			matrix = sMatrix;
		}
		/// <summary>
		/// Set at x and y pos
		/// </summary>
		/// <param name="x">pos</param>
		/// <param name="y">pos</param>
		/// <param name="val"></param>
		/// <returns></returns>
		bool SetMatrixValueAtPosition(int, int, MatrixNode);
		void DisplayMatrix();
	};
}
