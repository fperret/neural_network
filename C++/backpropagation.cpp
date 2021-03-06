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
	float epsilon_init = 0.12f;


	for (size_t i = 0; i < ret.size(); ++i)
	{
		for (size_t j = 0; j < ret[i].size(); ++j)
		{
			ret[i][j] = (distrib(gen) * 2 * epsilon_init) - epsilon_init;
		}
	}
	return (ret);
}

t_matrix	create_y_label(std::vector<float> &y, int m, int k)
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

void	update_theta(t_matrix &theta, t_matrix &grad, float &learning_rate)
{
	for (size_t i = 0; i < theta.size(); ++i)
	{
		for (size_t j = 0; j < theta[i].size(); ++j)
		{
			theta[i][j] -= learning_rate * grad[i][j];
		}
	}
}

float	cost_function(t_matrix &x, std::vector<float> &y, t_matrix &theta_1, t_matrix &theta_2, float lambda, int n, float &learning_rate)
{
	int	m = x.size();

	add_column(x, 1);
	t_matrix	z_2 = mult_mat(theta_1, transpose(x));
	t_matrix	a_2 = apply_sigmoid_new(z_2);
	a_2.push_front(std::deque<float>(a_2[0].size(), 1));

	t_matrix	a_3 = mult_mat_sigmoid(theta_2, a_2);

	t_matrix y_label = transpose(create_y_label(y, m, theta_2.size()));
	float cost = 0;
	for (size_t i = 0; i < y_label.size(); ++i)
	{
		for (size_t j = 0; j < y_label[i].size(); ++j)
		{
			float left_member = (-y_label[i][j] * log(a_3[i][j]));
			float right_member = (1 - y_label[i][j]) * log(1 - a_3[i][j]);
			cost += (left_member - right_member);
		}
	}
	cost *= (1 / float(m));
	cost += (lambda / float((2 * m))) * (squared_sum_mat(theta_1) + squared_sum_mat(theta_2));
	printf("cost %f\n", cost);

	t_matrix	error_l3(a_3.size(), std::deque<float>(a_3[0].size()));
	for (size_t i = 0; i < error_l3.size(); ++i)
	{
		for (size_t j = 0; j < error_l3[i].size(); ++j)
		{
			error_l3[i][j] = a_3[i][j] - y_label[i][j];
		}
	}
	// Remove bias
	t_matrix	theta2_cpy = theta_2;
	delete_first_column(theta2_cpy);
	t_matrix	error_l2(theta_2[0].size(), std::deque<float>(m));
	t_matrix	transpose_theta_2 = transpose(theta_2);
	error_l2 = mult_mat(transpose(theta2_cpy), error_l3);

	apply_sigmoid_gradient_on(error_l2, z_2);

	t_matrix	delta_1 = mult_mat(error_l2, x);
	t_matrix	delta_2 = mult_mat(error_l3, transpose(a_2));
	t_matrix	theta1_grad = apply_factor_new(delta_1, (1.0f / float(m)));
	t_matrix	theta2_grad = apply_factor_new(delta_2, (1.0f / float(m)));

	for (size_t i = 0; i < theta1_grad.size(); ++i)
	{
		for (size_t j = 1; j < theta1_grad[i].size(); ++j)
		{
			theta1_grad[i][j] += float((lambda / float(m))) * theta_1[i][j];
		}
	}

	for (size_t i = 0; i < theta2_grad.size(); ++i)
	{
		for (size_t j = 1; j < theta2_grad[i].size(); ++j)
		{
			theta2_grad[i][j] += float((lambda / float(m))) * theta_2[i][j];
		}
	}

	update_theta(theta_1, theta1_grad, learning_rate);
	update_theta(theta_2, theta2_grad, learning_rate);

	delete_first_column(x);
	return (cost);
}