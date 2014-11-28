all: grader world_time calendar
grader: grader.cc grader_main.cc
	g++ -o grader grader.cc grader_main.cc

world_time: world_time.cc world_time_main.cc
	g++ -o world_time world_time.cc world_time_main.cc

calendar: calendar.cc calendar_main.cc
	g++ -o calendar calendar.cc calendar_main.cc

