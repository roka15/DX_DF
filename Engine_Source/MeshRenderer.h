#pragma once
#include "Component.h"
#include "Mesh.h"
#include "Material.h"
namespace roka
{
	using namespace roka::graphics;
	class MeshRenderer : public Component
	{
	private:
		MeshRenderer();
		MeshRenderer(const MeshRenderer& ref);
		virtual void Copy(Component* src)override;
	public:
		~MeshRenderer();
		virtual void Initialize()override;
		virtual void Update()override;
		virtual void LateUpdate()override;
		virtual void Render()override;

		void Execute();
		void SetMesh(std::shared_ptr<Mesh> mesh) { mMesh = mesh; }
		std::shared_ptr<Mesh> GetMesh() { return mMesh; }
		void SetMaterial(std::shared_ptr<Material> material) { mMaterial = material; }
		std::shared_ptr<Material> GetMaterial() { return mMaterial; }
		void SetAlpha(float alpha) { mAlpha = alpha; }
		float GetAlpha() { return mAlpha; }

		PROPERTY(GetMesh,SetMesh) std::shared_ptr<Mesh> mesh;
		PROPERTY(GetMaterial,SetMaterial) std::shared_ptr<Material> material;
		PROPERTY(GetAlpha, SetAlpha) float alpha;
	private:
		friend class FactoryBase;
		friend class ComponentFactory;
		std::shared_ptr<Mesh> mMesh;
		std::shared_ptr<Material> mMaterial;
		float mAlpha;
	};
}


