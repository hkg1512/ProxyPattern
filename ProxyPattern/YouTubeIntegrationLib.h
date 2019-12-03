#pragma once
#ifndef YTIL_H
#define YTIL_H

#include "IYouTubeLib.h"
#include "Video.h"

class YouTubeIntegrationLib: public IYouTubeLib
{
public:
	YouTubeIntegrationLib();
	virtual ~YouTubeIntegrationLib();

	virtual Video* Download(std::string videoLink, std::string videoName);
};

#endif