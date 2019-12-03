#pragma once
#ifndef VIDEO_H
#define VIDEO_H

#include <iostream>
#include <string>

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

	void SetName(std::string name);
	void SetCompletePath(std::string path);
	void SetState(IVideoState* videoState);

	inline std::string GetInfo() { return std::string("[Id: " + m_id + " Name: " + m_name + " FullPath: " + m_completePath + " Resolution: " + m_resolution + " HD: " + std::to_string(m_isHD) + " Duration: " +std::to_string(m_duration)); }
};


class Video
{
private:	
	VideoInfo * m_videoInfo;

private:
	void Run();
	void Control();
	std::string VideoRunner(VideoState state);
	VideoState State();


public:
	Video(VideoInfo* videoInfo);
	~Video();

	VideoInfo* GetVInfo() { return m_videoInfo; };

	void Play();
};

#endif

