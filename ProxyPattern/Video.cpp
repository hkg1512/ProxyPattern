#include "stdafx.h"
#include "Video.h"

#include <cstdlib>
#include <thread>

using namespace std;

void BeginState::ExecuteState(Video* videoRef)
{
	if (videoRef->GetVInfo() != NULL)
	{
		if (videoRef->GetVInfo()->GetState() != NULL)
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
		cout << "\n(Video is playing)-@-[ElapsedDuration: " + to_string(videoRef->GetVInfo()->GetElapsedDuration()) + " DurationLeft: " + to_string(videoRef->GetVInfo()->GetDurationLeft()) + "]\n";
		videoRef->GetVInfo()->ElapsedDuration();
		videoRef->GetVInfo()->DurationLeft();

		if (videoRef->GetVInfo()->GetElapsedDuration() - videoRef->GetVInfo()->GetDurationLeft() == 60)
		{
			delete videoRef->GetVInfo()->GetState();
			videoRef->GetVInfo()->SetState(new PauseState());
		}

		if (videoRef->GetVInfo()->GetElapsedDuration() - videoRef->GetVInfo()->GetDurationLeft() == videoRef->GetVInfo()->GetDuration())
		{
			delete videoRef->GetVInfo()->GetState();
			videoRef->GetVInfo()->SetState(new StopState());
		}
	}
}
void PauseState::ExecuteState(Video* videoRef)
{
	if (videoRef->GetVInfo() != NULL)
	{
		if (videoRef->GetVInfo()->GetState() != NULL)
		{
			cout << "\n(Video is paused)-@-[ElapsedDuration: " + to_string(videoRef->GetVInfo()->GetElapsedDuration()) + " DurationLeft: " + to_string(videoRef->GetVInfo()->GetDurationLeft()) + "]\n";

			unsigned int iState = (rand() % 10 + 1);

			if (5 == iState)
			{
				delete videoRef->GetVInfo()->GetState();
				videoRef->GetVInfo()->SetState(new PlayState());
			}

			if (8 == iState)
			{
				delete videoRef->GetVInfo()->GetState();
				videoRef->GetVInfo()->SetState(new StopState());
			}
		}
	}
}
void StopState::ExecuteState(Video* videoRef)
{
	if (videoRef->GetVInfo() != NULL)
	{
		if (videoRef->GetVInfo()->GetState() != NULL)
		{
			cout << "\n(Video is stopped)\n";
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

void VideoInfo::ResetElapsedDuration()
{
	m_elapsedDuration = 0;
}

void VideoInfo::ResetDurationLeft()
{
	m_durationLeft = m_duration;
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

string VideoInfo::GetCompletePath()
{
	return m_completePath;
}

Video::Video(VideoInfo* videoInfo):m_videoInfo(videoInfo)
{
	cout << "\nVideo : " << m_videoInfo->GetInfo();

	srand(time(NULL));
}

Video::~Video()
{
	cout << "\n Destroyed : " << m_videoInfo->GetInfo();

	if (m_videoInfo != NULL)
	{
		delete m_videoInfo;
	}
}

void Video::Run()
{
	while (m_videoInfo->GetDurationLeft() > 0 && m_videoInfo->GetElapsedDuration() < m_videoInfo->GetDuration())
	{
		m_videoInfo->GetState()->ExecuteState(this);

		if (dynamic_cast<StopState*>(m_videoInfo->GetState()) != NULL)
		{
			m_videoInfo->GetState()->ExecuteState(this);
			m_videoInfo->ResetElapsedDuration();
			m_videoInfo->ResetDurationLeft();
			break;
		}
	}
}

void Video::Play()
{
	if (m_videoInfo->GetState() != NULL)
	{
		delete m_videoInfo->GetState();
	}

	m_videoInfo->SetState(new BeginState());

	thread Run(&Video::Run,this);

	Run.join();
}
