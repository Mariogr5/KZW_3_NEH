#include <vector>


class Task
{
public:
	Task(std::vector<int> Times, int TaskNumber)
	{
		times = Times;
		taskNumber = TaskNumber + 1;
		weight = calcWeight();
	}
	std::vector<int> times;
	int taskNumber;
	int weight;

	int calcWeight()
	{
		int sum = 0;
		for (int i = 0; i < times.size(); i++)
		{
			sum += times[i];
		}

		return sum;
	}
};