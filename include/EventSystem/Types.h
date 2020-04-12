#pragma once

#include <string>
#include <functional>
#include <vector>
#include <unordered_map>

namespace EventSystem {
	template <class... Args>
	using CallbackFn = std::function<void(Args...)>;
	typedef unsigned int EventHandlerId;

	class BaseCallback {
		public:
			virtual ~BaseCallback() {}
	};

	template<class... Args>
	class Callback : public BaseCallback {
		typedef CallbackFn<Args...> F;

		public:
			Callback() {}
			Callback(F f) { m_func = f; }
			~Callback() {}

			/* Overloaded Operators */
			inline void operator()(Args... args) { if(m_func) m_func(args...); }
		private:
			F m_func;
	};

	struct Event {
		Event() = default;
		Event(const std::string& t) : type(t) {}
		std::string type;
	};

	struct EventHandler {
		EventHandlerId id;
		Event* event;
		BaseCallback* callback;
	};

	typedef std::unordered_map<std::string, Event*> EventStore;
	typedef std::unordered_map<std::string, std::vector<EventHandler*> > EventHandlerStore;
}
