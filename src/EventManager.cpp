#include "EventSystem/EventManager.h"

namespace EventSystem {
	/* Getters */
	EventManager& EventManager::GetInstance() {
		static EventManager eventManager;
		return eventManager;
	}

	void EventManager::RemoveEventListener(const std::string& eventName, const EventHandlerId id) {

	}
}
