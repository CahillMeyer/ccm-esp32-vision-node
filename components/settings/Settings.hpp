/**
 * @file Settings.hpp
 * @brief Persistent configuration manager using NVS.
 *
 * Handles loading and saving of application settings to flash memory.
 *
 * @author CCM Code (Christie Cahill Meyer)
 * @date 2025
 * @copyright MIT License
 */

#pragma once

#include "CvPipeline.hpp" // For PipelineConfig struct
#include <esp_err.h>

/**
 * @brief Singleton manager for persistent application settings.
 */
class Settings {
public:
    /**
     * @brief Get the singleton instance.
     */
    static Settings& get();

    /**
     * @brief Initialize NVS and load settings.
     * @return ESP_OK on success.
     */
    esp_err_t init();

    /**
     * @brief Load settings from NVS.
     * Populates the internal config object with defaults if NVS is empty.
     */
    esp_err_t load();

    /**
     * @brief Save current settings to NVS.
     */
    esp_err_t save();

    /**
     * @brief Access the current configuration (Read-Only).
     */
    const PipelineConfig& cfg() const { return m_config; }

    /**
     * @brief Access the current configuration (Modifiable).
     * Note: Call save() after modifying to persist changes.
     */
    PipelineConfig& cfg() { return m_config; }

    /**
     * @brief Reset settings to hardcoded defaults.
     */
    void resetDefaults();

private:
    Settings() = default; // Private constructor (Singleton)
    
    PipelineConfig m_config;
    const char* NVS_NAMESPACE = "ccm_cfg";
    const char* NVS_KEY = "pipe_cfg";
};