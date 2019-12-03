#pragma once
#ifndef IYTL_H
#define IYTL_H

#include "Video.h"

class IYouTubeLib
{
public:
	virtual Video* Download(std::string videoLink, std::string videoName) = 0;
};
#endif