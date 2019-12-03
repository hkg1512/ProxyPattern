// ProxyPattern.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Video.h"
#include <iostream>

int main()
{
	Video* video = new Video(new VideoInfo("#1200", "SampleVideo.mp4", "C:/Users/ganghar/Documents/SampleVideo.mp4", "1280x720", true, 1000));
	video->Play();

	char ch;
	std::cin >> ch;

	return 0;
}

