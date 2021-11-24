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

#include <libevdev/libevdev.h>
#include <libevdev/libevdev-uinput.h>

#include <WonderRabbitProject/key.hxx>

#ifndef WIN32
#define DEVICE_PATH "/dev/ttyACM0"
#endif

//Display *display;
//Window focusWindow;
//unsigned int keycode;
//unsigned int key_mappings[8];
volatile sig_atomic_t done = 0;

int err;
struct libevdev *dev;
struct libevdev_uinput *uidev;

void handle_sigterm(int signum)
{
	printf("exiting...", stdout);
	// XCloseDisplay(display);
	done = 1;
}


void init (){
	/*
	dev = libevdev_new();
    libevdev_set_name(dev, "fake keyboard device");
	
	libevdev_enable_event_type(dev, EV_KEY);
    for(uint key = 1; key < 255; ++key) {
        libevdev_enable_event_code(dev, EV_KEY, key, NULL);
    }
	
	err = libevdev_uinput_create_from_device(dev,
	LIBEVDEV_UINPUT_OPEN_MANAGED,
	&uidev);

    if (err != 0) {
		printf("libevdev returned and error\n");
        return;
    }
	*/
	//display = XOpenDisplay(NULL);
	//int revert;
	//XGetInputFocus(display, &focusWindow, &revert);
	
	//keycode = XKeysymToKeycode(display, XK_Pause);
	//key_mappings[0] = XKeysymToKeycode(display, XK_X); // X 
	//key_mappings[1] = XKeysymToKeycode(display, XK_Z); // Z
	//key_mappings[2] = XKeysymToKeycode(display, XK_Escape); // ESC
	//key_mappings[3] = XKeysymToKeycode(display, XK_KP_Enter); // Enter
	//key_mappings[4] = XKeysymToKeycode(display, XK_KP_Up); // Up
	//key_mappings[5] = XKeysymToKeycode(display, XK_KP_Down); // Down
	//key_mappings[6] = XKeysymToKeycode(display, XK_KP_Left); // Left
	//key_mappings[7] = XKeysymToKeycode(display, XK_KP_Right); // Right
	
}

