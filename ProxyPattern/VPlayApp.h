#pragma once
#ifndef VPLAYAPP_H
#define VPLAYAPP_H

#include "IYouTubeLib.h"

class VPlayApp
{
private:
	IYouTubeLib * m_youTubeInf;

public:
	VPlayApp();
	~VPlayApp();

	void GetVideo();
};

#endif
