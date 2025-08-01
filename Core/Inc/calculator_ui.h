#pragma once

#ifndef CALCULATOR_UI_H
#define CALCULATOR_UI_H

#include <stdint.h>

/** Draw the static calculator UI (body, buttons, and initial value). */
void draw_calculator(void);

/**
 * Update the value shown in the calculator “screen” area.
 * Right-aligns the provided null-terminated ASCII string (e.g. "42", "3.14").
 * You’ll need to implement this if you want dynamic updates; it should
 * reuse the same 3x5 font logic from the UI implementation.
 */
void calculator_update_display(const char *value);

#endif // CALCULATOR_UI_H
