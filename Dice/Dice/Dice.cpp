#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

struct Dice {
    int top, bottom, left, right, front, back;

    Dice(int t, int f, int r) {
        // simple validation
        if (t < 1 || t > 6 || f < 1 || f > 6 || r < 1 || r > 6) {
            cerr << "The faces must be between 1 and 6\n"; exit(1);
        }
        if (t + f == 7 || t + r == 7 || f + r == 7) {
            cerr << "Opposite faces cannot be set simultaneously\n"; exit(1);
        }
        if (t == f || t == r || f == r) {
            cerr << "Face values should not be equal\n"; exit(1);
        }
        top = t;
        front = f;
        right = r;
        bottom = 7 - t;
        back = 7 - f;
        left = 7 - r;
    }

    void rotate(const string& direction) {
        int tmp;
        if (direction == "forward") {
            tmp = top;
            top = back;
            back = bottom;
            bottom = front;
            front = tmp;
        }
        else if (direction == "backward") {
            tmp = top;
            top = front;
            front = bottom;
            bottom = back;
            back = tmp;
        }
        else if (direction == "right") {
            tmp = top;
            top = left;
            left = bottom;
            bottom = right;
            right = tmp;
        }
        else if (direction == "left") {
            tmp = top;
            top = right;
            right = bottom;
            bottom = left;
            left = tmp;
        }
        else {
            cerr << "Error: invalid direction \"" << direction << "\"\n";
            exit(1);
        }
    }

    void printLayout() const {
        // spaces instead of setw
        cout << "   " << back << "\n";
        cout << "  -----\n";
        cout << left << " | " << top << " | " << right << "\n";
        cout << "  -----\n";
        cout << "   " << front << "\n";
        cout << "  -----\n";
        cout << "   " << bottom << "\n";
    }
};

int main() {
    int t, f, r;
    cout << "Enter the top, front, and right faces (separated by space): ";
    if (!(cin >> t >> f >> r)) {
        cerr << "Invalid input\n"; return 1;
    }

    Dice d(t, f, r);
    cout << "Current state:\n";
    d.printLayout();

    cout << "\nEnter directions (forward, backward, right, left) to roll the dice;\n"
        << "or \"quit\" to exit.\n";

    string cmd;
    while (cin >> cmd) {
        if (cmd == "quit") break;
        d.rotate(cmd);
        d.printLayout();
        cout << "\n";
    }

    return 0;
}
