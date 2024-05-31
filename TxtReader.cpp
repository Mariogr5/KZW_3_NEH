
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm> // std::all_of
#include <cctype>
#include "Task.cpp"
#include <String>

class TxtReader
{
public:
	TxtReader( std::string path)
	{
		tasks = getTasks("Datas/segment_120.txt");
	}
	int numberofMachines;
	int numberofTasks;
	std::vector<Task> tasks;


	std::vector<Task> getTasks(std::string fileName)
	{
		std::string line;
		std::ifstream plik;
		std::vector<Task> _tasks;

		plik.open(fileName.c_str());
		if (!plik.good())
			return _tasks;

		int i = 0;
		bool firstRow = true;
		while (std::getline(plik, line)) {
			if (line.empty() || std::all_of(line.begin(), line.end(), std::isspace)) {
				continue;
			}
			std::istringstream iss(line);
			std::vector<int> numbers;
			int number;
			while (iss >> number) {
				numbers.push_back(number);
			}

			if (!numbers.empty()) {
				if (firstRow)
				{
					getFirstRowDatas(numbers);
					firstRow = false;
					continue;
				}
				_tasks.push_back(Task(numbers, i));
				i++;
			}
		}

		std::cout << numberofTasks << " " << numberofMachines << std::endl;

		for (size_t i = 0; i < _tasks.size(); ++i) {
			std::cout << "Task number: " << _tasks[i].taskNumber << "  ";
			//std::cout << "Linia " << i + 1 << ": ";
			for (size_t j = 0; j < _tasks[i].times.size(); ++j) {
				std::cout << _tasks[i].times[j] << " ";
			}
			std::cout << std::endl;
		}

		plik.close();

		return _tasks;

	}

	void getFirstRowDatas(std::vector<int>& numbers)
	{
		this->numberofMachines = numbers[1];
		this->numberofTasks = numbers[0];
	}

	void swap_task(int number_task1, int number_task2)
	{
		Task temp = tasks[number_task1 - 1];
		tasks[number_task1 - 1] = tasks[number_task2 - 1];
		tasks[number_task2 - 1] = temp;
	}

};


