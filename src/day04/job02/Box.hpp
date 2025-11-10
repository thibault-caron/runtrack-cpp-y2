#ifndef BOX_HPP
#define BOX_HPP

/**
 * CustomTemplates Namespace
 * 
  Using namespaces to avoid name collisions!
 * Same namespace as max.hpp for consistency.
 */
namespace CustomTemplates {

/**
 * Box Class Template
 * 
 * A generic container that can hold a value of ANY type.
 * 

 * 
 * Template Parameters:
 *   T - The type of value to store (int, double, string, Player, etc.)
 * 
 * Key Concepts:
 *   1. Class Template: Can be instantiated with different types
 *      Box<int> box1;      // Box containing an int
 *      Box<string> box2;   // Box containing a string
 *      Box<Player> box3;   // Box containing a Player
 * 
 *   2. Type Must Be Specified: Unlike function templates, compiler
 *      cannot deduce the type from arguments, so it MUST be specified <T>
 * 
 *   3. Each Instantiation is Different: Box<int> and Box<string>
 *      are completely different classes (generated at compile-time)
 * 
 *   4. Requirements for T:
 *      - Must be copyable (copy constructor)
 *      - Must be assignable (assignment operator)
 *      - For default constructor: T must have default constructor
 */
template<typename T>
class Box {
private:
    T value;  // The stored value of type T

public:
    /**
     * Default Constructor
     * 
     * Creates a Box with a default-constructed value of type T.
     * 
     * Requirements:
     *   - Type T must have a default constructor
     *   - If T is int: value = 0
     *   - If T is string: value = ""
     *   - If T is custom class: calls T::T()
     */
    Box() : value() {
        // Member initializer list: value()
        // Calls default constructor of type T
    }

    /**
     * Parameterized Constructor
     * 
     * Creates a Box initialized with the provided value.
     * 
     * @param val The value to store in the Box
     * 
     * Example:
     *   Box<int> box(42);        // Stores 42
     *   Box<string> box("Hello"); // Stores "Hello"
     */
    Box(T val) : value(val) {
        // Member initializer list: value(val)
        // Calls copy constructor of type T
        // Creates a copy of val and stores it in value
    }

    /**
     * Setter: Modify the stored value
     * 
     * @param val The new value to store
     * 
     * Takes parameter by value (creates a copy).
     * Alternative: const T& val (more efficient for large objects)
     * 
     * Example:
     *   Box<int> box;
     *   box.setValue(100);  // Changes value to 100
     */
    void setValue(T val) {
        value = val;  // Assignment operator of type T
    }

    /**
     * Getter: Retrieve the stored value
     * 
     * @return A COPY of the stored value
     * 
     * Returns by value (creates a copy).
     * 
     * const keyword means:
     *   - This method doesn't modify the Box
     *   - Can be called on const Box objects
     * 
     * Example:
     *   Box<int> box(42);
     *   int x = box.getValue();  // x = 42
     */
    T getValue() const {
        return value;  // Returns a copy
    }
};

} // namespace CustomTemplates

#endif

