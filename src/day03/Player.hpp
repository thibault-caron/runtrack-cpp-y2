#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Character.hpp"
#include "Weapon.hpp"
#include "Bow.hpp"
#include "Spear.hpp"
#include "Sword.hpp"

/**
 * Player - User-controlled character with weapon system
 * 
 * Inherits from Character and implements weapon management.
 * 
 * Player Behavior (update method):
 * 1. Attack current target with current weapon
 * 2. Switch to next weapon in cycle
 * 
 * Weapon Cycle: Bow → Spear → Sword → Bow (repeats)
 * 
 * This demonstrates:
 * - Composition (Player HAS weapons)
 * - Strategy Pattern (switching attack strategies)
 * - Turn-based combat (attack then switch)
 * 
 * Inheritance: Player -> Character -> GameObject -> Vector2d
 */
class Player : public Character {
private:
    // Weapon system - all three weapons stored (composition)
    Bow bow;
    Spear spear;
    Sword sword;
    
    Weapon* currentWeapon;    // Pointer to currently equipped weapon
    Character* currentTarget; // Current enemy to attack

public:
    // ========== CONSTRUCTORS & DESTRUCTOR ==========
    
    /**
     * Constructor
     * @param x Starting x position
     * @param y Starting y position
     * @param name Player's name
     * @param health Player's health points (default 100)
     */
    Player(double x, double y, const std::string& name, int health = 100);
    
    /**
     * Destructor
     */
    ~Player();
    
    
    // ========== WEAPON MANAGEMENT ==========
    
    /**
     * Get currently equipped weapon
     * @return Pointer to current weapon
     */
    Weapon* getCurrentWeapon() const;
    
    /**
     * Switch to next weapon in cycle
     * 
     * Cycle: Bow → Spear → Sword → Bow (repeats)
     * 
     * This is the Strategy Pattern in action!
     * Changes combat strategy by switching weapon.
     */
    void switchWeapon();
    
    /**
     * Equip a specific weapon
     * @param weaponName "Bow", "Spear", or "Sword"
     * @return true if successful, false if invalid name
     */
    bool equipWeapon(const std::string& weaponName);
    
    
    // ========== TARGET MANAGEMENT ==========
    
    /**
     * Set target to attack
     * @param target Pointer to enemy character
     */
    void setTarget(Character* target);
    
    /**
     * Get current target
     * @return Pointer to current target
     */
    Character* getTarget() const;
    
    
    // ========== OVERRIDE METHODS ==========
    
    /**
     * Override draw to show Player-specific information
     */
    void draw() const override;
    
    /**
     * Player Update - Called each turn
     * 
     * Turn-based combat logic:
     * 1. Attack current target with current weapon
     * 2. Switch to next weapon in cycle
     * 
     * This follows the assignment specification exactly!
     */
    void update() override;
};

#endif // PLAYER_HPP

