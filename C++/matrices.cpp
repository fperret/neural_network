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

void	add_column(t_matrix &matrix, float value)
{
	// Search better way to do it
	for (t_matrix::iterator it = matrix.begin(); it != matrix.end(); ++it)
	{
		(*it).push_front(value);
	}
}

void	delete_first_column(t_matrix &matrix)
{
	for (t_matrix::iterator it = matrix.begin(); it != matrix.end(); ++it)
	{
		(*it).pop_front();
	}
}

t_matrix	get_transpose(t_matrix &m)
{
	t_matrix	ret(m[0].size(), std::deque<float>(m.size(), 0));

	for (int i = 0; i < m.size(); ++i)
	{
		for (int j = 0; j < m[i].size(); ++j)
		{
			ret[j][i] = m[i][j];
		}
	}
	return (ret);
}

float		squared_sum_mat(t_matrix &m)
{
	// /!\ First column is excluded
	float ret = 0;
	for (int i = 0; i < m.size(); ++i)
	{
		for (int j = 1; j < m[i].size(); ++j)
		{
			ret += m[i][j] * m[i][j];
		}
	}
	return (ret);
}

t_matrix	apply_sigmoid_new(t_matrix &m)
{
	t_matrix	ret(m.size(), std::deque<float>(m[0].size()));

	for (int i = 0; i < ret.size(); ++i)
	{
		for (int j = 0; j < ret[i].size(); ++j)
		{
			ret[i][j] = sigmoid(m[i][j]);
		}
	}
	return (ret);
}

t_matrix		apply_factor_new(t_matrix &m, float factor)
{
	t_matrix	ret(m.size(), std::deque<float>(m[0].size()));

	for (int i = 0; i < m.size(); ++i)
	{
		for (int j = 0; j < m[i].size(); ++j)
		{
			ret[i][j] = m[i][j] * factor;
		}
	}
	return (ret);
}

t_matrix	mult_mat_sigmoid(t_matrix &a, t_matrix &b)
{
	t_matrix			ret(a.size(), std::deque<float>(b.size(), 0));

	for (int i = 0, i_end = ret.size(); i < i_end; ++i)
	{
		for (int j = 0, j_end = ret[i].size(); j < j_end; ++j)
		{
			for (int k = 0, k_end = a[i].size(); k < k_end; ++k)
			{
				ret[i][j] += a[i][k] * b[j][k];
			}
			ret[i][j] = sigmoid(ret[i][j]);
		}
	}

	return (ret);
}

t_matrix	mult_mat(t_matrix &a, t_matrix &b)
{
	/*	 Naive implementation of matrices product
	 /!\ Operands size differ from normal matrices product /!\
			here :(m * n) x (o * n) -> (m * o)
			mult_mat(a, b) == a * b'
	*/
	// Need improvement with iterator ?

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