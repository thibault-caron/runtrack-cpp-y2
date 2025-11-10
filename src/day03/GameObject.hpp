#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include "Vector2d.hpp"
#include <string>

/**
 * GameObject - Abstract base class for all interactive game objects
 * 
 * This is an ABSTRACT CLASS - cannot be instantiated directly.
 * All game objects (players, enemies, decorations) inherit from this.
 * 
 * Inheritance: GameObject "is-a" Vector2d
 * - Inherits position (x, y)
 * - Inherits all Vector2d methods (getters, setters, operators, distance)
 * - Adds game-specific behavior (draw, update)
 */
class GameObject : public Vector2d {
private:
    std::string name;  // Name/identifier for the game object

public:
    // ========== CONSTRUCTORS & DESTRUCTOR ==========
    
    /**
     * Default constructor - creates object at origin with no name
     */
    GameObject();
    
    /**
     * Parameterized constructor - creates object at specific position with name
     * @param x The x coordinate
     * @param y The y coordinate
     * @param name The name/identifier for this object
     */
    GameObject(double x, double y, const std::string& name);
    
    /**
     * Virtual destructor - CRITICAL for inheritance!
     * 
     * When deleting a GameObject pointer that points to a child class,
     * this ensures the child's destructor is called properly.
     * Without "virtual", only GameObject destructor would run (memory leak!)
     */
    virtual ~GameObject();
    
    
    // ========== NAME ACCESSORS ==========
    
    /**
     * Get the object's name
     * @return The name string
     */
    std::string getName() const;
    
    /**
     * Set the object's name
     * @param name The new name
     */
    void setName(const std::string& name);
    
    
    // ========== PURE VIRTUAL METHODS (ABSTRACT) ==========
    
    /**
     * Draw the game object
     * 
     * PURE VIRTUAL (= 0) means:
     * - GameObject does NOT provide implementation
     * - Every child class MUST implement this
     * - Makes GameObject an abstract class
     * 
     * Each child decides HOW to draw itself:
     * - Player might draw "P" or a sprite
     * - Enemy might draw "E" or different sprite
     * - Decoration might draw "D" or terrain tile
     */
    virtual void draw() const = 0;
    
    /**
     * Update the game object (called every frame)
     * 
     * PURE VIRTUAL (= 0) means:
     * - GameObject does NOT provide implementation
     * - Every child class MUST implement this
     * 
     * Each child decides HOW to update:
     * - Player might read keyboard input
     * - Enemy might run AI logic
     * - Decoration might do nothing (but must still implement)
     */
    virtual void update() = 0;
};

#endif // GAMEOBJECT_HPP

