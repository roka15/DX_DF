#pragma once
#include "Component.h"
#include "Mesh.h"
#include "Material.h"
namespace roka
{
	using namespace roka::graphics;
	class MeshRenderer : public Component
	{
	public:
		MeshRenderer();
		~MeshRenderer();

		virtual void Initialize()override;
		virtual void Update()override;
		virtual void LateUpdate()override;
		virtual void Render()override;

		void SetMesh(std::shared_ptr<Mesh> mesh) { mMesh = mesh; }
		void SetMaterial(std::shared_ptr<Material> material) { mMaterial = material; }

		SET_PROPERTY(SetMesh) std::shared_ptr<Mesh> mesh;
		SET_PROPERTY(SetMaterial) std::shared_ptr<Material> material;
	private:
		std::shared_ptr<Mesh> mMesh;
		std::shared_ptr<Material> mMaterial;
	};
}


