#pragma once
#include "Script.h"
#include "ContentEnums.h"
namespace roka
{
	class Image;
	class Transform;
	using namespace enums;
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

		void CreatePartAni(EAvatarParts type, std::wstring npk_name, std::wstring pack_name,std::wstring set_name, UINT start, UINT end, float duration);
		void InsertStateAniInfo(EPlayerState state,EAvatarParts part, std::wstring ani_name);
		void SettingRightMaterial();
		void SettingLeftMaterial();
		void PlayPartsMotion();
		void PlayPartsMotion(EPlayerState state, int index, bool flag);
		void SetCompleteEventAnimation(EPlayerState state, int prev_index, int next_index);
		void SetCompleteEventAnimations(EPlayerState state);

		void SetStartEventAnimation(EPlayerState state, int prev_index, std::function<void()>func);
		void CompleteEventAnimation(EPlayerState state, std::function<void()> func);
		void CompleteEventAnimation(EPlayerState state, int prev_index, std::function<void()> func);
		void EndEventAnimation(EPlayerState state, int index, std::function<void()> func);
		void ConnectNextAnimations(EAvatarParts part, std::wstring prev_ani, std::wstring next_ani);
		void StopAni();
		void StartAni();
		void SetUpdateFlag(bool flag) { mUpdateFlag = flag; }

		SET_PROPERTY(SetUpdateFlag) bool update_flag;
	private:
		friend class FactoryBase;
		friend class ScriptFactory;

		bool mUpdateFlag;
		std::map<EPlayerState, std::map<EAvatarParts,std::vector<std::wstring>>> mStateAnis;
		std::map<EAvatarParts, std::weak_ptr<GameObject>> mParts;
	};

}

