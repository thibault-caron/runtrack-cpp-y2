#include "GameObject.hpp"

// ========== CONSTRUCTORS & DESTRUCTOR ==========

/**
 * Default constructor
 * Calls Vector2d default constructor (initializes position to 0,0)
 */
GameObject::GameObject() : Vector2d(), name("Unnamed") {
    // Vector2d() calls parent's default constructor
    // name("Unnamed") initializes the name member
}

/**
 * Parameterized constructor
 * 
 * Constructor initialization list:
 * - Vector2d(x, y) calls parent's parameterized constructor
 * - name(name) initializes the name member
 */
GameObject::GameObject(double x, double y, const std::string& name) 
    : Vector2d(x, y), name(name) {
    // Parent (Vector2d) is constructed first with (x, y)
    // Then our member (name) is initialized
}

/**
 * Virtual destructor
 * 
 * Even though we don't have dynamic memory to clean up here,
 * the "virtual" keyword is CRITICAL for proper inheritance.
 * 
 * Without "virtual":
 *   GameObject* obj = new Player();
 *   delete obj;  // Only ~GameObject() runs, Player cleanup skipped! (BAD)
 * 
 * With "virtual":
 *   GameObject* obj = new Player();
 *   delete obj;  // ~Player() runs first, then ~GameObject() (GOOD)
 */
GameObject::~GameObject() {
    // No manual cleanup needed, but destructor must exist
    // and be virtual for proper inheritance behavior
}


// ========== NAME ACCESSORS ==========

std::string GameObject::getName() const {
    return name;
}

void GameObject::setName(const std::string& name) {
    this->name = name;  // this->name distinguishes member from parameter
}


// ========== PURE VIRTUAL METHODS ==========

// NOTE: We do NOT implement draw() and update() here!
// They are pure virtual (= 0), so child classes MUST provide implementation.
// This makes GameObject an abstract class - cannot be instantiated directly.

