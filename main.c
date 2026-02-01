#include <stdio.h>
#include <stdlib.h>
#include "scheduler.h"
#include <stdbool.h>
#include <windows.h>

volatile bool rtos_running = true;

DWORD WINAPI rtos_thread(LPVOID arg) {
	while (rtos_running) {
		schedule();
		Sleep(100);
	}
	return 0;
}

DWORD WINAPI cancel_thread(LPVOID arg) {
	char buffer[128];
	printf("Type to Cancel: ");
	fgets(buffer, sizeof(buffer), stdin);
	rtos_running = false;
	return 0;
}

int main(void) {
	HANDLE hRTOS = CreateThread(NULL, 0, rtos_thread, NULL, 0, NULL);
	HANDLE hInput = CreateThread(NULL, 0, cancel_thread, NULL, 0, NULL);

	if (hRTOS == NULL) {
		return 1;
	}

	if (hInput == NULL) {
		CloseHandle(hRTOS);
		return 1;
	}

	WaitForSingleObject(hRTOS, INFINITE);
	WaitForSingleObject(hInput, INFINITE);
	CloseHandle(hRTOS);
	CloseHandle(hInput);
	return 0;
}