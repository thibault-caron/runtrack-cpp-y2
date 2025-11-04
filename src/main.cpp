#include "main.hpp"
#include "day01/day01.hpp"

int main() {
    int jobChoice;
    std::cout << "Choose a job (1-7): ";
    std::cin >> jobChoice;

    switch (jobChoice) {
        case 1: {
            std::string name = "Florence";
            say_hello(name);
            break;
        }
        case 2: {
            int c = mulitplyInteger(3, 6);
            std::cout << c << std::endl;
            break;
        }
        case 3: {
            // std::array<int, 5> numbers = getNumbers();
            // std::cout << "Average: " << average(numbers) << std::endl;
            break;
        }
        case 4: {
            std::cout << (isPair() ? "Even" : "Odd") << std::endl;
            break;
        }
        case 5: {
            int a = 123;
            int b = 321;
            swapInteger(a, b);
            break;
        }
        case 6: {
            std::cout << "Enter the price of whatever here :" << std::endl;
            float priceWithoutTaxes{0};
            std::cin >> priceWithoutTaxes;
            std::cout << "final price is : " << getTaxesIncludedPrice(priceWithoutTaxes, 15) << "€" << std::endl;
            break;
        }
        case 7: {
            std::cout << "Enter a number to revert" << std::endl;
            int number{0};
            std::cin >> number;
            std::cout << "Your reversed number is : " << revertNumber(number) << std::endl;
            break;
        }
        default:
            std::cout << "Invalid job number!" << std::endl;
    }

    return 0;
}