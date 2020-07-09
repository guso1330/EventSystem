#pragma once

#include <functional>

namespace EventSystem {
	template <class... Args>
	using CallbackFn = std::function<void(Args...)>;

	class BaseCallback {
		public:
			virtual ~BaseCallback() {}
	};

	template<class... Args>
	class Callback : public BaseCallback {
		typedef CallbackFn<Args...> F;

		public:
			Callback() {}
			Callback(F&& f) : m_func(f) {}
			~Callback() {}

			F* Get() { return &m_func; }

			/* Overloaded Operators */
			inline void operator() (Args... args) { if(m_func) m_func(args...); }

		private:
			F m_func;
	};
}
