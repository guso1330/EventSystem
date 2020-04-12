#include "EventSystem/EventSystem.h"

#include <iostream>

struct LogEvent : public EventSystem::Event {
	std::string message;
};

void testVoidFn () {
	std::cout << "testVoidFn()" << std::endl;
}

void testFn(const LogEvent& event) {
	std::cout << "testFn(const LogEvent& event) - event.message: " << event.message << std::endl;
}

int main(int argc, char const *argv[])
{
	LogEvent logEvent1;
	LogEvent logEvent2;
	LogEvent logEvent3;

	// LogEvent1
	logEvent1 = EventSystem::EventManager::GetInstance().CreateEvent<LogEvent>("LogEvent");
	logEvent1.message = "logEvent1";

	// LogEvent2
	logEvent2 = EventSystem::EventManager::GetInstance().CreateEvent<LogEvent>("LogEvent");
	logEvent2.message = "logEvent2";

	// LogEvent3
	logEvent3 = EventSystem::EventManager::GetInstance().CreateEvent<LogEvent>("LogEvent3");
	logEvent3.message = "logEvent3";

	EventSystem::EventManager::GetInstance().AddEventListener("LogEvent", testVoidFn);
	EventSystem::EventManager::GetInstance().AddEventListener<const LogEvent&>("LogEvent", testFn);
	EventSystem::EventManager::GetInstance().AddEventListener<const LogEvent&>("LogEvent3", testFn);

	return 0;
}
