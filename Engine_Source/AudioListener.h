#pragma once
#include "Component.h"


namespace roka
{
	class AudioListener : public Component
	{
	protected:
		AudioListener();
		AudioListener(const AudioListener& ref);
		virtual void Copy(Component* src)override;
	public:
	
		virtual ~AudioListener();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;
	private:
		friend class FactoryBase;
		friend class ComponentFactory;
	private:
	};
}