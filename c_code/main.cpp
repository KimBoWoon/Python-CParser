#include <iostream>
using namespace std;

namespace ns {
class Add {
private:
    int x, y;
public:
    Add(int _x = 0, int _y = 0) : x(_x), y(_y)  {}

    int add() {
        return x + y;
    }
};

int b = 1;
double c = 3.4;
}

int main() {
    ns::Add a(3, 3);

    if (a.add() == 6) {
        cout << "O" << endl;
    }
    else {
        cout << "X" << endl;
    }

    cout << a.add() << endl;
}