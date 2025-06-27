//
// Created by danciu-valentin-nicolae on 16.05.2025.
//

#include "AIConnectionPool.h"

#include <iostream>

#include "AI.h"
bool AIConnectionPool::useAIErrors = false;

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

void AIConnectionPool::switchAIErrors() {

    std::cout << "\n";
    std::cout << "Doresti sa activezi erorile AI?\n";
    std::cout << "Daca ai o conexiune de internet slaba sau nu ai configurat Ollama bine jocul va da crash (vezi tutorial in README).\n";
    std::cout << "(1 - da, 0 - nu): ";
    std::cin >> useAIErrors;
    std::cout << "\n";
}

bool AIConnectionPool::getuseAIErrors() {
    return useAIErrors;
}