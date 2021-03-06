#pragma once

#include <engine/core/memory/MemAllocDef.h>
#include <engine/core/render/interface/RenderState.h>
#include <engine/core/render/interface/Renderable.h>
#include <engine/core/scene/node.h>

namespace Echo
{
	class RenderQueue : public Node
	{
		ECHO_CLASS(RenderQueue, Node);

	public:
		RenderQueue();
		virtual ~RenderQueue();

		// render
		virtual void render();

		// add renderalbe
		void addRenderable(RenderableID id) { m_renderables.push_back(id); }

		// set name
		void setName(const String& name) { m_name = name; }

		// get name
		const String& getName() const { return m_name; }

	protected:
		String							m_name;
		vector<RenderableID>::type		m_renderables;
	};


	class DefaultRenderQueueOpaque : public RenderQueue
	{
	public:
		DefaultRenderQueueOpaque();

		// render
		virtual void render();
	};

	class DefaultRenderQueueTransparent : public RenderQueue
	{
	public:
		DefaultRenderQueueTransparent();

		// sort
		void sort();

		// render
		virtual void render();
	};
}
