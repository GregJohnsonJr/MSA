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
		public:
			MatrixNode() {}
			MatrixNode(std::string val, MatrixNode parent, std::string seqLetter)
			{
				this->_val = val;
				this->_parent = &parent;
				this->_seqLetter = seqLetter;
			}
		public:
			std::string _val = "";
			MatrixNode* _parent = nullptr;
			MatrixNode* _top = nullptr;
			MatrixNode* _middle = nullptr;
			MatrixNode* _left = nullptr;
			std::string _seqLetter = "";
			bool isGap = false;
		};
		std::vector<std::vector<MatrixNode*>> matrix;
		Matrix(int ySize, int xSize)
		{
			std::vector <std::vector<MatrixNode*>> sMatrix(ySize, std::vector<MatrixNode*>(xSize));
			matrix = sMatrix;
		}
		/// <summary>
		/// Set at x and y pos
		/// </summary>
		/// <param name="x">pos</param>
		/// <param name="y">pos</param>
		/// <param name="val"></param>
		/// <returns></returns>
		bool SetMatrixValueAtPosition(int, int, MatrixNode*);
		void DisplayMatrix();
		~Matrix()
		{
			for (auto i : matrix)
			{
				for (auto j : i)
				{
					delete(j);
				}
			}
		}
	};
}
