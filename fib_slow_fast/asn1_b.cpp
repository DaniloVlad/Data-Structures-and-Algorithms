#include <iostream>
#include <vector>
#include <stdlib.h>

//attempt at making a class to solve overflow didnt get far, no time or patience.
class BigInt {
    public:
        BigInt() {
            _value = std::vector<unsigned long long>();
        }

    private:
        std::vector<unsigned long long> _value;
};

//val will store (F(n), F(n - 1))
//computed fib in O(n) time 
//doesn't solve overflows
unsigned long long *fib(long n, unsigned long long *val) {
    if(n == 1) { //base case
        val = new unsigned long long[2]; //creates new array (0, 0, 0), 3rd value could be used for overflow?
        val[1] = 0;
        val[0] = 1;
    }
    else {
        val = fib(n-1, val);
        unsigned long long tot = val[0] + val[1];
        // if(tot < val[0]) {
        //     std::cout << "Overflow" << std::endl;
        // }
        val[1] = val[0];
        val[0] = tot;
        

    }
    return val;

}

//main function calls my fib function
int main() {
    long n = 0;
    std::cout << "Enter a number between 0 and 30: ";
    std::cin >> n;
    std::cout << "You entered: " << n << std::endl;
    if(n > 30 || n < 0) {
        std::cout << "Invalid input" << std::endl;
        return 1;
    }
    unsigned long long *val = new unsigned long long[2];
    val = fib(n*10, 0);
    std::cout << "Calculated: " << val[0]+val[1] << std::endl;

    return 0;
}