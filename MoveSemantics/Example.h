#pragma once
#include <vector>
#include <print>
#include <array>
#include <string>
#include <chrono>
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



class PerformanceInGet // Reference Qualifier
{

public:
	//std::string getName() const
	//{
	//	return name;
	//}
	PerformanceInGet(const std::string& s) : name{ s } {}
	PerformanceInGet(std::string&& s) : name{ std::move(s) } {}
	PerformanceInGet() : name{  } {}
	const std::string& getName() const&
	{
		return name;
	}
	std::string getName()&&
	{
		return std::move(name);
	}
	/*
		//- callable — who can call the function(based on qualifiers like const, &, &&)
			    // 🔹 Non-const lvalue
				std::string& ref = p.getName(); // Calls getName() &
				std::cout << "ref = " << ref << "\n";

				// 🔹 Const lvalue
				const std::string& cref = cp.getName(); // Calls getName() const&
				std::cout << "cref = " << cref << "\n";

				// 🔹 Rvalue
				std::string moved = PerformanceInGet().getName(); // Calls getName() &&
				std::cout << "moved = " << moved << "\n";

				// 🔹 Const rvalue
				std::string cmoved = std::move(cp).getName(); // Calls getName() const&&
				std::cout << "cmoved = " << cmoved << "\n";


	
	// -  returned — what the function gives back (based on return type like std::string, std::string&, std::string&&)
	
	
	*/
	

	/*
	Structure: 
		<return-type> <function-name>() [const] [& or &&] 
		{
			// function body
		}	
		std::string& getName()   // returns a reference
		std::string&& getName()  // returns an rvalue reference
		std::string getName()    // returns a copy

		std::string getName() &         // only callable on lvalues
		std::string getName() &&        // only callable on rvalues
		std::string getName() const&    // only callable on const lvalues
		std::string getName() const&&   // only callable on const rvalues
	*/
/*
Sample Code:
	std::vector<PerformanceInGet> v{ 10000};
	auto start = std::chrono::high_resolution_clock::now();
	for (const auto& p: v)
	{
		if (p.getStrConst().empty()) // safe but slow
			// Copies `name` unnecessarily
			std::print("");
	}
	auto end = std::chrono::high_resolution_clock::now();
	std::println("Time Took: {}ns", (end - start).count());


	start = std::chrono::high_resolution_clock::now();
	for (const auto& p: v)
	{
		if (p.getStrConsRefConst().empty()) // unsafe but fast
			std::print("");
		// Lifetime risks (dangling references if the source object is destroyed).
		// // UB! Temporary dies immediately
		//for (char c : p.getStrConsRefConst())
		//{
		//    if (c == ' ')
		//    {
		//
		//    }
		//}
	}
	end = std::chrono::high_resolution_clock::now();
	std::println("Time Took: {}ns", (end - start).count());
*/
/*
Performance Enhanced:
	std::vector<PerformanceInGet> v{ 100000 };
	auto start = std::chrono::high_resolution_clock::now();
	for (const auto& p : v)
	{
		if (p.getName().empty()) // safe but slow
			// Copies `name` unnecessarily
			std::print("");
	}
	auto end = std::chrono::high_resolution_clock::now();
	std::println("Time Took: {}ns", (end - start).count());

	PerformanceInGet p{ "Shanny" };
	start = std::chrono::high_resolution_clock::now();
	for (char c : p.getName())
	{
		if(c == ' ')
			std::print("");
	}
	end = std::chrono::high_resolution_clock::now();
	std::println("Time Took: {}ns", (end - start).count());

*/
private:
	std::string name;
};
PerformanceInGet returnPerformanceInGetByValue()
{
	PerformanceInGet p("Shanny");
	return p; // returns a copy (or move if optimized)
}
/*
Sample Code:
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

*/

class C
{
public:
	void foo() const&
	{
		std::println("foo() const& provoked!");
	}
	void foo()&
	{
		std::println("foo()& provoked!");
	}
	void foo()&&
	{
		std::println("foo()&& provoked!");
	}
	void foo() const&&
	{
		std::println("foo() const&& provoked!");
	}
	//void foo() const
	//{

	//}// ERROR: can’t overload by both reference and value qualifiers
	/*
	Sample Code:
		C x;
		x.foo(); // calls foo()&
		C{}.foo(); // calls foo()&&
		std::move(x).foo(); // calls foo()&&
    
		const C cx;
		cx.foo(); // calls foo() const&

		std::move(cx).foo(); // calls foo() const&&
	
	*/
};