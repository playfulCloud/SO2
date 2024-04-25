//
// Created by playfulCloud on 4/25/24.
//

#ifndef SO2_SHAREDRESOURCES_H
#define SO2_SHAREDRESOURCES_H

#include <mutex>
#include <condition_variable>

struct SharedResources {
    std::mutex raftMutex;
    std::condition_variable carsCanLoad;
    bool loadingCars = false;
};
#endif //SO2_SHAREDRESOURCES_H
