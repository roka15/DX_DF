#pragma once
#include "Script.h"
#include "Camera.h"
namespace roka
{
	class GridScript :
		public Script
	{
	private:
		GridScript();
		GridScript(const GridScript& ref);
		virtual void Copy(Component* src)override;
	public:
		virtual ~GridScript();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		void SetCamera(std::weak_ptr<Camera> camera) { mCamera = camera; }
		SET_PROPERTY(SetCamera) std::weak_ptr<Camera> camera;
	private:
		friend class FactoryBase;
		friend class ScriptFactory;
		std::weak_ptr<Camera> mCamera;
	};
}

