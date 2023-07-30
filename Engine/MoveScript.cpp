#include "MoveScript.h"
#include "GameObject.h"
#include "Transform.h"
#include "Input.h"
#include "RokaTime.h"
namespace roka
{
	MoveScript::MoveScript() :Script(EScriptType::Move)
		, mSpeed(0.0f)
		, mDir(Vector2::Zero)
	{
	}

	MoveScript::MoveScript(const MoveScript& ref) : Script(ref)
	{
		mSpeed = ref.mSpeed;
		mDir = ref.mDir;
	}

	void MoveScript::Copy(Component* src)
	{
		Script::Copy(src);
		MoveScript* source = dynamic_cast<MoveScript*>(src);
		mSpeed = source->mSpeed;
	}

	MoveScript::~MoveScript()
	{
	}

	void MoveScript::Initialize()
	{

	}

	void MoveScript::Update()
	{
		if (owner == nullptr)
			return;

		std::shared_ptr<Transform> tf = owner->GetComponent<Transform>();
		Vector3 pos = tf->position;

		pos.x += mDir.x * mSpeed * Time::DeltaTime();
		pos.y += mDir.y * mSpeed * Time::DeltaTime();

		tf->position = pos;
	}

	void MoveScript::LateUpdate()
	{
	}

	void MoveScript::Render()
	{
	}

}

