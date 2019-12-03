#include "stdafx.h"
#include "YouTubeLibProxy.h"
#include <iostream>

using namespace std;

YouTubeLibProxy::YouTubeLibProxy()
{
}


YouTubeLibProxy::~YouTubeLibProxy()
{
}

bool YouTubeLibProxy::CheckInCache(string videoPath)
{
	for (auto itr = m_videoCache.begin(); itr != m_videoCache.end(); ++itr)
	{
		if ((*itr)->GetVInfo()->GetCompletePath() == videoPath)
		{
			return true;
		}
	}

	return false;
}

Video* YouTubeLibProxy::RetrieveFromCache(string videoPath)
{
	for (auto itr = m_videoCache.begin(); itr != m_videoCache.end(); ++itr)
	{
		if ((*itr)->GetVInfo()->GetCompletePath() == videoPath)
		{
			return *itr;
		}
	}

	return NULL;
}

Video* YouTubeLibProxy::Download(std::string videoLink, std::string videoName)
{
	if (!m_videoCache.empty() && CheckInCache(videoLink + "/" + videoName))
	{
		cout << "\nVideo in cache!\n";
		return RetrieveFromCache(videoLink + "/" + videoName);
	}
	else
	{
		cout << "\nVideo download in progress... \n";

		if (m_youTubeIntegrationLib == NULL)
		{
			m_youTubeIntegrationLib = new YouTubeIntegrationLib();
		}

		m_videoCache.push_back(m_youTubeIntegrationLib->Download(videoLink, videoName));
	}

	return m_videoCache.at(m_videoCache.size()-1);
};