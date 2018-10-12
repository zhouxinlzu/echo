#pragma once

#include <interface/texture.h>

namespace Echo
{
	class GLESTexture2D: public Texture
	{
		friend class GLES2Renderer;

	public:
		// updateSubTex2D
		virtual	bool updateSubTex2D(ui32 level, const Rect& rect, void* pData, ui32 size) override;

	protected:
		GLESTexture2D(const String& name);
		virtual ~GLESTexture2D();

		// load
		virtual bool load() override;

		// unload
		bool unload();

	protected:
		// create
		void create2DTexture();

		// set surface data
		void set2DSurfaceData(int level, PixelFormat pixFmt, Dword usage, ui32 width, ui32 height, const Buffer& buff);

	public:
		GLuint		m_glesTexture;
	};
}
