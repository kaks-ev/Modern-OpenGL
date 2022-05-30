#include "renderer/window.h"
#include "renderer/shader.h"
#include "renderer/texture.h"
#include "Graphics/vertexArray.h"
#include "Graphics/indexBuffer.h"
#include "IO/keyListener.h"

Window Game("Flappy Bird - OpenGL");

Keyboard keyboard;
bool gameover;

int xScroll = 0;
int bg = 0;
float delta;

glm::vec3 position(0.0f);
float rotation = 0.0f;

void fall();

int main() {

	// background
	Shader bgShader("assets/shaders/bg.glsl");
	bgShader.Bind();
	Texture bgTexture("assets/img/bg.jpg");
	bgTexture.Bind(0);
	bgShader.SetUniformInt("uTexture", 0);
	
	float bgVertices[] =
	{
		// position					/ texture
		-16.0f, -10.0f, 0.2f, 0.0f, 0.0f,
			0.0f, -10.0f, 0.2f, 1.0f, 0.0f,
			0.0f,  10.0f, 0.2f, 1.0f, 1.0f,
		-16.0f,  10.0f, 0.2f, 0.0f, 1.0f
	};
	unsigned int bgIndices[] =
	{
		0, 1, 2,
		2, 3, 0
	};
	VertexArray bgVAO;
	VertexBuffer bgVBO(bgVertices, 20 * sizeof(float));
	VertexBufferLayout bgLayout;
	bgLayout.Push<float>(3);
	bgLayout.Push<float>(2);
	bgVAO.AddBuffer(bgVBO, bgLayout);
	IndexBuffer bgEBO(bgIndices, 6);

	glm::mat4 bgProjection;
	bgProjection = glm::ortho(-16.0f, 16.0f, -10.0f, 10.0f, -1.0f, 1.0f);
	bgShader.SetUniformMatrix("projection", bgProjection);
	
	// bird
	Shader birdShader("assets/shaders/bird.glsl");
	birdShader.Bind();
	Texture birdTexture("assets/img/bird.png");
	birdTexture.Bind(0);
	birdShader.SetUniformInt("uTexture", 0);
	

	float birdVertices[] = 
	{
		// position					/ texture
		-0.7f, -0.5f, 0.0f, 0.0f, 0.0f,
		 0.7f, -0.5f, 0.0f, 1.0f, 0.0f,
		 0.7f,  0.5f, 0.0f, 1.0f, 1.0f,
		-0.7f,  0.5f, 0.0f, 0.0f, 1.0f
	};
	unsigned int birdIndices[] = 
	{
		0, 1, 2,
		2, 3, 0
	};
	VertexArray birdVAO;
	VertexBuffer birdVBO(birdVertices, 20 * sizeof(float));
	VertexBufferLayout birdLayout;
	birdLayout.Push<float>(3);
	birdLayout.Push<float>(2);
	birdVAO.AddBuffer(birdVBO, birdLayout);
	IndexBuffer birdEBO(birdIndices, 6);

	glm::mat4 birdProjection = glm::mat4(1.0f);
	birdProjection = glm::ortho(-16.0f, 16.0f, -10.0f, 10.0f, -1.0f, 1.0f);
	birdShader.SetUniformMatrix("projection", birdProjection);
	
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::rotate(glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f));
	birdShader.SetUniformMatrix("model", model);

	glm::mat4 view = glm::mat4(1.0f);
	view = glm::translate(view, position);
	birdShader.SetUniformMatrix("view", view);

	while (Game.loop()) {
		Game.render();

		// =========== background ===========
		if (xScroll % 335 == 0) bg++;
		bgShader.Bind();
		xScroll--;
		bgTexture.Bind(0);
		bgShader.SetUniformInt("uTexture", 0);
	
		bgVAO.Bind();
		bgEBO.Bind();

		for (int i = bg; i < bg + 4; i++) {

			bgShader.SetUniformMatrix("view", glm::translate(glm::mat4(1.0f), glm::vec3(i * 10 + xScroll * 0.03f, 0.0f, 0.0f)));
			glDrawElements(GL_TRIANGLES, bgEBO.GetCount(), GL_UNSIGNED_INT, 0);
		}
		bgShader.Unbind();
		bgVAO.Unbind();
		bgEBO.Unbind();

		// =========== bird ===========
		birdShader.Bind();
		birdTexture.Bind(0);
		birdShader.SetUniformInt("uTexture", 0);

		fall();
		position.y -= delta;
		if (keyboard.key(GLFW_KEY_UP) || keyboard.key(GLFW_KEY_W) || keyboard.key(GLFW_KEY_SPACE)) {

			rotation += 13.0f * 0.8f;
			if (rotation >= 45.0f) {
				rotation = 45.0f;
			}
			delta = 0.075f * 0.5f;
			position.y += delta;
		}

		model = glm::rotate(glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f));
		birdShader.SetUniformMatrix("model", model);
		view = glm::translate(view, position);
		birdShader.SetUniformMatrix("view", view);
		
		birdVAO.Bind();
		birdEBO.Bind();

//	glLineWidth(2.0f);
//	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glDrawElements(GL_TRIANGLES, birdEBO.GetCount(), GL_UNSIGNED_INT, 0);
//	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		
		birdShader.Unbind();
		birdEBO.Unbind();
		birdVAO.Unbind();

		Game.update();
	}

	return 0;
}

void fall() {
	delta = 0.013f;

	rotation -= 4.8f * 0.8f;
	if (rotation < -40.0f) {
		rotation = -40.0f;
	}
}