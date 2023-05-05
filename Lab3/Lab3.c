#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <memory.h>
int main() {
	int ch;
	scanf_s("%i", &ch);
	SIZE_T size = (SIZE_T)1 << (SIZE_T)ch;
	void* ptr = VirtualAlloc(0,size , MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
	if (!ptr) {
		printf("Could not allocate memory!");
		return -1;
	}
	char* str = ptr;
	memset(str, 'a', size);
	memcpy(str, "GU khau darshan",16);
	printf_s("%s", str, size);
	ch = getchar();
	ch = getchar();
	ch = getchar();

	VirtualFree(ptr, 4096, MEM_RELEASE);

	return 0;

}