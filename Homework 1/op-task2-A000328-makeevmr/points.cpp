#include <iostream>

long long int circle_points_counter(long long int const R) {
    long long int points_counter = (2 * R + 1) * (2 * R + 1);
    long int dot[] = {-R, 1};
    long long int not_in_circle_dots = 0;
    for (long int i = -R; i < 0; ++i) {
        dot[0] = i;
        while ((dot[0] * dot[0] + dot[1] * dot[1]) <= R * R) {
            dot[1] += 1;
        }
        not_in_circle_dots += R - dot[1] + 1;
    }
    points_counter -= 4 * not_in_circle_dots;
    return points_counter;
}


int main() {
    long int radius;
    std::cin >> radius;
    std::cout << circle_points_counter(radius);
    return 0;
}
