//
// Created by playfulCloud on 4/25/24.
//

#include <GLFW/glfw3.h>
#include <thread>
#include <mutex>
#include <iostream>
#include "Raft.h"


std::mutex mutex;

Raft::Raft(GLFWwindow *win) {
    this->window = win;
}

void Raft::drawRectangle(float x1, float y1, float x2, float y2, float r, float g, float b) {
    glColor3f(r, g, b);
    glBegin(GL_QUADS);
    glVertex2f(x1, y1);
    glVertex2f(x2, y1);
    glVertex2f(x2, y2);
    glVertex2f(x1, y2);
    glEnd();
}






void Raft::moveRaftUpAndDown(){

   while(true) {
        rightUpperCorner -= move;
        leftBottomCorner -= move;
        this->drawRectangle(0.65f, leftBottomCorner,1.0f,rightUpperCorner,0.6f, 0.3f, 0.0f);
        if(leftBottomCorner == bottomY){
           rightUpperCorner  = standardRightCorner;
           leftBottomCorner = standardLeftCorner;
        }
   }
}

void Raft::updateRaftPosition() {
    while (true) { // 'running' to zmienna kontrolująca, kiedy wątek powinien zakończyć działanie
        std::this_thread::sleep_for(std::chrono::milliseconds(50)); // Opóźnienie dla symulacji animacji

        std::lock_guard<std::mutex> lock(mutex);

        std::cout << leftBottomCorner;
        if(leftBottomCorner <= bottomY){
            leftBottomCorner = standardLeftCorner;
            rightUpperCorner = standardRightCorner;
        }
        leftBottomCorner -= move;
        rightUpperCorner -= move;
    }
}


void Raft::drawRaft() {
    float localRightUpperPos;
    float localLeftBottomPos;

    // Skopiuj stan do lokalnej zmiennej podczas blokowania mutexu
    {
        std::lock_guard<std::mutex> lock(mutex);
        localLeftBottomPos = leftBottomCorner;
        localRightUpperPos = rightUpperCorner;

    }

    // Użyj localPosition do rysowania
//    drawRectangle(0.65f, localPosition, 1.0f, localPosition + height, 0.6f, 0.3f, 0.0f);
    this->drawRectangle(0.65f, localLeftBottomPos,1.0f,localRightUpperPos,0.6f, 0.3f, 0.0f);

}












