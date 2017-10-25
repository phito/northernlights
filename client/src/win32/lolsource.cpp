#include "win32/lolsource.h"

#include <iostream>
#include <windows.h>

void LolSource::run(Controller *controller)
{    
    _controller = controller;

    DWORD access = PROCESS_VM_READ |
                   PROCESS_QUERY_INFORMATION |
                   PROCESS_VM_OPERATION;
    HANDLE proc = OpenProcess(access, FALSE, 5352);

	/* alive
	int offsets[] = {
	0x02A144CC,
	0x3A98,
	0x50
	};*/

	int offsets[] = {
		0x02A1375C,
		0x6C,
		0x4,
		0x0,
		0x18
	};
	void *addr = (void*)offsets[0];
	int count = sizeof(offsets)/sizeof(*offsets);
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


		if (counter != prev)
		{
			// counter tick
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
				char red = 45;
				for (int i = 0; i < 9; i++)
				{
					_controller->set(Color(red, 0, 0));
					red -= 5;
					Sleep(16);
				}

				char green = 0;
				for (int i = 0; i < 255; i++)
				{
					_controller->set(Color(0, green, 0));
					green++;
					Sleep(16);
				}
			}
		}

		Sleep(16);
	}
}