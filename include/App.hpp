#pragma once

class App {
public:
  App() = default;
  void run(); // Main loop

private:
  void init();
  void shutdown();
  void update();
  void draw() const;
};
