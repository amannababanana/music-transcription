#include <vector>
#include <string>
#define _USE_MATH_DEFINES
#include <math.h>
#include "include\AL\al.h"

double resonate(std::vector<std::vector<short>> waveform, ALsizei sampleRate, float noteFreq, ALsizei startPos);
std::vector<std::vector<double>> sinWaveDetect(std::vector<std::vector<short>> waveform, ALsizei sampleRate);//TODO implement this
int getIDfromFreq(double freq)
{
	return(std::round(std::log2(freq / 13.75) * 120));
}
double getFreqfromID(int ID)
{
	return(std::pow(2, ID / 120)*13.75);
}