#ifndef VECTOR2D_HPP
#define VECTOR2D_HPP

/**
 * Vector2d - A 2D vector class for Campus Quest
 * 
 * Represents a position or direction in 2D space with x and y coordinates.
 * Supports vector arithmetic (addition, subtraction) and distance calculation.
 */
class Vector2d {
private:
    double x;  // X coordinate
    double y;  // Y coordinate

public:
    // ========== CONSTRUCTORS ==========
    
    /**
     * Default constructor - initializes vector to origin (0, 0)
     */
    Vector2d();
    
    /**
     * Parameterized constructor - initializes vector with specific coordinates
     * @param x The x coordinate
     * @param y The y coordinate
     */
    Vector2d(double x, double y);
    
    
    // ========== ACCESSORS (GETTERS) ==========
    
    /**
     * Get the X coordinate
     * @return The x value
     * const: This method doesn't modify the object
     */
    double getX() const;
    
    /**
     * Get the Y coordinate
     * @return The y value
     * const: This method doesn't modify the object
     */
    double getY() const;
    
    
    // ========== MUTATORS (SETTERS) ==========
    
    /**
     * Set the X coordinate with validation
     * @param x The new x value (must be a finite number)
     */
    void setX(double x);
    
    /**
     * Set the Y coordinate with validation
     * @param y The new y value (must be a finite number)
     */
    void setY(double y);
    
    
    // ========== OPERATOR OVERLOADING ==========
    
    /**
     * Vector addition operator
     * @param other The vector to add
     * @return A new vector that is the sum of this vector and other
     * 
     * Example: v1(3,4) + v2(1,2) = v3(4,6)
     */
    Vector2d operator+(const Vector2d& other) const;
    
    /**
     * Vector subtraction operator
     * @param other The vector to subtract
     * @return A new vector that is the difference of this vector and other
     * 
     * Example: v1(3,4) - v2(1,2) = v3(2,2)
     */
    Vector2d operator-(const Vector2d& other) const;
    
    
    // ========== DISTANCE CALCULATION ==========
    
    /**
     * Calculate Euclidean distance to another vector
     * @param other The target vector
     * @return The distance between this vector and other
     * 
     * Formula: sqrt((x2-x1)² + (y2-y1)²)
     */
    double distance(const Vector2d& other) const;
};

#endif // VECTOR2D_HPP

