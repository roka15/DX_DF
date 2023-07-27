#pragma once
#include "Script.h"
#include "ContentEnums.h"
namespace roka
{
	class Image;
	using namespace enums;
	class AvatarScript :
		public Script
	{
	private:
		AvatarScript();
		AvatarScript(const AvatarScript& ref);
		void Copy(AvatarScript* src);
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
		void PlayPartsMotion();
		
		void SetUpdateFlag(bool flag) { mUpdateFlag = flag; }

		SET_PROPERTY(SetUpdateFlag) bool update_flag;
	private:
		friend class FactoryBase;
		friend class ScriptFactory;

		bool mUpdateFlag;
		std::map<EPlayerState, std::vector<std::pair<EAvatarParts,std::wstring>>> mStateAnis;
		std::map<EAvatarParts, std::weak_ptr<Image>> mParts;
	};

}

