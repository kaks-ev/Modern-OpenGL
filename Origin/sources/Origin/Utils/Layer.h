#ifndef LAYER_H
#define LAYER_H

#include "core.h"
#include "Origin\IO\Events\Event.h"

namespace Origin {

	namespace Utils {

		class Layer
		{
		protected:
			std::string m_Name;

		public:
			Layer(const std::string& name = "layer");
			virtual ~Layer();

			virtual void OnAttach() {}
			virtual void OnDettach() {}
			virtual void OnUpdate() {}
			virtual void OnEvent(Event& e) {}

			inline const std::string& GetName() const { return m_Name;  }
		};
	}
}
#endif // !LAYER_H