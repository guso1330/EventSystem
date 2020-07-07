#pragma once

#include "EventSystem/Callback.h"

#include <string>
#include <vector>
#include <unordered_map>

namespace EventSystem {
	struct Event;
	struct EventHandler;

	typedef size_t Type;
	typedef unsigned int EventHandlerId;
	typedef std::vector<EventHandler*> EventHandlerList;
	typedef std::unordered_map<std::string, EventHandlerList> EventHandlerStore;

	namespace EventType {
		template<class T>
		static inline Type GetType() { return typeid(T).hash_code(); }
	}

	class Event {
		public:
			Event() = default;
			Event(Type type) : m_type(type) {}

			inline const Type GetType() const { return m_type; }

		private:
			Type m_type;
	};

	struct EventHandler {
		EventHandlerId id;
		BaseCallback* callback;
	};
}