int main()
{
	init();
	const auto& writer = WonderRabbitProject::key::writer_t::instance();
	
	int device_descriptor = open(DEVICE_PATH, O_NONBLOCK);
	//FILE *device_descriptor = fopen(DEVICE_PATH, "r"); 
	char buffer[1024];
	char input;	
	
	struct sigaction action;
	memset(&action, 0, sizeof(struct sigaction));
	action.sa_handler = handle_sigterm;
	sigaction(SIGTERM, &action, NULL);

	if(device_descriptor == -1)
		printf("Failed to get device descriptor with error %d\n", device_descriptor);

	/*enum class state_t: uint_fast8_t
	{ down_and_up = 0
	, down  = 1
	, up    = 2
	, press = down_and_up
	};*/
	//WonderRabbitProject::key::writer_t::state_t::down
	while(!done) {
		ssize_t size = read( device_descriptor, &input, 1);
		//input = getc(device_descriptor); 
		//printf("Byte: 0x%02X\n",input);
		//printf("Char: %c\n",input);	
		
		switch(input) {
		/*	case 'A': libevdev_uinput_write_event(uidev, EV_KEY, KEY_X, 1);break;
			case 'B': libevdev_uinput_write_event(uidev, EV_KEY, KEY_Z, 1);break;
			case 'E': libevdev_uinput_write_event(uidev, EV_KEY, KEY_ESC, 1);break;
			case 'S': libevdev_uinput_write_event(uidev, EV_KEY, KEY_ENTER, 1);break;
			case 'U': libevdev_uinput_write_event(uidev, EV_KEY, KEY_UP, 1);break;
			case 'D': libevdev_uinput_write_event(uidev, EV_KEY, KEY_DOWN, 1);break;
			case 'L': libevdev_uinput_write_event(uidev, EV_KEY, KEY_LEFT, 1);break;
			case 'R': libevdev_uinput_write_event(uidev, EV_KEY, KEY_RIGHT, 1);break;

			case '0': libevdev_uinput_write_event(uidev, EV_KEY, KEY_X, 0);break;
			case '1': libevdev_uinput_write_event(uidev, EV_KEY, KEY_Z, 0);break;
			case '7': libevdev_uinput_write_event(uidev, EV_KEY, KEY_ESC, 0);break;
			case '6': libevdev_uinput_write_event(uidev, EV_KEY, KEY_ENTER, 0);break;
			case '2': libevdev_uinput_write_event(uidev, EV_KEY, KEY_UP, 0);break;
			case '3': libevdev_uinput_write_event(uidev, EV_KEY, KEY_DOWN, 0);break;
			case '4': libevdev_uinput_write_event(uidev, EV_KEY, KEY_LEFT, 0);break;
			case '5': libevdev_uinput_write_event(uidev, EV_KEY, KEY_RIGHT, 0);break;
			*/	
	/*case 'A': printf("A pressed\n");break;
case 'B': printf("B pressed\n");break;

case 'E': printf("E pressed\n");break;
case 'S': printf("S pressed\n");break;
case 'U': printf("U pressed\n");break;
case 'D': printf("D pressed\n");break;
case 'L': printf("L pressed\n");break;
case 'R': printf("R pressed\n");break;

case '0': printf("A Released\n");break;
case '1': printf("B Released\n");break;
case '7': printf("E Released\n");break;
case '6': printf("S Released\n");break;
case '2': printf("U Released\n");break;
case '3': printf("D Released\n");break;
case '4': printf("L Released\n");break;
case '5': printf("R Released\n");break;*/
				
			
			case 'A': writer("x", WonderRabbitProject::key::writer_t::state_t::down); break;
			case 'B': writer("z", WonderRabbitProject::key::writer_t::state_t::down); break;
			//case 'E': writer("esacpe"); printf("E pressed\n");break;
			case 'S': writer("enter", WonderRabbitProject::key::writer_t::state_t::down); break;
			case 'U': writer("up", WonderRabbitProject::key::writer_t::state_t::down); break;
			case 'D': writer("down", WonderRabbitProject::key::writer_t::state_t::down); break;
			case 'L': writer("left", WonderRabbitProject::key::writer_t::state_t::down); break;
			case 'R': writer("right", WonderRabbitProject::key::writer_t::state_t::down); break;

			//case '0': writer("x", WonderRabbitProject::key::writer_t::state_t::up); break;
			//case '1': writer("z", WonderRabbitProject::key::writer_t::state_t::up); break;
			//case '7': writer("esacpe"); break;
			//case '6': writer("enter", WonderRabbitProject::key::writer_t::state_t::up); break;
			case '2': writer("up", WonderRabbitProject::key::writer_t::state_t::up);	 break;
			case '3': writer("down", WonderRabbitProject::key::writer_t::state_t::up); break;
			case '4': writer("left", WonderRabbitProject::key::writer_t::state_t::up); break;
			case '5': writer("right", WonderRabbitProject::key::writer_t::state_t::up); break;

				/*
			case 'A': XTestFakeKeyEvent(display, key_mappings[0], True, CurrentTime); printf("A pressed: %d\n",display);break;
			case 'B': XTestFakeKeyEvent(display, key_mappings[1], True, CurrentTime); printf("B pressed\n");break;
			case 'E': XTestFakeKeyEvent(display, key_mappings[2], True, CurrentTime); break;
			case 'S': XTestFakeKeyEvent(display, key_mappings[3], True, CurrentTime); break;
			case 'U': XTestFakeKeyEvent(display, key_mappings[4], True, CurrentTime); break;
			case 'D': XTestFakeKeyEvent(display, key_mappings[5], True, CurrentTime); break;
			case 'L': XTestFakeKeyEvent(display, key_mappings[6], True, CurrentTime); break;
			case 'R': XTestFakeKeyEvent(display, key_mappings[7], True, CurrentTime); break;
				
			case '0': XTestFakeKeyEvent(display, key_mappings[0], False, CurrentTime); printf("A Released\n");break;
			case '1': XTestFakeKeyEvent(display, key_mappings[1], False, CurrentTime); printf("B Released\n");break;
			case '7': XTestFakeKeyEvent(display, key_mappings[2], False, CurrentTime); break;
			case '6': XTestFakeKeyEvent(display, key_mappings[3], False, CurrentTime); break;
			case '2': XTestFakeKeyEvent(display, key_mappings[4], False, CurrentTime); break;
			case '3': XTestFakeKeyEvent(display, key_mappings[5], False, CurrentTime); break;
			case '4': XTestFakeKeyEvent(display, key_mappings[6], False, CurrentTime); break;
			case '5': XTestFakeKeyEvent(display, key_mappings[7], False, CurrentTime); break;*/
			//default:break;
		}
		//sleep(1);
		usleep(10000); 
		//printf("Buffer contents: 0x%X\n" , buffer);
	}
	 //XCloseDisplay(display);
	return 0;
}

