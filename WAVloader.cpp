#include "WAVloader.h"

std::vector<std::vector<short>> loadWavFile(const char* filename, ALuint* buffer,
	ALsizei* size, ALsizei* frequency, ALenum* format) {

	FILE* soundFile = NULL;
	WAVE_Format wave_format;
	RIFF_Header riff_header;
	WAVE_Data wave_data;
	unsigned char* data;

	try {
		//open file
		soundFile = fopen(filename, "rb");
		if (!soundFile)
			throw (filename);

		//get data of fixed length from front of file
		fread(&riff_header, sizeof(RIFF_Header), 1, soundFile);

		if ((riff_header.chunkID[0] != 'R' ||
			riff_header.chunkID[1] != 'I' ||
			riff_header.chunkID[2] != 'F' ||
			riff_header.chunkID[3] != 'F') &&
			(riff_header.format[0] != 'W' ||
			riff_header.format[1] != 'A' ||
			riff_header.format[2] != 'V' ||
			riff_header.format[3] != 'E'))
			throw ("Invalid RIFF or WAVE Header");

		fread(&wave_format, sizeof(WAVE_Format), 1, soundFile);

		if (wave_format.subChunkID[0] != 'f' ||
			wave_format.subChunkID[1] != 'm' ||
			wave_format.subChunkID[2] != 't' ||
			wave_format.subChunkID[3] != ' ')
			throw ("Invalid Wave Format");

		if (wave_format.subChunkSize > 16)
			fseek(soundFile, sizeof(short), SEEK_CUR);

		fread(&wave_data, sizeof(WAVE_Data), 1, soundFile);

		if (wave_data.subChunkID[0] != 'd' ||
			wave_data.subChunkID[1] != 'a' ||
			wave_data.subChunkID[2] != 't' ||
			wave_data.subChunkID[3] != 'a')
			throw ("Invalid data header");

		//load the audio data
		data = new unsigned char[wave_data.subChunk2Size];

		if (!fread(data, wave_data.subChunk2Size, 1, soundFile))
			throw ("error loading WAVE data into struct!");

		*size = wave_data.subChunk2Size;
		*frequency = wave_format.sampleRate;

		//get format
		if (wave_format.numChannels == 1) {
			if (wave_format.bitsPerSample == 8)
				*format = AL_FORMAT_MONO8;
			else if (wave_format.bitsPerSample == 16)
				*format = AL_FORMAT_MONO16;
		}
		else if (wave_format.numChannels == 2) {
			if (wave_format.bitsPerSample == 8)
				*format = AL_FORMAT_STEREO8;
			else if (wave_format.bitsPerSample == 16)
				*format = AL_FORMAT_STEREO16;
		}

		//generate things needed for OpenAL
		alGenBuffers(1, buffer);
		alBufferData(*buffer, *format, (void*)data,
			*size, *frequency);
		fclose(soundFile);

		//copy data into vector to make it more usable
		std::vector<std::vector<short>> usableData;
		for (int i = 0; i < wave_format.numChannels; i++) usableData.push_back(std::vector<short>());
		for (int i = 0; i < wave_data.subChunk2Size
			* 8 / (wave_format.bitsPerSample*wave_format.numChannels); i++)
		{
			switch (*format)
			{
			case AL_FORMAT_MONO8:
				usableData[0].push_back(((__int8*)data)[i]);
				break;
			case AL_FORMAT_MONO16:
				usableData[0].push_back(((__int16*)data)[i]);
				break;
			case AL_FORMAT_STEREO8:
				usableData[0].push_back(((__int8*)data)[i * 2]);
				usableData[1].push_back(((__int8*)data)[i * 2 + 1]);
				break;
			case AL_FORMAT_STEREO16:
				usableData[0].push_back(((__int16*)data)[i * 2]);
				usableData[1].push_back(((__int16*)data)[i * 2 + 1]);
				break;
			default:
				throw ("must have 1 or 2 channels, and must be 8 or 16 bit");
				break;
			}
		}
		//delete[] data;
		return usableData;
	}
	catch (std::string error) {
		if (soundFile != NULL) fclose(soundFile);
		throw (error);
		return std::vector<std::vector<short>>();
	}
}