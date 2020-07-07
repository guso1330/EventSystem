#include <type_traits>
#include <iostream>

namespace EventSystem {
	/* Public Methods */
	template<class E>
	E& EventManager::CreateEvent() {
		E* event = reinterpret_cast<E*>(new Event(EventType::GetType<E>()));
		return (*event);
	}

	template<class... Args, class F>
	EventHandlerId EventManager::AddEventListener(const std::string& eventName, F&& func) {
		typedef Callback<Args...> CallbackType;

		EventHandler* p_eventHandler;
		EventHandlerList* n_eventHandlerListPtr;
		EventHandlerStore::iterator handlerIt;

		p_eventHandler = new EventHandler();

		p_eventHandler->id = m_handlerId;
		p_eventHandler->callback = new CallbackType(func);
		++m_handlerId;

		handlerIt = m_eventHandlerStore.find(eventName);
		if (handlerIt == m_eventHandlerStore.end()) {
			n_eventHandlerListPtr = new EventHandlerList();
			n_eventHandlerListPtr->push_back(p_eventHandler);
			m_eventHandlerStore.insert(std::make_pair(eventName, (*n_eventHandlerListPtr)));
		} else {
			n_eventHandlerListPtr = &(handlerIt->second);
			n_eventHandlerListPtr->push_back(p_eventHandler);
		}

		return p_eventHandler->id;
	}

	template<class... Args>
	void EventManager::DispatchEvent(const std::string& eventName, Args&&... args) {
		typedef Callback<Args...> CallbackType;

		EventHandlerList callbackVector;
		EventHandlerList::const_iterator callbackVectorIt;
		EventHandlerStore::const_iterator storeIt;

		storeIt = m_eventHandlerStore.find(eventName);
		if (storeIt != m_eventHandlerStore.end()) {
			callbackVector = storeIt->second;
			for (callbackVectorIt = callbackVector.begin(); callbackVectorIt != callbackVector.end(); ++callbackVectorIt) {
				CallbackType* c = dynamic_cast<CallbackType*>((*callbackVectorIt)->callback);
				if(c) {
					(*c)(std::forward<Args>(args)...);
				}
			}
		}
	}
}
