#pragma once
#ifndef YTLP_H
#define YTLP_H

#include "Video.h"
#include "IYouTubeLib.h"
#include "YouTubeIntegrationLib.h"
#include <vector>

class YouTubeLibProxy : public IYouTubeLib
{
private:
	std::vector<Video*> m_videoCache;
	YouTubeIntegrationLib* m_youTubeIntegrationLib;

private: 
	bool CheckInCache(std::string videoPath);
	Video* RetrieveFromCache(std::string videoPath);

public:
	YouTubeLibProxy();
	virtual ~YouTubeLibProxy();

	virtual Video* Download(std::string videoLink, std::string videoName);
};

#endif
