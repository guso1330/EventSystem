#include "EventSystem/EventManager.h"

namespace EventSystem {
	/* Getters */
	EventManager& EventManager::GetInstance() {
		static EventManager eventManager;
		return eventManager;
	}

	void EventManager::RemoveEventListener(const std::string& eventName, const EventHandlerId id) {
    EventHandlerList* callbackVector;
    EventHandlerList::iterator callbackVectorIt;
    EventHandlerStore::const_iterator storeIt;

    storeIt = m_eventHandlerStore.find(eventName);
    if (storeIt != m_eventHandlerStore.end()) {
      callbackVector = storeIt->second;
      for (callbackVectorIt = callbackVector->begin(); callbackVectorIt != callbackVector->end(); ++callbackVectorIt) {
        if ((*callbackVectorIt)->id == id) {
          callbackVector->erase(callbackVectorIt);
          break;
        }
      }
    }
	}
}
