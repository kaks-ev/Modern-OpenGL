#include "renderer/window.h"
#include "renderer/shader.h"
#include "renderer/texture.h"
#include "IO/keyListener.h"
#include "IO/Camera.h"

Window Game("Yotta Engine <OpenGL>");
Keyboard keyboard;
Camera camera(glm::vec3(1.0f));

struct Vertex {
	glm::vec3 position;
	glm::vec3 color;
	glm::vec2 TexCoords;
	glm::vec1 TexID;
};
void controller();

int xTilling = 1, yTilling = 1;


Vertex* CreateQuad(Vertex* target, float x, float y, float textureID, bool xflip)
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

int main() {

	Shader shader("assets/shaders/default.glsl");
	shader.Bind();

	Texture plane("assets/img/plane.jpg");
	plane.Bind();

	GLint samplers[1] = { 0 };
	shader.SetUniformiv("uTexture", 1, samplers);

	const size_t MaxQuadCount = 1000;
	const size_t MaxVertexCount = MaxQuadCount * 4;
	const size_t MaxIndexCount = MaxQuadCount * 6;

	unsigned int vao, vbo, ebo;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, MaxVertexCount * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);

	// aPos
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
	glEnableVertexAttribArray(0);
	// aColor
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));
	glEnableVertexAttribArray(1);
	// aTexCoords
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));
	glEnableVertexAttribArray(2);
	// aTexID
	glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexID));
	glEnableVertexAttribArray(3);

	uint32_t indices[MaxIndexCount];
	uint32_t offset = 0;
	for (size_t i = 0; i < MaxIndexCount; i += 6)
	{
		indices[i + 0] = 0 + offset;
		indices[i + 1] = 1 + offset;
		indices[i + 2] = 2 + offset;

		indices[i + 3] = 2 + offset;
		indices[i + 4] = 3 + offset;
		indices[i + 5] = 0 + offset;

		offset += 4;
	}

	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glBindVertexArray(0);

	shader.SetUniformMatrix("projection", camera.GetProjectionMatrix());

	while (Game.loop()) {
		Game.render();
		controller();


		

		std::array<Vertex, 1000> vertices;
		Vertex* buffer = vertices.data();
		unsigned int IndexCount = 0;

		shader.Bind();
		shader.SetUniformMatrix("uView", camera.GetViewMatrix());

		// set texture
		glBindTextureUnit(0, plane.getID()); // 0

		for (int x = 0; x <= xTilling; x++) {
			for (int y = 0; y <= yTilling; y++) {
				buffer = CreateQuad(buffer, x, y, 0.0f, false);
				IndexCount += 6;
			}
		}

		glBindVertexArray(vao);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
		glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Vertex), vertices.data());

		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glDrawElements(GL_TRIANGLES, IndexCount, GL_UNSIGNED_INT, 0);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

		shader.Unbind();
		Game.ImGuiOnAttach();
		Game.update();
	}

	return 0;
}
void controller() {

	if (Keyboard::key(GLFW_KEY_A)) {
		camera.Position.x -= 0.2f;
	}
	if (Keyboard::key(GLFW_KEY_D)) {
		camera.Position.x += 0.2f;
	}
	if (Keyboard::key(GLFW_KEY_S)) {
		camera.Position.y -= 0.2f;
	}
	if (Keyboard::key(GLFW_KEY_W)) {
		camera.Position.y += 0.2f;
	}

}

void Window::ImGuiOnAttach() {

	Window::ImGuiNewFrame();

	ImGui::Begin("FPS COUNTER");
	ImGui::Text("%.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	ImGui::End();

	ImGui::Begin("Settings");
	ImGui::Text("");
	ImGui::SliderInt("X-Tiling", &xTilling, 1, 12, "");
	ImGui::SliderInt("Y-Tiling", &yTilling, 1, 12, "");
	ImGui::ColorEdit3("BG Color", Game.bgcolor, 0);
	ImGui::End();

	Window::ImGuiRender();
}