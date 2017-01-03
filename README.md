# Massive-Multiplayer-Observer

## Singleton for Game class

###Usage instructions (main.cpp):
```
// ...
  Game::instance().run();
// ...
```

###Game.h:
```
class Game
{
  public:
    static Game &instance();
    // ...
  private:
    Game(){};
};
```

###Game.cpp:
```
Game &Game::instance()
{
  static Game gameSingleton;
  return gameSingleton;
}
// ...
```

* Context: Access is needed in many different contexts
* Problem: 
* Solution:
* Consequences:
