#include "main.hpp"
#include "day01.hpp"

int main() {
    int jobChoice;
    std::cout << "Choose a job (1-14): ";
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
            std::array<int, 5> numbers = getNumbers();
            std::cout << "Average: " << average(numbers) << std::endl;
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
        case 8: {
            // Job 8
            std::cout << "Enter a year and check if it is a leap year :" << std::endl;
            int year{0};
            std::cin >> year;
            std::cout << year << (isLeapYear(year) ? " is " : " isn't ") << "a leap year."
            << std::endl;
            break;
        }
        case 9: {
            int numbersList[5]{1, 2, 0, 5, 11};
            std::cout << "The list is : ";
            for (int i = 0; i < 5; i++) {
            std::cout << numbersList[i] << " ";
            }

            std::cout << "The smallest number is : " << findSmallestInt(numbersList, 5)
                      << std::endl;
            break;
        }
        case 10: {
            // Job 10
            int a1{5}, b1{2}, c1{8}, d1{1}, e1{3};
            int* numbersListV2[5]{&a1, &b1, &c1, &d1, &e1};
            std::cout << "The list is : ";
            for (int i = 0; i < 5; i++) {
                std::cout << *numbersListV2[i] << " ";
            }

            std::cout << "The smallest number is : "
                        << findSmallestIntV2(numbersListV2, 5) << std::endl;
            break;
        }
        case 11: {
            // Job 11
            int a2 = 456;
            int b2 = 789;
            swapInteger(a2, b2);
            break;
        }
        case 12: {
                // Job 12
                printArray(numbersList, 5);
                int doubleArraySum{doubleArray(numbersList, 5)};
                std::cout << "sum is : " << doubleArraySum << std::endl;
                printArray(numbersList, 5);
            break;
        }
        case 13: {
            // Job 13 finobacci
            std::array<int, 10> finobacciArr = finobacci(20);
            for (int number : finobacciArr) {
                std::cout << number << " " << std::endl;
            }

            // Job 13 part 2
            uint32_t x = 0b1011;  // 3 bits set → odd
            std::cout << std::boolalpha << hasEvenBits(x) << std::endl;  // false

            x = 0b1100;                                // 2 bits set → even
            std::cout << hasEvenBits(x) << std::endl;  // true
            break;
        }
        case 14: {
            // Job 14 cube
            int numberOfCube = 7;
            std::cout << "addition of cube from 5 to " << numberOfCube << " is "
                      << cube(numberOfCube) << std::endl;
            break;
        }

        default:
            std::cout << "Invalid job number!" << std::endl;
    }

    return 0;
}