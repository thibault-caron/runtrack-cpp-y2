#ifndef PROJECTILE_HPP
#define PROJECTILE_HPP

#include "GameObject.hpp"
#include "Character.hpp"

/**
 * Projectile - Flying projectile (arrows, thrown weapons)
 * 
 * Represents arrows fired from the bow (and potentially other ranged weapons).
 * 
 * Lifecycle (Instant Model):
 * 1. Created when bow fires
 * 2. Immediately checks collision with target
 * 3. Deals damage on hit
 * 4. Marks itself as expired
 * 5. Removed from game
 * 
 * All happens in ONE turn!
 * 
 * Design Notes:
 * - This is a "visible instant hit" model
 * - Projectile exists as an object but hits immediately
 * - Can be extended to multi-turn flight later
 * - Makes Bow attacks feel different from melee
 * 
 * Inheritance: Projectile -> GameObject -> Vector2d
 */
class Projectile : public GameObject {
private:
    int damage;              // Damage dealt on hit
    GameObject* owner;       // Who fired this projectile (don't hit owner!)
    Character* target;       // Target to hit
    bool hasHit;             // Has this projectile already hit something?

public:
    // ========== CONSTRUCTORS & DESTRUCTOR ==========
    
    /**
     * Constructor
     * @param x Starting x position (usually owner's position)
     * @param y Starting y position
     * @param name Projectile name (e.g., "Arrow")
     * @param damage Damage dealt on hit
     * @param owner Who fired this projectile
     * @param target Target to hit
     */
    Projectile(double x, double y, const std::string& name,
               int damage, GameObject* owner, Character* target);
    
    /**
     * Destructor
     */
    ~Projectile();
    
    
    // ========== ACCESSORS ==========
    
    /**
     * Get projectile damage
     * @return Damage value
     */
    int getDamage() const;
    
    /**
     * Get projectile owner
     * @return Pointer to owner
     */
    GameObject* getOwner() const;
    
    /**
     * Get projectile target
     * @return Pointer to target
     */
    Character* getTarget() const;
    
    /**
     * Check if projectile has hit
     * @return true if already hit something
     */
    bool getHasHit() const;
    
    /**
     * Check if projectile should be removed
     * @return true if expired (already hit)
     * 
     * Used by GameManager to clean up expired projectiles
     */
    bool isExpired() const;
    
    
    // ========== OVERRIDE PURE VIRTUAL METHODS ==========
    
    /**
     * Draw the projectile
     * Shows arrow flying toward target
     */
    void draw() const override;
    
    /**
     * Update the projectile
     * 
     * For instant-hit model:
     * 1. Check collision with target
     * 2. If collision: deal damage
     * 3. Mark as hit (expired)
     * 
     * For multi-turn model (future):
     * 1. Move toward target
     * 2. Check collision each turn
     * 3. Deal damage on collision
     */
    void update() override;
    
    
    // ========== PROJECTILE-SPECIFIC METHODS ==========
    
    /**
     * Check if projectile hit the target
     * 
     * Uses collision detection to check if projectile
     * is close enough to target to register a hit.
     * 
     * @return true if hit detected
     */
    bool checkHit();
    
    /**
     * Deal damage to target
     * 
     * Applies projectile damage to the target.
     * Provides visual feedback.
     */
    void dealDamage();
};

#endif // PROJECTILE_HPP

