#makefile
#FastTravel

CC = g++

all: scheduler

scheduler: scheduler.cpp TaskScheduler.o TaskScheduler.hpp
	$(CC) -o scheduler scheduler.cpp TaskScheduler.o

TaskScheduler.o: TaskScheduler.cpp TaskScheduler.hpp Task.hpp Task.o
	$(CC) -c TaskScheduler.cpp

Task.o: Task.cpp Task.hpp
	$(CC) -c Task.cpp
