#include "AudioListener.h"
#include "Transform.h"
#include "GameObject.h"
#include "Fmod.h"
#include "AudioListener.h"

namespace roka
{
	AudioListener::AudioListener()
		: Component(EComponentType::AudioListener)
	{

	}

	AudioListener::AudioListener(const AudioListener& ref):Component(ref)
	{
	}

	void AudioListener::Copy(Component* src)
	{
	}

	AudioListener::~AudioListener()
	{

	}

	void AudioListener::Initialize()
	{

	}

	void AudioListener::Update()
	{

	}

	void AudioListener::LateUpdate()
	{
		std::shared_ptr<Transform> tr = GetOwner()->GetComponent<Transform>();
		Vector3 pos = tr->GetPosition();
		Vector3 foward = tr->forward;
		Vector3 up = tr->Up();

		Vector3 vel = { 0.0f, 0.0f, 0.0f };
		Fmod::Set3DListenerAttributes(&pos, &vel, &foward, &up);
	}

	void AudioListener::Render()
	{

	}
}