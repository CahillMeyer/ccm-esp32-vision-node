/**
 * @file Settings.cpp
 * @brief Implementation of NVS persistent settings.
 *
 * @author CCM Code (Christie Cahill Meyer)
 * @date 2025
 * @copyright MIT License
 */

#include "Settings.hpp"
#include <nvs_flash.h>
#include <nvs.h>
#include <esp_log.h>
#include <cstring>

static const char* TAG = "Settings";

Settings& Settings::get() {
    static Settings instance;
    return instance;
}

void Settings::resetDefaults() {
    // Define "Safe Factory Defaults"
    m_config.enable_grayscale = true;
    m_config.enable_threshold = false;
    m_config.threshold_val = 128;
    m_config.invert = false;
    
    m_config.enable_roi = false;
    m_config.roi_x = 0;
    m_config.roi_y = 0;
    m_config.roi_w = 320; // Default to QVGA width
    m_config.roi_h = 240; // Default to QVGA height
    
    m_config.downsample_factor = 1;
    
    m_config.enable_blob_detection = false;
    m_config.min_blob_area = 10;
    
    ESP_LOGI(TAG, "Settings reset to defaults");
}

esp_err_t Settings::init() {
    // 1. Initialize NVS partition
    esp_err_t err = nvs_flash_init();
    if (err == ESP_ERR_NVS_NO_FREE_PAGES || err == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        // NVS partition was truncated and needs to be erased
        ESP_LOGW(TAG, "Erasing NVS flash to recover...");
        ESP_ERROR_CHECK(nvs_flash_erase());
        err = nvs_flash_init();
    }
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "Failed to init NVS: %s", esp_err_to_name(err));
        return err;
    }

    // 2. Load existing values
    return load();
}

esp_err_t Settings::load() {
    nvs_handle_t handle;
    esp_err_t err = nvs_open(NVS_NAMESPACE, NVS_READONLY, &handle);
    
    if (err == ESP_ERR_NVS_NOT_FOUND) {
        ESP_LOGW(TAG, "No config found in NVS, using defaults.");
        resetDefaults();
        return save(); // Save defaults so NVS is initialized next time
    }
    else if (err != ESP_OK) {
        ESP_LOGE(TAG, "Error opening NVS handle: %s", esp_err_to_name(err));
        return err;
    }

    // Read Blob
    size_t required_size = sizeof(PipelineConfig);
    err = nvs_get_blob(handle, NVS_KEY, &m_config, &required_size);
    
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "Failed to read config blob: %s", esp_err_to_name(err));
        resetDefaults();
    } else {
        ESP_LOGI(TAG, "Config loaded from NVS");
    }

    nvs_close(handle);
    return err;
}

esp_err_t Settings::save() {
    nvs_handle_t handle;
    esp_err_t err = nvs_open(NVS_NAMESPACE, NVS_READWRITE, &handle);
    if (err != ESP_OK) return err;

    err = nvs_set_blob(handle, NVS_KEY, &m_config, sizeof(PipelineConfig));
    if (err == ESP_OK) {
        err = nvs_commit(handle);
        ESP_LOGI(TAG, "Config saved to NVS");
    } else {
        ESP_LOGE(TAG, "Failed to write config blob");
    }

    nvs_close(handle);
    return err;
}