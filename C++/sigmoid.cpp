#include "neural_network.h"
#include "stdafx.h"

float	sigmoid(float &value)
{
	return ((1 / (1 + exp(-value))));
}

float	sigmoid_gradient(float value)
{
	return (sigmoid(value) * (1 - sigmoid(value)));
}

void	apply_sigmoid_gradient_on(t_matrix &a, t_matrix &b)
{
	for (int i = 0; i < a.size(); ++i)
	{
		for (int j = 0; j < a[i].size(); ++j)
		{
			a[i][j] = sigmoid_gradient(b[i][j]);
		}
	}
}