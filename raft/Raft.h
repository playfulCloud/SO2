//
// Created by playfulCloud on 4/25/24.
//

#ifndef SO2_RAFT_H
#define SO2_RAFT_H


#include "../shared/SharedResources.h"

class Raft {

private:

    GLFWwindow* window;
    const float move = 0.01f;
    const float bottomY = -1.0f;
    const float standardRightCorner = 1.0f;
    const float standardLeftCorner = 0.65;
    float rightUpperCorner = standardRightCorner;
    float leftBottomCorner =standardLeftCorner;
    SharedResources& sharedResource;
public:
    Raft(GLFWwindow *win);
    void drawRectangle(float x1, float y1, float x2, float y2, float r, float g, float b);
    void drawRaft();
    void updateRaftPosition();
    void setLoading();

    Raft(GLFWwindow *win, SharedResources &sharedResources);

    void setUnLoading();

    void SwimTheRaft();
};


#endif //SO2_RAFT_H
