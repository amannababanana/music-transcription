#include "include\AL\al.h"
#include "include\AL\alc.h"
#include "WAVloader.h"
#include "playMusic.h"
#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>
#include <vector>
#include <string>

void processAudio(unsigned char *data, ALsizei length);
int main(int argc, char* argv[])
{
	startAL();

	ALenum alFormatBuffer;
	ALsizei alFreqBuffer;
	ALsizei alBufferLen;
	unsigned int alSource;
	unsigned int alSampleSet;
	std::vector<std::vector<short>> data;
	data = loadWavFile("test.wav", &alSampleSet, &alBufferLen, &alFreqBuffer, &alFormatBuffer);
	startMusic(alSampleSet);
	_sleep(1000);
	stopMusic();
	system("pause");
}


void processAudio(unsigned char *data, ALsizei length)
{
	std::cout << sizeof(float);
	double x = 0, x_deriv = 0, x_deriv2 = 0, period = 261;
	for (int i = 0; i < (length>5000?5000:length); i++) {
		x_deriv2 = (data[i]) * .05 - x;
		x_deriv += x_deriv2 * 2 * M_PI / period;
		x += x_deriv * 2 * M_PI / period;
	}
}