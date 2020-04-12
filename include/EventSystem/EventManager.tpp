namespace EventSystem {
	/* Public Methods */
	template<class E>
	E& EventManager::CreateEvent(const std::string& type) {
		E* event;
		EventStore::iterator eventIt;

		event = reinterpret_cast<E*>(new Event(type));
		eventIt = m_eventStore.find(type);

		// If Event doesn't exist in eventStore, store it
		if(eventIt == m_eventStore.end()) {
			m_eventStore.insert(std::make_pair(type, event));
		}

		return (*event);
	}

	template<class... Args, class F>
	EventHandlerId EventManager::AddEventListener(const std::string& type, F&& f) {
		typedef Callback<Args...> CallbackType;

		CallbackType* callback;
		EventHandler* p_eventHandler;
		EventHandlerStore::iterator handlerIt;
		
		callback = new CallbackType(CallbackFn<Args...>(f));
		p_eventHandler = new EventHandler();

		// p_eventHandler->id = m_handlerId;
		// p_eventHandler->callback = callback;
	}
}
