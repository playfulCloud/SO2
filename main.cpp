#include <GLFW/glfw3.h>
#include <iostream>
#include <thread>
#include <random>
#include <vector>
#include <atomic>
#include "board/Board.h"
#include "raft/Raft.h"
#include "car/Car.h"

std::atomic<bool> shutdownThreads(false);  // Flag to signal all threads to stop

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
        shutdownThreads = true;  // Set the shutdown flag when space is pressed
    }
}

void manageCarThreads(std::vector<std::thread>& carThreads, std::vector<Car*>& cars, GLFWwindow* window, SharedResources& sharedResources) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 10000);

    while (!glfwWindowShouldClose(window) && !shutdownThreads) {
        if (dis(gen) < 500 && cars.size() < 4) {
            Car* newCar = new Car(window, sharedResources);
            cars.push_back(newCar);
            carThreads.emplace_back(&Car::updateCarPosition, newCar);
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Avoid high CPU usage
    }
}

int main(void) {
    GLFWwindow* window;

    if (!glfwInit()) {
        return -1;
    }

    window = glfwCreateWindow(800, 480, "Niebieski prostokąt w OpenGL", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwSetKeyCallback(window, keyCallback);  // Set the keyboard callback

    SharedResources sharedResources;
    Board board(window);
    Raft raft(window, sharedResources);
    std::vector<std::thread> carThreads;
    std::vector<Car*> cars;

    glfwMakeContextCurrent(window);

    std::thread raftThread(&Raft::updateRaftPosition, &raft);
    std::thread manageCarsThread(manageCarThreads, std::ref(carThreads), std::ref(cars), window, std::ref(sharedResources));

    while (!glfwWindowShouldClose(window)) {
        if (shutdownThreads) break;  // Exit loop if shutdown is triggered

        board.clearScreen();

        board.drawBoard();
        raft.drawRaft();
        for (auto car : cars) {
            car->drawCar();
        }

        board.display();
        board.processInput();
    }

    manageCarsThread.join();
    raftThread.join();
    for (auto& carThread : carThreads) {
        if (carThread.joinable()) {
            carThread.join();
        }
    }
    for (auto car : cars) {
        delete car;
    }

    glfwTerminate();
    return 0;
}
