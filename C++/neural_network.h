#pragma once
#include "stdafx.h"

typedef std::vector<std::deque<float> > t_matrix;

Data	read_data(std::string filename);
t_matrix	mult_mat(t_matrix &a, t_matrix &b);