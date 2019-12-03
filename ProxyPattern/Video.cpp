#include "stdafx.h"
#include "Video.h"
#include <cstdlib>
#include <thread>

using namespace std;

void BeginState::ExecuteState(Video* videoRef)
{
	if (videoRef->GetVInfo() != NULL)
	{
		if (videoRef->GetVInfo()->GetState != NULL)
		{
			delete videoRef->GetVInfo()->GetState();
			videoRef->GetVInfo()->SetState(new PlayState());
		}
	}
}

void PlayState::ExecuteState(Video* videoRef)
{
	if (videoRef->GetVInfo() != NULL)
	{
		"\n(Video is playing)-[ElapsedDuration: " + to_string(videoRef->GetVInfo()->GetElapsedDuration()) + " DurationLeft: " + to_string(videoRef->GetVInfo()->GetDurationLeft()) + "]\n";
		videoRef->GetVInfo()->ElapsedDuration();
		videoRef->GetVInfo()->DurationLeft();
	}
}
void PauseState::ExecuteState(Video* videoRef)
{
	if (videoRef->GetVInfo() != NULL)
	{
		if (videoRef->GetVInfo()->GetState != NULL)
		{
			"\n(Video is paused)-[ElapsedDuration: " + to_string(videoRef->GetVInfo()->GetElapsedDuration()) + " DurationLeft: " + to_string(videoRef->GetVInfo()->GetDurationLeft()) + "]\n";
		}
	}
}
void StopState::ExecuteState(Video* videoRef)
{
	if (videoRef->GetVInfo() != NULL)
	{
		if (videoRef->GetVInfo()->GetState != NULL)
		{
			"\n(Video is stopped)\n";
		}
	}
}

void BeginState::ExecuteState(Video* videoRef)
{
	if (videoRef->GetVInfo() != NULL)
	{
		if (videoRef->GetVInfo()->GetState != NULL)
		{
			delete videoRef->GetVInfo()->GetState();
			videoRef->GetVInfo()->SetState(new PlayState());
		}
	}
}
VideoInfo::VideoInfo(string id, string name, string completePath, string resolution, bool isHD, unsigned int duration):m_id(id),m_name(name),
                                                                                                                                           m_completePath(completePath),m_resolution(resolution),
	                                                                                                                                       m_isHD(isHD),m_duration(duration),m_elapsedDuration(0),m_durationLeft(duration)

{
}

VideoInfo::~VideoInfo()
{

}

void VideoInfo::SetName(string name)
{
	m_name = name;
}

void VideoInfo::SetCompletePath(string path)
{
	m_completePath = path;
}

void VideoInfo::SetState(IVideoState* videoState)
{
	m_videoState = videoState;
}

void VideoInfo::ElapsedDuration()
{
	++m_elapsedDuration;
}
void VideoInfo::DurationLeft()
{
	--m_durationLeft;
}

unsigned int VideoInfo::GetElapsedDuration()
{
	return m_elapsedDuration;
}

unsigned int VideoInfo::GetDurationLeft()
{
	return m_durationLeft;
}

unsigned int VideoInfo::GetDuration()
{
	return m_duration;
}

IVideoState* VideoInfo::GetState()
{
	return m_videoState;
}

Video::Video(VideoInfo* videoInfo):m_videoInfo(videoInfo)
{
	cout << "\n Created video : " << m_videoInfo->GetInfo();
	m_videoInfo->SetState(VideoState::BEGINNING);
}

Video::~Video()
{
	cout << "\n Destroyed : " << m_videoInfo->GetInfo();

	if (m_videoInfo != NULL)
	{
		delete m_videoInfo;
	}
}

string Video::VideoRunner(VideoState state)
{
	string runTimeString;

	if (VideoState::PLAYING == state)
	{
		m_videoInfo->ElapsedDuration();
		m_videoInfo->DurationLeft();

		runTimeString = "Video is playing";
	}

	if (VideoState::PAUSE == state)
	{
		runTimeString = "Video is paused";
	}

	return "\n("+runTimeString+")-[ElapsedDuration: " + to_string(m_videoInfo->GetElapsedDuration()) + " DurationLeft: " + to_string(m_videoInfo->GetDurationLeft()) + "]\n";
}

VideoState Video::State()
{
	return m_videoInfo->GetState();
}

void Video::Run()
{

	while (m_videoInfo->GetDurationLeft() > 0 && m_videoInfo->GetElapsedDuration() < m_videoInfo->GetDuration())
	{
		cout << VideoRunner(State());
	}
}

void Video::Control()
{
	while (State() == VideoState::PLAYING || State() == VideoState::PAUSE)
	{
		char ch;
		cin >> ch;

		if (ch == 'P' || ch == 'p')
		{
			m_videoInfo->SetState(VideoState::PAUSE);
		}

		if (ch == 'S')
		{
			m_videoInfo->SetState(VideoState::STOPPED);
		}
	}
}

void Video::Play()
{
	m_videoInfo->SetState(VideoState::PLAYING);

	thread Run(&Video::Run,this);
	thread Control(&Video::Control, this);

	while (1)
	{

	}
}
