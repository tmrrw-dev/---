#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>

using namespace std;

const int SIZE = 10;

struct Ship {
    int size;
    vector<pair<int, int>> cells;
    bool sunk = false;
};

bool placeShip(vector<vector<char>>& board, Ship& ship, bool manual = false) {
    int x, y, dir;
    if (manual) {
        cout << "Введите координаты начала (x y) и направление (0 = горизонтально, 1 = вертикально) для корабля размером "
             << ship.size << ": ";
        cin >> x >> y >> dir;
    } else {
        x = rand() % SIZE;
        y = rand() % SIZE;
        dir = rand() % 2;
    }

    if (dir == 0 && x + ship.size > SIZE) return false;
    if (dir == 1 && y + ship.size > SIZE) return false;

    for (int i = 0; i < ship.size; i++) {
        int nx = x + (dir == 0 ? i : 0);
        int ny = y + (dir == 1 ? i : 0);
        if (board[ny][nx] != '.') return false;
    }

    ship.cells.clear();
    for (int i = 0; i < ship.size; i++) {
        int nx = x + (dir == 0 ? i : 0);
        int ny = y + (dir == 1 ? i : 0);
        board[ny][nx] = 'O';
        ship.cells.push_back({nx, ny});
    }
    return true;
}

bool allSunk(vector<Ship>& fleet) {
    for (auto& s : fleet) {
        if (!s.sunk) return false;
    }
    return true;
}

bool attack(vector<vector<char>>& board, vector<Ship>& fleet, int x, int y) {
    if (board[y][x] == 'O') {
        board[y][x] = 'X';
        cout << "Попадание!\n";
        for (auto& s : fleet) {
            bool allHit = true;
            for (auto& c : s.cells) {
                if (board[c.second][c.first] == 'O') {
                    allHit = false;
                    break;
                }
            }
            if (allHit && !s.sunk) {
                s.sunk = true;
                cout << "Корабль уничтожен!\n";
            }
        }
        return true;
    } else if (board[y][x] == '.') {
        board[y][x] = '*';
        cout << "Мимо.\n";
    } else {
        cout << "Уже стреляли сюда.\n";
    }
    return false;
}

void printBoard(vector<vector<char>>& board, bool hideShips = false) {
    cout << "  ";
    for (int i = 0; i < SIZE; i++) cout << i << " ";
    cout << endl;
    for (int y = 0; y < SIZE; y++) {
        cout << y << " ";
        for (int x = 0; x < SIZE; x++) {
            if (hideShips && board[y][x] == 'O') cout << ". ";
            else cout << board[y][x] << " ";
        }
        cout << endl;
    }
}

int main() {
    srand(time(0));

    vector<vector<char>> playerBoard(SIZE, vector<char>(SIZE, '.'));
    vector<vector<char>> botBoard(SIZE, vector<char>(SIZE, '.'));

    vector<Ship> playerFleet = {
        {4}, {3}, {3}, {2}, {2}, {2}, {1}, {1}, {1}, {1}
    };

    vector<Ship> botFleet = playerFleet;

    cout << "Расставьте свои корабли:\n";
    for (auto& s : playerFleet) {
        bool ok = false;
        while (!ok) {
            ok = placeShip(playerBoard, s, true);
            if (!ok) cout << "Ошибка размещения, попробуйте снова.\n";
        }
        printBoard(playerBoard);
    }

    cout << "Бот расставляет корабли...\n";
    for (auto& s : botFleet) {
        bool ok = false;
        while (!ok) {
            ok = placeShip(botBoard, s, false);
        }
    }

    cout << "\nНачинается игра!\n";

    while (true) {
        cout << "\nВаше поле:\n";
        printBoard(playerBoard);
        cout << "\nПоле бота:\n";
        printBoard(botBoard, true);

        int x, y;
        cout << "\nВаш выстрел (x y): ";
        cin >> x >> y;
        attack(botBoard, botFleet, x, y);

        if (allSunk(botFleet)) {
            cout << "Поздравляем, вы победили!\n";
            break;
        }

        x = rand() % SIZE;
        y = rand() % SIZE;
        cout << "Бот стреляет в (" << x << ", " << y << ")\n";
        attack(playerBoard, playerFleet, x, y);

        if (allSunk(playerFleet)) {
            cout << "Бот победил!\n";
            break;
        }
    }

    return 0;
}
