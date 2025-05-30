#include "window.h"
#include "mock_glfw.h"
#include <stdio.h>
#include <assert.h>

void test_window_init_success(void) {
    printf("\n--- Test: window_init success ---\n");
    mock_reset();
    mock_set_init_return(1); // GLFW_TRUE

    int result = window_init();

    assert(result == 1);
    assert(mock_get_init_calls() == 1);
    printf("✓ Test réussi: window_init success\n");
}

void test_window_init_failure(void) {
    printf("\n--- Test: window_init failure ---\n");
    mock_reset();
    mock_set_init_return(0); // GLFW_FALSE

    int result = window_init();

    assert(result == 0);
    assert(mock_get_init_calls() == 1);
    printf("✓ Test réussi: window_init failure\n");
}

void test_window_create_success(void) {
    printf("\n--- Test: window_create success ---\n");
    mock_reset();

    Window* window = window_create(640, 480, "Test Window");

    assert(window != NULL);
    assert(mock_get_create_window_calls() == 1);

    window_destroy(window);
    assert(mock_get_destroy_window_calls() == 1);
    printf("✓ Test réussi: window_create success\n");
}

void test_window_create_failure(void) {
    printf("\n--- Test: window_create failure ---\n");
    mock_reset();
    mock_set_create_window_fail_after(1); // Échoue au premier appel

    Window* window = window_create(640, 480, "Test Window");

    assert(window == NULL);
    assert(mock_get_create_window_calls() == 1);
    printf("✓ Test réussi: window_create failure\n");
}

void test_complete_lifecycle(void) {
    printf("\n--- Test: complete lifecycle ---\n");
    mock_reset();
    mock_set_init_return(1);
    mock_set_window_should_close(1); // Fermeture immédiate

    // Même code que dans app.c mais avec vérifications
    assert(window_init() == 1);

    Window* window = window_create(800, 600, "Test App");
    assert(window != NULL);

    // Simulation de quelques frames
    int frame_count = 0;
    while (!window_should_close(window) && frame_count < 3) {
        window_poll_events();
        window_swap_buffers(window);
        frame_count++;
    }

    window_destroy(window);
    window_terminate();

    // Vérifications des appels
    assert(mock_get_init_calls() == 1);
    assert(mock_get_create_window_calls() == 1);
    assert(mock_get_destroy_window_calls() == 1);
    assert(mock_get_terminate_calls() == 1);
    // window_should_close retourne 1, donc la boucle s'arrête immédiatement
    assert(frame_count == 0);

    printf("✓ Test réussi: complete lifecycle\n");
}

int main(void) {
    printf("=== Tests unitaires avec mocks ===\n");

    test_window_init_success();
    test_window_init_failure();
    test_window_create_success();
    test_window_create_failure();
    test_complete_lifecycle();

    printf("\n🎉 Tous les tests sont passés avec succès!\n");
    return 0;
}
