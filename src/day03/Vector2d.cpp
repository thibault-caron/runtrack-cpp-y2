#include "Vector2d.hpp"
#include <cmath>      // For sqrt() and pow()
#include <stdexcept>  // For exceptions
#include <limits>     // For checking infinity/NaN

// ========== CONSTRUCTORS ==========

/**
 * Default constructor - creates vector at origin
 */
Vector2d::Vector2d() : x(0.0), y(0.0) {
    // Member initializer list: efficient way to initialize members
    // x(0.0) means: set x = 0.0
    // y(0.0) means: set y = 0.0
}

/**
 * Parameterized constructor - creates vector at specific coordinates
 */
Vector2d::Vector2d(double x, double y) : x(x), y(y) {
    // Note: x(x) means: this->x = parameter x
    // The first x is the member variable, second x is the parameter
    
    // Validate the inputs
    if (!std::isfinite(x) || !std::isfinite(y)) {
        throw std::invalid_argument("Vector2d coordinates must be finite numbers (not NaN or infinity)");
    }
}


// ========== ACCESSORS (GETTERS) ==========

double Vector2d::getX() const {
    return x;  // Simply return the x coordinate
}

double Vector2d::getY() const {
    return y;  // Simply return the y coordinate
}


// ========== MUTATORS (SETTERS) ==========

void Vector2d::setX(double x) {
    // Validation: Check if x is a valid finite number
    if (!std::isfinite(x)) {
        throw std::invalid_argument("X coordinate must be a finite number (not NaN or infinity)");
    }
    this->x = x;  // this->x refers to the member variable
}

void Vector2d::setY(double y) {
    // Validation: Check if y is a valid finite number
    if (!std::isfinite(y)) {
        throw std::invalid_argument("Y coordinate must be a finite number (not NaN or infinity)");
    }
    this->y = y;  // this->y refers to the member variable
}


// ========== OPERATOR OVERLOADING ==========

/**
 * Addition operator: Adds two vectors component-wise
 * 
 * When you write: v1 + v2
 * - v1 is "this" object
 * - v2 is "other" parameter
 * - Returns a NEW vector (doesn't modify v1 or v2)
 */
Vector2d Vector2d::operator+(const Vector2d& other) const {
    double newX = this->x + other.x;  // Add x components
    double newY = this->y + other.y;  // Add y components
    
    return Vector2d(newX, newY);  // Create and return new vector
}

/**
 * Subtraction operator: Subtracts two vectors component-wise
 * 
 * When you write: v1 - v2
 * - v1 is "this" object
 * - v2 is "other" parameter
 * - Returns a NEW vector (doesn't modify v1 or v2)
 */
Vector2d Vector2d::operator-(const Vector2d& other) const {
    double newX = this->x - other.x;  // Subtract x components
    double newY = this->y - other.y;  // Subtract y components
    
    return Vector2d(newX, newY);  // Create and return new vector
}


// ========== DISTANCE CALCULATION ==========

/**
 * Calculate Euclidean distance between two vectors
 * 
 * Formula: distance = sqrt((x2-x1)² + (y2-y1)²)
 * 
 * This is the "straight line" distance between two points
 */
double Vector2d::distance(const Vector2d& other) const {
    // Calculate differences
    double dx = other.x - this->x;  // Difference in x
    double dy = other.y - this->y;  // Difference in y
    
    // Apply Pythagorean theorem
    // pow(dx, 2) means dx²
    // sqrt() computes square root
    double dist = std::sqrt(std::pow(dx, 2) + std::pow(dy, 2));
    
    return dist;
}

