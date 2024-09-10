// SceneCreator.c

#include "SceneCreator.h"
#include "OledDisplayManager.h"
#include "fonts.h"

void createWelcomeScene() {
    Scene welcomeScene;
    welcomeScene.draw = drawWelcomeScene; // Set the draw function
    welcomeScene.duration = 5000; // Display the scene for 5000 ms
    OledDisplayManager_AddScene(welcomeScene);
}

void drawWelcomeScene() {
    SSD1306_GotoXY (0,0);
    SSD1306_Puts ("Kompetter-X", &Font_11x18, 1);
    SSD1306_GotoXY (0, 20);
    SSD1306_Puts ("v.02", &Font_7x10, 1);
    SSD1306_UpdateScreen(); // Update the screen after drawing the scene
}
