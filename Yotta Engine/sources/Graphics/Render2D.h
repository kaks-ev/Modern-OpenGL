#ifndef RENDER2D_H
#define RENDER2D_H

#include "core.h"
#include "vertex.h"

namespace Yotta
{
	namespace Render2D {

		const size_t MaxQuadCount = 1000;
		const size_t MaxVertexCount = MaxQuadCount * 4;
		const size_t MaxIndexCount = MaxQuadCount * 6;
		unsigned int vao, vbo, ebo;

		class Render2D {
		public:

			unsigned int indexCount = 0;
			void VertexAttrib();
			static void Draw(std::array<Vertex, 1000> vertices, unsigned int IndexCount);
		};
	}

}
#endif // !RENDER2D_H