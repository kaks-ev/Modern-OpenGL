#pragma once
#include "core.h"
struct Vertex {
	glm::vec3 position;
	glm::vec3 color;
	glm::vec2 TexCoords;
	glm::vec1 TexID;
};

Vertex* CreateQuad2D(Vertex* target, float x, float y, float textureID, bool xflip)
{
	float size = 1.0f;

	// bottom left
	target->position = { x, y, 0.0f };
	target->color = { 1.0f, 1.0f, 1.0f };
	if (xflip == false) target->TexCoords = { 0.0f, 0.0f };
	else target->TexCoords = { 1.0f, 0.0f };
	target->TexID = glm::vec1(textureID);
	target++;

	// bottom right
	target->position = { x + size, y, 0.0f };
	target->color = { 1.0f, 1.0f, 1.0f };
	if (xflip == false) target->TexCoords = { 1.0f, 0.0f };
	else target->TexCoords = { 0.0f, 0.0f };
	target->TexID = glm::vec1(textureID);
	target++;

	// top right
	target->position = { x + size, y + size, 0.0f };
	target->color = { 1.0f, 1.0f, 1.0f };
	if (xflip == false) target->TexCoords = { 1.0f, 1.0f };
	else target->TexCoords = { 0.0f, 1.0f };
	target->TexID = glm::vec1(textureID);
	target++;

	// top left
	target->position = { x, y + size, 0.0f };
	target->color = { 1.0f, 1.0f, 1.0f };
	if (xflip == false)target->TexCoords = { 0.0f, 1.0f };
	else target->TexCoords = { 1.0f, 1.0f };
	target->TexID = glm::vec1(textureID);
	target++;

	return target;
}