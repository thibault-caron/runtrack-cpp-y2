#ifndef DECOR_HPP
#define DECOR_HPP

#include "GameObject.hpp"

/**
 * Decor - Concrete class for static decorative elements
 * 
 * Represents non-moving environment objects like trees, rocks, buildings.
 * This is a CONCRETE class - can be instantiated.
 * 
 * Inheritance chain: Decor -> GameObject -> Vector2d
 * 
 * Key characteristic: Decor objects don't move (update() does nothing)
 */
class Decor : public GameObject {
public:
    // ========== CONSTRUCTORS & DESTRUCTOR ==========
    
    /**
     * Default constructor - creates decor at origin
     */
    Decor();
    
    /**
     * Parameterized constructor
     * @param x The x coordinate
     * @param y The y coordinate
     * @param name The name/type of decoration (e.g., "Tree", "Rock")
     */
    Decor(double x, double y, const std::string& name);
    
    /**
     * Destructor
     */
    ~Decor();
    
    
    // ========== OVERRIDE PURE VIRTUAL METHODS ==========
    
    /**
     * Draw the decoration
     * Implementation of pure virtual from GameObject
     */
    void draw() const override;
    
    /**
     * Update the decoration
     * Implementation of pure virtual from GameObject
     * 
     * Decor objects are STATIC - they don't move or change state.
     * This method has an empty implementation.
     */
    void update() override;
};

#endif // DECOR_HPP

