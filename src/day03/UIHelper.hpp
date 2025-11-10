#ifndef UIHELPER_HPP
#define UIHELPER_HPP

#include <string>
#include <iostream>

/**
 * UIHelper - Text-based User Interface Enhancement Module
 * 
 * JOB 11 - USER INTERFACE
 * 
 * Provides professional text UI features:
 * - ANSI color codes (terminal colors)
 * - Health bars (visual health representation)
 * - Enhanced borders (box-drawing characters)
 * - Status dashboard (comprehensive info display)
 * 
 * This transforms the game from basic text output
 * to a PROFESSIONAL terminal game interface!
 * 
 * Used by roguelikes, terminal games, CLI tools.
 */

namespace UI {
    
    // ========== ANSI COLOR CODES ==========
    
    /**
     * ANSI escape codes for terminal colors
     * 
     * Usage: cout << COLOR_RED << "Error!" << COLOR_RESET;
     * 
     * Works on:
     * - Mac/Linux terminals (full support)
     * - Windows 10+ (with VT100 enabled)
     * - Most modern terminals
     */
    
    // Text colors
    const std::string COLOR_RESET   = "\033[0m";
    const std::string COLOR_BLACK   = "\033[30m";
    const std::string COLOR_RED     = "\033[31m";
    const std::string COLOR_GREEN   = "\033[32m";
    const std::string COLOR_YELLOW  = "\033[33m";
    const std::string COLOR_BLUE    = "\033[34m";
    const std::string COLOR_MAGENTA = "\033[35m";
    const std::string COLOR_CYAN    = "\033[36m";
    const std::string COLOR_WHITE   = "\033[37m";
    
    // Bright colors
    const std::string COLOR_BRIGHT_RED    = "\033[91m";
    const std::string COLOR_BRIGHT_GREEN  = "\033[92m";
    const std::string COLOR_BRIGHT_YELLOW = "\033[93m";
    const std::string COLOR_BRIGHT_BLUE   = "\033[94m";
    const std::string COLOR_BRIGHT_CYAN   = "\033[96m";
    
    // Text styles
    const std::string STYLE_BOLD      = "\033[1m";
    const std::string STYLE_DIM       = "\033[2m";
    const std::string STYLE_UNDERLINE = "\033[4m";
    
    
    // ========== HEALTH BAR FUNCTIONS ==========
    
    /**
     * Draw ASCII health bar
     * 
     * @param current Current health
     * @param max Maximum health
     * @param barWidth Width of the bar in characters (default 10)
     * @param useColor Use color coding (green/yellow/red)
     * @return String representation of health bar
     * 
     * Example output:
     * [████████░░] 80/100 HP  (80% - green)
     * [████░░░░░░] 40/100 HP  (40% - yellow)
     * [█░░░░░░░░░] 10/100 HP  (10% - red)
     */
    std::string getHealthBar(int current, int max, int barWidth = 10, bool useColor = true);
    
    /**
     * Draw simple health bar without returning string
     * Directly outputs to console
     */
    void drawHealthBar(int current, int max, int barWidth = 10, bool useColor = true);
    
    /**
     * Get health color based on percentage
     * 
     * @param current Current health
     * @param max Maximum health
     * @return Color code (green/yellow/red)
     * 
     * > 60% = GREEN (healthy)
     * 30-60% = YELLOW (wounded)
     * < 30% = RED (critical)
     */
    std::string getHealthColor(int current, int max);
    
    
    // ========== BOX DRAWING ==========
    
    /**
     * Draw a title box with enhanced borders
     * 
     * @param title Title text
     * @param width Box width (default 50)
     * 
     * Example:
     * ╔════════════════════════════════╗
     * ║         TURN 1                 ║
     * ╚════════════════════════════════╝
     */
    void drawTitleBox(const std::string& title, int width = 50);
    
    /**
     * Draw a section header
     * 
     * @param title Section title
     * @param width Width (default 40)
     * 
     * Example:
     * ┌─────────────────────────────────┐
     * │      PLAYER STATUS              │
     * └─────────────────────────────────┘
     */
    void drawSectionHeader(const std::string& title, int width = 40);
    
    /**
     * Draw a horizontal separator
     * 
     * @param width Width (default 50)
     * @param style Character to use ('=' or '-')
     */
    void drawSeparator(int width = 50, char style = '=');
    
    
    // ========== STATUS DISPLAY ==========
    
    /**
     * Draw comprehensive status dashboard
     * 
     * Shows:
     * - Player info (health, position, weapon)
     * - Target info (if any)
     * - Enemy count
     * - Turn information
     * 
     * This is a "HUD" (Heads-Up Display) for text games!
     */
    void drawStatusDashboard(
        const std::string& playerName,
        int playerHealth,
        int playerMaxHealth,
        double playerX,
        double playerY,
        const std::string& weaponName,
        int weaponRange,
        int weaponPower,
        const std::string& targetName,
        int targetHealth,
        int targetMaxHealth,
        double targetDistance,
        int enemyCount,
        int currentTurn,
        int maxTurns
    );
    
    
    // ========== UTILITY FUNCTIONS ==========
    
    /**
     * Center text within a given width
     * @param text Text to center
     * @param width Total width
     * @return Centered text with padding
     */
    std::string centerText(const std::string& text, int width);
    
    /**
     * Colored text helper
     * @param text Text to color
     * @param color Color code
     * @return Colored text with reset
     */
    std::string colorText(const std::string& text, const std::string& color);
    
    /**
     * Progress bar (generic)
     * @param current Current value
     * @param max Maximum value
     * @param width Bar width
     * @param fillChar Character for filled portion
     * @param emptyChar Character for empty portion
     * @return Progress bar string
     */
    std::string getProgressBar(int current, int max, int width = 10, 
                               char fillChar = '#', char emptyChar = '-');
    
} // namespace UI

#endif // UIHELPER_HPP

