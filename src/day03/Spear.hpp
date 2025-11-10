#ifndef SPEAR_HPP
#define SPEAR_HPP

#include "Weapon.hpp"

/**
 * Spear - Balanced medium-range weapon
 * 
 * Stats: Range=2, Power=2
 * 
 * Gameplay characteristics:
 * - Medium range
 * - Medium damage
 * - Strategy: Balanced, versatile, adaptable to situations
 * 
 * Inheritance: Spear -> Weapon
 */
class Spear : public Weapon {
public:
    // ========== CONSTRUCTOR & DESTRUCTOR ==========
    
    /**
     * Constructor - creates a spear with predefined stats
     * Range=2, Power=2 (balanced)
     */
    Spear();
    
    /**
     * Destructor
     */
    ~Spear();
    
    
    // ========== OVERRIDE PURE VIRTUAL METHODS ==========
    
    /**
     * Get weapon name
     * Implementation of pure virtual from Weapon
     */
    std::string getName() const override;
    
    /**
     * Attack with spear
     * Implementation of pure virtual from Weapon
     * 
     * Spear attack: thrusts spear dealing 2 damage at range 2
     */
    void attack(Character& target) override;
};

#endif // SPEAR_HPP

