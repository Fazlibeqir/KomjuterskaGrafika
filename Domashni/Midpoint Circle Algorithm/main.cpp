#include<stdio.h>

// Implementing Mid-Point Circle Drawing Algorithm
void midPointCircleDraw(int x_centre, int y_centre, int r)
{
    int x = 0, y = r;
    // Printing the initial point on the axes
    // after translation
    printf("(%d, %d) ", x + x_centre, y + y_centre);
    // Initialising the value of P
    int P = 1 - r;
    while (x < y)
    {
        x++;
        // Mid-point is inside or on the perimeter
        if (P <= 0)
            P = P + 2*x + 1;
            // Mid-point is outside the perimeter
        else
        {
            y--;
            P = P + 2*x - 2*y + 1;
        }
        // All the perimeter points have already been printed
        if (x >= y)
            break;
        // Printing the generated point and its reflection
        // in the other octants after translation
        printf("(%d, %d) ", x + x_centre, y + y_centre);
        printf("(%d, %d) ", y + x_centre, x + y_centre);
        printf("(%d, %d) ", -x + x_centre, y + y_centre);
        printf("(%d, %d)\n", -y + x_centre, x + y_centre);
    }
}

// Driver code
int main()
{
    // To draw a circle of radius 10 centered at (0, 0)
    midPointCircleDraw(0, 0, 10);
    return 0;
}