#pragma once

/// @brief Thin abstraction around ESP-IDF logging macros.
///
/// This is mostly here to provide a single place to adjust logging behaviour,
/// prefixes, or formatting, without touching application code everywhere.
namespace Logger {

void init();

// Future helpers might include:
//  - Scoped timing logs
//  - Conditional debug logging
//  - Redirection to UART / network, etc.

} // namespace Logger
