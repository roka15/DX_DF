#pragma once
#include <Script.h>
#include "Camera.h"
namespace roka
{
	class GridScript :
		public Script
	{
	public:
		GridScript();
		~GridScript();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		void SetCamera(Camera* camera) { mCamera = camera; }
		SET_PROPERTY(SetCamera) Camera* camera;
	private:
		Camera* mCamera;
	};
}

