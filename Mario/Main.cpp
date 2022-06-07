#include "renderer/window.h"
#include "renderer/shader.h"
#include "renderer/texture.h"
#include "IO/keyListener.h"
#include "IO/Camera.h"

Window Game("Yotta Engine <OpenGL>");
Keyboard keyboard;
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));

struct vec2 { float x = 1.0f, y = 2.0f; };
float delta;
vec2 position;
float endSkySize = 10.0f;

struct Vertex {
	glm::vec3 position;
	glm::vec3 color;
	glm::vec2 TexCoords;
	glm::vec1 TexID;
};
void controller();
void gravity();
bool xFlip = false;

float lastFrame = 0.0f;
float deltaTime = 0.0f;

Vertex* CreateQuad(Vertex* target, float x, float y, float size, float textureID, bool xflip)
{
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

	Texture mario("assets/mario.png");
	Texture obstacle("assets/obstacle.png");
	Texture brick("assets/brick.png");
	Texture bg("assets/bg.jpg");

	GLint samplers[4] = { 0, 1, 2, 3 };
	shader.SetUniformiv("uTexture", 4, samplers);

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

	unsigned int indices[MaxIndexCount];
	unsigned int offset = 0;
	for (int i = 0; i < MaxIndexCount; i += 6)
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
	//glm::mat4 projection =  glm::perspective(glm::radians(90.0f), (float)Game.getWidth() / (float)Game.getHeight(), 0.1f, 100.f);
	shader.SetUniformMatrix("projection", camera.GetProjectionMatrix());

	while (Game.loop()) {

		auto currentFrame = static_cast<float>(glfwGetTime());
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		Game.render();
		gravity();
		controller();

		std::array<Vertex, 1000> vertices;
		Vertex* buffer = vertices.data();
		unsigned int IndexCount = 0;

		shader.Bind();
		shader.SetUniformMatrix("uView", camera.GetViewMatrix());

		// set texture
		glBindTextureUnit(0, mario.getID()); // 0
		glBindTextureUnit(1, brick.getID()); // 1
		glBindTextureUnit(2, obstacle.getID()); // 2
		glBindTextureUnit(3, bg.getID()); // 3

		for (int x = 0; x <= 12.0f; x++) {
			buffer = CreateQuad(buffer, x, 0.0f, 1.0f, 3.0f, false);
			IndexCount += 6;
		}

		// obstacle
		for (int x = 6; x < 9; x++) {
			buffer = CreateQuad(buffer, x, 3.0f, 0.8f, 2.0f, false);
			IndexCount += 6;
			for (int position = x; position <= x + x; position += x) {
				buffer = CreateQuad(buffer, position, 3.0f, 0.8f, 2.0f, false);
				IndexCount += 6;
			}
		}
		// brick
		for (int x = 0; x < 20; x++) {
			buffer = CreateQuad(buffer, x, 0.0f, 1.0f, 1.0f, false);
			IndexCount += 6;
		}
		// mario
		buffer = CreateQuad(buffer, position.x, position.y,1.0f, 0.0f, xFlip);
		IndexCount += 6;

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
		Game.update();
	}

	return 0;
}
void gravity() {
	delta = 0.1f;
	position.y -= delta;
	if (position.y <= 1.0f) {
		position.y = 1.0f;
	}
}
void controller() {

	// mario controller
	if (Keyboard::key(GLFW_KEY_A)) {
		xFlip = true;
		position.x -= 0.05f;
		std::cout << "LEFT\n";
	}
	if (Keyboard::key(GLFW_KEY_D)) {
		xFlip = false;
		position.x += 0.05f;
		std::cout << "RIGHT\n";
	}
	if (glfwGetKey(Game.getWindow(), GLFW_KEY_SPACE) == GLFW_PRESS) {
		position.y += 0.35f;
		if (position.y >= 5.0f) {
			position.y = 5.0f;
			delta = 2.f;
			position.y -= delta;
		}
	}
}
void Window::ImGuiRender() {

	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	ImGui::Begin("Controls");
	ImGui::Text("%.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	ImGui::SliderFloat2("Quad Position", &position.x, 1.0f, 16.0f, "px", 1.0f);
	ImGui::End();

	ImGui::Render();
}