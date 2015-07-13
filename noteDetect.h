#include <vector>
#include <string>
#define _USE_MATH_DEFINES
#include <math.h>
#include "include\AL\al.h"
#include "moreMath.h"

std::vector<std::vector<double>> sinWaveDetect(DiscreteFunction waveform);
inline int getIDfromFreq(double freq)
{
	return(std::round(std::log2(freq / 13.75) * 24));
}
inline double getFreqfromID(int ID)
{
	return(std::pow(2, ID / 120)*13.75);
}