#ifndef MESH_H
#define MESH_H

#include "core.h"
#include "renderer/shader.h"

struct Vertex {
	glm::vec3 position;
	glm::vec3 color;
	glm::vec2 texCoords;
	glm::vec1 texId;
};

class Mesh {
private:
	const int MAX_VERTEX_SIZE = 1000;
	const int MAX_VERTICES_SIZE = MAX_VERTEX_SIZE * 4;
	const int MAX_INDICES_SIZE = MAX_VERTEX_SIZE * 6;

public:
	std::vector<Vertex> vertex;
	unsigned int vao, vbo, ebo;
	const void* indices;

	Mesh();
	~Mesh();

	void createQuad(float x, float y, float texID, float size);
	void Init();
	void Draw();
	void calculateIndices();
};

#endif // !MESH_H