#include <GLFW/glfw3.h>

int main(void) {
    GLFWwindow* window;

    // Inicjalizacja biblioteki GLFW
    if (!glfwInit()) {
        return -1;
    }

    // Utworzenie okna i jego kontekstu OpenGL
    window = glfwCreateWindow(640, 480, "Niebieski prostokąt w OpenGL", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    // Ustawienie kontekstu okna jako bieżącego
    glfwMakeContextCurrent(window);

    // Główna pętla programu
    while (!glfwWindowShouldClose(window)) {
        // Czyszczenie zawartości okna
        glClear(GL_COLOR_BUFFER_BIT);

        // Ustawienie koloru rysowania (niebieski)
        glColor3f(0.0f, 0.0f, 1.0f);

        // Rysowanie prostokąta
        glBegin(GL_QUADS);
        glVertex2f(-0.5f, -0.5f);
        glVertex2f(0.5f, -0.5f);
        glVertex2f(0.5f, 0.5f);
        glVertex2f(-0.5f, 0.5f);
        glEnd();

        // Zamiana buforów i obsługa zdarzeń
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
