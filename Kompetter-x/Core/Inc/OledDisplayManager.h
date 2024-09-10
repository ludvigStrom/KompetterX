#ifndef OLED_DISPLAY_MANAGER_H
#define OLED_DISPLAY_MANAGER_H

#include "ssd1306.h"
#include "fonts.h"

#define MAX_ELEMENTS 10

typedef struct {
    char* text;
    FontDef_t* font;
    uint8_t x;
    uint8_t y;
    char* variable; // Pointer to the variable to display
} SceneElement;

typedef struct {
    void (*draw)(void); // Function to draw the scene
    uint32_t duration;  // Duration to display the scene (in milliseconds), 0 for infinite duration
    uint8_t num_elements; // Number of elements in the scene
    SceneElement elements[MAX_ELEMENTS]; // Array of elements in the scene
} Scene;

// Initialize the OLED display manager
void OledDisplayManager_Init(void);

// Add a scene to the queue
void OledDisplayManager_AddScene(Scene scene);

// Update the display with the current scene
void OledDisplayManager_Update(void);

// Clear the display
void OledDisplayManager_Clear(void);

#endif // OLED_DISPLAY_MANAGER_H
