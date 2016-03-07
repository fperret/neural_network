#pragma once
#include "stdafx.h"

typedef std::deque<std::deque<float> > t_matrix;

t_matrix	forward_propagation(Data data, t_matrix &theta_1, t_matrix &theta_2);

float	sigmoid(float &value);
float	sigmoid_gradient(float value);
void	apply_sigmoid_gradient_on(t_matrix &a, t_matrix &b);

Data	read_data(std::string filename);


void		print_mat(t_matrix &a);
t_matrix	apply_sigmoid_new(t_matrix &m);
t_matrix	apply_factor_new(t_matrix &m, float factor);
float		squared_sum_mat(t_matrix &m);
t_matrix	mult_mat(t_matrix &a, t_matrix &b);
t_matrix	mult_mat_sigmoid(t_matrix &a, t_matrix &b);
t_matrix	get_transpose(t_matrix &m);
void	add_column(t_matrix &matrix, float value);
void	delete_first_column(t_matrix &matrix);


t_matrix	random_initialize_weights(int &l_in, int &l_out);
float	regularization_term(int m, t_matrix &theta_1, t_matrix &theta_2, float lambda);
float	cost_function(Data data, t_matrix &theta_1, t_matrix &theta_2, float lambda, int n);

void	check_nn_gradients();
