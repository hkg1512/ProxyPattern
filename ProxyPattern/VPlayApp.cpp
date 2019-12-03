#include "stdafx.h"
#include "VPlayApp.h"

#include "YouTubeLibProxy.h"

using namespace std;

VPlayApp::VPlayApp():m_youTubeInf(new YouTubeLibProxy())
{
	cout << "\n Welcome to VPlay App V.1.00.0";
}

VPlayApp::~VPlayApp()
{
	delete m_youTubeInf;
}

void VPlayApp::GetVideo()
{
	int count = 5;

	while (count--)
	{
		m_youTubeInf->Download("https://youtube.com", "P45ff2dqd3")->Play();
	}
}