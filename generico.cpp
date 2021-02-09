#include <iostream>
#include <Windows.h>
#include <winternl.h>
#pragma comment(lib,"ntdll.lib")

const char *Crypt(const char *buff) {
	PEB peb = { 0 };
	NtQueryInformationProcess(GetCurrentProcess(), ProcessBasicInformation, &peb, sizeof(PROCESS_BASIC_INFORMATION), NULL);
	char *out = (char*)calloc(sizeof(buff), sizeof(char*));
	if (out == nullptr) {
		return NULL;
	}
	for (unsigned int i = 0; i < strlen(buff); i++) {
		out[i] = buff[i] ^ (DWORD32)&peb;
	}
	free(out);
	return out;
}

int main()
{
	const char *toCrypt = Crypt("KB1te");
	printf("%s\n",toCrypt);
	printf("%s\n", Crypt(toCrypt));
}

