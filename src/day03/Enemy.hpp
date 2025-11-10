#ifndef ENEMY_HPP
#define ENEMY_HPP

#include "Character.hpp"

// Forward declaration to avoid circular dependency
class Player;

/**
 * Enemy - AI-controlled hostile character
 * 
 * Inherits from Character and implements combat AI behavior.
 * 
 * AI Behavior (update method):
 * 1. Calculate distance to target player
 * 2. If distance > 1.0: Move progressively towards player (pathfinding)
 * 3. If distance ≤ 1.0: Attack player with melee damage
 * 
 * This demonstrates:
 * - AI pathfinding (movement towards target)
 * - Range checking (attack when in range)
 * - Autonomous behavior (update does everything)
 * 
 * Inheritance: Enemy -> Character -> GameObject -> Vector2d
 */
class Enemy : public Character {
private:
    Character* targetPlayer;  // Reference to player to attack
    int attackDamage;         // Melee attack damage
    double attackRange;       // Attack range (1.0 for melee)
    double moveSpeed;         // Movement speed (units per turn)

public:
    // ========== CONSTRUCTORS & DESTRUCTOR ==========
    
    /**
     * Constructor
     * @param x Starting x position
     * @param y Starting y position
     * @param name Enemy's name
     * @param health Enemy's health points
     * @param targetPlayer Pointer to player character to pursue
     * @param attackDamage Damage dealt when attacking (default 5)
     */
    Enemy(double x, double y, const std::string& name, int health,
          Character* targetPlayer, int attackDamage = 5);
    
    /**
     * Destructor
     */
    ~Enemy();
    
    
    // ========== ACCESSORS ==========
    
    /**
     * Get attack damage
     * @return Damage dealt per attack
     */
    int getAttackDamage() const;
    
    /**
     * Get attack range
     * @return Maximum attack distance
     */
    double getAttackRange() const;
    
    /**
     * Get move speed
     * @return Movement speed in units per turn
     */
    double getMoveSpeed() const;
    
    /**
     * Set target player
     * @param player New target to pursue
     */
    void setTarget(Character* player);
    
    
    // ========== OVERRIDE METHODS ==========
    
    /**
     * Override draw to show Enemy-specific information
     */
    void draw() const override;
    
    /**
     * AI Update - Called each turn
     * 
     * Implements enemy AI behavior:
     * 1. Check if alive and has valid target
     * 2. Calculate distance to target
     * 3. If far: Move towards target (pathfinding)
     * 4. If close: Attack target
     * 
     * This is the CORE of enemy AI!
     */
    void update() override;

private:
    // ========== PRIVATE HELPER METHODS ==========
    
    /**
     * Move towards target player
     * Uses normalized direction vector to move exactly moveSpeed units
     */
    void moveTowardsTarget();
    
    /**
     * Attack the target player
     * Deals attackDamage to target
     */
    void attackTarget();
};

#endif // ENEMY_HPP

