#ifndef WINDOW_H
#define WINDOW_H

// Déclaration anticipée pour éviter d'inclure GLFW/glfw3.h dans le header
struct GLFWwindow;

class Window {
public:
    // Méthodes statiques (anciennement fonctions globales)
    static bool init();
    static void terminate();

    // Constructeur/destructeur
    Window(int width, int height, const char* title);
    ~Window();

    // Méthodes d'instance
    bool shouldClose() const;
    void swapBuffers() const;
    static void pollEvents();

    // Getter pour le pointeur GLFWwindow (nécessaire pour les tests)
    GLFWwindow* getGLFWwindow() const { return m_glfwWindow; }

    // Empêcher la copie
    Window(const Window&) = delete;
    Window& operator=(const Window&) = delete;

private:
    int m_width;
    int m_height;
    const char* m_title;
    GLFWwindow* m_glfwWindow;
};

// Fonctions de compatibilité pour garder les tests C fonctionnels
// Ces fonctions agiront comme une couche d'adaptation
extern "C" {
    int window_init(void);
    void window_terminate(void);
    Window* window_create(int width, int height, const char* title);
    void window_destroy(Window* window);
    int window_should_close(Window* window);
    void window_swap_buffers(Window* window);
    void window_poll_events(void);
}

#endif