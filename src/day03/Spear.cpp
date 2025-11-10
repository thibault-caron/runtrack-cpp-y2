#include "Spear.hpp"
#include <iostream>

// ========== CONSTRUCTOR & DESTRUCTOR ==========

/**
 * Constructor - initializes Spear with stats
 * Range=2, Power=2
 */
Spear::Spear() : Weapon(2, 2) {
    // Call parent Weapon constructor with Spear's specific stats
    // Weapon(2, 2) sets range=2, power=2
}

Spear::~Spear() {
    // No special cleanup needed
}


// ========== OVERRIDE PURE VIRTUAL METHODS ==========

std::string Spear::getName() const {
    return "Spear";
}

/**
 * Spear attack implementation
 * 
 * Thrusts the spear at the target:
 * - Deals 2 damage (power=2)
 * - Can reach up to 2 distance units (range=2)
 * 
 * Balanced weapon - moderate range and damage.
 */
void Spear::attack(Character& target) {
    std::cout << "🗡️  Spear thrust! ";
    
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

