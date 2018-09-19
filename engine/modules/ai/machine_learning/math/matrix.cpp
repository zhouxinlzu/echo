#include "matrix.h"

namespace nn
{
	Matrix::Matrix()
	{
	}

	Matrix::Matrix(int width, int height)
		: m_width(width)
		, m_height(height)
	{
		m_array.resize(m_width * m_height, 0.0);
	}

	// apply function
	Matrix Matrix::applyFunction(double(*function)(double)) const
	{
		Matrix result(m_width, m_height);
		//for (int i = getNumberElements()-1; i >= 0; i--)
		//{
		//	result[i] = (*function)((*this)[i]);
		//}

		return result;
	}
}