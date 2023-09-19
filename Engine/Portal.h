#pragma once
#include "ICollisionListener.h"

namespace roka
{
	using namespace enums;
	class Portal : public ICollisionListener
	{
	public:
		Portal(EPortalType portal, ESceneType scene) :mCurScene(scene),mCurPortal(portal) {}
		virtual void OnCollisionEnter(std::shared_ptr<GameObject> caster, std::shared_ptr<GameObject> target) = 0;
		virtual void OnCollisionStay(std::shared_ptr<GameObject> caster, std::shared_ptr<GameObject> target) = 0;
		virtual void OnCollisionExit(std::shared_ptr<GameObject> caster, std::shared_ptr<GameObject> target) = 0;
		ESceneType GetCurScene() { return mCurScene; }
		EPortalType GetCurPortal() { return mCurPortal; }
		virtual void SetCollisionListener(std::shared_ptr<GameObject>& obj)override;
	protected:
		const ESceneType mCurScene;
		const EPortalType mCurPortal;
	};

	class DirectPortal :public Portal
	{
	public:
		DirectPortal(EPortalType portal, ESceneType scene) :Portal(portal, scene) {}
		virtual void OnCollisionEnter(std::shared_ptr<GameObject> caster, std::shared_ptr<GameObject> target);
		virtual void OnCollisionStay(std::shared_ptr<GameObject> caster, std::shared_ptr<GameObject> target);
		virtual void OnCollisionExit(std::shared_ptr<GameObject> caster, std::shared_ptr<GameObject> target);
		void SetConnectScene(ESceneType connect) { mConnectScene = connect; }
		void SetConnectPortal(EPortalType portal) { mConnectPortal = portal; }
	protected:
		ESceneType mConnectScene;
		EPortalType mConnectPortal;
	};

	class SelectPortal :public Portal
	{
	public:
		SelectPortal(EPortalType portal, ESceneType scene) :Portal(portal, scene) {}
		virtual void OnCollisionEnter(std::shared_ptr<GameObject> caster, std::shared_ptr<GameObject> target);
		virtual void OnCollisionStay(std::shared_ptr<GameObject> caster, std::shared_ptr<GameObject> target);
		virtual void OnCollisionExit(std::shared_ptr<GameObject> caster, std::shared_ptr<GameObject> target);
	protected:
		std::vector<ESceneType> mConnectScenes;
		std::vector<EPortalType> mConnectPortals;
	};
}


