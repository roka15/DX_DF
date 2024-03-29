#pragma once
#include "ISkill.h"
namespace roka
{
	class AntiGravity :
		public Skill
	{
	public:
		AntiGravity(const UINT& damage):Skill(damage) {}
		virtual ~AntiGravity() {}
		virtual void Execute(std::shared_ptr<GameObject> caster) override;
		virtual void SpawnEffect(std::shared_ptr<GameObject> caster, std::wstring key) override;
		virtual void DeSpawnEffect(std::shared_ptr<GameObject> caster, std::wstring key) override;
		virtual void SpawnCollider(std::shared_ptr<GameObject> caster) override;
		virtual void DeSpawnCollider(std::shared_ptr<GameObject> caster) override;
		virtual void EnableCollision(std::shared_ptr<GameObject> caster) override;
		virtual void DisableCollision(std::shared_ptr<GameObject> caster) override;
		virtual void Left(std::shared_ptr<GameObject> caster)override;
		virtual void Right(std::shared_ptr<GameObject> caster)override;
		virtual void Sound(std::wstring key)override;
		virtual void End(std::shared_ptr<GameObject> caster) override;
		virtual void OnAnimationFramEvent(std::shared_ptr<GameObject> caster, std::wstring frameEvent) override;

		virtual void OnCollisionEnter(std::shared_ptr<GameObject> caster, std::shared_ptr<GameObject> target)override;
		virtual void OnCollisionStay(std::shared_ptr<GameObject> caster, std::shared_ptr<GameObject> target)override;
		virtual void OnCollisionExit(std::shared_ptr<GameObject> caster, std::shared_ptr<GameObject> target)override;
	
		virtual void Release()override;

		void PlutoAniType1(std::shared_ptr<GameObject> caster);
		void PlutoAniType2(std::shared_ptr<GameObject> caster);
		void EyeType1(std::shared_ptr<GameObject> caster);
		void EyeType2(std::shared_ptr<GameObject> caster);
		void PlutoSparkEffect(std::shared_ptr<GameObject> caster);
	
		void CreateHomonculouse(std::shared_ptr<GameObject> caster,std::wstring key);
		void CreatePluto(std::shared_ptr<GameObject> caster, std::wstring key);
		void CreatePlutoEffect(std::shared_ptr<GameObject> caster, std::wstring key);
		void CreateSuccessTube(std::shared_ptr<GameObject> caster, std::wstring key,Vector3 offset);
		void CreateCircle(std::shared_ptr<GameObject> caster, std::wstring key);
		void CreateCircleEft(std::shared_ptr<GameObject>caster);
		void CreateFamiliarEft(std::shared_ptr<GameObject> caster);
		void CreateFamiliar(Vector3 pos);
		
		void DeSpawnCircle(std::shared_ptr<GameObject> caster);
		void DeSpawnFamiliarEft();
		void DeSpawnFamiliar(std::shared_ptr<GameObject> caster);
	private:
		Vector3 mEyeOriginPos;
		float mDir;
	};
}


