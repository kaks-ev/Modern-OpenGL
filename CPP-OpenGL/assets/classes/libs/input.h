#include "core.h"

void userInput(GLFWwindow *window)
{
  // MOUSE
  // mouse position
  double mouseX;
  double mouseY;
  //std::string empty = "-";
  
  glfwGetCursorPos(window, &mouseX, &mouseY);
  if (mouseX < 0 || mouseX > SCREEN_WIDTH || mouseY < 0 || mouseY > SCREEN_HEIGHT)
  {
   // std::cout << "mouse X : " << empty << " mouse Y : " << empty << std::endl;
  }
  else
    //std::cout << "mouse X : " << mouseX << " mouse Y : " << mouseY << std::endl;

  // mouse button
  if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
  {
    std::cout << "LEFT MOUSE" << std::endl;
  };
  if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
  {
    std::cout << "RIGHT MOUSE" << std::endl;
  };
  if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_PRESS)
  {
    std::cout << "MIDDLE BUTTON" << std::endl;
  };

  // KEYBOARD
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
  {
    glfwSetWindowShouldClose(window, true);
  }

  if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
  {
    std::cout << "A" << std::endl;
    // std::cout << "TURN LEFT" << std::endl;
  }
  if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
  {
    std::cout << "D" << std::endl;
    // std::cout << "TURN RIGHT" << std::endl;
  }
  if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
  {
    std::cout << "W" << std::endl;
    // std::cout << "TURN FORWARD" << std::endl;
  }
  if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
  {
    std::cout << "S" << std::endl;
    // std::cout << "TURN BACKWARD" << std::endl;
  }

  if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
  {
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  }
  if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
  {
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  }
}