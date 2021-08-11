#include <condition_variable>
#include <stdio.h>
#include <vector>
#include <string>
#include <cstdlib>
#include <chrono>
#include <thread>
#include <iostream>
#include <unistd.h>

const int NUM_PHILOSOPHERS = 5;
std::mutex m;
std::unique_lock<std::mutex> lk(m);
class Fork
{
public:
	std::condition_variable* NotInUse;
	int Id;
	Fork()
	{
		this->Id = -1;
	}
	Fork(int id)
	{
		this->Id = id;
	}
};

struct PhilosophersTable
{
public:
	bool Ready = false;
	std::vector<Fork> Forks = std::vector<Fork>(NUM_PHILOSOPHERS);
	PhilosophersTable(){}
	PhilosophersTable(Fork forks[])
	{
		for (int i = 0;i < NUM_PHILOSOPHERS;i++)
		{
			this->Forks.push_back(forks[i]);
		}
	}
};
class Philosopher
{
public:
	int  Id;
	PhilosophersTable Table;
	Fork LeftFork;
	Fork RightFork;
	int MaxIterations;
	int Interations;

	Philosopher(int name, PhilosophersTable table, Fork leftFork, Fork rightFork, int iterations)
	{
		this->Id = name;
		this->Table = table;
		this->LeftFork = leftFork;
		this->RightFork = rightFork;
		this->MaxIterations = iterations;
		this->Interations = 0;
	}


	void  dine()
	{
		do {
			think();
			eat();
			this->Interations++;
		} while (Table.Ready && (this->Interations < this->MaxIterations));
	}

	void think()
	{
		printf("\nphilosopher %d is thinking", this->Id);
		printf("\nphilosopher %d has stopped thinking", this->Id);
	}

	void eat()
	{

		if (Id == NUM_PHILOSOPHERS - 1)
		{
			printf("\nphilosopher %d is waiting for right fork(FID = %d)", this->Id, this->RightFork.Id);

			RightFork.NotInUse->wait(lk);
			printf("\nphilosopher %d is waiting for left fork(FID = %d)", this->Id, this->LeftFork.Id);
			LeftFork.NotInUse->wait(lk);
			printf("\nphilosopher %d obtained both forks(%d and %d)", this->Id, this->LeftFork.Id, this->RightFork.Id);
		}
		else
		{
			printf("\nphilosopher %d is waiting for left fork(FID=%d)", this->Id, this->LeftFork.Id);
			LeftFork.NotInUse->wait(lk);
			printf("\nphilosopher %d is waiting for right fork(FID=%d)", this->Id, this->RightFork.Id);
			RightFork.NotInUse->wait(lk);
			printf("\nphilosopher %d obtained both forks(%d and %d)", this->Id, this->LeftFork.Id, this->RightFork.Id);
		}
		printf("\nphilosopher %d is eating with forks %d and %d", this->Id, this->LeftFork.Id, this->RightFork.Id);
		printf("\nphilosopher %d stopped eating with forks %d and %d", this->Id, this->LeftFork.Id, this->RightFork.Id);
		LeftFork.NotInUse->notify_one();
		RightFork.NotInUse->notify_one();
	}
};

void startThread(Philosopher* ph)
{
	ph->dine();
}
int main(void)
{
	Fork forks[NUM_PHILOSOPHERS];

	for (int i = 0; i < NUM_PHILOSOPHERS; i++)
	{
		forks[i] = Fork(i + 1);
	}

	PhilosophersTable Table = PhilosophersTable(forks);

	std::thread phThreads[NUM_PHILOSOPHERS];
	for (int i = 0; i < NUM_PHILOSOPHERS; i++)
	{
		auto ph = new Philosopher(10 + i, Table, forks[(i + 1) % NUM_PHILOSOPHERS], forks[(i)], 5);
		phThreads[i] = std::thread([ph] {startThread(ph);});
	}
	Table.Ready = true;
	for (int i = 0; i < NUM_PHILOSOPHERS; i++)
	{
		phThreads[i].join();
	}
	std::cout << "\nPress any key to exit...............\n";
	float tmp = 0;
	std::cin >> tmp;
	return 0;
}
