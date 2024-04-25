//
// Created by playfulCloud on 4/25/24.
//

#ifndef SO2_BOARD_H
#define SO2_BOARD_H


#include <GLFW/glfw3.h>

class Board {
private:
    GLFWwindow* window;
public:
    Board(GLFWwindow* win);
    void clearScreen();
    void drawRectangle(float x1, float y1, float x2, float y2, float r, float g, float b);
    void display();
    void processInput();

    void drawBoard();
};


#endif //SO2_BOARD_H
