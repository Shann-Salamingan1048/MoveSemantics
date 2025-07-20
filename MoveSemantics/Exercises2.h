#pragma once
#include <print>
#include <expected>
#include <vector>
#include <string>
template<typename T>
class DynamicArray
{
public:
	DynamicArray(size_t initialCapacity = 0)
		: m_size{ initialCapacity }, m_capacity{ initialCapacity }
	{
		if (m_capacity > 0)
			m_arr = new T[m_capacity];
		std::println("Constructor has been provoked");
	}

	~DynamicArray()
	{
		delete[] m_arr;
		std::println("Destructor has been provoked");
	}

	DynamicArray(const DynamicArray& other)
		: m_size{ other.m_size }, m_capacity{ other.m_capacity }
	{
		if (m_capacity > 0)
		{
			m_arr = new T[m_capacity];
			std::copy(other.m_arr, other.m_arr + m_size, m_arr);
			std::println("Copy Constructor has been provoked");
		}
	}
	DynamicArray(DynamicArray&& other) noexcept
		: m_arr{ other.m_arr }, m_size{ other.m_size }, m_capacity{ other.m_capacity }
	{
		other.m_arr = nullptr;
		other.m_size = 0;
		other.m_capacity = 0;

		std::println("Move Constructor has been provoked");
	}
public:
	void push_back(T val)
	{
		if (m_size == m_capacity)
			resize();
		m_arr[m_size++] = val;
	}

	void resize()
	{
		m_capacity = m_capacity == 0 ? 1 : m_capacity * 2;
		T* newArr = new T[m_capacity];

		std::copy(m_arr, m_arr + m_size, newArr);
		delete[] m_arr;
		m_arr = newArr;
	}


public:
	size_t getSize() const { return m_size; };
	size_t getCapacity() const { return m_capacity; };

	T getVal(size_t index) const
	{
		const auto result = outOfBoundsIndexGetVal(index);
		if (!result)
		{
			std::println("Error: {}", result.error());
		}
		return result.value();
	}

	void set(size_t index, T val)
	{
		const auto result = outOfBoundsIndexSetVal(index);
		if (!result)
		{
			std::println("Error: {}", result.error());
		}
		else
		{
			m_arr[index] = val;
			std::println("Successfully set the value {} at index {}.", val, index);
		}
	}

	T* getArr() const
	{
		return m_arr;
	}
private:
	std::expected<std::monostate, std::string> outOfBoundsIndexSetVal(size_t index)
	{
		if (index >= m_size)
			return std::unexpected("Index out of bounds");
		return std::monostate{}; // success no value to return
	}
	std::expected<T, std::string> outOfBoundsIndexGetVal(size_t index)
	{
		if (index >= m_size)
			return std::unexpected("Index out of bounds");
		return m_arr[index];
	}
private:
	T* m_arr = nullptr;
	size_t m_capacity; // Current allocated capacity of the array
	size_t m_size;  // Current number of elements in the array
};

template<typename T>
void printArr(T* arr, size_t size)
{
	if (size == 0)
	{
		std::println("The Array is Empty! ");
		return;
	}
	std::print("Array Elemnts: ");
	for (size_t i = 0; i < size; ++i)
	{
		std::print("{} ", i);
	}
	std::println();
}

struct MoveOnlyString
{
	MoveOnlyString()
		: stringMem{ "Default" }
	{
	}
	MoveOnlyString(const std::string& str)
		: stringMem{ str } 
	{
	}
	MoveOnlyString(MoveOnlyString&& other) noexcept
		: stringMem{ std::move(other.stringMem) }
	{
		std::println("Move Constructor has been provoked");
	}
	MoveOnlyString& operator=(MoveOnlyString&& other) noexcept
	{
		if (this != &other)
		{
			std::println("Move Assignment Constructor has been provoked");
			stringMem = std::move(other.stringMem);
		}
		return *this;
	};

	std::string stringMem;

};
template<typename T>
void printVec(const std::vector<T> v)
{
	if (v.size()  == 0)
	{
		std::println("The Vector is Empty! ");
		return;
	}
	std::print("Vector Elemnts: ");
	for(const auto& i : v)
		std::print("{} ", i);
}
class Document
{
public:
	Document(std::vector<std::string>& v, int id)
		: vec {v}, docID{id}
	{ 
		std::println("Constructor has been provoked");
	}
	Document(std::vector<std::string>&& v, int id) noexcept
		: vec{ std::move(v) }, docID{ id }
	{
		std::println("Constructor has been provoked");
		std::println("in a Constructor the vector move has been provoked");
	}
	Document(Document&& other) noexcept
		: vec { std::move(other.vec)}, docID {other.docID}
	{
		std::println("Move Constructor has been provoked");
	}

public:
	std::vector<std::string> vec;
	const int docID;
};
class Exercises2
{
public:
	void Run();


private:
	void DynamicArrayClass(); 
	/*
	Task: Implement a class DynamicArray that manages a 
	heap-allocated integer array. 
	Include:
		A copy constructor (deep copy).
		A move constructor (transfer ownership).
		A destructor to free memory.

	Test Case:
		Create an object arr1, populate it, then create arr2 
		via copy and arr3 via move. Verify memory ownership is 
		correctly transferred.
	*/
	void MoveOnlyWrapper();
	/*
	Task: Create a class MoveOnlyString that:
		Contains a std::string member.
		Disables copying (delete copy operations).
		Implements move constructor/assignment.
	Test Case:
		Move the object between functions and check that copies 
		are blocked at compile time.
	*/
	void FallbackToCopying();
	/*
	Task: Implement a class Document with:
		A movable member (std::vector<std::string> for lines).
		A non-movable member (const int docID).
	Goal:
		The move constructor should move the vector but copy docID. 
		Verify this behavior.
	
	*/
};