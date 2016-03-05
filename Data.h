#pragma once
class Data
{
	private:

	public:
		int									m;
		int									nb_parameters;
		std::vector<std::vector<float> >	x;
		std::vector<int>					y;

		Data();
		virtual ~Data();
};

