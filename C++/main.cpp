// Neural_network.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "neural_network.h"

void	load_thetas(t_matrix &theta, std::string filename)
{
	// Change to one single allocation
	std::ifstream	file(filename);

	if (!file.good())
	{
		std::cout << "Could not read weights file" << std::endl;
		exit(-1);
	}

	std::string		line;
	std::string		value;
	while (std::getline(file, line))
	{
		std::stringstream	ss(line);

		std::deque<float>	row;
		while (std::getline(ss, value, ','))
		{
			row.push_back(std::strtof(value.c_str(), NULL));
		}
		theta.push_back(row);
	}
}

t_matrix	forward_propagation(t_matrix &x, t_matrix &theta_1, t_matrix &theta_2)
{
	std::cout << "forward_propagation() call" << std::endl;
	add_column(x, 1);
	t_matrix	z_2 = mult_mat(theta_1, transpose(x));
	t_matrix	a_2 = apply_sigmoid_new(z_2);
	a_2.push_front(std::deque<float>(a_2[0].size(), 1));

	t_matrix	a_3 = mult_mat_sigmoid(theta_2, a_2);
	delete_first_column(x);
	return (a_3);
}

void	predict(t_matrix &x, std::vector<float> &y, t_matrix &theta_1, t_matrix &theta_2)
{
	t_matrix	hypothesis = transpose(forward_propagation(x, theta_1, theta_2));
	int	m = x.size();
	std::vector<int>	prediction(m);

	for (int i = 0; i < m; ++i)
	{
		int	index_max = 0;
		float	value_max = 0;
		for (size_t j = 0; j < hypothesis[i].size(); ++j)
		{
			if (hypothesis[i][j] >= value_max)
			{
				value_max = hypothesis[i][j];
				index_max = j;
			}
		}
		prediction[i] = index_max + 1;
	}
	int	correct = 0;
	for (size_t i = 0; i < prediction.size(); ++i)
	{
		if (prediction[i] == y[i])
			correct++;
	}
	std::cout << correct << std::endl;
}


int main()
{
//	check_nn_gradients();
//	Data	data = read_data("data.csv", 400);
//	write_input_read_to_file(data);

	int		nb_example = 5000;
	int		nb_feature = 400;
	t_matrix	x(nb_example, std::deque<float>(nb_feature));
	std::vector<float>	y(nb_example, 0);
	testread_data("data.csv", x, y);

	t_matrix	theta_1;
	t_matrix	theta_2;
	int		input_layer_size = 400;
	int		hidden_layer_size = 25;
	int		output_layer_size = 10;
	float		lambda = 1;
	
	std::cout << "X : " << nb_example << " * " << nb_feature << "|| y : " << nb_example << " * " << "1" << std::endl;

//	load_thetas(theta_1, "weights1.csv");
//	load_thetas(theta_2, "weights2.csv");
	theta_1 = random_initialize_weights(input_layer_size, hidden_layer_size);
	theta_2 = random_initialize_weights(hidden_layer_size, output_layer_size);
	float	learning_rate = 1.1f;
	int		nb_iter = 10;
	for (int i = 0; i < nb_iter; ++i)
	{
		clock_t	t = clock();
		printf("cost : %f\n", cost_function(x, y, theta_1, theta_2, lambda, output_layer_size, learning_rate));
		t = clock() - t;
		std::cout << ((float)t) / CLOCKS_PER_SEC << " seconds" << std::endl;
	}
	int final_m = 5000;
	t_matrix	final_x(final_m, std::deque<float>(nb_feature));
	std::vector<float>	final_y(final_m);
	testread_data("data.csv", final_x, final_y);
	predict(final_x, final_y, theta_1, theta_2);
	write_matrix_to_file(theta_1, "theta1.txt");
	write_matrix_to_file(theta_2, "theta2.txt");
    return (0);
}

