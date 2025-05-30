#include "window.h"
#include <stdio.h>

int main(void) {
    printf("=== Application principale ===\n");

    if (!window_init()) {
        printf("Erreur: impossible d'initialiser la fenêtre\n");
        return -1;
    }

    Window* window = window_create(800, 600, "Mon Application");
    if (!window) {
        printf("Erreur: impossible de créer la fenêtre\n");
        window_terminate();
        return -1;
    }

    printf("Fenêtre créée avec succès!\n");

    // Boucle principale simple
    int frame_count = 0;
    while (!window_should_close(window)) {
        window_poll_events();
        window_swap_buffers(window);
        frame_count++;
        printf("Frame %d\n", frame_count);
    }

    window_destroy(window);
    window_terminate();

    printf("Application terminée proprement\n");
    return 0;
}
