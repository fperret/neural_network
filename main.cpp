// Neural_network.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Data.h"

Data	read_data(std::string filename)
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
	data.x = std::vector<std::vector<float> >(data.m, std::vector<float>(data.nb_parameters));
	data.y = std::vector<int>(data.m);
	file.close();
	file.open(filename);
	int	i = 0;
	int j;
	while (std::getline(file, line))
	{
		std::stringstream	ss(line);

		j = 0;
		while (std::getline(ss, value, ','))
		{
			if (j == 400)
				data.y[i] = std::atoi(value.c_str());
			else
				data.x[i][j] = std::strtof(value.c_str(), NULL);
			j++;
		}
	}
	return (data);
}

int main()
{
	Data	data = read_data("data.csv");
	std::cout << "X : " << data.m << " * " << data.nb_parameters << "|| y : " << data.nb_parameters << " * " << "1" << std::endl;
    return 0;
}

