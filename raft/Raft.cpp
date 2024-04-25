#include <GLFW/glfw3.h>
#include <thread>
#include <mutex>
#include <iostream>
#include "Raft.h"


std::mutex raftMutex;

Raft::Raft(GLFWwindow *win, SharedResources& sharedResources) : window(win), sharedResource(sharedResources){
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


void Raft::updateRaftPosition() {
    while (true) {
        std::this_thread::sleep_for(std::chrono::milliseconds(50)); // Opóźnienie dla symulacji animacji
        std::lock_guard<std::mutex> lock(raftMutex);

        if (leftBottomCorner <= bottomY) {
            sharedResource.loadingCars = true;
            leftBottomCorner = standardLeftCorner;
            rightUpperCorner = standardRightCorner;
            setLoading();
        }
        if (!sharedResource.loadingCars) {
            leftBottomCorner -= move;
            rightUpperCorner -= move;
        }
    }
}


void Raft::drawRaft() {
    float localRightUpperPos;
    float localLeftBottomPos;

    {
        std::lock_guard<std::mutex> lock(raftMutex);
        localLeftBottomPos = leftBottomCorner;
        localRightUpperPos = rightUpperCorner;
    }

    this->drawRectangle(0.65f, localLeftBottomPos, 1.0f, localRightUpperPos, 0.6f, 0.3f, 0.0f);
}

void Raft::setLoading() {
    sharedResource.raftSwim = false;
    std::thread([this]() {
        sharedResource.carsCanLoad.notify_all();
        std::this_thread::sleep_for(std::chrono::seconds(2));
        {
            std::lock_guard<std::mutex> lock(raftMutex);
            sharedResource.loadingCars = false;
            sharedResource.raftSwim = true;
        }

    }).detach();
}
