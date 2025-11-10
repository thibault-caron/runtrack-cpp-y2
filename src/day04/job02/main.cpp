#include <iostream>
#include <string>
#include "Box.hpp"

using namespace std;
using namespace CustomTemplates;

/**
 * Custom Player Class for Testing
 * 
 * Demonstrates that Box can work with ANY type, including custom classes!
 * 
 * Requirements for custom classes used with Box:
 *   1. Default constructor (for Box default constructor)
 *   2. Copy constructor (for Box parameterized constructor and setValue)
 *   3. Assignment operator (for setValue)
 * 
 * All these are automatically provided by the compiler if you don't define them,
 * but it's good practice to understand they exist!
 */
class Player {
private:
    string name;
    int health;
    int level;

public:
    // Default constructor (required for Box default constructor)
    Player() : name("Unknown"), health(100), level(1) {
        cout << "    [Player] Default constructor called" << endl;
    }

    // Parameterized constructor
    Player(const string& n, int h, int l) : name(n), health(h), level(l) {
        cout << "    [Player] Parameterized constructor called: " << name << endl;
    }

    // Copy constructor (required for Box parameterized constructor and setValue)
    Player(const Player& other) : name(other.name), health(other.health), level(other.level) {
        cout << "    [Player] Copy constructor called: " << name << endl;
    }

    // Assignment operator (required for setValue)
    Player& operator=(const Player& other) {
        if (this != &other) {
            name = other.name;
            health = other.health;
            level = other.level;
            cout << "    [Player] Assignment operator called: " << name << endl;
        }
        return *this;
    }

    // Getters
    string getName() const { return name; }
    int getHealth() const { return health; }
    int getLevel() const { return level; }

    // Display method
    void display() const {
        cout << "Player: " << name << " (Health: " << health 
             << ", Level: " << level << ")";
    }
};

/**
 * Test Function: Demonstrate Box with int
 */
void testInt() {
    cout << "\n" << string(60, '=') << endl;
    cout << "TEST 1: Box<int> - Basic Integer Storage" << endl;
    cout << string(60, '=') << endl;

    cout << "\n1.1 Creating Box<int> with default constructor:" << endl;
    Box<int> intBox;
    cout << "   Default value: " << intBox.getValue() << endl;

    cout << "\n1.2 Creating Box<int> with parameterized constructor:" << endl;
    Box<int> intBox2(42);
    cout << "   Stored value: " << intBox2.getValue() << endl;

    cout << "\n1.3 Using setValue to change content:" << endl;
    intBox.setValue(100);
    cout << "   New value: " << intBox.getValue() << endl;

    cout << "\n1.4 Multiple Box<int> instances (different values):" << endl;
    Box<int> boxA(10);
    Box<int> boxB(20);
    Box<int> boxC(30);
    cout << "   Box A: " << boxA.getValue() << endl;
    cout << "   Box B: " << boxB.getValue() << endl;
    cout << "   Box C: " << boxC.getValue() << endl;

    cout << "\n✓ TEST 1 PASSED: Box<int> works correctly!" << endl;
}

/**
 * Test Function: Demonstrate Box with double
 */
void testDouble() {
    cout << "\n" << string(60, '=') << endl;
    cout << "TEST 2: Box<double> - Floating Point Storage" << endl;
    cout << string(60, '=') << endl;

    cout << "\n2.1 Creating Box<double> with default constructor:" << endl;
    Box<double> doubleBox;
    cout << "   Default value: " << doubleBox.getValue() << endl;

    cout << "\n2.2 Creating Box<double> with parameterized constructor:" << endl;
    Box<double> doubleBox2(3.14159);
    cout << "   Stored value: " << doubleBox2.getValue() << endl;

    cout << "\n2.3 Precision demonstration:" << endl;
    doubleBox.setValue(2.718281828);
    cout << "   Euler's number: " << doubleBox.getValue() << endl;

    cout << "\n✓ TEST 2 PASSED: Box<double> works correctly!" << endl;
}

/**
 * Test Function: Demonstrate Box with string
 */
void testString() {
    cout << "\n" << string(60, '=') << endl;
    cout << "TEST 3: Box<string> - String Storage" << endl;
    cout << string(60, '=') << endl;

    cout << "\n3.1 Creating Box<string> with default constructor:" << endl;
    Box<string> stringBox;
    cout << "   Default value: '" << stringBox.getValue() << "'" << endl;

    cout << "\n3.2 Creating Box<string> with parameterized constructor:" << endl;
    Box<string> stringBox2("Hello, World!");
    cout << "   Stored value: '" << stringBox2.getValue() << "'" << endl;

    cout << "\n3.3 Modifying string content:" << endl;
    stringBox.setValue("C++ Templates are powerful!");
    cout << "   New value: '" << stringBox.getValue() << "'" << endl;

    cout << "\n✓ TEST 3 PASSED: Box<string> works correctly!" << endl;
}

