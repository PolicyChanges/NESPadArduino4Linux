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

volatile sig_atomic_t done = 0;



void handle_sigterm(int signum)
{
	printf("exiting...", stdout);
	// XCloseDisplay(display);
	done = 1;
}


int main()
{
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

	
	while(!done) {
		ssize_t size = read( device_descriptor, &input, 1);

		
		switch(input) {

			/*
			case 'A': printf("A pressed\n");break;
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
			case '5': printf("R Released\n");break;
			*/
			
			case 'A': writer(KEY_X, WonderRabbitProject::key::writer_t::state_t::down); break;
			case '0': writer(KEY_X, WonderRabbitProject::key::writer_t::state_t::up); break;
				
			case 'B': writer(KEY_Z, WonderRabbitProject::key::writer_t::state_t::down); break;
			case '1': writer(KEY_Z, WonderRabbitProject::key::writer_t::state_t::up); break;
			
			case 'E': writer(KEY_ESC, WonderRabbitProject::key::writer_t::state_t::up); break;
			case '7': writer(KEY_ESC, WonderRabbitProject::key::writer_t::state_t::down); break;
			
			case 'S': writer(KEY_ENTER, WonderRabbitProject::key::writer_t::state_t::down); break;
			case '6': writer(KEY_ENTER, WonderRabbitProject::key::writer_t::state_t::up); break;
			
			case 'U': writer(KEY_UP, WonderRabbitProject::key::writer_t::state_t::down); break;
			case '2': writer(KEY_UP, WonderRabbitProject::key::writer_t::state_t::up);	 break;
			
			case 'D': writer(KEY_DOWN, WonderRabbitProject::key::writer_t::state_t::down); break;
			case '3': writer(KEY_DOWN, WonderRabbitProject::key::writer_t::state_t::up); break;
			
			case 'L': writer(KEY_LEFT, WonderRabbitProject::key::writer_t::state_t::down); break;
			case '4': writer(KEY_LEFT, WonderRabbitProject::key::writer_t::state_t::up); break;
			
			case 'R': writer(KEY_RIGHT, WonderRabbitProject::key::writer_t::state_t::down); break;
			case '5': writer(KEY_RIGHT, WonderRabbitProject::key::writer_t::state_t::up); break;

			//default:break;
		}
		//sleep(1);
		usleep(10000); 
	}
	return 0;
}

