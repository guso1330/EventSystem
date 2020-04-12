#pragma once

#include "EventSystem/Types.h"

#include <utility>

namespace EventSystem {
	class EventManager {
		public:
			EventManager(const EventManager&) = delete;
			~EventManager() = default;

			/* Public Methods */
			template<class E>
			E& CreateEvent(const std::string& type);
			template<class... Args, class F>
			EventHandlerId AddEventListener(const std::string& type, F&& f);
			void RemoveEventListener(const std::string& type, EventHandlerId id);

			/* Getters */
			static EventManager& GetInstance();

			/* Operator Overload */
			void operator=(EventManager const&) = delete;
		private:
			EventManager() = default;
		private:
			unsigned int m_handlerId = 0;
			EventStore m_eventStore;
			EventHandlerStore m_eventHandlerStore;
	};
}

#include "EventSystem/EventManager.tpp"
