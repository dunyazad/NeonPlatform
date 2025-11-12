#include "interfaces/INeonRender.h"
#include "core/NeonCommon.h"
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

class NeonRender : public INeonRender {
public:
    bool Initialize() override {
        NEON_LOG_INFO("Initializing NeonRender (ImGui docking)");
        window = glfwGetCurrentContext();
        if (!window) {
            NEON_LOG_ERROR("GLFW context not found!");
            return false;
        }
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
            NEON_LOG_ERROR("Failed to initialize GLAD");
            return false;
        }

        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO();
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

        ImGui::StyleColorsDark();
        ImGuiStyle& style = ImGui::GetStyle();
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
            style.WindowRounding = 0.0f;
            style.Colors[ImGuiCol_WindowBg].w = 1.0f;
        }

        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init("#version 460");

        NEON_LOG_INFO("ImGui initialized with docking branch");
        return true;
    }

    void Update() override { RenderFrame(); }

    void RenderFrame() override {
        glfwMakeContextCurrent(window);
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());
        ImGui::Begin("Neon Docking");
        ImGui::Text("ImGui Docking branch active!");
        ImGui::End();

        ImGui::Render();
        int w, h;
        glfwGetFramebufferSize(window, &w, &h);
        glViewport(0, 0, w, h);
        glClearColor(0.12f, 0.12f, 0.13f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        ImGuiIO& io = ImGui::GetIO();
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
            GLFWwindow* backup = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(backup);
        }
        glfwSwapBuffers(window);
    }

    void Shutdown() override {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
        NEON_LOG_INFO("Renderer shutdown");
    }

    const char* GetName() const override { return "NeonRender"; }

private:
    GLFWwindow* window = nullptr;
};

extern "C" NEON_EXPORT INeonPlugin* CreatePlugin() {
    return new NeonRender();
}
