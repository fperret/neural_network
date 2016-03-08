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
	int	m = a.size();
	int	n = a[0].size();
	int	o = b[0].size();
	t_matrix	ret(m, std::deque<float>(o));

	for (int i = 0; i < m; ++i)
	{
		for (int j = 0; j < o; ++j)
		{
			float	sum = 0;
			for (int k = 0; k < n; ++k)
			{
				sum += a[i][k] * b[k][j];
			}
			ret[i][j] = sigmoid(sum);
		}
	}
	return (ret);
}

t_matrix	mult_mat(t_matrix &a, t_matrix &b)
{
	int	m = a.size();
	int	n = a[0].size();
	int	o = b[0].size();
	t_matrix	ret(m, std::deque<float>(o));

	for (int i = 0; i < m; ++i)
	{
		for (int j = 0; j < o; ++j)
		{
			float	sum = 0;
			for (int k = 0; k < n; ++k)
			{
				sum += a[i][k] * b[k][j];
			}
			ret[i][j] = sum;
		}
	}
	return (ret);
}