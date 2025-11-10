#include "Weapon.hpp"

// ========== CONSTRUCTOR & DESTRUCTOR ==========

/**
 * Constructor - initializes weapon stats
 * 
 * Protected: Can only be called by subclass constructors
 */
Weapon::Weapon(int range, int power) : range(range), power(power) {
    // Initialize range and power using member initializer list
    // Subclasses will call this to set their specific stats
}

/**
 * Virtual destructor
 * 
 * Even though we don't have dynamic memory here, virtual destructor
 * is essential for polymorphism. Without it:
 * 
 *   Weapon* w = new Sword();
 *   delete w;  // Without virtual: only ~Weapon() runs (BAD!)
 *              // With virtual: ~Sword() then ~Weapon() (GOOD!)
 */
Weapon::~Weapon() {
    // No manual cleanup needed, but must be virtual
}


// ========== ACCESSORS ==========

int Weapon::getRange() const {
    return range;
}

int Weapon::getPower() const {
    return power;
}


// ========== PURE VIRTUAL METHODS ==========

// NOTE: We do NOT implement getName() and attack() here!
// They are pure virtual (= 0), so subclasses MUST provide implementation.
// This makes Weapon an abstract class - cannot be instantiated directly.

