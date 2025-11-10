#include "Sword.hpp"
#include <iostream>

// ========== CONSTRUCTOR & DESTRUCTOR ==========

/**
 * Constructor - initializes Sword with stats
 * Range=1, Power=4
 */
Sword::Sword() : Weapon(1, 4) {
    // Call parent Weapon constructor with Sword's specific stats
    // Weapon(1, 4) sets range=1, power=4
}

Sword::~Sword() {
    // No special cleanup needed
}


// ========== OVERRIDE PURE VIRTUAL METHODS ==========

std::string Sword::getName() const {
    return "Sword";
}

/**
 * Sword attack implementation
 * 
 * Slashes the target with a sword:
 * - Deals 4 damage (power=4) - HIGHEST damage!
 * - Only reaches 1 distance unit (range=1) - melee only
 * 
 * High risk (must be close), high reward (massive damage).
 */
void Sword::attack(Character& target) {
    std::cout << "⚔️  Sword slash! ";
    
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

