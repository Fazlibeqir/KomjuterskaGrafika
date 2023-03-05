#include <iostream>

using namespace std;

void drawLine(int x0, int y0, int x1, int y1) {
    int dx = x1 - x0;
    int dy = y1 - y0;
    int p = 2 * dy - dx;
    int x = x0;
    int y = y0;
    int order = 0;
    cout << "Number in order\t" << "xi\t" << "pi\t" << "Pi>=0\t" << "yi" << endl;
    cout << order << "\t\t\t" << x << "\t" << p << "\t" << (p >= 0 ? "True" : "False") << "\t" << y << endl;
    while (x < x1) {
        order++;
        x++;
        if(order>9){
            break;
        }
        if (p < 0) {
            cout << order << "\t\t\t" << x << "\t" << p << "\t" << "False\t" << y << endl;
            p = p + 2 * dy;
        } else {
            y++;
            cout << order << "\t\t\t" << x << "\t" << p << "\t" << "True\t" << y << endl;
            p = p + 2 * dy - 2 * dx;
        }
    }
}

int main() {
    drawLine(5, 5, 15, 10); // Draw a line from (2, 2) to (7, 4)
    return 0;
}
