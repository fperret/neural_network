#include "stdafx.h"

void	write_input_read_to_file(Data data)
{
	std::ofstream	outfile_x("x.txt");
	std::ofstream	outfile_y("y.txt");

	for (size_t i = 0; i < data.x.size(); ++i)
	{
		std::string	output = "";
		for (size_t j = 0; j < data.x[i].size(); ++j)
		{
			output += std::to_string(data.x[i][j]) + " ";
		}
		output += "\n";
		outfile_x.write(output.c_str(), output.size());

		output = std::to_string(data.y[i]) + "\n";
		outfile_y.write(output.c_str(), output.size());
	}
	outfile_x.close();
	outfile_y.close();
}

void	write_matrix_to_file(t_matrix &matrix, std::string name)
{
	std::ofstream	outfile(name);

	for (size_t i = 0; i < matrix.size(); ++i)
	{
		std::string	output = "";
		for (size_t j = 0; j < matrix[i].size(); ++j)
		{
			output += std::to_string(matrix[i][j]) + ",";
		}
		output += "\n";
		outfile.write(output.c_str(), output.size());
	}
	outfile.close();
}