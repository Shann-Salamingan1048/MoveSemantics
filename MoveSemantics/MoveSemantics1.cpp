#include "MoveSemantics1.h"

void printVector(const std::vector<std::string>& v)
{
	for (const auto& val : v)
	{
        if (val.empty())
        {
            std::print("Empty!(0) ");
            continue;
        }
		std::print("{} ", val);
	}
	std::println();
}

std::vector<std::string> MoveSemantics::initVector1()
{
    std::vector<std::string> v;
    v.reserve(3);  // Allocates memory but doesn't change size
    std::string s = "data";

    v.push_back(s);            // copies "data" (v.size() = 1)
    v.push_back(s + s);        // creates and copies "datadata" (v.size() = 2)
    v.push_back(std::move(s)); // moves "data" (v.size() = 3, s is now empty)
    // in order for std::move() to take effect it should have a function that supports rvalue reference
    // otherwise the copy constructor will be activated instead or in other term the std::move() will not be in effect
    // the std::move() will cast it into rvalue
    
    // std::move cant move const for const blocks moving
    // These will cause reallocation since we exceeded reserve(3)
    //v.push_back(s);            // copies empty string (v.size() = 4)
    //v.push_back(s);            // copies empty string (v.size() = 5)
    //v.push_back(s);            // copies empty string (v.size() = 6)
    //v.push_back(s);            // copies empty string (v.size() = 7)

    return v;
}