#include "AudioSource.h"
#include "AudioClip.h"
#include "Transform.h"
#include "GameObject.h"

namespace roka
{
	AudioSource::AudioSource()
		: Component(EComponentType::AudioSource)
		, mAudioClip(nullptr)
	{

	}

	AudioSource::AudioSource(const AudioSource& ref):Component(ref)
	{
	}

	void AudioSource::Copy(Component* src)
	{
	}

	AudioSource::~AudioSource()
	{

	}

	void AudioSource::Initialize()
	{
	}

	void AudioSource::Update()
	{
	}

	void AudioSource::LateUpdate()
	{
		std::shared_ptr<Transform> tr = GetOwner()->GetComponent<Transform>();
		Vector3 pos = tr->GetPosition();
		Vector3 foward = tr->forward;

		mAudioClip->Set3DAttributes(pos, foward);
	}

	void AudioSource::Render()
	{
	}

	void AudioSource::Play()
	{
		mAudioClip->Play();
	}
	void AudioSource::Stop()
	{
		mAudioClip->Stop();
	}
	void AudioSource::SetLoop(bool loop)
	{
		mAudioClip->SetLoop(loop);
	}
}