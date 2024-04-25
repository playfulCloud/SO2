//
// Created by playfulCloud on 4/25/24.
//

#ifndef SO2_CAR_H
#define SO2_CAR_H


#include "../shared/SharedResources.h"

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
};


#endif //SO2_CAR_H
