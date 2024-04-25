#include <GLFW/glfw3.h>
#include <iostream>
#include <thread>
#include "board/Board.h"
#include "raft/Raft.h"
#include "car/Car.h"

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
    SharedResources sharedResources;
    auto *board = new Board(window);
    auto *raft = new Raft(window,sharedResources);
    auto *car = new Car(window,sharedResources);
    glfwMakeContextCurrent(window);

    std::thread raftThread(&Raft::updateRaftPosition, raft);
    std::thread carThread(&Car::updateCarPosition, car);


    while (!glfwWindowShouldClose(window)) {
        board->clearScreen();

        board->drawBoard();
        raft->drawRaft();
        car->drawCar();


        board->display();
        board->processInput();
    }

    glfwTerminate();
    return 0;
}
