#include "MoveScript.h"
#include "GameObject.h"
#include "Transform.h"
#include "Input.h"
#include "RokaTime.h"
namespace roka
{
	MoveScript::MoveScript():Script(EScriptType::Move)
	{
	}

	MoveScript::MoveScript(const MoveScript& ref):Script(ref)
	{
	}

	void MoveScript::Copy(Component* src)
	{
		Script::Copy(src);
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

		if (Input::GetKey(EKeyCode::RIGHT))
			pos.x += 0.01f * Time::DeltaTime();
	}

	void MoveScript::LateUpdate()
	{
	}

	void MoveScript::Render()
	{
	}
}

