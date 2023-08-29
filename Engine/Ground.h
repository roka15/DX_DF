#pragma once
#include "Script.h"
namespace roka
{
	class Ground :
		public Script
	{
	private:
		Ground();
		Ground(const Ground& ref);
		void Copy(Component* src);
	public:
		~Ground();
		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		virtual void OnCollisionEnter(std::shared_ptr<Collider2D> other);
		virtual void OnCollisionStay(std::shared_ptr<Collider2D> other);
		virtual void OnCollisionExit(std::shared_ptr<Collider2D> other);
	private:
	};
}


