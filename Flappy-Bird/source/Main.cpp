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
glm::vec3 rot(0.0f);

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
	model = glm::translate(model, position);
	birdShader.SetUniformMatrix("model", model);

	glm::mat4 view = glm::mat4(1.0f);
	birdShader.SetUniformMatrix("view", view);

	while (Game.loop()) {
		Game.render();

		// =========== background ===========
		bgShader.Bind();
		xScroll--;
		if (xScroll % 335 == 0) bg++;
		bgTexture.Bind(0);
		bgShader.SetUniformInt("uTexture", 0);
	
		bgVAO.Bind();
		bgEBO.Bind();

		for (int i = bg; i < bg + 4; i++) {

			bgShader.SetUniformMatrix("view", glm::translate(glm::mat4(1.0f), glm::vec3(i * 10 + xScroll * 0.03f, 0.0f, 0.0f)));
			glDrawElements(GL_TRIANGLES, bgEBO.GetCount(), GL_UNSIGNED_INT, 0);
		}
		bgShader.Unbind();
		bgEBO.Unbind();
		bgVAO.Unbind();

		// =========== bird ===========
		birdShader.Bind();
		birdTexture.Bind(0);
		birdShader.SetUniformInt("uTexture", 0);

		fall();
		position.y -= delta;
		if (keyboard.keyWentDown(GLFW_KEY_UP) || keyboard.keyWentDown(GLFW_KEY_W) || keyboard.keyWentDown(GLFW_KEY_SPACE)) {
			std::cout << "up\n";
			delta += 0.3f;
			position.y += delta;
		}
		else delta += 0.5f;

		model = glm::translate(model, position);
		birdShader.SetUniformMatrix("model", model);

		
		birdVAO.Bind();
		birdEBO.Bind();
		glDrawElements(GL_TRIANGLES, birdEBO.GetCount(), GL_UNSIGNED_INT, 0);
		
		birdShader.Unbind();
		birdVAO.Unbind();
		birdEBO.Unbind();
		
		Game.update();
	}

	return 0;
}

void fall() {
	delta = 0.002f;
	position.y -= delta;
}