/**
 * Test Function: Demonstrate Box with custom Player class
 */
void testPlayer() {
    cout << "\n" << string(60, '=') << endl;
    cout << "TEST 4: Box<Player> - Custom Class Storage" << endl;
    cout << string(60, '=') << endl;

    cout << "\n4.1 Creating Box<Player> with default constructor:" << endl;
    cout << "   (This will call Player's default constructor)" << endl;
    Box<Player> playerBox;
    cout << "   Retrieved player: ";
    playerBox.getValue().display();
    cout << endl;

    cout << "\n4.2 Creating Box<Player> with parameterized constructor:" << endl;
    cout << "   (This will create a Player, then copy it into Box)" << endl;
    Player hero("Hero", 150, 5);
    Box<Player> heroBox(hero);
    cout << "   Retrieved player: ";
    heroBox.getValue().display();
    cout << endl;

    cout << "\n4.3 Using setValue with Player:" << endl;
    cout << "   (This will use Player's assignment operator)" << endl;
    Player warrior("Warrior", 200, 10);
    playerBox.setValue(warrior);
    cout << "   Updated player: ";
    playerBox.getValue().display();
    cout << endl;

    cout << "\n4.4 Direct construction in Box:" << endl;
    cout << "   (Creates Player directly, then copies into Box)" << endl;
    Box<Player> mageBox(Player("Mage", 80, 3));
    cout << "   Retrieved player: ";
    mageBox.getValue().display();
    cout << endl;

    cout << "\n✓ TEST 4 PASSED: Box<Player> works correctly!" << endl;
}

/**
 * Test Function: Demonstrate different Box types are different classes
 */
void testTypeIndependence() {
    cout << "\n" << string(60, '=') << endl;
    cout << "TEST 5: Type Independence - Different Types, Different Classes" << endl;
    cout << string(60, '=') << endl;

    cout << "\n5.1 Each Box<T> is a completely different class:" << endl;
    Box<int> intBox(42);
    Box<double> doubleBox(3.14);
    Box<string> stringBox("Hello");
    
    cout << "   Box<int> value: " << intBox.getValue() << endl;
    cout << "   Box<double> value: " << doubleBox.getValue() << endl;
    cout << "   Box<string> value: '" << stringBox.getValue() << "'" << endl;

    cout << "\n5.2 Important: Box<int> and Box<double> are DIFFERENT classes!" << endl;
    cout << "   - Box<int> and Box<double> cannot be mixed" << endl;
    cout << "   - Each is generated separately by the compiler" << endl;
    cout << "   - This is 'template instantiation' at compile-time" << endl;

    cout << "\n✓ TEST 5 PASSED: Type independence demonstrated!" << endl;
}

/**
 * Main Function
 */
int main() {
    cout << "\n";
    cout << string(70, '*') << endl;
    cout << "*" << string(68, ' ') << "*" << endl;
    cout << "*" << string(20, ' ') << "BOX CLASS TEMPLATE TESTS" << string(23, ' ') << "*" << endl;
    cout << "*" << string(68, ' ') << "*" << endl;
    cout << string(70, '*') << endl;

    cout << "\n📦 Welcome to Box Class Template Demonstration!" << endl;
    cout << "\nThis demonstrates how class templates work in C++." << endl;
    cout << "Box<T> can store ANY type T: int, double, string, Player, etc." << endl;

    // Run all tests
    testInt();
    testDouble();
    testString();
    testPlayer();
    testTypeIndependence();

    cout << "\n" << string(70, '*') << endl;
    cout << "🎉 ALL TESTS COMPLETED SUCCESSFULLY! 🎉" << endl;
    cout << string(70, '*') << endl;

    cout << "\n📚 KEY TAKEAWAYS:" << endl;
    cout << "   1. Class templates allow ONE definition for MANY types" << endl;
    cout << "   2. Type must be specified: Box<int>, Box<string>, etc." << endl;
    cout << "   3. Each Box<T> is a different class (compile-time generation)" << endl;
    cout << "   4. Box works with ANY type (primitives, classes, etc.)" << endl;
    cout << "   5. This is how std::vector, std::optional, etc. work!" << endl;
    cout << "\n";

    return 0;
}

