// ProxyPattern.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "VPlayApp.h"
#include <iostream>

int main()
{
	VPlayApp vApp;

	vApp.GetVideo();

	char ch;
	std::cin >> ch;

	return 0;
}

