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
	}
	while (std::cin>>xd) {
		if (xd == 'y' || xd == 'Y') {
			if (window) {
				EnableWindow(window, FALSE);
				printf("Window is now disabled\n");
			}
			else {
				printf("action failed\n");
				EnableWindow(window, TRUE);
			}
		}
		else if (xd == 'n' || xd == 'N') {
			EnableWindow(window, TRUE);
			printf("window is enabled again\n");
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