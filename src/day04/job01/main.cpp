#include <iostream>
#include <string>
#include "max.hpp"

using namespace std;

/**
 * Custom class to demonstrate template type requirements
 * 
 * This class has operator> defined, so it works with max template!
 */
class Score {
private:
    int value;
    string playerName;

public:
    Score(int value, const string& name) : value(value), playerName(name) {}
    
    int getValue() const { return value; }
    string getName() const { return playerName; }
    
    // operator> MUST be defined for max template to work!
    // This is a TYPE REQUIREMENT for our template
    bool operator>(const Score& other) const {
        return value > other.value;
    }
    
    // For printing
    void display() const {
        cout << playerName << ": " << value << " points";
    }
};

/**
 * Test program for max template
 * 
 * Demonstrates:
 * - Template instantiation with different types
 * - Compile-time polymorphism
 * - Type requirements (operator>)
 * - Generic programming
 */
int main() {
    cout << "========================================" << endl;
    cout << "   Function Template Test - max<T>     " << endl;
    cout << "========================================" << endl;
    cout << endl;
    
    
    // ========== TEST 1: Integer Type ==========
    cout << "TEST 1: Integer Type (int)" << endl;
    cout << "--------------------------" << endl;
    
    int num1 = 5, num2 = 10;
    cout << "CustomTemplates::max(" << num1 << ", " << num2 << ") = ";
    int resultInt = CustomTemplates::max(num1, num2);  // Using our namespace!
    cout << resultInt << endl;
    
    cout << "\nWhat happened:" << endl;
    cout << "  1. Compiler saw CustomTemplates::max(int, int)" << endl;
    cout << "  2. Generated max<int> function in CustomTemplates namespace" << endl;
    cout << "  3. Compared using int's operator>" << endl;
    cout << "  4. Returned larger value" << endl;
    cout << endl;
    
    cout << "NOTE: Using namespace avoids collision with std::max!" << endl;
    cout << "      Professional approach for organizing code." << endl;
    cout << endl;
    
    
    // ========== TEST 2: Double Type ==========
    cout << "TEST 2: Floating Point Type (double)" << endl;
    cout << "-------------------------------------" << endl;
    
    double pi = 3.14159, e = 2.71828;
    cout << "CustomTemplates::max(" << pi << ", " << e << ") = ";
    double resultDouble = CustomTemplates::max(pi, e);
    cout << resultDouble << endl;
    
    cout << "\nWhat happened:" << endl;
    cout << "  1. Compiler saw max(double, double)" << endl;
    cout << "  2. Generated max<double> function (DIFFERENT from max<int>!)" << endl;
    cout << "  3. Compared using double's operator>" << endl;
    cout << "  4. Returned larger value" << endl;
    cout << endl;
    
    
    // ========== TEST 3: Character Type ==========
    cout << "TEST 3: Character Type (char)" << endl;
    cout << "------------------------------" << endl;
    
    char letter1 = 'a', letter2 = 'z';
    cout << "CustomTemplates::max('" << letter1 << "', '" << letter2 << "') = '";
    char resultChar = CustomTemplates::max(letter1, letter2);
    cout << resultChar << "'" << endl;
    
    cout << "\nWhat happened:" << endl;
    cout << "  1. Compiler saw max(char, char)" << endl;
    cout << "  2. Generated max<char> function" << endl;
    cout << "  3. Compared ASCII values (a=97, z=122)" << endl;
    cout << "  4. Returned 'z' (larger ASCII value)" << endl;
    cout << endl;
    
    
    // ========== TEST 4: String Type ==========
    cout << "TEST 4: String Type (std::string)" << endl;
    cout << "----------------------------------" << endl;
    
    string str1 = "apple", str2 = "banana";
    cout << "CustomTemplates::max(\"" << str1 << "\", \"" << str2 << "\") = \"";
    string resultString = CustomTemplates::max(str1, str2);
    cout << resultString << "\"" << endl;
    
    cout << "\nWhat happened:" << endl;
    cout << "  1. Compiler saw max(string, string)" << endl;
    cout << "  2. Generated max<string> function" << endl;
    cout << "  3. Compared using string's operator> (lexicographic)" << endl;
    cout << "  4. Returned \"banana\" (lexicographically larger)" << endl;
    cout << endl;
    
    
    // ========== TEST 5: Custom Class ==========
    cout << "TEST 5: Custom Class Type (Score)" << endl;
    cout << "----------------------------------" << endl;
    
    Score player1(85, "Alice");
    Score player2(92, "Bob");
    
    cout << "Comparing two Score objects:" << endl;
    cout << "  Player 1: ";
    player1.display();
    cout << endl;
    cout << "  Player 2: ";
    player2.display();
    cout << endl;
    
    cout << "\nCustomTemplates::max(player1, player2) = ";
    Score resultScore = CustomTemplates::max(player1, player2);
    resultScore.display();
    cout << endl;
    
    cout << "\nWhat happened:" << endl;
    cout << "  1. Compiler saw max(Score, Score)" << endl;
    cout << "  2. Generated max<Score> function" << endl;
    cout << "  3. Compared using Score's operator>" << endl;
    cout << "  4. Returned player with higher score" << endl;
    cout << endl;
    
    cout << "NOTE: This works ONLY because Score has operator> defined!" << endl;
    cout << "      Without operator>, compilation would FAIL." << endl;
    cout << endl;
    
    
    // ========== TEST 6: Template Instantiation Count ==========
    cout << "TEST 6: Template Instantiation Analysis" << endl;
    cout << "----------------------------------------" << endl;
    
    cout << "We called max with:" << endl;
    cout << "  - int (Test 1)" << endl;
    cout << "  - double (Test 2)" << endl;
    cout << "  - char (Test 3)" << endl;
    cout << "  - string (Test 4)" << endl;
    cout << "  - Score (Test 5)" << endl;
    cout << endl;
    
    cout << "Compiler generated 5 DIFFERENT functions:" << endl;
    cout << "  1. max<int>(int, int)" << endl;
    cout << "  2. max<double>(double, double)" << endl;
    cout << "  3. max<char>(char, char)" << endl;
    cout << "  4. max<string>(string, string)" << endl;
    cout << "  5. max<Score>(Score, Score)" << endl;
    cout << endl;
    
    cout << "ONE template → FIVE functions!" << endl;
    cout << "This is COMPILE-TIME code generation!" << endl;
    cout << endl;
    
    
    // ========== TEST 7: Edge Cases ==========
    cout << "TEST 7: Edge Cases" << endl;
    cout << "------------------" << endl;
    
    cout << "Equal values:" << endl;
    int equal1 = 5, equal2 = 5;
    cout << "  CustomTemplates::max(" << equal1 << ", " << equal2 << ") = " 
         << CustomTemplates::max(equal1, equal2) << endl;
    cout << "  (Returns second value when equal)" << endl;
    cout << endl;
    
    cout << "Negative numbers:" << endl;
    int neg1 = -10, neg2 = -5;
    cout << "  CustomTemplates::max(" << neg1 << ", " << neg2 << ") = " 
         << CustomTemplates::max(neg1, neg2) << endl;
    cout << "  (-5 is greater than -10)" << endl;
    cout << endl;
    
    
    // ========== TEST 8: Demonstration of Type Safety ==========
    cout << "TEST 8: Type Safety" << endl;
    cout << "-------------------" << endl;
    
    cout << "Templates enforce type matching!" << endl;
    cout << endl;
    cout << "This works:" << endl;
    cout << "  CustomTemplates::max(5, 10)      → Both int ✓" << endl;
    cout << "  CustomTemplates::max(3.14, 2.71) → Both double ✓" << endl;
    cout << endl;
    
    cout << "This would FAIL to compile:" << endl;
    cout << "  // CustomTemplates::max(5, 3.14)   → int vs double ✗" << endl;
    cout << "  // Template requires BOTH parameters to be same type!" << endl;
    cout << endl;
    cout << "This is TYPE SAFETY - compiler catches mistakes!" << endl;
    cout << endl;
    
    cout << "Comparison with std::max:" << endl;
    cout << "  std::max(5, 10) = " << std::max(5, 10) << " (standard library)" << endl;
    cout << "  CustomTemplates::max(5, 10) = " << CustomTemplates::max(5, 10) << " (ours)" << endl;
    cout << "  Both work! Namespaces prevent collision." << endl;
    cout << endl;
    
    
    // ========== Summary ==========
    cout << "========================================" << endl;
    cout << "   All tests completed successfully!    " << endl;
    cout << "========================================" << endl;
    cout << endl;
    
    cout << "Key Concepts Demonstrated:" << endl;
    cout << "  ✓ Function templates (generic functions)" << endl;
    cout << "  ✓ Template instantiation (compiler generates code)" << endl;
    cout << "  ✓ Type requirements (operator> needed)" << endl;
    cout << "  ✓ Compile-time polymorphism (resolved at compile time)" << endl;
    cout << "  ✓ Type safety (enforces matching types)" << endl;
    cout << "  ✓ Works with built-in and custom types" << endl;
    cout << endl;
    
    cout << "Template Benefits:" << endl;
    cout << "  ✓ Code reuse (write once, use with any type)" << endl;
    cout << "  ✓ Type safe (compiler checks correctness)" << endl;
    cout << "  ✓ Zero overhead (inlined, optimized)" << endl;
    cout << "  ✓ Maintainable (one definition to update)" << endl;
    cout << endl;
    
    cout << "Real-world usage:" << endl;
    cout << "  - C++ Standard Library (vector<T>, max<T>, sort<T>)" << endl;
    cout << "  - Game engines (generic components)" << endl;
    cout << "  - Math libraries (generic algorithms)" << endl;
    cout << "  - Container classes (generic storage)" << endl;
    cout << endl;
    
    cout << "🎉 You've mastered function templates!" << endl;
    cout << "This is the foundation of generic programming in C++!" << endl;
    
    return 0;
}

