#pragma once

typedef std::deque<std::deque<float> > t_matrix;

class Data
{
	// Need better encapsulation
	private:

	public:
		int									m;
		int									nb_parameters;
		t_matrix							x;
		std::vector<int>					y;

		Data();
		virtual ~Data();
};

