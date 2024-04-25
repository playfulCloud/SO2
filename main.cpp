#include <GLFW/glfw3.h>
#include <iostream>
#include <thread>
#include "board/Board.h"
#include "raft/Raft.h"

int main(void) {
    GLFWwindow *window;

    // Inicjalizacja biblioteki GLFW
    if (!glfwInit()) {
        return -1;
    }

    window = glfwCreateWindow(800, 480, "Niebieski prostokąt w OpenGL", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }
    auto *board = new Board(window);
    auto *raft = new Raft(window);
    glfwMakeContextCurrent(window);

    std::thread raftThread(&Raft::updateRaftPosition, raft);


    while (!glfwWindowShouldClose(window)) {
        board->clearScreen();

        board->drawBoard();
        raft->drawRaft();

        board->display();
        board->processInput();
    }

    glfwTerminate();
    return 0;
}
