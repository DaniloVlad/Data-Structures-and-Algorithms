#include <iostream>
#include <stdlib.h>

//recursive function to calculate fib
long fib(long n) {
    if(n == 0) return 0;
    else if(n == 1) return 1;
    else return fib(n-1) + fib(n-2); 
}

int main() {
    long n = 0;

    //take user input and check the value
    std::cout << "Enter a number between 0 and 10: ";
    std::cin >> n;
    std::cout << "You entered: " << n << std::endl;
    if(n > 10 || n < 0) {
        std::cout << "Invalid input" << std::endl;
        return 1;
    }
    //call function and print results
    std::cout << "Calculated: " << fib(n*5) << std::endl;

    return 0;
}