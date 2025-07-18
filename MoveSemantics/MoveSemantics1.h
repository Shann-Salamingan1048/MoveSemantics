#pragma once
#include <vector>
#include <string>
#include <print>

void printVector(const std::vector<std::string>& v);

class MoveSemantics
{
public:
	std::vector<std::string> v;

	std::vector<std::string> initVector1();
};