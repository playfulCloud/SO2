//
// Created by playfulCloud on 4/25/24.
//

#include "Board.h"

void Board::clearScreen() {
    glClear(GL_COLOR_BUFFER_BIT);
}

void Board::drawBoard(){
    this->clearScreen();

    this->drawRectangle(-1.0f, -1.0f, 1.0f, 1.0f, 0.6f, 0.3f, 0.0f);
    this->drawRectangle(-0.75f, -0.65f, 0.65f, 0.65f, 0.0f, 1.0f, 0.0f);
    this->drawRectangle(0.65f, -1.0f, 1.0f, 1.0f,0.0f, 0.0f, 1.0f);

    this->display();
    this->processInput();

}

void Board::drawRectangle(float x1, float y1, float x2, float y2, float r, float g, float b) {
    glColor3f(r, g, b);
    glBegin(GL_QUADS);
    glVertex2f(x1, y1);
    glVertex2f(x2, y1);
    glVertex2f(x2, y2);
    glVertex2f(x1, y2);
    glEnd();
}

void Board::display() {
    glfwSwapBuffers(this->window);
}

void Board::processInput() {
    glfwPollEvents();
}


Board::Board(GLFWwindow *win) {
    this->window = win;
}
