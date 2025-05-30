// Inclure mock_glfw.h en mode C pour assurer la compatibilité
extern "C" {
#include "mock_glfw.h"
}

#include "window.h"
#include <iostream>
#include <cassert>

void test_window_init_success() {
    std::cout << "\n--- Test: window_init success ---\n";
    mock_reset();
    mock_set_init_return(1); // GLFW_TRUE

    bool result = Window::init();

    assert(result == true);
    assert(mock_get_init_calls() == 1);
    std::cout << "✓ Test réussi: window_init success\n";
}

void test_window_init_failure() {
    std::cout << "\n--- Test: window_init failure ---\n";
    mock_reset();
    mock_set_init_return(0); // GLFW_FALSE

    bool result = Window::init();

    assert(result == false);
    assert(mock_get_init_calls() == 1);
    std::cout << "✓ Test réussi: window_init failure\n";
}

void test_window_create_success() {
    std::cout << "\n--- Test: window_create success ---\n";
    mock_reset();

    Window* window = new Window(640, 480, "Test Window");

    assert(window != nullptr);
    assert(window->getGLFWwindow() != nullptr);
    assert(mock_get_create_window_calls() == 1);

    delete window;
    assert(mock_get_destroy_window_calls() == 1);
    std::cout << "✓ Test réussi: window_create success\n";
}

void test_window_create_failure() {
    std::cout << "\n--- Test: window_create failure ---\n";
    mock_reset();
    mock_set_create_window_fail_after(1); // Échoue au premier appel

    Window* window = new Window(640, 480, "Test Window");

    assert(window->getGLFWwindow() == nullptr);
    assert(mock_get_create_window_calls() == 1);
    delete window; // On doit quand même libérer l'objet Window
    std::cout << "✓ Test réussi: window_create failure\n";
}

void test_complete_lifecycle() {
    std::cout << "\n--- Test: complete lifecycle ---\n";
    mock_reset();
    mock_set_init_return(1);
    mock_set_window_should_close(1); // Fermeture immédiate

    // Test avec l'API orientée objet
    assert(Window::init() == true);

    Window* window = new Window(800, 600, "Test App");
    assert(window->getGLFWwindow() != nullptr);

    // Simulation de quelques frames
    int frame_count = 0;
    while (!window->shouldClose()) {
        Window::pollEvents();
        window->swapBuffers();
        frame_count++;
    }

    delete window;
    Window::terminate();

    // Vérifications des appels
    assert(mock_get_init_calls() == 1);
    assert(mock_get_create_window_calls() == 1);
    assert(mock_get_destroy_window_calls() == 1);
    assert(mock_get_terminate_calls() == 1);
    // window_should_close retourne 1, donc la boucle s'arrête immédiatement
    assert(frame_count == 0);

    std::cout << "✓ Test réussi: complete lifecycle\n";
}

int main() {
    std::cout << "=== Tests unitaires avec mocks ===\n";

    test_window_init_success();
    test_window_init_failure();
    test_window_create_success();
    test_window_create_failure();
    test_complete_lifecycle();

    std::cout << "\n🎉 Tous les tests sont passés avec succès!\n";
    return 0;
}
