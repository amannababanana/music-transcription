#include "playMusic.h"

unsigned int alSource;
unsigned int alSampleSet;

void startAL()
{
	ALCdevice *dev;
	ALCcontext *ctx;

	//initialize everything
	dev = alcOpenDevice(NULL);
	if (!dev)
	{
		throw ("Oops\n");
	}
	ctx = alcCreateContext(dev, NULL);
	alcMakeContextCurrent(ctx);
	if (!ctx)
	{
		throw ("Oops2\n");
	}
	alGetError();
}

void startMusic(ALuint buffer)
{
	alSampleSet = buffer;
	//provide all the required parameters
	alGenSources(1, &alSource);
	alSourcei(alSource, AL_BUFFER, alSampleSet);
	alSource3f(alSource, AL_POSITION, 1, 0, 0);
	alSource3f(alSource, AL_VELOCITY, 0, 0, 0);
	float listenerx, listenery, listenerz;
	float vec[6];
	listenerx = 0.0f;
	listenery = 0.0f;
	listenerz = 0.0f;
	vec[0] = 1; //forward x
	vec[1] = 0;
	vec[2] = 0;
	vec[3] = 0; //up x
	vec[4] = 1;
	vec[5] = 0;
	alListener3f(AL_POSITION, listenerx, listenery, listenerz);
	alListenerfv(AL_ORIENTATION, vec);
	alSourcei(alSource, AL_LOOPING, AL_TRUE);

	//play the music
	alSourcePlay(alSource);
}

void stopMusic()
{
	//stop playing the music
	alSourceStop(alSource);

	//de-initialize everything
	alDeleteSources(1, &alSource);
	alDeleteBuffers(1, &alSampleSet);
	auto Context = alcGetCurrentContext();
	auto Device = alcGetContextsDevice(Context);
	alcMakeContextCurrent(NULL);
	alcDestroyContext(Context);
	alcCloseDevice(Device);
}