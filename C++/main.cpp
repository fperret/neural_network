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

void	add_column(t_matrix &matrix, float value)
{
	// Search better way to do it
	for (t_matrix::iterator it = matrix.begin(); it != matrix.end(); ++it)
	{
		(*it).push_front(value);
	}
}

float	sigmoid(float value)
{
	return ((1 / (1 + exp(-value))));
}

void	forward_propagation(Data data, t_matrix &theta_1, t_matrix &theta_2)
{
	// Maybe do not modify data.x directly
	add_column(data.x, 1);
	std::cout << data.x[0].size() << std::endl;
	std::vector<int>	prediction(data.m);
	for (int i = 0; i < data.m; ++i)
	{
		std::deque<float>	z_2(theta_1.size(), 0);
		for (int j = 0; j < z_2.size(); ++j)
		{
			for (int k = 0; k < data.x[i].size(); ++k)
			{
				z_2[j] += data.x[i][k] * theta_1[j][k];
			}
			z_2[j] = sigmoid(z_2[j]);
		}
		z_2.push_front(1);

		std::deque<float>	z_3(theta_2.size(), 0);
		int	index_max = 0;
		float	value_max = 0;
		for (int j = 0; j < z_3.size(); ++j)
		{
			for (int k = 0; k < z_2.size(); ++k)
			{
				z_3[j] += z_2[k] * theta_2[j][k];
			}
			z_3[j] = sigmoid(z_3[j]);
			if (z_3[j] >= value_max)
			{
				value_max = z_3[j];
				index_max = j;
			}
		}
		prediction[i] = index_max + 1;
		std::cout << "Prediction for example no. " << i << " : " << prediction[i] << ". Correct value : " << data.y[i] << std::endl;
	}
}

int main()
{
	Data	data = read_data("data.csv");
	t_matrix	theta_1;
	t_matrix	theta_2;
	std::cout << "X : " << data.m << " * " << data.nb_parameters << "|| y : " << data.nb_parameters << " * " << "1" << std::endl;

	load_thetas(theta_1, "weights1.csv");
	load_thetas(theta_2, "weights2.csv");
	std::cout << "theta 1 : " << theta_1.size() << " * " << theta_1[0].size() << std::endl;
	std::cout << "theta 2 : " << theta_2.size() << " * " << theta_2[0].size() << std::endl;
	forward_propagation(data, theta_1, theta_2);
    return 0;
}

