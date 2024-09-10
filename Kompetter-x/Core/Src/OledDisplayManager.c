#include "OledDisplayManager.h"
#include "queue.h"

static Queue sceneQueue; // Queue of scenes
static Scene currentScene; // Current scene being displayed
static uint32_t sceneStartTime; // Time when the current scene started

void OledDisplayManager_Init(void) {
    SSD1306_Init();
    SSD1306_Clear();
    queueInit(&sceneQueue, 2);
}

void OledDisplayManager_AddScene(Scene scene) {
	if (queueIsFull(&sceneQueue)) {
	        // TODO: Handle the error - queue is full
			// remove the last scene and add incoming scene instead
	        return;
	    }

	    // Add the scene to the queue
		queueEnqueue(&sceneQueue, scene);
}

void OledDisplayManager_Update(void) {
    uint32_t currentTime = HAL_GetTick();

    // If the current scene has finished (and it's not an infinite duration scene), get the next scene from the queue
    if (currentScene.duration != 0 && currentTime - sceneStartTime >= currentScene.duration) {
        if (!queueIsEmpty(&sceneQueue)) {
            currentScene = queueDequeue(&sceneQueue);
            sceneStartTime = currentTime;
        } else {
            // If the queue is empty, clear the current scene
            currentScene.draw = NULL;
            currentScene.duration = 0;
        }
    }

    // Draw the current scene
    if (currentScene.draw != NULL) {
        currentScene.draw();
    } else {
        // If there's no current scene, clear the display
        OledDisplayManager_Clear();
    }
}

void OledDisplayManager_Clear(void) {
    SSD1306_Clear();
}
