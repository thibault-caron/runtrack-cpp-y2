#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include "GameObject.hpp"

/**
 * Character - Concrete class for living entities
 * 
 * Represents living characters like players, NPCs, enemies.
 * This is a CONCRETE class - can be instantiated.
 * 
 * Inheritance chain: Character -> GameObject -> Vector2d
 * 
 * Key characteristics:
 * - Has health points (points de vie)
 * - Can be alive or dead based on health
 * - Can move and update state
 */
class Character : public GameObject {
private:
    int health;  // Health points (points de vie)

public:
    // ========== CONSTRUCTORS & DESTRUCTOR ==========
    
    /**
     * Default constructor - creates character at origin with 100 health
     */
    Character();
    
    /**
     * Parameterized constructor
     * @param x The x coordinate
     * @param y The y coordinate
     * @param name The character's name
     * @param health The character's health points (default 100)
     */
    Character(double x, double y, const std::string& name, int health = 100);
    
    /**
     * Destructor
     */
    ~Character();
    
    
    // ========== HEALTH MANAGEMENT ==========
    
    /**
     * Get the character's current health
     * @return Health points
     */
    int getHealth() const;
    
    /**
     * Set the character's health
     * @param health New health value
     */
    void setHealth(int health);
    
    /**
     * Check if the character is alive
     * @return true if health > 0, false otherwise
     * 
     * A character is considered alive if they have any health remaining.
     */
    bool isAlive() const;
    
    
    // ========== OVERRIDE PURE VIRTUAL METHODS ==========
    
    /**
     * Draw the character
     * Implementation of pure virtual from GameObject
     */
    void draw() const override;
    
    /**
     * Update the character's state
     * Implementation of pure virtual from GameObject
     */
    void update() override;
};

#endif // CHARACTER_HPP

