#pragma once
#include <Windows.h>
#include <mmsystem.h>
#include "Entity.h"

class AudioClip : Module
{
private:
	LPCSTR filename;

public:
	void Play()
	{
		PlaySound(filename, NULL, SND_ASYNC);
	}

	AudioClip(char* filename);
	~AudioClip();
};