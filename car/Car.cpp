//
// Created by playfulCloud on 4/25/24.
//

#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include "Car.h"

Car::Car(GLFWwindow *win) {
    this->window = win;

}


void Car::drawTriangle(float x1, float y1, float x2, float y2, float x3, float y3, float r, float g, float b) {
    glColor3f(r, g, b); // Ustaw kolor trójkąta
    glBegin(GL_TRIANGLES); // Rozpocznij rysowanie trójkątów
    glVertex2f(x1, y1); // Wierzchołek 1
    glVertex2f(x2, y2); // Wierzchołek 2
    glVertex2f(x3, y3); // Wierzchołek 3
    glEnd(); // Zakończ rysowanie trójkątów
}




//void Car::drawCar(){
//    drawTriangle(`)
//}

