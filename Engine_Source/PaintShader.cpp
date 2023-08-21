#include "PaintShader.h"
#include "Texture.h"
#include "Sprite.h"

namespace roka::graphics
{
	void PaintShader::Binds()
	{
		mTarget->BindUnorderedAccessViews(0);
	
		const Vector2 size = mTarget->GetSprite().canvas_size;

		mGroupX = size.x / mThreadGroupCountX + 1;
		mGroupY = size.y / mThreadGroupCountY + 1;
		mGroupZ = 1;
	}

	void PaintShader::Clear()
	{
		mTarget->ClearUnorderedAccessViews(0);
	}

}
