#include "MoveSemantics1.h"
#include "Exercises.h"
#include "Exercises2.h"
#include "Example.h"
int main()
{
    //MoveSemantics ms;
    //ms.v = ms.initVector1();
 //   printVector(ms.v);  // Output: data datadata data     

 //   std::println("{} ", ms.v.size());

 //   // Resize to 3 elements (removes last 4 elements)
 //   ms.v.resize(3);
 //   std::println("{} ", ms.v.size());

 //   printVector(ms.v);  // Output: data datadata data

 //   Exercises e;
 //   e.Run();

    //Exercises2 e2;
    //e2.Run();

	std::vector<PerformanceInGet> v{ 10000 };
	auto start = std::chrono::high_resolution_clock::now();
	for (const auto& p : v) // const std::string& getName() const&
	{
		if (p.getName().empty()) // safe but slow
			// Copies `name` unnecessarily
			std::print("");
	}
	auto end = std::chrono::high_resolution_clock::now();
	std::println("Time Took: {}ns", (end - start).count());

	PerformanceInGet p{ "Shanny" };
	start = std::chrono::high_resolution_clock::now();
	for (char c : returnPerformanceInGetByValue().getName()) // std::string getName()&&
	{
		if(c == ' ')
			std::print("");
	}
	end = std::chrono::high_resolution_clock::now();
	std::println("Time Took: {}ns", (end - start).count());

	return 0;

    // page 54 or 93/260
}