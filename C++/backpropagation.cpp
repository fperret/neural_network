#include "stdafx.h"
#include "neural_network.h"

t_matrix	random_initialize_weights(int &l_in, int &l_out)
{
	t_matrix	ret(l_out, std::deque<float>(l_in + 1));
	std::random_device						rd;
	std::mt19937							gen(rd());
	std::uniform_real_distribution<float>	distrib;

//	float epsilon_init = (sqrt(6) / sqrt(l_in + l_out));
	//std::cout << epsilon_init << std::endl;
	float epsilon_init = 0.12;


	for (int i = 0; i < ret.size(); ++i)
	{
		for (int j = 0; j < ret[i].size(); ++j)
		{
			ret[i][j] = (distrib(gen) * 2 * epsilon_init) - epsilon_init;
		}
	}
	return (ret);
}

t_matrix	create_y_label(std::vector<int> &y, int m, int k)
{
	t_matrix	ret(m, std::deque<float>(k, 0));

	for (int i = 0; i < m; ++i)
	{
		for (int j = 0; j < k; ++j)
		{
			if (y[i] == j + 1)
				ret[i][j] = 1;
		}
	}
	return (ret);
}

float	cost_function(Data data, t_matrix &theta_1, t_matrix &theta_2, float lambda, int n)
{
	// a_3 -> (5000 * 10)
	add_column(data.x, 1);
	t_matrix	z_2 = mult_mat(theta_1, data.x);
	t_matrix	a_2 = apply_sigmoid_new(z_2);
	a_2.push_front(std::deque<float>(a_2[0].size(), 1));
	a_2 = get_transpose(a_2);

	t_matrix	a_3 = mult_mat_sigmoid(theta_2, a_2);
	a_3 = get_transpose(a_3);
	delete_first_column(data.x);

	t_matrix y_label = create_y_label(data.y, data.m, theta_2.size());
	float cost = 0;
	for (int i = 0; i < data.m; ++i)
	{
		for (int j = 0; j < y_label[i].size(); ++j)
		{
			float left_member = (-y_label[i][j] * log(a_3[i][j]));
			float right_member = (1 - y_label[i][j]) * log(1 - a_3[i][j]);
			cost += (left_member - right_member);
		}
	}
	cost *= (1 / float(data.m));
	cost += (lambda / (2 * data.m)) * (squared_sum_mat(theta_1) + squared_sum_mat(theta_2));

	t_matrix	error_l3(a_3.size(), std::deque<float>(a_3[0].size()));
	for (int i = 0; i < data.m; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			error_l3[i][j] = a_3[i][j] - y_label[i][j];
		}
	}
	t_matrix	error_l2(theta_2[0].size(), std::deque<float>(data.m));
	t_matrix	transpose_theta_2 = get_transpose(theta_2);
	error_l2 = mult_mat(transpose_theta_2, error_l3);
	float	save = error_l2[3][0];
	// Remove bias
	error_l2.pop_front();
	apply_sigmoid_gradient_on(error_l2, z_2);
	t_matrix	delta_1 = mult_mat(error_l2, get_transpose(data.x));
	t_matrix	delta_2 = mult_mat(get_transpose(error_l3), get_transpose(a_2));
	t_matrix	theta1_grad = apply_factor_new(delta_1, (1 / data.m));
	t_matrix	theta2_grad = apply_factor_new(delta_2, (1 / data.m));

	for (int i = 0; i < theta2_grad.size(); ++i)
	{
		for (int j = 0; j < theta2_grad[0].size(); ++j)
		{
			if (j < 10)
				std::cout << theta2_grad[i][j] << " ";
		}
		std::cout << std::endl;
	}
	return (cost);
}