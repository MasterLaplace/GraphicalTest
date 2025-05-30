#include "window.h"
#include <iostream>

int main() {
    std::cout << "=== Application principale ===\n";

    if (!Window::init()) {
        std::cout << "Erreur: impossible d'initialiser la fenêtre\n";
        return -1;
    }

    Window* window = new Window(800, 600, "Mon Application");
    if (!window->getGLFWwindow()) {
        std::cout << "Erreur: impossible de créer la fenêtre\n";
        delete window;
        Window::terminate();
        return -1;
    }

    std::cout << "Fenêtre créée avec succès!\n";

    // Boucle principale simple
    int frame_count = 0;
    while (!window->shouldClose()) {
        Window::pollEvents();
        window->swapBuffers();
        frame_count++;
        std::cout << "Frame " << frame_count << std::endl;
    }

    delete window;
    Window::terminate();

    std::cout << "Application terminée proprement\n";
    return 0;
}
