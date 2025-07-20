#include "Exercises2.h"

void Exercises2::Run()
{
	DynamicArrayClass();
	MoveOnlyWrapper();
	FallbackToCopying();
}
void Exercises2::DynamicArrayClass()
{
	std::println("Dynnamic Array Class: ");
	DynamicArray<int> da{ 5 };
	for (uint8_t i = 0; i < 5; ++i)
		da.push_back(i);

	DynamicArray<int> da2 = da;
	DynamicArray<int> da3 = std::move(da);

	printArr(da.getArr(), da.getSize());
	printArr(da2.getArr(), da2.getSize());
	printArr(da3.getArr(), da3.getSize());

}

void Exercises2::MoveOnlyWrapper()
{
	std::println("Move only wrapper: ");
	MoveOnlyString mos{ "Sample1" };
	MoveOnlyString mos2{ std::move(mos)};
	MoveOnlyString mos3;
	mos3 = std::move(mos2);

}
void Exercises2::FallbackToCopying()
{
	std::vector<std::string> v{"Shann", "Delfin", "Caturla", "Salamingan", "III"};
	Document d(std::move(v), 10);

	Document d2{ std::move(d) };

	std::println("Fall back to copying: ");
	printVec(v);
	printVec(d.vec);
	std::println(", ID: {}", d.docID);
	printVec(d2.vec);
	std::println(", ID: {}", d2.docID);
}