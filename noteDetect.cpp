#include "noteDetect.h"
#include <fstream>
#include <iostream>


std::vector<std::vector<double>> sinWaveDetect(DiscreteFunction waveform)
{
	std::ofstream log;
	log.open("log2.csv", std::ios_base::trunc);
	auto sinwave = [](double freq)->std::function<double(double)>{return [freq](double x)->double{return std::sin(2 * M_PI * freq * x); }; };
	auto remove_sinwave = [](std::function<double(double)> f, double center)->std::function < double(double) >
	{
		return [f, center](double x)->double
		{
			try{ return (f(center + x) + f(center - x))*.5; }
			catch (...) { throw "exception here"; }
		}; 
	};
	auto remove_coswave = [remove_sinwave](DiscreteFunction f, double dist, double step)->std::function<double(double)>
	{
		return [f, dist, step, remove_sinwave](double x)
		{
			DiscreteFunction g = f;
			for (int i = 0; i < dist / step; i++)
			{
				try{ g = (remove_sinwave(f, i*step + x), f); }
				catch (...){}
				//std::cout << '\t' << i << '/' << dist / step << '\n';
			}
			return g.integral(x, x + step);
		};
	};
	DiscreteFunction data0 = waveform*sinwave(261);//fourier transform
	std::vector<double> data = DiscreteFunction(remove_coswave(data0, .25/261, 1/data0.getSamplerate()*100), data0).getData();//work on this
	for (int i = 0; i < data.size(); i++) log << data[i] << '\n';
	log.close();
	return std::vector<std::vector<double>>();
}