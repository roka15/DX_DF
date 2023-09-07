#pragma once
#include "Script.h"

namespace roka
{
	class SkillScript : public Script
	{
	protected:
		SkillScript();
		SkillScript(EScriptType type);
		SkillScript(const SkillScript& ref);
		void Copy(Component* src);
	public:
		virtual ~SkillScript();
		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		virtual void OnCollisionEnter(std::shared_ptr<Collider2D> other) {}
		virtual void OnCollisionStay(std::shared_ptr<Collider2D> other) {}
		virtual void OnCollisionExit(std::shared_ptr<Collider2D> other) {}

		virtual void Play();
		virtual void Exit();

		virtual void Start() {}
		virtual void Middle() {}
		virtual void End() {}

		virtual void CreateColliderObject() {}
		EStunState GetStunType() { return mStunType; }
		void SetStunType(EStunState type) { mStunType = type;}

		std::wstring GetStartAniKey() { return mStartKey; }
		void SetStartAniKey(std::wstring key) { mStartKey = key; }
		
		PROPERTY(GetStunType, SetStunType) EStunState stun_type;
		PROPERTY(GetRange, SetRange)Vector2 range;
		PROPERTY(GetDistance, SetDistance) Vector2 distance;
		PROPERTY(GetStartPos, SetStartPos) Vector2 startPos;
		PROPERTY(GetDeleteTime, SetDeleteTime) double deleteTime;
		PROPERTY(GetStartAniKey, SetStartAniKey) std::wstring startKey;

	private:
		friend class FactoryBase;
		friend class ScriptFactory;
	protected:
		EStunState mStunType;
		std::wstring mStartKey;

		//collider object info
		std::shared_ptr<GameObject> mColObj;
	};
}


