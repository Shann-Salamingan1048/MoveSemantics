#pragma once
#include <string>
#include <print>
#include <vector>
std::string transferString(std::string& input);
std::vector<int> stealVector(std::vector<int>& vec);

void printStr(const std::string& str);
void printVectorSize(const std::vector<int>& vec);

class ResourceHolder
{
public:
	ResourceHolder();
	ResourceHolder(const std::string& str);

	ResourceHolder(ResourceHolder&& other) noexcept; // move constructor
	ResourceHolder(const ResourceHolder& other); // copy constructor

	std::string strClass;
};

void printResourceHolder(const ResourceHolder& rh);
class Exercises
{
public:
	void Run();
private:
	void StringExercise(); //Create a function transferString that 
	//takes a std::string input, moves it into another std::string,
	// and returns the new string. Verify that the original string 
	// is empty after the move.

	void move_a_vectorExercise(); // Write a function stealVector that 
	//takes a std::vector<int>, moves it into another vector, and 
	// returns the new vector. Print the size of the original vector 
	// after the move to confirm it was emptied.
	void moveSemanticsInAClass(); // Define a class ResourceHolder with 
	//a std::string member.Implement a move constructor that transfers 
	// ownership of the string from another ResourceHolder object.
	// Test it by moving one object into another.
	void concatenateStr(); // Write a function combineStrings that takes 
	//two std::string objects, moves the second string into the first 
	// (e.g., s1 += std::move(s2)), and returns the result. 
	// Check if the second string is empty afterward.
	void moveAndSwap(); //Create a function swapWithMove that swaps 
	//two std::string objects using std::move(instead of the 
	// traditional copy - based swap).Verify that the swap worked 
	// correctly.

	
};

