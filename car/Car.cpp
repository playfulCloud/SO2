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

Car::Car(GLFWwindow *win, SharedResources& resources) : window(win), resource(resources){
    this->firstColor = generateRandomFloat(0.0f,1.0f);
   this->secondColor = generateRandomFloat(0.0f,1.0f);
   this->thirdColor = generateRandomFloat(0.0f,1.0f);
   this->move = generateRandomFloat(0.02f, 0.04);
   this->firstX = firstRespawnX;
   this->firstY = firstRespawnY;
   this->secondX = secondRespawnX;
    this->secondY = secondRespawnY;
    this->thirdX = thirdRespawnX;
    this->thirdY = thirdRespawnY;
    this->onRaft = false;
}

std::mutex carMutex;


void Car::drawTriangle(float x1, float y1, float x2, float y2, float x3, float y3, float r, float g, float b) {
    glColor3f(r, g, b);
    glBegin(GL_TRIANGLES);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glVertex2f(x3, y3);
    glEnd();
}


void Car::goRight(){
    firstX += move;
    secondX += move;
    thirdX += move;
}

void Car::goWithRaft(){
    firstY -= 0.01f;
    secondY -= 0.01f;
    thirdY -= 0.01f;
}

void Car::goUp(){
    firstY += move;
    secondY += move;
    thirdY += move;
}

void Car::goLeft(){
    firstX -= move;
    secondX -= move;
    thirdX -= move;
}

void Car::enterRaft() {
    firstX += 0.10f;
    secondX += 0.10f;
    thirdX += 0.10f;
}

void Car::updateCarPosition() {
    while (counter != 4) {
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        if (firstX >= 0.62f && !resource.loadingCars && !onRaft) {
            waitForLoading();
            right = false;
        }else if(onRaft && resource.raftSwim){
           goWithRaft();
            if(firstY <= -0.65f){
                leaveTheRaft();
            }
        }else if(this->right){
            goRight();
            if(firstX >= 0.60f && resource.loadingCars){
                enterRaft();
                enterTheRaftWithOutWaiting();
            }
        }else if(this->left && enterTheField){
            goLeft();
            if(firstX <= -0.82){
                turnUp();
            }
        }else if(this->up){
            goUp();
            if(firstY >= 0.70f){
                turnRight();
            }
        }else if(this->dontMove){

        }
    }
}


void Car::drawCar(){
    float localFirstX;
    float localFirstY;
    float localSecondX;
    float localSecondY;
    float localThirdX;
    float localThirdY;

    {
        std::lock_guard<std::mutex> lock(carMutex);
        localFirstX = firstX;
        localFirstY = firstY;
        localSecondX = secondX;
        localSecondY = secondY;
        localThirdX = thirdX;
        localThirdY = thirdY;
    }


    this->drawTriangle(localFirstX,localFirstY,localSecondX,localSecondY,localThirdX,localThirdY,firstColor,secondColor,thirdColor);
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

void Car::leaveTheRaft(){
   firstX = 0.60f;
   firstY = -0.77f;
   secondX = 0.65f;
   secondY = -0.80f;
   thirdX = 0.65f;
   thirdY = -0.75f;
   this->enterTheField = true;
   this->left = true;
   this->onRaft = false;
}

void Car::turnUp(){
    this->left = false;
    this->up = true;
}

void Car::turnRight(){
   this->right = true;
   this->up = false;
   counter +=1;
   rearrangeVertices();
}

void Car::enterTheRaftWithOutWaiting(){
    this->right = false;
    onRaft = true;
}

void Car::dontMoveOnRaft(){
}

void Car::rearrangeVertices() {
    float tempX = firstX, tempY = firstY;
    firstX = secondX;
    secondX = tempX;
    firstY = secondY;
    secondY = tempY;
}