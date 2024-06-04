//
// Created by playfulCloud on 4/25/24.
//

#ifndef SO2_CAR_H
#define SO2_CAR_H

#include "../shared/SharedResources.h"

enum class CarDirection {
    Right, Left, Up, OnRaft, None
};

class Car {
private:
    const float firstRespawnX = -0.90f;
    const float firstRespawnY = 0.92f;
    const float noSpeeding = 0.01f;
    float normalMove;
    float move;
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
    bool left = false;
    bool up = false;
    bool enterTheField = false;
    int counter = 0;
    bool dontMove = false;
    CarDirection direction = CarDirection::Right;
    std::vector<Car>car;
public:
    Car(GLFWwindow *win);
    void drawRectangle(float x1, float y1, float width, float height, float r, float g, float b);

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
};

#endif //SO2_CAR_H
