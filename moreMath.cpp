#include "moreMath.h"
#include <iostream>

DiscreteFunction::DiscreteFunction(std::vector<double> data0, double samplerate0, double start0)
	:data(data0), samplerate(samplerate0), start(start0){}

DiscreteFunction::DiscreteFunction(std::function<double(double)> func, double samplerate0, double start0, double end)
	:samplerate(samplerate0), start(start0)
{
	for (int i = 0; i < (end - start0)*samplerate0; i++)
	{
		data.push_back(func(i / samplerate0 + start0));
		//std::cout << '\t' << i << '/' << (end - start0)*samplerate0 << '\n';
	}
}

double DiscreteFunction::integral(double begin, double end)
{
	double retval = 0;
	for (int i = 0; i < (end - start)*samplerate - 1; i++) if (i + begin*samplerate < data.size()) retval += data[i + begin*samplerate];
	retval /= samplerate;
	return retval;
}

DiscreteFunction DiscreteFunction::integral()
{
	std::vector<double> retval;
	for (int i = 0; i < data.size(); i++) retval.push_back(data[i]/samplerate);
	return DiscreteFunction(retval, samplerate, start);
}

double DiscreteFunction::derivative(double pt)
{
	return (data[pt*samplerate - start*samplerate + .5] - data[pt*samplerate - start*samplerate - .5]) * samplerate;
}

DiscreteFunction DiscreteFunction::derivative()
{
	std::vector<double> retval;
	for (int i = 0; i < data.size() - 1; i++) retval.push_back((data[i + 1] - data[i]) * samplerate);
	return DiscreteFunction(retval, samplerate, start);
}

double findFreq();