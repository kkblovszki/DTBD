#include <iostream>

int addition(int a, int b);

/**
 * @brief This is a brief description of the main function
 * @return int 
 */
int main() {
    std::cout << addition(1,2) << std::endl;
    return 0;

}

/**
 * @brief This is a brief description of the addition function
 * 
 * @param a 
 * @param b 
 * @return int 
 */
int addition(int a, int b) {
    return a + b;
}