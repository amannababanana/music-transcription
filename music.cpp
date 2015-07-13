#include "include\AL\al.h"
#include "include\AL\alc.h"
#include "WAVloader.h"
#include "playMusic.h"
#include "noteDetect.h"
#include "moreMath.h"
#include <iostream>
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
	std::vector<double> data;
	data = convert(loadWavFile("test2.wav", &alSampleSet, &alBufferLen, &alFreqBuffer, &alFormatBuffer)[0], data);
	startMusic(alSampleSet);
	DiscreteFunction waveform=DiscreteFunction(data, alFreqBuffer);
	sinWaveDetect(waveform);
	stopMusic();
	system("pause");
}