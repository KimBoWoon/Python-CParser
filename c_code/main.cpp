#include <iostream>
using namespace std;

class Add {
private:
    int x, y;
public:
    Add(int _x = 0, int _y = 0) : x(_x), y(_y)  {}

    int add() {
        return x + y;
    }
};

int main() {
    Add a(3, 3);

    cout << a.add() << endl;
}