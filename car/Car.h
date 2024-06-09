//
// Created by playfulCloud on 4/25/24.
//

#ifndef SO2_CAR_H
#define SO2_CAR_H

#include <queue>
#include "../shared/SharedResources.h"

enum class CarDirection {
    Right, Left, Up, OnRaft, None
};

class Car {
private:

    const float firstRespawnX = -0.90f;
    const float firstRespawnY = 0.92f;
    float posX;
    float posY;
    float width;
    float height;
    SharedResources& resource;
    GLFWwindow* window;
    float colorR;
    float colorG;
    float colorB;
    bool right = true;
    bool up = false;
    bool enterTheField = false;
    bool colision = true;
    int counter = 0;
    bool dontMove = false;
    CarDirection direction = CarDirection::Right;
    std::queue<Car>bottomPaceCars;
    std::chrono::steady_clock::time_point collisionTime;

public:
    bool left = false;
    float normalMove;
    float move;
    bool isInQueue = false;
    Car(GLFWwindow *win);
    void drawRectangle(float x1, float y1, float width, float height, float r, float g, float b);
    bool isWaitingForLoading() const;

    void drawCar();

    float generateRandomFloat(float bottomBorder, float topBorder);

    void doLap();

    void goRight();

    void updateCarPosition();

    void goWithRaft();

    void enterRaft();

    Car(GLFWwindow *win, SharedResources &resources);

    void waitForLoading();

    bool onRaft;

    void goLeft();

    void leaveTheRaft();

    void turnUp();

    void goUp();

    void turnRight();

    void enterTheRaftWithOutWaiting();

    void dontMoveOnRaft();

    bool isCollidingWith(const Car& other);

    void handleCollision(Car& other);

    std::queue<Car> cars;

    Car(GLFWwindow *win, SharedResources &resources, std::queue<Car> cars);
};

#endif //SO2_CAR_H
