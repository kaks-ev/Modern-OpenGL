#ifndef CORE_H
#define CORE_H

#include <iostream>
#include <stdio.h>
#include <string>
#include <fstream>
#include <sstream>
#include <Windows.h>
#include <vector>
#include <unordered_map>
#include <array>

// GUI
#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>
#include <imgui/imgui_internal.h>

// GL
#define GLEW_STATIC
#include <glew/glew.h>
#include <glfw/glfw3.h>
#include <stb_image/stb_image.h>

// MATH
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include<glm/gtx/rotate_vector.hpp>
#include<glm/gtx/vector_angle.hpp>

#endif