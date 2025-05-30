#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>

// État global du mock
static struct {
    int init_calls;
    int terminate_calls;
    int create_window_calls;
    int destroy_window_calls;
    int poll_events_calls;
    int swap_buffers_calls;
    int window_should_close_calls;

    int init_return_value;
    int window_should_close_return_value;
    int create_window_fail_after; // Échoue après N appels (0 = jamais)
} mock_state = {
    .init_return_value = GLFW_TRUE,
    .window_should_close_return_value = GLFW_FALSE,
    .create_window_fail_after = 0
};

// Fonctions pour configurer le mock (utilisées dans les tests)
void mock_reset(void) {
    mock_state.init_calls = 0;
    mock_state.terminate_calls = 0;
    mock_state.create_window_calls = 0;
    mock_state.destroy_window_calls = 0;
    mock_state.poll_events_calls = 0;
    mock_state.swap_buffers_calls = 0;
    mock_state.window_should_close_calls = 0;
    mock_state.init_return_value = GLFW_TRUE;
    mock_state.window_should_close_return_value = GLFW_FALSE;
    mock_state.create_window_fail_after = 0;
}

void mock_set_init_return(int value) {
    mock_state.init_return_value = value;
}

void mock_set_window_should_close(int value) {
    mock_state.window_should_close_return_value = value;
}

void mock_set_create_window_fail_after(int count) {
    mock_state.create_window_fail_after = count;
}

// Getters pour les assertions dans les tests
int mock_get_init_calls(void) { return mock_state.init_calls; }
int mock_get_terminate_calls(void) { return mock_state.terminate_calls; }
int mock_get_create_window_calls(void) { return mock_state.create_window_calls; }
int mock_get_destroy_window_calls(void) { return mock_state.destroy_window_calls; }
int mock_get_poll_events_calls(void) { return mock_state.poll_events_calls; }
int mock_get_swap_buffers_calls(void) { return mock_state.swap_buffers_calls; }

// Implémentations mockées des fonctions GLFW
// Ces fonctions remplaceront les vraies fonctions GLFW grâce à l'ordre de linkage
int glfwInit(void) {
    mock_state.init_calls++;
    printf("[MOCK] glfwInit() appelé (appel #%d)\n", mock_state.init_calls);
    return mock_state.init_return_value;
}

void glfwTerminate(void) {
    mock_state.terminate_calls++;
    printf("[MOCK] glfwTerminate() appelé (appel #%d)\n", mock_state.terminate_calls);
}

GLFWwindow* glfwCreateWindow(int width, int height, const char* title, GLFWmonitor* monitor, GLFWwindow* share) {
    mock_state.create_window_calls++;
    printf("[MOCK] glfwCreateWindow(%d, %d, \"%s\") appelé (appel #%d)\n",
           width, height, title, mock_state.create_window_calls);

    // Simuler un échec après un certain nombre d'appels
    if (mock_state.create_window_fail_after > 0 &&
        mock_state.create_window_calls >= mock_state.create_window_fail_after) {
        printf("[MOCK] glfwCreateWindow échoue (simulé)\n");
        return NULL;
    }

    // Retourner un pointeur factice non-NULL
    return (GLFWwindow*)0xDEADBEEF;
}

void glfwDestroyWindow(GLFWwindow* window) {
    mock_state.destroy_window_calls++;
    printf("[MOCK] glfwDestroyWindow(%p) appelé (appel #%d)\n",
           window, mock_state.destroy_window_calls);
}

void glfwPollEvents(void) {
    mock_state.poll_events_calls++;
    printf("[MOCK] glfwPollEvents() appelé (appel #%d)\n", mock_state.poll_events_calls);
}

void glfwSwapBuffers(GLFWwindow* window) {
    mock_state.swap_buffers_calls++;
    printf("[MOCK] glfwSwapBuffers(%p) appelé (appel #%d)\n",
           window, mock_state.swap_buffers_calls);
}

int glfwWindowShouldClose(GLFWwindow* window) {
    mock_state.window_should_close_calls++;
    printf("[MOCK] glfwWindowShouldClose(%p) appelé (appel #%d) -> %d\n",
           window, mock_state.window_should_close_calls, mock_state.window_should_close_return_value);
    return mock_state.window_should_close_return_value;
}
void glfwSetWindowShouldClose(GLFWwindow* window, int value) {
    mock_state.window_should_close_return_value = value;
    printf("[MOCK] glfwSetWindowShouldClose(%p, %d) appelé\n", window, value);
}
