#include <assert.h>
#include <stdio.h>
#include "window.h"

int main(void)
{
    assert(window_init() == 0);
    puts("✅ window_init() a bien échoué en mock");

    GLFWwindow* win = window_create(640, 480, "Test");
    assert(win == NULL);
    puts("✅ window_create() a bien retourné NULL en mock");

    assert(window_main_loop(win) == 0);
    puts("✅ window_main_loop() a bien échoué avec win=NULL");

    return 0;
}
