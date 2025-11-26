idf_component_register(
    SRCS
        "Settings.cpp"
    INCLUDE_DIRS
        "."
    REQUIRES
        nvs_flash
        cv_pipeline  # Needs access to the PipelineConfig struct definition
        utils        # For logging
)