
#ifndef BOILER_WINDOW
#define BOILER_WINDOW

struct Window {
    int width;
    int height;
    void *instance;
};

typedef struct Window * WindowPtr;

WindowPtr WindowCreate(int width, int height);

void WindowDestroy(WindowPtr windowPtr);

#endif
