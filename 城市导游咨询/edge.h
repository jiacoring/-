#pragma once

#include<string>

enum class road
{
	driveway, //����
	sidewalk  //���е�
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
