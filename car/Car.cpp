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


#include <cmath>

std::mutex carMutex;
bool Car::redZoneOccupied = false;
std::mutex Car::redZoneMutex;
std::condition_variable Car::redZoneCond;

// Sprawdzanie kolizji z innym samochodem
bool Car::isCollidingWith(const Car& other) {
    std::lock_guard<std::mutex> lock(carMutex);
    return std::abs(this->posX - other.posX) < this->width && std::abs(this->posY - other.posY) < this->height;
}

void Car::enterRedZone() {
    std::cout << "tak" << std::endl;
    move = normalMove;
    waitingForRedZone = false;
    std::unique_lock<std::mutex> lock(redZoneMutex);
    redZoneCond.wait(lock, [] { return !redZoneOccupied; });
    redZoneOccupied = true;
}

void Car::leaveRedZone() {
    std::cout << "leave" << std::endl;
    std::lock_guard<std::mutex> lock(redZoneMutex);
    waitingForRedZone = true;
    redZoneOccupied = false;
    redZoneCond.notify_one();
}
void Car::goUp() {
    direction = CarDirection::Up;
    if(posY >= -0.35f && !redZoneOccupied){
        enterRedZone();
    }else if(posY >= -0.35f && redZoneOccupied && waitingForRedZone){
        move = 0;
    }
    if(posY >= 0.25f && !waitingForRedZone){
        leaveRedZone();
    }

    posY += move;
}

// Obsługa kolizji z innym samochodem
void Car::handleCollision(Car& other) {
    if (this->isCollidingWith(other)) {
        // Samochód, który uderza, zmniejsza prędkość na chwilę
        this->move = 0.005f;
        this->collisionTime = std::chrono::steady_clock::now();
        this->posY += 0.01f;
        other.posY -= 0.01f;
        // Uderzony samochód przyspiesza
        other.move += 0.001f;

        std::cout << "Kolizja" << std::endl;
    }
}
Car::Car(GLFWwindow *win, SharedResources& resources) : window(win), resource(resources){
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

bool Car::isWaitingForLoading() const {
    return colision;
}

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
    colision = true;
    if (std::chrono::steady_clock::now() - collisionTime > std::chrono::seconds(1)) {
        move = normalMove;
    }
    posX += move;
    direction = CarDirection::Right;
}

void Car::goWithRaft() {
    posY -= 0.01f;
    direction = CarDirection::OnRaft;
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
        if(posX > 0.40f){
            this->colision = false;
        }

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
            if (posX <= -0.82f) {
                turnUp();
            }
        } else if (this->up) {
            goUp();
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
