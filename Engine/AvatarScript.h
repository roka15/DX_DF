#pragma once
#include "Script.h"
#include "ContentEnums.h"
namespace roka
{
	namespace graphics
	{
		class Texture;
	}
	class Image;
	class Transform;
	class AvatarSubPartInfo;
	using namespace enums;
	using namespace graphics;
	
	class AvatarScript :
		public Script
	{
	private:
		AvatarScript();
		AvatarScript(const AvatarScript& ref);
		virtual void Copy(Component* src)override;
	public:
		~AvatarScript();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		virtual void OnCollisionEnter(std::shared_ptr<Collider2D> other) {}
		virtual void OnCollisionStay(std::shared_ptr<Collider2D> other) {}
		virtual void OnCollisionExit(std::shared_ptr<Collider2D> other) {}

		void EquipPart(EAvatarParts type, std::wstring name);
		void EquipPart(EAvatarParts type, std::vector<AvatarSubPartInfo>infos);
		void RegisterPart(EAvatarParts type, std::shared_ptr<GameObject> obj) { mParts[type] = obj; }

		void CreatePartAni(EAvatarParts type, std::wstring npk_name, std::wstring pack_name,std::wstring set_name, UINT start, UINT end, float duration);
		void CreatePartAni(EAvatarParts type, std::shared_ptr<Texture> atlas,std::wstring set_name, UINT start, UINT end, float duration);
		
		void InsertStateAniInfo(EPlayerState state,EAvatarParts part, std::wstring ani_name);
		void SettingRightMaterial();
		void SettingLeftMaterial();
		void PlayPartsMotion();
		void SkillPartsMotion(std::wstring key);
		
		void PlayPartsSprite(EPlayerState state, int index);
		void SetCompleteEventAnimation(EPlayerState state, int prev_index, int next_index);
		void SetCompleteEventAnimations(EPlayerState state);

		void SetStartEventAnimation(EPlayerState state, int prev_index, std::function<void()>func);
		void CompleteEventAnimation(EPlayerState state, std::function<void()> func);
		void CompleteEventAnimation(EPlayerState state, int prev_index, std::function<void()> func);
		void EndEventAnimation(EPlayerState state, int index, std::function<void()> func);
		void ConnectNextAnimations(EAvatarParts part, std::wstring prev_ani, std::wstring next_ani);
		void StopAni();
		void StartAni();
		void AddSpriteIndex();

		std::shared_ptr<GameObject> GetPart(EAvatarParts part) { mParts[part]; }
		bool IsAniStop() { return mbAniStop; }
	private:
		friend class FactoryBase;
		friend class ScriptFactory;

		std::map<EPlayerState, std::map<EAvatarParts,std::vector<std::wstring>>> mStateAnis;
		std::map<EAvatarParts, std::weak_ptr<GameObject>> mParts;
		bool mbAniStop;
	};

}

