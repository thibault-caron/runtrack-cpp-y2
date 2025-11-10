#include "GameManager.hpp"
#include "Character.hpp"
#include "Projectile.hpp"  // For projectile cleanup (Job 10)
#include <iostream>
#include <algorithm>
#include <cmath>  // For sqrt() in collision detection

// ========== CONSTRUCTORS & DESTRUCTOR ==========

GameManager::GameManager() {
    // Vector automatically initialized as empty
    std::cout << "[GameManager] Created" << std::endl;
}

/**
 * Destructor
 * 
 * This is BEAUTIFUL in modern C++:
 * - vector destructor is called
 * - Each unique_ptr destructor is called
 * - Each GameObject is automatically deleted
 * - NO MANUAL CLEANUP NEEDED!
 * 
 * This is RAII (Resource Acquisition Is Initialization) in action!
 */
GameManager::~GameManager() {
    std::cout << "[GameManager] Destroying " << objects.size() << " objects..." << std::endl;
    // unique_ptr automatically deletes all objects here!
    // No manual delete needed - automatic memory management!
}


// ========== ADDING OBJECTS ==========

/**
 * Add object using move semantics
 * 
 * Move semantics explained:
 * 1. Caller creates unique_ptr
 * 2. Caller calls std::move() to transfer ownership
 * 3. This function receives ownership
 * 4. Caller's pointer becomes nullptr
 * 5. GameManager now owns the object
 */
void GameManager::addObject(std::unique_ptr<GameObject> obj) {
    if (!obj) {
        std::cerr << "[GameManager] Warning: Attempted to add null object" << std::endl;
        return;
    }
    
    std::cout << "[GameManager] Adding object: " << obj->getName() << std::endl;
    
    // Move into vector (ownership transfer)
    // After this, 'obj' parameter becomes nullptr
    objects.push_back(std::move(obj));
}


// ========== GAME LOOP OPERATIONS ==========

/**
 * Update all objects
 * 
 * This is the heart of the game loop!
 * Called every frame/turn to update all game logic.
 */
void GameManager::updateAll() {
    // Range-based for loop with references
    // auto& means: reference to unique_ptr (no copying)
    for (auto& obj : objects) {
        if (obj) {  // Safety check (should always be true)
            obj->update();  // Polymorphic call - correct update() for each type!
        }
    }
}

/**
 * Draw all objects
 * 
 * Renders all game objects to screen.
 */
void GameManager::drawAll() {
    for (const auto& obj : objects) {  // const auto& for read-only
        if (obj) {
            obj->draw();  // Polymorphic call - correct draw() for each type!
        }
    }
}


// ========== CONTAINER OPERATIONS ==========

size_t GameManager::size() const {
    return objects.size();
}

bool GameManager::empty() const {
    return objects.empty();
}

/**
 * Clear all objects
 * 
 * Modern C++ magic:
 * - vector.clear() removes all elements
 * - Each unique_ptr is destroyed
 * - Each GameObject is automatically deleted
 * - NO MEMORY LEAKS!
 */
void GameManager::clear() {
    std::cout << "[GameManager] Clearing " << objects.size() << " objects" << std::endl;
    objects.clear();  // Automatic deletion of all objects!
}

/**
 * Get object by index
 * 
 * Returns RAW POINTER (not unique_ptr):
 * - Caller can use the object
 * - But GameManager still owns it
 * - No ownership transfer
 * - This is "borrowing" in Rust terminology
 */
GameObject* GameManager::getObject(size_t index) {
    if (index >= objects.size()) {
        throw std::out_of_range("GameManager::getObject - index out of range");
    }
    return objects[index].get();  // .get() returns raw pointer
}

const GameObject* GameManager::getObject(size_t index) const {
    if (index >= objects.size()) {
        throw std::out_of_range("GameManager::getObject - index out of range");
    }
    return objects[index].get();
}


// ========== ADVANCED OPERATIONS ==========

/**
 * Remove dead objects
 * 
 * Uses std::remove_if (erase-remove idiom):
 * - remove_if moves dead objects to end
 * - erase actually removes them
 * - unique_ptr automatically deletes removed objects!
 * 
 * This is a CLASSIC C++ idiom!
 */
size_t GameManager::removeDeadObjects() {
    size_t originalSize = objects.size();
    
    // Erase-remove idiom
    objects.erase(
        std::remove_if(
            objects.begin(),
            objects.end(),
            [](const std::unique_ptr<GameObject>& obj) {
                // Try to cast to Character to check if alive
                // dynamic_cast returns nullptr if not a Character
                if (const Character* character = dynamic_cast<const Character*>(obj.get())) {
                    if (!character->isAlive()) {
                        std::cout << "[GameManager] Removing dead object: " 
                                  << character->getName() << std::endl;
                        return true;  // Mark for removal
                    }
                }
                return false;  // Keep this object
            }
        ),
        objects.end()
    );
    
    size_t removed = originalSize - objects.size();
    return removed;
}

/**
 * Remove expired projectiles (JOB 10)
 * 
 * Removes projectiles that have already hit their target.
 * Uses the same erase-remove idiom as removeDeadObjects.
 * 
 * This is called after processing projectiles to clean them up.
 */
