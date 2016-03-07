#include "stdafx.h"
#include "neural_network.h"

void		print_mat(t_matrix &a)
{
	for (int i = 0; i < a.size(); ++i)
	{
		for (int j = 0; j < a[i].size(); ++j)
		{
			std::cout << a[i][j] << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

t_matrix	mult_mat(t_matrix &a, t_matrix &b)
{
	/*	 Naive implementation of matrices product
	 /!\ Operands size differ from normal matrices product /!\
			here :(m * n) x (o * n) -> (m * o)
			mult_mat(a, b) == a * b'
	*/

	t_matrix			ret(a.size(), std::deque<float>(b.size(), 0));

	for (int i = 0, i_end = ret.size(); i < i_end; ++i)
	{
		for (int j = 0, j_end = ret[i].size(); j < j_end; ++j)
		{
			for (int k = 0, k_end = a[i].size(); k < k_end; ++k)
			{
				ret[i][j] += a[i][k] * b[j][k];
			}
		}
	}

	return (ret);
}