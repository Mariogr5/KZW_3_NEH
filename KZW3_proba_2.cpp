
#include <iostream>
#include "TxtReader.cpp"
#include "Machine.cpp"


int C_MAX(TxtReader reader)
{
    std::vector<Task> tasks = reader.tasks;
    int numberOfTasks = reader.numberofTasks;
    int numberOfMachines = reader.numberofMachines;

    std::vector<Machine> machines;
    int max = 0;


    for (int i = 0; i <= numberOfMachines - 1; i++)
    {
        std::vector<int> endTimes;
        for (int j = 0; j <= numberOfTasks - 1; j++)
        {
            int currentOpDuration = tasks[j].times[i];

            if (i == 0) { 

                if (j == 0)
                {
                    endTimes.push_back(currentOpDuration);

                }
                else
                {
                    endTimes.push_back(endTimes[j - 1] + currentOpDuration);
                }
            }
            else {
                if (j == 0)
                {
                    endTimes.push_back(machines[i - 1].endTimes[j] + currentOpDuration);
                }
                else
                {
                    if (endTimes[j - 1] < machines[i - 1].endTimes[j])
                        endTimes.push_back(machines[i - 1].endTimes[j] + currentOpDuration);
                    else
                    {
                        endTimes.push_back(endTimes[j - 1] + currentOpDuration);
                    }
                }
            }
            if (max <= endTimes[j])
                max = endTimes[j];
        }
        machines.push_back(Machine(endTimes));
    }
    return max;
}

void sortVectorByWeight(std::vector<Task>& myVector)
{
    sort(myVector.begin(), myVector.end(), [](const Task& a, const Task& b)
        {
            return a.weight > b.weight;
        });
}


void insert_task(std::vector<Task>& tasks, int position, Task newTask)
{
    if (position == tasks.size())
        tasks.push_back(newTask);
    else
        tasks.insert(tasks.begin() + position, newTask);
}




void NEH(TxtReader& reader)
{
    std::vector<Task> tasks = reader.tasks;
    std::vector<Task> resultTasks;
    std::vector<Task> tempTasks;
    std::vector<Task> finalTasks;

    int numberOfTasks = reader.numberofTasks;
    int numberOfMachines = reader.numberofMachines;

    sortVectorByWeight(tasks);
    reader.tasks = tasks;


    for (int i = 0; i < tasks.size(); i++)
    {
        int C = 100000;
        if (i == 0)
        {
            resultTasks.push_back(tasks[i]);
            continue;
        }

        for (int j = 0; j < resultTasks.size() + 1; j++)
        {
            std::vector<Task> tempTasks = resultTasks;
            insert_task(tempTasks, j, tasks[i]);
            reader.tasks = tempTasks;
            reader.numberofTasks = tempTasks.size();
            int C_max = C_MAX(reader);
            if (C > C_max)
            {
                finalTasks = tempTasks;
                C = C_max;
            }
        }
        resultTasks = finalTasks;
        //resultTasks.push_back()
    }
    reader.tasks = resultTasks;
    reader.numberofTasks = resultTasks.size();

    std::cout<<"Wynik: "<<C_MAX(reader) <<std::endl;

}



//1 Krok obliczyć wagę (Suma czasów taska na wszystkich maszynach) - OK
//2 Krok wrzucić taska o największej wadze na początek _OK(sort)
//3 Krok wrzucać po kolei taski zgodnie z wagami(malejąco) i nowo wrzucony task wstawić na wszystkie pozycje i sprawdzić C_MAX
//4 Krok wybierać najmniejszy C_MAX aż do skończenia tasków


int main()
{
    TxtReader _reader = TxtReader("Datas/segment_5.txt");

    NEH(_reader);
    for (int i = 0; i < _reader.tasks.size(); i++)
    {
        std::cout << _reader.tasks[i].taskNumber << " ";
    }

}

