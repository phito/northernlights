#include "win32/lolsource.h"

#include <iostream>
#include <windows.h>
#include <tlhelp32.h>
#include "screensource.h"

DWORD FindProcessId(const char *processname)
{
	HANDLE hProcessSnap;
	PROCESSENTRY32 pe32;
	DWORD result = NULL;

	// Take a snapshot of all processes in the system.
	hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (INVALID_HANDLE_VALUE == hProcessSnap) return(FALSE);

	pe32.dwSize = sizeof(PROCESSENTRY32); // <----- IMPORTANT

	// Retrieve information about the first process,
	// and exit if unsuccessful
	if (!Process32First(hProcessSnap, &pe32))
	{
		CloseHandle(hProcessSnap);          // clean the snapshot object
		return(NULL);
	}

	do
	{
		if (0 == strcmp(processname, pe32.szExeFile))
		{
			result = pe32.th32ProcessID;
			break;
		}
	} while (Process32Next(hProcessSnap, &pe32));

	CloseHandle(hProcessSnap);

	return result;
}

void LolSource::run(Controller *controller)
{
	_controller = controller;

	ScreenSource screen;
	screen.run(_controller);

	DWORD access = PROCESS_VM_READ |
		PROCESS_QUERY_INFORMATION |
		PROCESS_VM_OPERATION;
	HANDLE proc = OpenProcess(access, FALSE, FindProcessId("League of Legends.exe"));

	/* alive
	int offsets[] = {
	0x02A144CC,
	0x3A98,
	0x50
	};*/

	// death timer
	int offsets[] = {
		0x0252375C,
		0x24,
		0x78
	};
	void *addr = (void*)offsets[0];
	int count = sizeof(offsets) / sizeof(*offsets);
	int value;
	SIZE_T read;

	for (int i = 1; i < count; i++)
	{
		ReadProcessMemory(proc, addr, &value, sizeof(value), &read);
		addr = (void*)(value + offsets[i]);
	}

	int counter = 0, prev;
	while (true)
	{
		prev = counter;
		ReadProcessMemory(proc, addr, &counter, sizeof(counter), &read);

		// counter tick        
		if (counter != prev)
		{
			// just died
			if (counter && prev == 0)
			{
				screen.disable();
			}

			if (counter)
			{
				char red = 255;
				for (int i = 0; i < 30; i++)
				{
					_controller->set(Color(red, 0, 0));
					red -= 7;
					Sleep(16);
				}
			}
			// revived
			else
			{
				screen.enable();
			}
		}

		Sleep(16);
	}
}