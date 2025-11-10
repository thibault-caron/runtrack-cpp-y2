#ifndef SWORD_HPP
#define SWORD_HPP

#include "Weapon.hpp"

/**
 * Sword - Melee, high-power weapon
 * 
 * Stats: Range=1, Power=4
 * 
 * Gameplay characteristics:
 * - Shortest range (melee only)
 * - Highest damage per hit
 * - Strategy: Close combat, high risk/high reward, burst damage
 * 
 * Inheritance: Sword -> Weapon
 */
class Sword : public Weapon {
public:
    // ========== CONSTRUCTOR & DESTRUCTOR ==========
    
    /**
     * Constructor - creates a sword with predefined stats
     * Range=1, Power=4 (melee, high damage)
     */
    Sword();
    
    /**
     * Destructor
     */
    ~Sword();
    
    
    // ========== OVERRIDE PURE VIRTUAL METHODS ==========
    
    /**
     * Get weapon name
     * Implementation of pure virtual from Weapon
     */
    std::string getName() const override;
    
    /**
     * Attack with sword
     * Implementation of pure virtual from Weapon
     * 
     * Sword attack: slashes with sword dealing 4 damage at range 1
     */
    void attack(Character& target) override;
};

#endif // SWORD_HPP

