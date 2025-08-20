#pragma once
#include <array>
#include <thread>
#include <print>
#include <exception>
#include <iostream>

class TasksTry
{
public:
	TasksTry() = default;


	// enable default move semantics
	TasksTry(TasksTry&&) = default;
	TasksTry& operator=(TasksTry&&) = default;
	~TasksTry()
	{
		for (int i = 0; i < m_numThreads; ++i) 
		{
			m_threads[i].join();
		}

	}
public:
	template<typename T>
	void start(T op)
	{
		m_threads[m_numThreads] = std::thread{ std::move(op) };
		++m_numThreads;
		std::println("TasksTry start template provoked!");
	}
private:
	std::array<std::thread, 10> m_threads;
	uint64_t m_numThreads{ 0 };


/*
Sample Code: 
	try
    {
        TasksTry ts;
        ts.start([]
            {
                std::this_thread::sleep_for(std::chrono::seconds{ 2 });
                std::println("t1 done");
            });
        ts.start([]
            {
                std::println("t2 done");
            });
        TasksTry other{ std::move(ts) };
    }
    catch (const std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << '\n';
    }

*/

};