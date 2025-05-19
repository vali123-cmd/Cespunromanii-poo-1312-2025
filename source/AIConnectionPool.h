//
// Created by danciu-valentin-nicolae on 16.05.2025.
//

#ifndef AICONNECTIONPOOL_H
#define AICONNECTIONPOOL_H
#include <memory>
#include <vector>


class AI;

class AIConnectionPool {
    std::vector<std::unique_ptr<AI>> connections;
public:
    AI* getConnection();

    void releaseConnection(AI* conn);

};



#endif //AICONNECTIONPOOL_H
