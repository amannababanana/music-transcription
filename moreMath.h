#pragma once
#include <math.h>
#include <vector>
#include <algorithm>
#include <functional>

class DiscreteFunction
{
protected:
	std::vector<double> data;
	double start;
	double samplerate;
public:
	DiscreteFunction(std::vector<double> data0, double samplerate0, double start0 = 0);
	DiscreteFunction(std::function<double(double)> func, double samplerate0, double start0, double end);
	DiscreteFunction(std::function<double(double)> func, DiscreteFunction extra)
	{
		*this = DiscreteFunction(func, extra.samplerate, extra.start, extra.data.size() / extra.samplerate);
	}
	DiscreteFunction(const DiscreteFunction& rhs) : data(rhs.data), start(rhs.start), samplerate(rhs.samplerate){}
	double getSamplerate(){ return samplerate; }
	std::vector<double> getData(){ return data; }
	double getStart(){ return start; }
	double operator()(double x)
	{
		int i = x*samplerate;
		if (i >= data.size() || i<0) throw "out of range";
		return data[(int)(x*samplerate)];
	}

	DiscreteFunction operator+(std::function<double(double)> func)
	{ 
		return DiscreteFunction([func, this](double x){return (*this)(x)+func(x);},
			this->samplerate, this->start, this->data.size() / this->samplerate + this->start); }
	DiscreteFunction operator-(std::function<double(double)> func)
	{ 
		return DiscreteFunction([func, this](double x){return (*this)(x)-func(x); },
			this->samplerate, this->start, this->data.size() / this->samplerate + this->start); }
	DiscreteFunction operator*(std::function<double(double)> func)
	{ 
		return DiscreteFunction([func, this](double x){return (*this)(x)*func(x); },
			this->samplerate, this->start, this->data.size() / this->samplerate + this->start); }
	DiscreteFunction operator/(std::function<double(double)> func)
	{
		return DiscreteFunction([func, this](double x){return (*this)(x)/func(x); },
			this->samplerate, this->start, this->data.size() / this->samplerate + this->start);
	}
	DiscreteFunction operator()(std::function<double(double)> func)
	{
		return DiscreteFunction([func, this](double x){return (*this)(func(x)); },
			this->samplerate, this->start, this->data.size() / this->samplerate + this->start);
	}

	double derivative(double x);
	DiscreteFunction derivative();
	double integral(double begin, double end);
	DiscreteFunction integral();
};

template<typename _S, typename _T>
std::vector<_S> convert(std::vector<_T> rhs, std::vector<_S> extra)
{
	std::vector<_S> retval;
	for (int i = 0; i < rhs.size(); i++) retval.push_back(rhs[i]);
	return retval;
}
