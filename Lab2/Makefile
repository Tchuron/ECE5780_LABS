#makefile
#FastTravel

CC = g++

all: scheduler

scheduler: scheduler.cpp TaskScheduler.o TaskScheduler.hpp
	$(CC) -o scheduler scheduler.cpp TaskScheduler.o

TaskScheduler.o: TaskScheduler.cpp TaskScheduler.hpp
	$(CC) -c TaskScheduler.cpp
