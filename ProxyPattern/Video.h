#pragma once
#ifndef VIDEO_H
#define VIDEO_H

#include <iostream>
#include <string>

class Video;

class IVideoState
{
public:
	virtual void ExecuteState(Video* videoRef) = 0;
};

class BeginState : public IVideoState
{
public:
	virtual void ExecuteState(Video* videoRef);
};

class PlayState : public IVideoState
{
public:
	virtual void ExecuteState(Video* videoRef);
};

class PauseState : public IVideoState
{
public:
	virtual void ExecuteState(Video* videoRef);
};

class StopState : public IVideoState
{
public:
	virtual void ExecuteState(Video* videoState);
};

class VideoInfo
{
private:
	std::string m_id;
	std::string m_name;
	std::string m_completePath;
	std::string m_resolution;

	bool m_isHD;

	unsigned int m_duration;
	unsigned int m_elapsedDuration;
	unsigned int m_durationLeft;

	IVideoState* m_videoState;

public:
	VideoInfo(std::string id, std::string name, std::string completePath, std::string resolution, bool isHD, unsigned int duration);
	~VideoInfo();

	void ElapsedDuration();
	void DurationLeft();

	unsigned int GetElapsedDuration();
	unsigned int GetDurationLeft();
	unsigned int GetDuration();
	IVideoState* GetState();
	std::string GetCompletePath();

	void SetName(std::string name);
	void SetCompletePath(std::string path);
	void SetState(IVideoState* videoState);
	void ResetElapsedDuration();
	void ResetDurationLeft();

	inline std::string GetInfo() { return std::string("\n[\n\tId: " + m_id + " \n\tName: " + m_name + " \n\tFullPath: " + m_completePath + \
		" \n\tResolution: " + m_resolution + " \n\tHD: " + std::to_string(m_isHD) + "\n\tDuration: " +std::to_string(m_duration))+"\n]\n\n\n"; }
};


class Video
{
private:	
	VideoInfo * m_videoInfo;

private:
	void Run();

public:
	Video(VideoInfo* videoInfo);
	~Video();

	VideoInfo* GetVInfo() { return m_videoInfo; };

	void Play();
};

#endif

