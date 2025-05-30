#ifndef MOCK_GLFW_H
#define MOCK_GLFW_H

// Fonctions pour configurer le comportement du mock
void mock_reset(void);
void mock_set_init_return(int value);
void mock_set_window_should_close(int value);
void mock_set_create_window_fail_after(int count);

// Fonctions pour vérifier les appels dans les tests
int mock_get_init_calls(void);
int mock_get_terminate_calls(void);
int mock_get_create_window_calls(void);
int mock_get_destroy_window_calls(void);
int mock_get_poll_events_calls(void);
int mock_get_swap_buffers_calls(void);

#endif
