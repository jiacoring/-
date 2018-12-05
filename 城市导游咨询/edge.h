#pragma once

#include<string>

enum class road
{
	driveway, //车道
	sidewalk  //人行道
};
enum class viewLev
{
	bad,
	normal,
	nice,
	grand
};
struct edge {
	road rd;
	viewLev vLev;
	int length;
	std::string name;
};
