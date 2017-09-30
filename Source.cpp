#include <cstdio>
#include <Windows.h>
#include <iostream>
#include <string>
void idk() {
	HWND window;
	char xd = NULL;
	std::string nameOfWindow; std::getline(std::cin, nameOfWindow);
	window = FindWindowA(NULL, nameOfWindow.c_str());
	if(window <= 0) {
		printf("window '%s' does not exist, try again\n\n", nameOfWindow.c_str());
		idk();
	}else{
	    printf("Window found.\n\nPress y/Y to disable it, and n/N to enable it. To quit the program press b/B\n\n");
	}
	while (std::cin>>xd) {
		if (xd == 'y' || xd == 'Y') {
			if (window) {
				EnableWindow(window, FALSE);
				printf("Window '%s' is now disabled\n", nameOfWindow.c_str());
			}
			else {
				printf("action failed\n");
				EnableWindow(window, TRUE);
			}
		}
		else if (xd == 'n' || xd == 'N') {
			EnableWindow(window, TRUE);
			printf("window '%s' is enabled again\n", nameOfWindow.c_str());
		}
		else if (xd == 'b' || xd == 'B')
			break;
	}
}

int main() {
	idk();
	getchar();
	return 0;
}
