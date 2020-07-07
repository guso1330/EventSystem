#pragma once

#include "EventSystem/Types.h"

#include <utility>

namespace EventSystem {
	class EventManager {
		public:
			/* Constructors / Destructors */
			EventManager(const EventManager&) = delete;
			~EventManager() = default;

			/* Templated Public Methods */
			template<class E>
			E& CreateEvent();
			template<class... Args, class F>
			EventHandlerId AddEventListener(const std::string& eventName, F&& func);
			template<class... Args>
			void DispatchEvent(const std::string& eventName, Args&&... args);

			/* Public Methods */
			void RemoveEventListener(const std::string& eventName, const EventHandlerId id);

			/* Getters */
			inline const EventHandlerStore& GetEventHandlerStore() const { return m_eventHandlerStore; }
			static EventManager& GetInstance();

			/* Operator Overload */
			void operator=(EventManager const&) = delete;

		private:
			EventManager() = default;

		private:
			unsigned int m_handlerId = 0;
			EventHandlerStore m_eventHandlerStore;
	};
}

#include "EventSystem/EventManager.tpp"
