# Морской бой (C++)

Классическая консольная версия игры **Морской бой** 10x10 с полным набором кораблей.

## 🚀 Сборка и запуск

### Windows (MinGW или MSVC)
```bash
g++ src/battleship.cpp -o battleship.exe
./battleship.exe
```

### Linux / macOS
```bash
g++ src/battleship.cpp -o battleship
./battleship
```

### CMake (универсально)
```bash
mkdir build
cd build
cmake ..
make
./battleship
```

## 🎮 Правила
- Игровое поле 10×10  
- Набор кораблей:  
  - 1 × 4-палубный  
  - 2 × 3-палубных  
  - 3 × 2-палубных  
  - 4 × 1-палубных  
- Игрок расставляет корабли вручную, бот — случайно.  
- Побеждает тот, кто первым уничтожит все корабли соперника.
