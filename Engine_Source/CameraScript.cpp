#include "CameraScript.h"
#include "GameObject.h"
#include "Transform.h"
#include "RokaTime.h"
#include "Input.h"
namespace roka
{
	CameraScript::CameraScript() :Script()
	{
	}
	CameraScript::~CameraScript()
	{
	}
	void CameraScript::Update()
	{
		Transform* tf = GetOwner()->GetComponent<Transform>();
		Vector3 pos = tf->position;

		if (Input::GetKey(EKeyCode::W))
		{
			pos.z += 5.0f * Time::DeltaTime();
		}
		else if (Input::GetKey(EKeyCode::S))
		{
			pos.z -= 5.0f * Time::DeltaTime();
		}

		if (Input::GetKey(EKeyCode::A))
		{
			pos.x -= 5.0f * Time::DeltaTime();
		}
		else if (Input::GetKey(EKeyCode::D))
		{
			pos.x += 5.0f * Time::DeltaTime();
		}

		if (Input::GetKey(EKeyCode::Q))
		{
			pos.y -= 5.0f * Time::DeltaTime();
		}
		else if (Input::GetKey(EKeyCode::E))
		{
			pos.y += 5.0f * Time::DeltaTime();
		}

		tf->position = pos;
	}
}