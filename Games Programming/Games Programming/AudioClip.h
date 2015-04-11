#pragma once
#include <Windows.h>
#include <mmsystem.h>
#include "Entity.h"

class AudioClip : Module
{
private:
	string name;
	LPCSTR filename;

public:
	void Play()
	{
		string command = "play " + name;
		mciSendString(command.c_str(), NULL, 0, 0);
	}

	void Pause()
	{
		string command = "pause " + name;
		mciSendString(command.c_str(), NULL, 0, 0);
	}

	void Stop()
	{
		string command = "stop " + name;
		mciSendString(command.c_str(), NULL, 0, 0);
	}

	AudioClip(string filename, string name)
	{
		string command = "open " + filename + " type mpegvideo alias " + name;
		mciSendString(command.c_str(), NULL, 0, 0);
	}
	~AudioClip()
	{

	}
};