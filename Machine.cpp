#include <vector>

class Machine
{
public:
	Machine()
	{

	}
	Machine(std::vector<int> times)
	{
		endTimes = times;
	}
	int number_of_machine;
	std::vector<int> endTimes;
};