#include "Bow.hpp"
#include <iostream>

// ========== CONSTRUCTOR & DESTRUCTOR ==========

/**
 * Constructor - initializes Bow with stats
 * Range=4, Power=1
 */
Bow::Bow() : Weapon(4, 1) {
    // Call parent Weapon constructor with Bow's specific stats
    // Weapon(4, 1) sets range=4, power=1
}

Bow::~Bow() {
    // No special cleanup needed
}


// ========== OVERRIDE PURE VIRTUAL METHODS ==========

std::string Bow::getName() const {
    return "Bow";
}

/**
 * Bow attack implementation
 * 
 * Shoots an arrow at the target:
 * - Deals 1 damage (power=1)
 * - Can reach up to 4 distance units (range=4)
 * 
 * For this implementation, we assume the attacker is in range
 * and directly apply damage.
 */
void Bow::attack(Character& target) {
    std::cout << "🏹 Bow shoots arrow! ";
    
    // Check if target is alive before attacking
    if (!target.isAlive()) {
        std::cout << target.getName() << " is already dead!" << std::endl;
        return;
    }
    
    // Apply damage
    int currentHealth = target.getHealth();
    int newHealth = currentHealth - power;
    target.setHealth(newHealth);
    
    std::cout << "Deals " << power << " damage to " << target.getName();
    std::cout << " (HP: " << currentHealth << " → " << target.getHealth() << ")";
    
    if (!target.isAlive()) {
        std::cout << " [DEFEATED!]";
    }
    
    std::cout << std::endl;
}

