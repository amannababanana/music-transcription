#include "noteDetect.h"
#include <fstream>
#include <iostream>

double resonate(std::vector<std::vector<short>> waveform, ALsizei sampleRate, float noteFreq, ALsizei startPos)
{
	// k is spring constant
	double k = (2 * M_PI * noteFreq / sampleRate);
	k *= k;
	//make sure it doesn't go out of bounds
	if (startPos > waveform[0].size() - 3 * sampleRate / noteFreq)
	{
		startPos = waveform[0].size() - 3 * sampleRate / noteFreq;
	}
	//fancy resonation stuff
	std::vector<double> data;
	double x = 0, x_deriv = 0, x_deriv2 = 0;
	std::ofstream log;
	log.open("log.csv", std::ios_base::trunc);
	for (int i = 0; i < 3 * sampleRate / noteFreq; i++)
	{
		x_deriv2 = (waveform[0][i+startPos]) - x*k;
		x_deriv += x_deriv2;
		x += x_deriv;
		data.push_back(x);
		log << x << ',';
		log << waveform[0][i + startPos] << '\n';
	}
	//find 2nd peak
	char countdown = 2;
	double max = 0;
	bool active = false;
	int pos = 0;
	for (int i = 3; i < data.size(); i++)
	{
		if (data[i]>max)
		{
			active = true;
			max = data[i];
		}
		else if (active)
		{
			pos = i - 1;
			active = false;
			countdown--;
			std::cout << max<<'\n';
		}
		if (countdown == 0)
		{
			log << max << ',' << pos << '\n';
			log.close();
			return max / pos;
		}
	}
	log.close();
	return -1;
}