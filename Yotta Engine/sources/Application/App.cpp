#include "App.h"
#include "Utils\ImGuiLayer.h"
#include "Graphics\vertex.h"
#include "Graphics\Render2D.h"

using namespace Yotta;
Camera camera(glm::vec3(1.0f));

const size_t MaxQuadCount = 1000;
const size_t MaxVertexCount = MaxQuadCount * 4;
const size_t MaxIndexCount = MaxQuadCount * 6;

unsigned int vao, vbo, ebo;

void App::onStart() {

	// code here
	shader.Bind();
	texture.Bind();
	GLint samplers[1] = { 0 };
	shader.SetUniformiv("uTexture", 1, samplers);
	shader.SetUniformMatrix("projection", camera.GetProjectionMatrix());
	
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, MaxVertexCount * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);

	// aPos
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, position));
	glEnableVertexAttribArray(0);
	// aColor
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, color));
	glEnableVertexAttribArray(1);
	// aTexCoords
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, TexCoords));
	glEnableVertexAttribArray(2);
	// aTexID
	glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, TexID));
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

}
void App::update() {

	while (window.loop()) {
		window.render();
		App::CameraControl();
		App::ImGuiOnAttach();
		// code here

		shader.Bind();
		texture.Bind();

		std::array<Vertex, 1000> vertices;
		Vertex* buffer = vertices.data();
		unsigned int IndexCount = 0;

		shader.SetUniformMatrix("uView", camera.GetViewMatrix());

		glBindTextureUnit(0, texture.getID());
		for (int x = 0; x <= 10; x++) {
			for (int y = 0; y <= 10; y++) {
				buffer = CreateQuad2D(buffer, (float)x, (float)y, 0.0f, false);
				IndexCount += 6;
			}
		}

		glBindVertexArray(vao);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
		glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Vertex), vertices.data());
		glDrawElements(GL_TRIANGLES, IndexCount, GL_UNSIGNED_INT, 0);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

		texture.Unbind();
		shader.Unbind();

		window.update();
	}
}
void App::run() {
	onStart();
	update();
}

void App::CameraControl() {

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

void App::ImGuiOnAttach() {
	ImGui::Begin("Controls", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
	ImGui::ColorEdit4("clear color", window.bgcolor);
	if (ImGui::Button("reset color", ImVec2(85, 20))) {
		window.bgcolor[0] = 0.1f;
		window.bgcolor[1] = 0.1f;
		window.bgcolor[2] = 0.1f;
		window.bgcolor[3] = 1.0f;
	}
	ImGui::ShowDemoWindow();
	ImGui::End();

	//ImGui::ShowStyleEditor();

}