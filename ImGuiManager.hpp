﻿#pragma once

#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

namespace ImGuiManager{

	inline void Setup(GLFWwindow* window){
	  // Setup Dear ImGui context
	  IMGUI_CHECKVERSION();
	  ImGui::CreateContext();
	  ImGuiIO &io = ImGui::GetIO();
	  io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	  io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

	  // Setup Platform/Renderer backends
	  ImGui_ImplGlfw_InitForOpenGL(window, true);          // Second param install_callback=true will install GLFW callbacks and chain to existing ones.
	  ImGui_ImplOpenGL3_Init();
	}
	
	inline void NewFrame(){
	  ImGui_ImplOpenGL3_NewFrame();
	  ImGui_ImplGlfw_NewFrame();
	  ImGui::NewFrame();
	}
	
	inline void PostFrame(){
	  ImGui::Render();
	  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}
}