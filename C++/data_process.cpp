#include "stdafx.h"

Data	read_data(std::string filename, int limit_example)
{
	std::ifstream	file(filename);
	std::string		line;
	std::string		value;
	Data			data;
	int				count_parameters;

	if (!file.good())
	{
		std::cout << "Could not read data file" << std::endl;
		exit(-1);
	}
	// First pass to get sizes
	while (std::getline(file, line))
	{
		std::stringstream	ss(line);

		count_parameters = 0;
		while (std::getline(ss, value, ','))
		{
			if (data.m == 0)
				data.nb_parameters++;
			count_parameters++;
		}
		if (count_parameters != data.nb_parameters)
		{
			std::cout << "Error in csv file. (input not consistent)" << std::endl;
			exit(-1);
		}
		data.m++;
	}
	data.nb_parameters--;
	if (data.m == 0 || data.nb_parameters <= 0)
	{
		std::cout << "Error in csv file. (no input)" << std::endl;
		exit(-1);
	}
	data.x = t_matrix(limit_example, std::deque<float>(400));
	data.y = std::vector<int>(limit_example);
	file.close();
	file.open(filename);
	int	i = 0;
	int j;
	int	tmp = 0;
	// doesn't work
	//int	jump = (500 / (5000 / limit_example);
	int jump = 500;
	std::cout << jump << std::endl;
	while (std::getline(file, line))
	{
		std::stringstream	ss(line);

		j = 0;
		if (tmp < jump)
		{
			while (std::getline(ss, value, ','))
			{
				if (j == data.nb_parameters)
					data.y[i] = std::atoi(value.c_str());
				else
					data.x[i][j] = std::strtof(value.c_str(), NULL);
				j++;
			}
			i++;
		}
		tmp++;
		if (tmp == 500)
			tmp = 0;
	}
	file.close();
	std::cout << i << std::endl;
	data.nb_parameters = 400;
	data.m = limit_example;
//	shuffle_data(data, limit_example, limit_feature);
/*	int	shuffle_count = data.x.size();
	std::random_device	rd;
	std::mt19937		gen(rd());

	while (shuffle_count > 0)
	{
		std::uniform_real_distribution<int>	distrib(0, shuffle_count);
		int	random = distrib(gen);
		std::deque<float>	tmp_row = data.x.back();
		data.x[data.x.size() - 1] = data.x[random];
		data.x[random] = tmp_row;

		int	tmp = data.y.back();
		data.y[data.y.size() - 1] = data.y[random];
		data.y[random] = tmp;
		shuffle_count--;
	}*/
	return (data);
}


void	testread_data(std::string filename, t_matrix &x, std::vector<float> &y)
{
	std::ifstream	file(filename);
	std::string		line;
	std::string		value;
	int				count_parameters;
	int				nb_parameters = 0;
	int				nb_line = 0;

	if (!file.good())
	{
		std::cout << "Could not read data file" << std::endl;
		exit(-1);
	}
	// First pass to get sizes
	while (std::getline(file, line))
	{
		std::stringstream	ss(line);

		count_parameters = 0;
		while (std::getline(ss, value, ','))
		{
			if (nb_line == 0)
				nb_parameters++;
			count_parameters++;
		}
		if (count_parameters != nb_parameters)
		{
			std::cout << "Error in csv file. (input not consistent)" << std::endl;
			exit(-1);
		}
		nb_line++;
		if (nb_line == x.size())
			break;
	}
	if (nb_line == 0 || nb_parameters <= 0)
	{
		std::cout << "Error in csv file. (no input)" << std::endl;
		exit(-1);
	}
	nb_parameters--;

	// Store data
	file.close();
	file.open(filename);
	int	i = 0;
	int	tmp = 0;
	// Doesn't work
	//int	jump = 500 / (5000 / x.size());
	int jump = 500;
	int j;
	while (std::getline(file, line))
	{
		std::stringstream	ss(line);

		j = 0;
		if (tmp < jump)
		{
			while (std::getline(ss, value, ','))
			{
				if (j == nb_parameters)
					y[i] = std::strtof(value.c_str(), NULL);
				else
					x[i][j] = std::strtof(value.c_str(), NULL);
				j++;
			}
			i++;
		}
		tmp++;
		if (tmp == 500)
			tmp = 0;
	}
}

