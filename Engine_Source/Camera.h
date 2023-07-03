#pragma once
#include "Component.h"
namespace roka
{
	class Camera :public Component
	{
	public:
		enum class EProjectionType
		{
			Perpective,
			OrthoGraphic,
			None
		};
		Camera();
		virtual ~Camera();
		static Matrix GetViewMatrix() { return mView; }
		static Matrix GetProjectionMatrix() { return mProjection; }


		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		bool CreateViewMatrix();
		bool CreateProjectionMatrix(EProjectionType type);
		void RegisterCameraInRenderer();

		void TurnLayerMask(ELayerType type, bool enable = true);
		void EnableLayerMasks(){mLayerMask.set();}
		void DisableLayerMasks(){mLayerMask.reset();}
		
	private:
		void SortGameObjects();
		void RenderOpaque();
		void RenderCutOut();
		void RenderTransparent();
	private:
		static Matrix mView;
		static Matrix mProjection;

		float mAspectRatio;
		float mNear;
		float mFar;
		float mSize;

		EProjectionType mType;

		std::bitset<(UINT)ELayerType::End> mLayerMask;
		std::vector<GameObject*> mOpaqueGameObjects;
		std::vector<GameObject*> mCutOutGameObjects;
		std::vector<GameObject*> mTransparentObjects;
	};
}


