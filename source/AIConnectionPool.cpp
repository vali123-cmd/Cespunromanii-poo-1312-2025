//
// Created by danciu-valentin-nicolae on 16.05.2025.
//

#include "AIConnectionPool.h"

#include "AI.h"

AI* AIConnectionPool::getConnection() {
   for (auto& conn: connections) {
       if (!conn->isActive()) {
           conn->connect();
           return conn.get();
       }

   }
    auto newConn = std::make_unique<AI>();
    newConn->connect();
    AI* rawPtr = newConn.get();
    connections.push_back(std::move(newConn));
    return rawPtr;
}

void AIConnectionPool::releaseConnection(AI* conn) {
    conn->disconnect();
}