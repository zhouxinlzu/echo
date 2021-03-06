#pragma once

#include "engine/core/render/interface/ShaderProgram.h"
#include "mt_render_base.h"

namespace Echo
{
    /**
     * https://developer.apple.com/library/archive/documentation/Miscellaneous/Conceptual/MetalProgrammingGuide/Prog-Func/Prog-Func.html
     */
	class MTShaderProgram : public ShaderProgram
	{
    public:
        // link
        virtual bool linkShaders() override {return true;}
        
        // get mtl function
        id<MTLFunction> getMetalVertexFunction() { return m_metalVertexShader; }
        id<MTLFunction> getMetalFragmentFunction() { return m_metalFragmentShader; }
        
    private:
        // create shader library
        virtual bool createShaderProgram(const String& vsContent, const String& psContent) override;
        
    private:
        id<MTLLibrary>      m_metalLibrary;
        id<MTLFunction>     m_metalVertexShader;
        id<MTLFunction>     m_metalFragmentShader;
	};
}
