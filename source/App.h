//
// Created by danciu-valentin-nicolae on 16.05.2025.
//

#ifndef APP_H
#define APP_H



class App {
    App() = default;
public:
    App(const App&) = delete;
    App& operator=(const App&) = delete;
    App(App&&) = delete;
    App& operator=(App&&) = delete;
    ~App() = default;
    static App& getInstance();
    void run();

};



#endif //APP_H
