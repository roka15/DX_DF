#pragma once
#include "Script.h"
#include "ContentEnums.h"
#include "Renderer.h"
using namespace roka::graphics;
namespace roka
{
	namespace graphics
	{
		class Texture;
	}

	class PartScript :
		public Script
	{
	protected:
		PartScript();
		PartScript(const PartScript& ref);
		void Copy(Component* src);
	public:
		~PartScript();
		
		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		virtual void PlayPartMotion(std::wstring name, bool flag);
		virtual void PlayPartSprite(std::wstring name, int index);

		virtual void CreateAni(std::wstring npk_name, std::wstring pack_name, std::wstring set_name, UINT start, UINT end, float duration);
		virtual void CreateAni(std::shared_ptr<Texture> atlas, std::wstring set_name, UINT start, UINT end, float duration);
		
		virtual void ConnectAnimations(std::wstring prev_name, std::wstring next_name);

		virtual void ConnectEvent(UINT type,std::wstring name,std::function<void()> func);

		virtual void Right();
		virtual void Left();
		virtual void Stop();
		virtual void Start();

		virtual void NextSprite();
		void SetPartType(EAvatarParts type) { mPartType = type; }
		EAvatarParts GetPartType() { return mPartType; }

		PROPERTY(GetPartType,SetPartType) EAvatarParts part_type;
	private:
		friend class FactoryBase;
		friend class ScriptFactory;
		EAvatarParts mPartType;
	};
}


