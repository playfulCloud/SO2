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
    std::condition_variable carsCanUnload;
    bool loadingCars = false;
    bool raftSwim = false;
    bool unloadingCars = false;
};
#endif //SO2_SHAREDRESOURCES_H
