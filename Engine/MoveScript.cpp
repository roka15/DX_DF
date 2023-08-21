#include "MoveScript.h"
#include "GameObject.h"
#include "Transform.h"
#include "Rigidbody.h"
#include "Input.h"
#include "RokaTime.h"
namespace roka
{
	MoveScript::MoveScript(EScriptType type):Script(type)
		, mSpeed(0.0f)
		, mDir(Vector2::Zero)
	{
	}
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
		if (mbActive == false)
			return;
		std::shared_ptr<Transform> tf = owner->GetComponent<Transform>();
		Vector3 pos = tf->position;
		Vector2 origin_pos = Vector2(pos.x,pos.y);
		pos.x += mDir.x * mSpeed * Time::DeltaTime();
		pos.y += mDir.y * mSpeed * Time::DeltaTime();

		
		Vector2 diff = origin_pos - Vector2(pos.x,pos.y);
		diff *= -1;
		std::shared_ptr<Rigidbody>rigid = owner->GetComponent<Rigidbody>();
		rigid->AddLandingPoint(diff);

		tf->position = pos;
	}

	void MoveScript::LateUpdate()
	{
	}

	void MoveScript::Render()
	{
	}

}

