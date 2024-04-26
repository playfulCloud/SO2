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
    const float secondRespawnX = -0.95f;
    const float secondRespawnY = 0.95f;
    const float thirdRespawnX = -0.95f;
    const float thirdRespawnY = 0.90f;
    float move;
    float firstX;
    float firstY;
    float secondX;
    float secondY;
    float thirdX;
    float thirdY;
    SharedResources& resource;
    GLFWwindow* window;
    float firstColor;
    float secondColor;
    float thirdColor;
    bool right = true;
    bool left=false;
    bool up = false;
    bool enterTheField = false;
    int counter = 0;
    bool dontMove = false;
    CarDirection direction = CarDirection::Right;
public:
    Car(GLFWwindow *win);
    void drawTriangle(float x1, float y1, float x2, float y2, float x3, float y3, float r, float g, float b);

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

    void rearrangeVertices();
};


#endif //SO2_CAR_H
