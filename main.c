#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


// IF YOU RUN THIS, CURRENTLY IT WOULD PREVENT ANY KEYBOARD ACTIONS IN SYSTEM
//
// Requires libx11-dev

int main() {
	Display *display;
	Window root;
	display = XOpenDisplay(NULL);
	if (display == NULL) {
		fprintf(stderr, "Cannot open display\n");
		exit(1);
	}

	root = DefaultRootWindow(display);
	XEvent event;
	KeySym key;
	char key_text[255];

	for (int i = 0; i < 0xFFFF; i++){
		XGrabKey(display, XKeysymToKeycode(display, i), AnyModifier, root, True, GrabModeAsync, GrabModeAsync);
	}

	XSelectInput(display, root, KeyPressMask);
	while (1) {
		printf("Listening...\n");
		XNextEvent(display, &event);
		if (event.type == KeyPress) {
			XLookupString(&event.xkey, key_text, sizeof(key_text), &key, NULL);
		
			printf("Entered: %s\n", key_text);


//XKeyEvent knt = event.xkey;
//			knt.window = RootWindow(display, DefaultScreen(display));
//			XSendEvent(display, knt.window, True, KeyPressMask, (XEvent *) &knt);
//			XFlush(display);
			// Cleaning Text
			memset(key_text, 0, sizeof(key_text));
		}
	}

	XCloseDisplay(display);

	return 0;

}
