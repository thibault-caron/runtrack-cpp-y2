#ifndef MAX_HPP
#define MAX_HPP

/**
 * CustomTemplates Namespace
 * 
 * PROFESSIONAL APPROACH: Using namespaces to avoid name collisions!
 * 
 * Why namespace?
 * - Prevents collision with std::max
 * - Organizes code (like folders)
 * - Professional C++ practice
 * - Used by all major libraries (std::, boost::, etc.)
 * 
 * Usage:
 *   CustomTemplates::max(5, 10)    // Our max
 *   std::max(5, 10)                // Standard library max
 *   No conflict! Both can coexist!
 */
namespace CustomTemplates {


template<typename T>
T max(T a, T b) {
    // Compare using operator>
    // T must have operator> defined, or compilation will fail
    return (a > b) ? a : b;
    
    // Ternary operator breakdown:
    // (condition) ? valueIfTrue : valueIfFalse
    // 
    // If a > b: return a
    // Otherwise: return b
}


} // namespace CustomTemplates

#endif 

