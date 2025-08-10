#pragma once
#include <vector>
#include <print>
#include <array>
#include <string>
/*
	When it comes to initialization, Pass by value + move is best
	When it comes to modifying existing members, Pass by value const& is best
	When it comes cheap move operations such as vectors, strings, pass by value + move is best
	When it comes expensive move operations such as std::arrays, Large structs, or types with many small allocations, Overload Constructors are the best
	When it comes adding to containers (vectors, arrays), Pass by value  + move is best

	Cheap Moves  (O(1)):
		The type uses pointer indirection (e.g., dynamic allocations).
		Moving only swaps pointers, avoiding deep copies.
			Examples:
				std::string (typically stores data on the heap).
				std::vector, std::list, std::unordered_map (own heap-allocated data).
				std::unique_ptr (just a pointer swap).

	Expensive Moves (O(N)):
		The type stores data contiguously in itself (no indirection).
		Moving requires copying/moving each element individually.
			Examples:
				std::array<T, N> (fixed-size stack allocation, moves each T).
				Plain structs with many members (struct BigData { int[1000]; };).
				std::tuple or std::pair with non-movable types.


	Small objects (e.g., int, double) are cheap to copy/move.
	Large objects (e.g., std::array<int, 1000000>) are costly.

	Compare copy vs. move performance:
	BenchMark:
		auto start = std::chrono::high_resolution_clock::now();
		auto moved_obj = std::move(obj);  // Test move
		auto end = std::chrono::high_resolution_clock::now();
		std::println("Move took: {}ns, (end - start).count()); 

	If move ≈ copy time → Expensive.
	If move ≪ copy time → Cheap.
*/
class example
{
public:
	example(std::string n, std::vector<std::string> v, const std::array<std::string, 1000>& arr)
	: name{std::move(n)}, valVec{std::move((v))}, valArr(arr)
	{}
	example(std::string n, std::vector<std::string> v,  std::array<std::string, 1000>&& arr)
		: name{ std::move(n) }, valVec{ std::move((v)) }, valArr(std::move(arr))
	{}

	void setName(const std::string s)
	{
		name = s; 
		// The assignment operator will
		// only allocate new memory if the new length exceeds the current amount of memory allocated for the value.
	}
	void addVec(std::string s)
	{
		valVec.push_back(std::move(s));
	}
	void setArr(const std::string& s, uint64_t index)
	{
		valArr[index] = s;
	}
private:
	std::string name;
	std::vector<std::string> valVec;
	std::array<std::string, 1000> valArr;

};


class objDerived
{
public:
	virtual void run() const = 0;
	virtual ~objDerived() = default;
	objDerived() = default;

protected:
	// declare the copy operator
	objDerived(const objDerived&) = default;
	objDerived(objDerived&&) = default;

	// delete assignment operator
	objDerived& operator=(const objDerived&) = delete;
	objDerived& operator=(objDerived&&) = delete;
	// Well You could just remove the virtual destructor so that you wont declare those. 
	// Declare the virtual destructor in derived classes only when needed
protected: // only the inhitors will inherit this class
	std::string name;
};
class inhitorObj : public objDerived
{
public:
	void run() const
	{
		std::println("inhitor Run Provoked! with value: {}", RadiusDaw);
	}

	const int RadiusDaw = 10;

	/*
	Sample Code:
				inhitorObj lol;
				objDerived& idk{ lol };
				idk.run();
				// idk = lol; // it sliced because assignment operator is not virtual.
				// slice means only the derivedClass is copied meaning everything else in inhitors will not be copied.
				// so it errors
				// to solve this delete the assignment operators to prevent it to accident assigns
				// now after deleting it, now it errors to prevent us from assignments
				lol.run();
				std::println("lol: {}", lol.RadiusDaw);

				//idk = lol;
				idk.run();
				//std::println("idk: {}", idk.RadiusDaw);
	
	*/
};