#include "include\AL\al.h"
#include "include\AL\alc.h"
#include "WAVloader.h"
#include "playMusic.h"
#include "noteDetect.h"
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
	std::vector<std::vector<short>> data;
	data = loadWavFile("test2.wav", &alSampleSet, &alBufferLen, &alFreqBuffer, &alFormatBuffer);
	std::cout<<resonate(data, alFreqBuffer, 261, 2000);
	startMusic(alSampleSet);
	_sleep(1000);
	stopMusic();
	system("pause");
}