#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

#include <signal.h>
#include <unistd.h>
#include <string.h>

#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <X11/extensions/XTest.h>


#ifndef WIN32
#define DEVICE_PATH "/dev/ttyACM0"
#endif

Display *display;
unsigned int keycode;
unsigned int key_mappings[8];
volatile sig_atomic_t done = 0;

void handle_sigterm(int signum)
{
	printf("exiting...", stdout);	
	done = 1;
}


void init (){
	display = XOpenDisplay(NULL);
	//keycode = XKeysymToKeycode(display, XK_Pause);
	key_mappings[0] = XKeysymToKeycode(display, XK_A); // X 
	key_mappings[1] = XKeysymToKeycode(display, XK_B); // Z
	key_mappings[2] = XKeysymToKeycode(display, XK_Escape); // ESC
	key_mappings[3] = XKeysymToKeycode(display, XK_KP_Enter); // Enter
	key_mappings[4] = XKeysymToKeycode(display, XK_KP_Up); // Up
	key_mappings[5] = XKeysymToKeycode(display, XK_KP_Down); // Down
	key_mappings[6] = XKeysymToKeycode(display, XK_KP_Left); // Left
	key_mappings[7] = XKeysymToKeycode(display, XK_KP_Right); // Right
	
}

int main()
{
	init();
	int device_descriptor = open(DEVICE_PATH, O_RDONLY);//O_NONBLOCK);
	//FILE *device_descriptor = fopen(DEVICE_PATH, "r"); 
	char buffer[1024];
	char input;	
	
	struct sigaction action;
	memset(&action, 0, sizeof(struct sigaction));
	action.sa_handler = handle_sigterm;
	sigaction(SIGTERM, &action, NULL);

	if(device_descriptor == -1)
		printf("Failed to get device descriptor with error %d\n", device_descriptor);

	while(!done) {
		ssize_t size = read( device_descriptor, &input, 1);
		//input = getc(device_descriptor); 
		//printf("Byte: 0x%02X\n",input);
		//printf("Char: %c\n",input);	
		switch(input) {
			case 'A': XTestFakeKeyEvent(display, key_mappings[0], True, 0); break;
			case 'B': XTestFakeKeyEvent(display, key_mappings[1], True, 0); break;
			case 'E': XTestFakeKeyEvent(display, key_mappings[2], True, 0); break;
			case 'S': XTestFakeKeyEvent(display, key_mappings[3], True, 0); break;
			case 'U': XTestFakeKeyEvent(display, key_mappings[4], True, 0); break;
			case 'D': XTestFakeKeyEvent(display, key_mappings[5], True, 0); break;
			case 'L': XTestFakeKeyEvent(display, key_mappings[6], True, 0); break;
			case 'R': XTestFakeKeyEvent(display, key_mappings[7], True, 0); break;
				
			case '0': XTestFakeKeyEvent(display, key_mappings[0], False, 0); break;
			case '1': XTestFakeKeyEvent(display, key_mappings[1], False, 0); break;
			case '2': XTestFakeKeyEvent(display, key_mappings[2], False, 0); break;
			case '3': XTestFakeKeyEvent(display, key_mappings[3], False, 0); break;
			case '4': XTestFakeKeyEvent(display, key_mappings[4], False, 0); break;
			case '5': XTestFakeKeyEvent(display, key_mappings[5], False, 0); break;
			case '6': XTestFakeKeyEvent(display, key_mappings[6], False, 0); break;
			case '7': XTestFakeKeyEvent(display, key_mappings[7], False, 0); break;
			default:
		}
		usleep(2000); 
		//printf("Buffer contents: 0x%X\n" , buffer);
	}
	
	return 0;
}

