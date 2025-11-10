#ifndef BOW_HPP
#define BOW_HPP

#include "Weapon.hpp"

/**
 * Bow - Long-range, low-power weapon
 * 
 * Stats: Range=4, Power=1
 * 
 * Gameplay characteristics:
 * - Longest range of all weapons
 * - Lowest damage per hit
 * - Strategy: Hit from safety, kiting, multiple shots
 * 
 * Inheritance: Bow -> Weapon
 */
class Bow : public Weapon {
public:
    // ========== CONSTRUCTOR & DESTRUCTOR ==========
    
    /**
     * Constructor - creates a bow with predefined stats
     * Range=4, Power=1 (long range, low damage)
     */
    Bow();
    
    /**
     * Destructor
     */
    ~Bow();
    
    
    // ========== OVERRIDE PURE VIRTUAL METHODS ==========
    
    /**
     * Get weapon name
     * Implementation of pure virtual from Weapon
     */
    std::string getName() const override;
    
    /**
     * Attack with bow
     * Implementation of pure virtual from Weapon
     * 
     * Bow attack: shoots arrow dealing 1 damage at range 4
     */
    void attack(Character& target) override;
};

#endif // BOW_HPP

