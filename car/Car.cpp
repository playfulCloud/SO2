//
// Created by playfulCloud on 4/25/24.
//

#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <random>
#include <thread>
#include <mutex>
#include <iostream>
#include <algorithm>
#include "Car.h"

Car::Car(GLFWwindow *win, SharedResources& resources) : window(win), resource(resources) {
    this->colorR = generateRandomFloat(0.0f, 1.0f);
    this->colorG = generateRandomFloat(0.0f, 1.0f);
    this->colorB = generateRandomFloat(0.0f, 1.0f);
    this->move = generateRandomFloat(0.02f, 0.04f);
    this->posX = firstRespawnX;
    this->posY = firstRespawnY;
    this->width = 0.1f;  // Adjust width as necessary
    this->height = 0.05f; // Adjust height as necessary
    this->onRaft = false;
    this->normalMove = move;
}

std::mutex carMutex;

void Car::drawRectangle(float x1, float y1, float width, float height, float r, float g, float b) {
    glColor3f(r, g, b);
    glBegin(GL_QUADS);
    glVertex2f(x1, y1);
    glVertex2f(x1 + width, y1);
    glVertex2f(x1 + width, y1 - height);
    glVertex2f(x1, y1 - height);
    glEnd();
}

void Car::goRight() {
    posX += move;
    direction = CarDirection::Right;
}

void Car::goWithRaft() {
    posY -= 0.01f;
    direction = CarDirection::OnRaft;
}

void Car::goUp() {
    posY += move;
    direction = CarDirection::Up;
}

void Car::goLeft() {
    posX -= move;
    direction = CarDirection::Left;
}

void Car::enterRaft() {
    posX += 0.20f;
    direction = CarDirection::OnRaft;
}

void Car::updateCarPosition() {
    while (counter != 4) {
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        if (posX >= 0.58f && !resource.loadingCars && !onRaft) {
            waitForLoading();
            right = false;
        } else if (onRaft && resource.raftSwim) {
            goWithRaft();
            if (posY <= -0.65f) {
                leaveTheRaft();
            }
        } else if (this->right) {
            goRight();
            if (posX >= 0.60f && resource.loadingCars) {
                enterRaft();
                enterTheRaftWithOutWaiting();
            }
        } else if (this->left && enterTheField) {
            goLeft();
            this->move = noSpeeding;
            if (posX <= -0.82f) {
                turnUp();
            }
        } else if (this->up) {
            goUp();
            this->move = normalMove;
            if (posY >= 0.70f) {
                turnRight();
            }
        } else if (this->dontMove) {
            // Do nothing
        }
    }
}

void Car::drawCar() {
    float localPosX;
    float localPosY;

    {
        std::lock_guard<std::mutex> lock(carMutex);
        localPosX = posX;
        localPosY = posY;
    }

    glPushMatrix();
    glTranslatef(localPosX, localPosY, 0.0f);

    switch (direction) {
        case CarDirection::Right:
            glRotatef(0.0f, 0.0f, 0.0f, 1.0f);
            break;
        case CarDirection::Left:
            glRotatef(180.0f, 0.0f, 0.0f, 1.0f);
            break;
        case CarDirection::Up:
            glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
            break;
        case CarDirection::OnRaft:
            // No rotation needed
            break;
        default:
            break;
    }

    this->drawRectangle(-width / 2, height / 2, width, height, colorR, colorG, colorB);

    glPopMatrix();
}

float Car::generateRandomFloat(float bottomBorder, float topBorder) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dis(bottomBorder, topBorder);
    return dis(gen);
}

void Car::waitForLoading() {
    std::unique_lock<std::mutex> lock(resource.raftMutex);
    resource.carsCanLoad.wait(lock, [this]{ return resource.loadingCars; });

    enterRaft();
    onRaft = true;
}

void Car::leaveTheRaft() {
    posX = 0.55f;
    posY = -0.77f;
    this->enterTheField = true;
    this->left = true;
    this->onRaft = false;
}

void Car::turnUp() {
    this->left = false;
    this->up = true;
}

void Car::turnRight() {
    this->right = true;
    this->up = false;
    counter += 1;
}

void Car::enterTheRaftWithOutWaiting() {
    this->right = false;
    onRaft = true;
}

void Car::dontMoveOnRaft() {
    // Do nothing
}