size_t GameManager::removeExpiredProjectiles() {
    size_t originalSize = objects.size();
    
    // Erase-remove idiom with dynamic_cast
    objects.erase(
        std::remove_if(
            objects.begin(),
            objects.end(),
            [](const std::unique_ptr<GameObject>& obj) {
                // Try to cast to Projectile
                if (const Projectile* projectile = dynamic_cast<const Projectile*>(obj.get())) {
                    // Check if projectile has expired (already hit)
                    if (projectile->isExpired()) {
                        std::cout << "[GameManager] Removing expired projectile: " 
                                  << projectile->getName() << std::endl;
                        return true;  // Mark for removal
                    }
                }
                return false;  // Keep this object
            }
        ),
        objects.end()
    );
    
    size_t removed = originalSize - objects.size();
    return removed;
}

/**
 * Find object by name
 * 
 * Linear search through all objects.
 * Returns raw pointer (doesn't transfer ownership).
 */
GameObject* GameManager::findByName(const std::string& name) {
    for (auto& obj : objects) {
        if (obj && obj->getName() == name) {
            return obj.get();  // Return raw pointer
        }
    }
    return nullptr;  // Not found
}

/**
 * Print statistics
 * 
 * Analyzes all objects and prints useful information.
 * Demonstrates type checking with dynamic_cast.
 */
void GameManager::printStats() const {
    std::cout << "\n╔════════════════════════════════════════╗" << std::endl;
    std::cout << "║       GAME MANAGER STATISTICS          ║" << std::endl;
    std::cout << "╚════════════════════════════════════════╝" << std::endl;
    
    std::cout << "Total objects: " << objects.size() << std::endl;
    
    // Count by type using dynamic_cast
    int players = 0, enemies = 0, characters = 0, others = 0;
    int alive = 0, dead = 0;
    
    for (const auto& obj : objects) {
        if (!obj) continue;
        
        // Check if it's a Character (has health/alive status)
        if (const Character* character = dynamic_cast<const Character*>(obj.get())) {
            characters++;
            if (character->isAlive()) {
                alive++;
            } else {
                dead++;
            }
            
            // Further type checking
            // Note: This would require including Player.hpp and Enemy.hpp
            // For now, we'll just count Characters
        } else {
            others++;  // Decor, etc.
        }
    }
    
    std::cout << "Characters: " << characters << std::endl;
    std::cout << "  - Alive: " << alive << std::endl;
    std::cout << "  - Dead: " << dead << std::endl;
    std::cout << "Other objects (Decor, etc.): " << others << std::endl;
    
    std::cout << "════════════════════════════════════════" << std::endl;
}


// ========== COLLISION DETECTION (JOB 09) ==========

/**
 * Check if two objects are colliding
 * 
 * Uses distance-based collision detection:
 * - Calculate distance between objects
 * - If distance < COLLISION_RADIUS, they're colliding
 * 
 * This is the STANDARD 2D collision detection for circular bounds!
 */
bool GameManager::checkCollision(const GameObject* a, const GameObject* b) const {
    if (!a || !b) {
        return false;  // Null objects don't collide
    }
    
    if (a == b) {
        return false;  // Object doesn't collide with itself
    }
    
    // Calculate distance between objects
    double dist = a->distance(*b);
    
    // Collision if distance is less than collision radius
    return dist < COLLISION_RADIUS;
}

/**
 * Check if object can move to position without colliding
 * 
 * Algorithm:
 * 1. Create temporary position at (newX, newY)
 * 2. Check distance from (newX, newY) to all other objects
 * 3. If any distance < COLLISION_RADIUS, movement blocked
 * 4. Otherwise, movement is valid
 * 
 * This is preventive collision detection - we check BEFORE moving!
 */
bool GameManager::canMoveTo(const GameObject* obj, double newX, double newY) const {
    if (!obj) {
        return false;  // Null object can't move
    }
    
    // Check collision with all other objects
    for (const auto& other : objects) {
        // Skip if checking against self
        if (other.get() == obj) {
            continue;
        }
        
        // Skip if other object is null
        if (!other) {
            continue;
        }
        
        // Calculate distance from new position to other object
        double dx = newX - other->getX();
        double dy = newY - other->getY();
        double distance = std::sqrt(dx * dx + dy * dy);
        
        // Check for collision
        if (distance < COLLISION_RADIUS) {
            // Would collide! Movement blocked
            return false;
        }
    }
    
    // No collisions detected, movement is valid
    return true;
}

/**
 * Get the object that would block movement
 * 
 * Similar to canMoveTo, but returns WHICH object is blocking.
 * Useful for providing feedback to player:
 * "Can't move there - Goblin in the way!"
 */
GameObject* GameManager::getBlockingObject(const GameObject* obj, double newX, double newY) const {
    if (!obj) {
        return nullptr;
    }
    
    // Check collision with all other objects
    for (const auto& other : objects) {
        // Skip if checking against self
        if (other.get() == obj) {
            continue;
        }
        
        // Skip if other object is null
        if (!other) {
            continue;
        }
        
        // Calculate distance from new position to other object
        double dx = newX - other->getX();
        double dy = newY - other->getY();
        double distance = std::sqrt(dx * dx + dy * dy);
        
        // Check for collision
        if (distance < COLLISION_RADIUS) {
            // Found the blocking object!
            return other.get();  // Return raw pointer
        }
    }
    
    // No blocking object
    return nullptr;
}

