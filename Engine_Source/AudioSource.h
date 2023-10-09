#pragma once
#include "Component.h"
#include "AudioClip.h"

namespace roka
{
	class AudioSource : public Component
	{
	protected:
		AudioSource();
		AudioSource(const AudioSource& ref);
		virtual void Copy(Component* src)override;
	public:
		virtual ~AudioSource();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		void Play();
		void Stop();
		void SetLoop(bool loop);

		void SetClip(std::shared_ptr<AudioClip> clip) { mAudioClip = clip; }
		std::shared_ptr<AudioClip> GetClip() { return mAudioClip; }

	private:
		friend class FactoryBase;
		friend class ComponentFactory;
	private:
		std::shared_ptr<AudioClip> mAudioClip;
	};
}
