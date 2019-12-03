#include "stdafx.h"
#include "YouTubeIntegrationLib.h"

#include <cstdlib>

using namespace std;

YouTubeIntegrationLib::YouTubeIntegrationLib()
{
	srand(time_t(NULL));
}

YouTubeIntegrationLib::~YouTubeIntegrationLib()
{
}

Video* YouTubeIntegrationLib::Download(string videoLink, string videoName)
{
	const string resolutionArray[5] = { "800x600", "1024x768","1280x768","1900x1600","3840x2160" };
	const bool isHDArray[2] = { true, false };

	return new Video(new VideoInfo("#" + to_string(rand() % 5000 + 1000), videoName, videoLink + "/" + videoName, resolutionArray[rand() % 5 + 1], isHDArray[rand() % 2 + 1], rand() % 5000 + 1));
}