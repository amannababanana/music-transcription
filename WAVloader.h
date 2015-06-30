//because VS thinks fopen is unsafe
#define _CRT_SECURE_NO_DEPRECATE
#define _CRT_SECURE_NO_WARNINGS
#pragma warning (disable : 4996)

#include <fstream>
#include <vector>
#include <string>
#include "include\AL\al.h"
#include "include\AL\alc.h"

struct RIFF_Header {
	char chunkID[4];
	long chunkSize;
	char format[4];
};

struct WAVE_Format {
	char subChunkID[4];
	long subChunkSize;
	short audioFormat;
	short numChannels;
	long sampleRate;
	long byteRate;
	short blockAlign;
	short bitsPerSample;
};

struct WAVE_Data {
	char subChunkID[4];
	long subChunk2Size;
};

std::vector<std::vector<short>> loadWavFile(const char* filename, ALuint* buffer,
	ALsizei* size, ALsizei* frequency, ALenum* format);