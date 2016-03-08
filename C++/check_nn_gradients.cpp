#include "stdafx.h"
#include "neural_network.h"

// Something doesn't work, maybe in the way the matrices are unrolled
/*
t_matrix	debug_init_weights(int fan_out, int fan_in)
{
	t_matrix	ret(fan_out, std::deque<float>(fan_in + 1));

	int count = 0;
	for (int j = 0; j < ret[0].size(); ++j)
	{
		for (int i = 0; i < ret.size(); ++i)
		{
			count++;
			ret[i][j] = float(sin(count) / float(10));
		}
	}
	return (ret);
}

t_matrix		apply_add_mat_new(t_matrix &a, t_matrix &b)
{
	t_matrix	ret(a.size(), std::deque<float>(a[0].size(), 0));

	for (int j = 0; j < a[0].size(); ++j)
	{
		for (int i = 0; i < a.size(); ++i)
		{
			ret[i][j] = a[i][j] + b[i][j];
		}
	}
	return (ret);
}

t_matrix		apply_sub_mat_new(t_matrix &a, t_matrix &b)
{
	t_matrix	ret(a.size(), std::deque<float>(a[0].size(), 0));

	for (int j = 0; j < a[0].size(); ++j)
	{
		for (int i = 0; i < a.size(); ++i)
		{
			ret[i][j] = a[i][j] - b[i][j];
		}
	}
	return (ret);
}

t_matrix	compute_numerical_grad(Data data, t_matrix &theta_1, t_matrix &theta_2, int num_labels)
{
	t_matrix	numgrad1(theta_1.size(), std::deque<float>(theta_1[0].size(), 0));
	t_matrix	perturb1(theta_1.size(), std::deque<float>(theta_1[0].size(), 0));
	float epsilon = 0.0001f;

	std::cout << theta_1.size() * theta_1[0].size() << std::endl;

	for (int j = 0; j < theta_1[0].size(); ++j)
	{
		for (int i = 0; i < theta_1.size(); ++i)
		{
			perturb1[i][j] = epsilon;
			float	loss1 = cost_function(data,
				apply_sub_mat_new(theta_1, perturb1),
				theta_2, 0, num_labels);
			float	loss2 = cost_function(data,
				apply_add_mat_new(theta_1, perturb1),
				theta_2, 0, num_labels);
			numgrad1[i][j] = (loss2 - loss1) / float(2 * epsilon);
			perturb1[i][j] = 0;
		}
	}
	print_mat(numgrad1);
	t_matrix	numgrad2(theta_2.size(), std::deque<float>(theta_2[0].size(), 0));
	t_matrix	perturb2(theta_2.size(), std::deque<float>(theta_2[0].size(), 0));

	for (int j = 0; j < theta_2[0].size(); ++j)
	{
		for (int i = 0; i < theta_2.size(); ++i)
		{
			perturb2[i][j] = epsilon;
			float	loss1 = cost_function(data,
				theta_1,
				apply_sub_mat_new(theta_2, perturb2), 0, num_labels);
			float	loss2 = cost_function(data,
				theta_1,
				apply_add_mat_new(theta_2, perturb2), 0, num_labels);
			numgrad2[i][j] = (loss2 - loss1) / float(2 * epsilon);
			perturb2[i][j] = 0;
		}
	}
	print_mat(numgrad2);
	return (numgrad1);
}

void	check_nn_gradients()
{
	int	input_layer_size = 3;
	int	hidden_layer_size = 5;
	int	num_labels = 3;
	int	m = 5;

	t_matrix	theta_1 = debug_init_weights(hidden_layer_size, input_layer_size);
	t_matrix	theta_2 = debug_init_weights(num_labels, hidden_layer_size);
	t_matrix	X = debug_init_weights(m, input_layer_size - 1);
	std::vector<int>	y(m);
	Data		data;

	data.x = X;
	data.m = m;
	int count = 2;
	for (int j = 0; j < y.size(); ++j)
	{
		y[j] = count;
		count++;
		if (count == 4)
			count = 2;
	}
	data.y = y;
	compute_numerical_grad(data, theta_1, theta_2, num_labels);
}*/