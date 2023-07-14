#pragma once
#include "Component.h"
namespace roka
{
	class Camera :public Component
	{
	private:
		Camera();
		Camera(const Camera& ref);
		virtual void Copy(Component* src)override;
	public:
		enum class EProjectionType
		{
			Perpective,
			OrthoGraphic,
			None
		};
		
		virtual ~Camera();

		static Matrix GetViewMatrix() { return View; }
		static Matrix GetProjectionMatrix() { return Projection; }


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
		
		float GetSize() { return mSize; }
		GET_PROPERTY(GetSize) float size;

	private:
		void AlphaSortGameObjects();
		void ZSortTransparencyGameObjects();
		void DivideAlphaBlendGameObjects(const std::vector<GameObject*> objs);

		void RenderOpaque();
		void RenderCutOut();
		void RenderTransparent();

		void EnableDepthStencilState();
		void DisableDepthStencilState();
	private:
		friend class ComponentFactory;
		static Matrix View;
		static Matrix Projection;

		Matrix mView;
		Matrix mProjection;

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


