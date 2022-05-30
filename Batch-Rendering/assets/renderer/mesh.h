#ifndef MESH_H
#define MESH_H

#include "core.h"
#include "renderer/shader.h"

struct Vertex {
	glm::vec3 position;
	glm::vec3 color;
	glm::vec2 texCoords;
	glm::vec1 texID;
};

class Mesh
{
private:

public:
	Mesh(Vertex position, Shader& shader);
	
	void init() const;

	void Bind();
	void Draw();
	void Render();
};


#endif // !MESH_H