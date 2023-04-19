#include <iostream>
using namespace std;



struct wcPt2D {
    float x, y;
};

int round(float a) {
    return int(a + 0.5);
}

// Define a four-bit code for each of the outside regions of a rectangular clipping window
const int winLeftBitCode = 0x1;
const int winRightBitCode = 0x2;
const int winBottomBitCode = 0x4;
const int winTopBitCode = 0x8;

// A bit-mask region code is also assigned to each endpoint of an input line segment
// according to its position relative to the four edges of an input rectangular clip window
// If the 'or' operation for the two endpoint codes produces a value of false, the entire line defined by these two endpoints is saved (accepted)
// If the 'and' operation between two endpoint codes is true, the line is completely outside the clipping window, and it is eliminated (rejected) from further processing.

int inside(int code) {
    return !code;
}

int reject(int code1, int code2) {
    return code1 & code2;
}

int accept(int code1, int code2) {
    return !(code1 | code2);
}

unsigned char encode(wcPt2D pt, wcPt2D winMin, wcPt2D winMax) {
    unsigned char code = 0x00;
    if (pt.x < winMin.x)
        code = code | winLeftBitCode;
    if (pt.x > winMax.x)
        code = code | winRightBitCode;
    if (pt.y < winMin.y)
        code = code | winBottomBitCode;
    if (pt.y > winMax.y)
        code = code | winTopBitCode;
    return code;
}

void swapPts(wcPt2D &p1, wcPt2D &p2) {
    wcPt2D tmp = p1;
    p1 = p2;
    p2 = tmp;
}

void swapCodes(unsigned char &c1, unsigned char &c2) {
    unsigned char tmp = c1;
    c1 = c2;
    c2 = tmp;
}
void plotPixel(int x, int y) {
    cout << "Pixel (" << x << ", " << y << ") plotted\n";
}
void lineBres(int x0, int y0, int x1, int y1) {
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = x0 < x1 ? 1 : -1;
    int sy = y0 < y1 ? 1 : -1;
    int err = dx - dy;

    while (x0 != x1 || y0 != y1) {
        // plot the current point (x0, y0)
        plotPixel(x0, y0);

        int e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            x0 += sx;
        }
        if (e2 < dx) {
            err += dx;
            y0 += sy;
        }
    }
    // plot the final point (x1, y1)
    plotPixel(x1, y1);
}


// This function clips a line segment against a rectangular clipping window using Cohen-Sutherland algorithm
void lineClipCohSuth(wcPt2D winMin, wcPt2D winMax, wcPt2D p1, wcPt2D p2) {
    unsigned char code1, code2;
    bool done = false, plotLine = false;
    float m;
    while (!done) {
        code1 = encode(p1, winMin, winMax);
        code2 = encode(p2, winMin, winMax);
        if (accept(code1, code2)) {
            done = true;
            plotLine = true;
        } else if (reject(code1, code2)) {
            done = true;
        } else {
            // Label the endpoint outside the display window as p1.
            if (inside(code1)) {
                swapPts(p1, p2);
                swapCodes(code1, code2);
            }
            // Use slope m to find line-clipEdge intersection.
            if (p2.x != p1.x) {
                m = (p2.y - p1.y) / (p2.x - p1.x);
            }
            if (code1 & winLeftBitCode) {
                p1.y += (winMin.x - p1.x) * m;
                p1.x = winMin.x;
            } else if (code1 & winRightBitCode) {
                p1.y += (winMax.x - p1.x) * m;
                p1.x = winMax.x;
            } else if (code1 & winBottomBitCode) {
                /* Need to update p1.x for nonvertical lines only. */
                if (p2.x != p1.x)
                    p1.x += (winMin.y - p1.y) / m;
                p1.y = winMin.y;
            } else if (code1 & winTopBitCode) {
                if (p2.x != p1.x)
                    p1.x += (winMax.y - p1.y) / m;
                p1.y = winMax.y;
            }
        }
    }
    if (plotLine)
        lineBres(round(p1.x), round(p1.y), round(p2.x), round(p2.y));
}
int main(){
    wcPt2D winMin={0,0};
    wcPt2D winMax={1,1};
    wcPt2D p1={-0.5,0.5};
    wcPt2D p2={2.0,1.75};
    lineClipCohSuth(winMin,winMax,p1,p2);
    return 0;
}