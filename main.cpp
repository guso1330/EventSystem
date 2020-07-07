#include "EventSystem/EventSystem.h"

#include <iostream>

struct LogEvent : public EventSystem::Event {
	std::string message;
};

void testFn1() {
	std::cout << "testFn1()" << std::endl;
}

void testFn2(int x, int y) {
	std::cout << "testFn2(): " << x + y << std::endl;
}

void testFn3(int& total, int x, int y) {
	total += x + y;
	std::cout << "testFn3(): " << total << std::endl;
}

void testFn4(int total, int x, int y) {
	total += x + y;
	std::cout << "testFn4(): " << total << " (int)" << std::endl;
}

void testFn5(const int& total) {
	std::cout << "testFn5(): " << total << " (const int&)" << std::endl;
}

int main(int argc, char const *argv[])
{
	/*
		Testing Callback Functions
	*/
	EventSystem::Callback<> test1Callback;
	EventSystem::Callback<int, int> test2Callback;
	EventSystem::Callback<int&, int, int> test3Callback;
	EventSystem::Callback<int&, int, int>* test3PtrCallback;
	EventSystem::Callback<int, int, int> test4Callback;
	EventSystem::Callback<const int&> test5Callback;

	int total = 0;

	test1Callback = EventSystem::Callback<>(testFn1);
	test2Callback = EventSystem::Callback<int, int>(testFn2);
	test3Callback = EventSystem::Callback<int&, int, int>(testFn3);
	test3PtrCallback = new EventSystem::Callback<int&, int, int>(testFn3);
	test4Callback = EventSystem::Callback<int, int, int>(testFn4);
	test5Callback = EventSystem::Callback<const int&>(testFn5);

	std::cout << "BEGIN - EventSystem::Callback" << std::endl;
		test1Callback();
		test2Callback(1, 1);
		test3Callback(total, 1, 1);
		(*test3PtrCallback)(total, 1, 1);
		test4Callback(total, 1, 1);
		test5Callback(total);
		std::cout << "total = " << total << " after Callbacks called" << std::endl;
	std::cout << "END - EventSystem::Callback" << std::endl << std::endl;

	/*
		Testing Event Creation
	*/
	EventSystem::Event event1;
	LogEvent logEvent1;
	LogEvent logEvent2;
	LogEvent logEvent3;

	event1 = EventSystem::EventManager::GetInstance().CreateEvent<EventSystem::Event>();

	logEvent1 = EventSystem::EventManager::GetInstance().CreateEvent<LogEvent>();
	logEvent1.message = "logEvent1";

	logEvent2 = EventSystem::EventManager::GetInstance().CreateEvent<LogEvent>();
	logEvent2.message = "logEvent2";

	logEvent3 = EventSystem::EventManager::GetInstance().CreateEvent<LogEvent>();
	logEvent3.message = "logEvent3";

	std::cout << "BEGIN - CreateEvent Test" << std::endl;
		std::cout << "event1 type: " << event1.GetType() << std::endl;
		std::cout << "logEvent1 type: " << logEvent1.GetType() << std::endl;
		std::cout << "logEvent2 type: " << logEvent2.GetType() << std::endl;
		std::cout << "logEvent3 type: " << logEvent3.GetType() << std::endl;
	std::cout << "END - CreateEvent Test" << std::endl << std::endl;

	/*
		Testing AddEventListener
	*/
	int id1, id2, id3, id4, id5, id6;
	std::cout << "BEGIN - AddEventListener Test" << std::endl;
		id1 = EventSystem::EventManager::GetInstance().AddEventListener<>("Event", []() { std::cout << "Event anonymous function" << std::endl; });
		id2 = EventSystem::EventManager::GetInstance().AddEventListener<>("LogEvent", testFn1);
		id3 = EventSystem::EventManager::GetInstance().AddEventListener<int, int>("LogEvent", testFn2);
		id4 = EventSystem::EventManager::GetInstance().AddEventListener<int&, int, int>("LogEvent", testFn3);
		id5 = EventSystem::EventManager::GetInstance().AddEventListener<int, int, int>("LogEvent", testFn4);
		id6 = EventSystem::EventManager::GetInstance().AddEventListener<const int&>("LogEvent", testFn5);
	std::cout << "id1: " << id1 << std::endl;
	std::cout << "id2: " << id2 << std::endl;
	std::cout << "id3: " << id3 << std::endl;
	std::cout << "id4: " << id4 << std::endl;
	std::cout << "id5: " << id5 << std::endl;
	std::cout << "id6: " << id6 << std::endl;
	std::cout << "END - AddEventListener Test" << std::endl << std::endl;

	/*
		Testing DispatchEvent
	*/
	std::cout << "BEGIN - DispatchEvent Test" << std::endl;
		total = 0;
		EventSystem::EventManager::GetInstance().DispatchEvent("Event");
		EventSystem::EventManager::GetInstance().DispatchEvent("LogEvent");
		EventSystem::EventManager::GetInstance().DispatchEvent("LogEvent", 1, 1);
		EventSystem::EventManager::GetInstance().DispatchEvent("LogEvent", total, 1, 1);
		EventSystem::EventManager::GetInstance().DispatchEvent("LogEvent", (int)total, 1, 1);
		EventSystem::EventManager::GetInstance().DispatchEvent("LogEvent", (const int&)total);
		std::cout << "total = " << total << " after LogEvent dispatched" << std::endl;
	std::cout << "END - DispatchEvent Test" << std::endl << std::endl;

	/*
		Testing RemoveEventListener
	*/
	EventSystem::EventManager::GetInstance().RemoveEventListener("Event", id1);
	EventSystem::EventManager::GetInstance().RemoveEventListener("LogEvent", id2);
	EventSystem::EventManager::GetInstance().DispatchEvent("Event");
	EventSystem::EventManager::GetInstance().DispatchEvent("LogEvent");

	return 0;  
}
