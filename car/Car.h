//
// Created by playfulCloud on 4/25/24.
//

#ifndef SO2_CAR_H
#define SO2_CAR_H


class Car {
private:
    const float firstRespawnX = 1.0f;
    const float firstRespawnY = 1.0f;
    const float secondRespawnX = 1.0f;
    const float secondRespawnY = 1.0f;
    const float thirdRespawnX = 1.0f;
    const float thirdRespawnY = 1.0f;
    GLFWwindow* window;
    float firstColor;
    float secondColor;
    float thirdColor;
public:
    Car(GLFWwindow *win);
    void drawTriangle(float x1, float y1, float x2, float y2, float x3, float y3, float r, float g, float b);

    void drawCar();
};


#endif //SO2_CAR_H
