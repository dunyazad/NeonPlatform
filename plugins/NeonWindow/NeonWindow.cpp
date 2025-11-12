#include <INeonWindow.h>
#include <GLFW/glfw3.h>

class NeonWindow : public INeonWindow {
public:
    bool Initialize() override {
        NEON_LOG_INFO("Initializing GLFW...");
        if (!glfwInit()) return false;
        window = glfwCreateWindow(1280, 720, "Neon Window", nullptr, nullptr);
        glfwMakeContextCurrent(window);
        return window != nullptr;
    }

    void Update() override {
        if (window) glfwPollEvents();
    }

    void Shutdown() override {
        glfwDestroyWindow(window);
        glfwTerminate();
        NEON_LOG_INFO("GLFW window destroyed");
    }

    const char* GetName() const override { return "NeonWindow"; }
    GLFWwindow* GetGLFWWindow() override { return window; }

private:
    GLFWwindow* window = nullptr;
};

extern "C" NEON_EXPORT INeonPlugin* CreatePlugin() {
    return new NeonWindow();
}
