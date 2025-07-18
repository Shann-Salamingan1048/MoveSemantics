#include "Exercises.h"
void Exercises::Run()
{
	std::println();
	std::println("String Exercise: ");
	StringExercise();
	std::println("move_a_vectorExercise Exercise: ");
	move_a_vectorExercise();
	std::println("moveSemanticsInAClass Exercise: ");
	moveSemanticsInAClass();
	std::println("concatenateStr Exercise: ");
	concatenateStr();
	std::println("moveAndSwap Exercise: ");
	moveAndSwap();
}
void Exercises::moveAndSwap()
{
	std::string str1 = "Sample1";
	std::string str2 = "Sample2";
	std::string temp = std::move(str1);

	str1 = std::move(str2);
	str2 = std::move(temp);
	printStr(str1);
	printStr(str2);
}
void Exercises::concatenateStr()
{
	std::string str1 = "Hi";
	std::string str2 = "Hello";
	// str1 +=  std::move(str2); // its not empty
	str1 = str1 + std::move(str2); // its empty
	printStr(str1);
	printStr(str2);

}

void printResourceHolder(const ResourceHolder& rh)
{
	if (rh.strClass.empty())
	{
		std::println("ResourceHolder strClass is Empty!(0)");
		return;
	}
	std::println("ResourceHolder strClass: {}", rh.strClass);
}

void Exercises::moveSemanticsInAClass()
{
	ResourceHolder rh1;
	ResourceHolder rh2{ std::move(rh1) };

	printResourceHolder(rh1);
	printResourceHolder(rh2);
}

ResourceHolder::ResourceHolder(const std::string& str)
	: strClass{ str } {}
ResourceHolder::ResourceHolder()
	: strClass {"Sample"} { }
ResourceHolder::ResourceHolder(const ResourceHolder& other)
	: strClass {other.strClass} { }
ResourceHolder::ResourceHolder(ResourceHolder&& other) noexcept
	: strClass {std::move(other.strClass)} { }

void printVectorSize(const std::vector<int>& vec)
{
	if (vec.empty())
	{
		std::println("Vector is Empty!(0)");
		return;
	}
	std::println("Vector Size: {}", vec.size());
}
std::vector<int> stealVector(std::vector<int>& vec)
{
	return std::move(vec);
}
void Exercises::move_a_vectorExercise()
{
	std::vector<int> originalVector{ 1,2,3 };
	std::vector<int> newVec{ stealVector(originalVector) };
	printVectorSize(originalVector);
	printVectorSize(newVec);
}

std::string transferString(std::string& input)
{
	return std::move(input);
}
void printStr(const std::string& str)
{
	if (str.empty())
	{
		std::println("String Empty!(0)");
		return;
	}
	std::println("String: {}", str);
}
void Exercises::StringExercise()
{
	std::string originalString = "Sample";
	std::string newString = transferString(originalString);
	
	printStr(originalString);
	printStr(newString);
}