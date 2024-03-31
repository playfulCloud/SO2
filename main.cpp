#include <GLFW/glfw3.h>
#include <iostream>

int main(void) {
    GLFWwindow* window;

    // Inicjalizacja biblioteki GLFW
    if (!glfwInit()) {
        return -1;
    }

    // Utworzenie okna i jego kontekstu OpenGL
    window = glfwCreateWindow(800, 480, "Niebieski prostokąt w OpenGL", NULL, NULL);
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
        std::cout << "test" << std::endl;
        // Ustawienie koloru rysowania (niebieski)
        glColor3f(0.0f, 0.0f, 1.0f);

        // Rysowanie prostokąta
        glBegin(
                GL_QUADS);
        glVertex2f(-1.5f, -1.5f);
        glVertex2f(2.0f, -1.5f);
        glVertex2f(2.0f, 1.5f);
        glVertex2f(-1.5f, 1.5f);

        
        glVertex2f(-1.5f, -1.5f);
        glVertex2f(2.0f, -1.5f);
        glVertex2f(2.0f, 1.5f);
        glVertex2f(-1.5f, 1.5f);

        glColor3f(0.0f, 1.0f, 0.0f);
        glVertex2f(-0.75f, -0.75f);
        glVertex2f(0.75f, -0.75f);
        glVertex2f(0.75f, 0.75f);
        glVertex2f(-0.75f, 0.75f);
        glEnd();

        // Zamiana buforów i obsługa zdarzeń
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
