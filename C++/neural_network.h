#pragma once
#include "stdafx.h"

typedef std::deque<std::deque<float> > t_matrix;

// output.cpp
void	write_input_read_to_file(Data data);
void	write_matrix_to_file(t_matrix &matrix, std::string name);

// main.cpp
t_matrix	forward_propagation(t_matrix &x, std::vector<float> &y, t_matrix &theta_1, t_matrix &theta_2);

// sigmoid.cpp
float	sigmoid(float &value);
float	sigmoid_gradient(float value);
void	apply_sigmoid_gradient_on(t_matrix &a, t_matrix &b);

// data_process.cpp
Data	read_data(std::string filename, int limit_example);
void	testread_data(std::string filename, t_matrix &x, std::vector<float> &y);

// matrices.cpp
void		print_mat(t_matrix &a);
t_matrix	apply_sigmoid_new(t_matrix &m);
t_matrix	apply_factor_new(t_matrix &m, float factor);
float		squared_sum_mat(t_matrix &m);
t_matrix	mult_mat(t_matrix &a, t_matrix &b);
t_matrix	mult_mat_sigmoid(t_matrix &a, t_matrix &b);
t_matrix	transpose(t_matrix &m);
void	add_column(t_matrix &matrix, float value);
void	delete_first_column(t_matrix &matrix);

// backpropagation.cpp
t_matrix	random_initialize_weights(int &l_in, int &l_out);
float	regularization_term(int m, t_matrix &theta_1, t_matrix &theta_2, float lambda);
float	cost_function(t_matrix &x, std::vector<float> &y, t_matrix &theta_1, t_matrix &theta_2, float lambda, int n, float &learning_rate);

// check_nn_gradints.cpp
void	check_nn_gradients();
