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
		PartScript(EScriptType type);
		PartScript(const PartScript& ref);
		void Copy(Component* src);
	public:
		~PartScript();
		
		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		virtual void SetEvent() {};
		virtual void Idle();
		virtual void Walk();
		virtual void Run();
		virtual void Jump();
		virtual void Fall();
		virtual void JumpDash();
		virtual void JumpHold();
		virtual void NormalAtk();
		virtual void Stagger();
		virtual void Down();
		virtual void Standing();
		virtual void Landing();

		
		// 여기서부터 
		virtual void PlayPartMotion(std::wstring name, bool flag);
		virtual void PlayPartSprite(std::wstring name, int index);
        //여기까지 지우기 
		virtual void CreateAni(std::wstring npk_name, std::wstring pack_name, std::wstring set_name, UINT start, UINT end, float duration);
		virtual void CreateAni(std::shared_ptr<Texture> atlas, std::wstring set_name, UINT start, UINT end, float duration);
		
		virtual void ConnectAnimations(std::wstring prev_name, std::wstring next_name);

		virtual void ConnectEvent(UINT type,std::wstring name,std::function<void()> func);
		
		virtual void Create(std::wstring npk, std::wstring pack);

		virtual void Right();
		virtual void Left();
		virtual void Stop();
		virtual void Start();

		virtual void DisableMove();
		virtual void EnableMove();
		virtual void NextState();
		virtual void DownDelayEvent();
		virtual void StandingCompleteEvent();

		virtual void NextSprite();
		void SetPartType(EAvatarParts type) { mPartType = type; }
		EAvatarParts GetPartType() { return mPartType; }

		PROPERTY(GetPartType,SetPartType) EAvatarParts part_type;
	private:
		friend class FactoryBase;
		friend class ScriptFactory;
	protected:
		EAvatarParts mPartType;
	};
}


