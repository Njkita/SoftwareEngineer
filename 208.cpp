#include <iostream>
#include <cmath> 
#include <iterator>
#include <algorithm>
#include <vector>
#include <string>

void move(int disk, char from_rod, char to_rod) {
    std::cout << "диск " << disk << " с " << from_rod << " на " << to_rod << std::endl;
}

void hanoi(int n, char from_rod, char to_rod, char aux_rod) {
    if (n == 1) {
        move(1, from_rod, to_rod);
        return;
    }
    hanoi(n - 1, from_rod, aux_rod, to_rod);
    move(n, from_rod, to_rod);
    hanoi(n - 1, aux_rod, to_rod, from_rod);
}

int main() {
    int n; 
    std::cin >> n;
    hanoi(n, 'A', 'C', 'B');  
    return 0;
}