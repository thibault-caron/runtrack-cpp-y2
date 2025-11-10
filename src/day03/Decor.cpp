#include "Decor.hpp"
#include "UIHelper.hpp"  // JOB 11 - Enhanced UI
#include <iostream>

// ========== CONSTRUCTORS & DESTRUCTOR ==========

/**
 * Default constructor
 * Calls GameObject default constructor
 */
Decor::Decor() : GameObject(0.0, 0.0, "Decor") {
    // GameObject constructor sets position to (0, 0) and name to "Decor"
}

/**
 * Parameterized constructor
 */
Decor::Decor(double x, double y, const std::string& name)
    : GameObject(x, y, name) {
    // GameObject constructor sets position and name
    // Decor has no additional properties to initialize
}

/**
 * Destructor
 */
Decor::~Decor() {
    // No dynamic resources to clean up
}


// ========== OVERRIDE PURE VIRTUAL METHODS ==========

/**
 * Draw the decoration
 * 
 * Displays the decoration's name and position
 */
void Decor::draw() const {
    // JOB 11: Enhanced UI with colors
    std::cout << "[DECOR '" << UI::COLOR_GREEN << getName() << UI::COLOR_RESET << "'] ";
    std::cout << "Pos:(" << getX() << ", " << getY() << ")";
    std::cout << std::endl;
}

/**
 * Update the decoration
 * 
 * Decorations are STATIC environment elements.
 * They don't move, animate, or change state.
 * This method intentionally does nothing.
 */
void Decor::update() {
    // Decor objects don't update - they are static environment elements
    // No movement, no state changes
}

