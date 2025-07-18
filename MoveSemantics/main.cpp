#include "MoveSemantics1.h"
#include "Exercises.h"
int main()
{
	MoveSemantics ms;
	ms.v = ms.initVector1();
    printVector(ms.v);  // Output: data datadata data     

    std::println("{} ", ms.v.size());

    // Resize to 3 elements (removes last 4 elements)
    ms.v.resize(3);
    std::println("{} ", ms.v.size());

    printVector(ms.v);  // Output: data datadata data

    Exercises e;
    e.Run();
    // page 48 or 65/260

	return 0;
}