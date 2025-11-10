#ifndef WEAPON_HPP
#define WEAPON_HPP

#include "Character.hpp"
#include <string>

/**
 * Weapon - Interface/Abstract base class for all weapons
 * 
 * This is an INTERFACE (mostly) - defines the contract for all weapons.
 * Cannot be instantiated directly (has pure virtual methods).
 * 
 * Design Pattern: Strategy Pattern
 * - Different weapons = different attack strategies
 * - Can be used polymorphically
 * - Allows runtime weapon switching
 * 
 * NOTE: This is a "pragmatic interface" - it has protected data members
 * (range, power) for convenience. A "pure interface" would only have
 * pure virtual methods, but this is common in game development.
 */
class Weapon {
protected:
    // Weapon statistics
    int range;  // Attack range (distance units)
    int power;  // Attack power (damage dealt)

public:
    // ========== CONSTRUCTOR & DESTRUCTOR ==========
    
    /**
     * Protected constructor - only subclasses can call this
     * @param range Attack range
     * @param power Attack power/damage
     */
    Weapon(int range, int power);
    
    /**
     * Virtual destructor - CRITICAL for polymorphism!
     * Ensures proper cleanup when deleting through base pointer
     */
    virtual ~Weapon();
    
    
    // ========== ACCESSORS ==========
    
    /**
     * Get weapon's attack range
     * @return Range value
     */
    int getRange() const;
    
    /**
     * Get weapon's attack power
     * @return Power/damage value
     */
    int getPower() const;
    
    
    // ========== PURE VIRTUAL METHODS (INTERFACE) ==========
    
    /**
     * Get weapon's name/type
     * @return Weapon name (e.g., "Bow", "Sword")
     * 
     * PURE VIRTUAL - each weapon must identify itself
     */
    virtual std::string getName() const = 0;
    
    /**
     * Attack a character
     * @param target Reference to the character being attacked
     * 
     * PURE VIRTUAL - each weapon implements its own attack logic
     * 
     * This is the core of the Strategy Pattern:
     * - Same interface (attack a character)
     * - Different implementations (bow vs sword damage application)
     */
    virtual void attack(Character& target) = 0;
};

#endif // WEAPON_HPP

