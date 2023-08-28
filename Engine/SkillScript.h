#pragma once
#include "Script.h"
#include "ContentEnums.h"
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
		~SkillScript() {}
		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		virtual void OnCollisionEnter(std::shared_ptr<Collider2D> other) {}
		virtual void OnCollisionStay(std::shared_ptr<Collider2D> other) {}
		virtual void OnCollisionExit(std::shared_ptr<Collider2D> other) {}

		virtual void Play(EDir4Type dir);
		virtual void End();

		EStunState GetStunType() { return mStunType; }
		void SetStunType(EStunState type) { mStunType = type;}

		Vector2 GetRange() { return mRange; }
		void SetRange(Vector2 range) { mRange = range; }

		Vector2 GetDistance() { return mDistance; }
		void SetDistance(Vector2 distance) { mDistance = distance; }

		Vector2 GetStartPos() { return mStartPos; }
		void SetStartPos(Vector2 pos) { mStartPos = pos; }

		double GetDeleteTime() { return mDeleteTime; }
		void SetDeleteTime(double time) { mDeleteTime = time; }

		std::wstring GetStartAniKey() { return mStartKey; }
		void SetStartAniKey(std::wstring key) { mStartKey = key; }
		
		PROPERTY(GetStunType, SetStunType) EStunState stun_type;
		PROPERTY(GetRange, SetRange)Vector2 range;
		PROPERTY(GetDistance, SetDistance) Vector2 distance;
		PROPERTY(GetStartPos, SetStartPos) Vector2 startPos;
		PROPERTY(GetDeleteTime, SetDeleteTime) double deleteTime;
		PROPERTY(GetStartAniKey, SetStartAniKey) std::wstring startKey;

		static void SkillEndEvent(std::weak_ptr<void> ptr);
	private:
		friend class FactoryBase;
		friend class ScriptFactory;
	protected:
		EStunState mStunType;
		Vector2 mRange;
		Vector2 mDistance;
		Vector2 mStartPos;
		double mDeleteTime;
		std::wstring mStartKey;
	};
}


