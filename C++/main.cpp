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

t_matrix	forward_propagation(Data data, t_matrix &theta_1, t_matrix &theta_2)
{
	std::cout << "forward_propagation() call" << std::endl;
	add_column(data.x, 1);
	t_matrix	a_2 = mult_mat_sigmoid(theta_1, get_transpose(data.x));
	a_2.push_front(std::deque<float>(a_2[0].size(), 1));

	t_matrix	a_3 = mult_mat_sigmoid(theta_2, a_2);
	a_3 = get_transpose(a_3);
	delete_first_column(data.x);
	return (a_3);
}

void	predict(Data data, t_matrix &theta_1, t_matrix &theta_2)
{
	t_matrix	hypothesis = forward_propagation(data, theta_1, theta_2);
	std::vector<int>	prediction(data.m);
	for (int i = 0; i < data.m; ++i)
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
	std::cout << "count correct" << std::endl;

	int	correct = 0;
	for (size_t i = 0; i < prediction.size(); ++i)
	{
		if (prediction[i] == data.y[i])
			correct++;
	}
	std::cout << correct << std::endl;
}


int main()
{
//	check_nn_gradients();
	Data	data = read_data("data.csv");
	t_matrix	theta_1;
	t_matrix	theta_2;
	int		input_layer_size = 400;
	int		hidden_layer_size = 25;
	int		output_layer_size = 10;
	float		lambda = 1;
	
	srand(time(NULL));
	std::cout << "X : " << data.m << " * " << data.nb_parameters << "|| y : " << data.m << " * " << "1" << std::endl;

	load_thetas(theta_1, "weights1.csv");
	load_thetas(theta_2, "weights2.csv");
//	std::cout << "theta 1 : " << theta_1.size() << " * " << theta_1[0].size() << std::endl;
//	std::cout << "theta 2 : " << theta_2.size() << " * " << theta_2[0].size() << std::endl;
	//predict(data, theta_1, theta_2);
//	theta_1 = random_initialize_weights(input_layer_size, hidden_layer_size);
	//theta_2 = random_initialize_weights(hidden_layer_size, output_layer_size);
	printf("cost : %f\n", cost_function(data, theta_1, theta_2, lambda, output_layer_size));
    return (0);
}

