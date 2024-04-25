//
// Created by playfulCloud on 4/25/24.
//

#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <random>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <iostream>
#include "Car.h"

Car::Car(GLFWwindow *win, SharedResources& resources) : window(win), resource(resources){
    this->firstColor = generateRandomFloat(0.0f,1.0f);
   this->secondColor = generateRandomFloat(0.0f,1.0f);
   this->thirdColor = generateRandomFloat(0.0f,1.0f);
   this->move = generateRandomFloat(0.0f, 0.03);
   this->firstX = firstRespawnX;
   this->firstY = firstRespawnY;
   this->secondX = secondRespawnX;
    this->secondY = secondRespawnY;
    this->thirdX = thirdRespawnX;
    this->thirdY = thirdRespawnY;
}

std::mutex carMutex;


void Car::drawTriangle(float x1, float y1, float x2, float y2, float x3, float y3, float r, float g, float b) {
    glColor3f(r, g, b); // Ustaw kolor trójkąta
    glBegin(GL_TRIANGLES); // Rozpocznij rysowanie trójkątów
    glVertex2f(x1, y1); // Wierzchołek 1
    glVertex2f(x2, y2); // Wierzchołek 2
    glVertex2f(x3, y3); // Wierzchołek 3
    glEnd(); // Zakończ rysowanie trójkątów
}

void Car::doLap(){

}

void Car::goRight(){
    firstX += move;
    secondX += move;
    thirdX += move;
}

void Car::goWithRaft(){
    firstY += 0.01f;
    secondY += 0.01f;
    thirdY += 0.01f;
}

//
//void Car::enterRaft() {
//    std::unique_lock<std::mutex> lock(raftMutex);
//    carsCanLoad.wait(lock, [this]{ return loadingCars; }); // Czekaj aż tratwa będzie gotowa
//    // Logika załadunku samochodu na tratwę
//}

void Car::updateCarPosition() {
    while (true) {
        std::this_thread::sleep_for(std::chrono::milliseconds(50)); // Opóźnienie dla symulacji animacji
        std::lock_guard<std::mutex> lock(carMutex);

        if(firstX >= 0.65f){
            waitForLoading();
        }

        goRight();

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

    return dis(gen); // Wygeneruj losowy float.
}

void Car::waitForLoading() {
    std::cout << "Car can now load onto the raft." << std::endl;
    std::unique_lock<std::mutex> lock(resource.raftMutex);
    resource.carsCanLoad.wait(lock, [this]{ return resource.loadingCars; });

    // Po przebudzeniu, możesz kontynuować z logiką załadunku samochodu
    // ... tutaj realizacja logiki załadunku
}
