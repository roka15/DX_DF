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
	private:
		static Matrix mView;
		static Matrix mProjection;

		float mAspectRatio;
		float mNear;
		float mFar;
		float mSize;

		EProjectionType mType;
	};
}


