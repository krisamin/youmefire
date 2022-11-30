#include "utils.h"

inline WCHAR* GetReadFile(char* fileName) {
	WCHAR* temp = (WCHAR*)malloc(sizeof(WCHAR) * 0);
	FILE* fp;
	fopen_s(&fp, fileName, "r,ccs=UTF-8");

	int length = 0;
	while (true) {
		temp = (WCHAR*)realloc(temp, sizeof(WCHAR) * (length + 1));
		temp[length] = fgetwc(fp);
		if (temp[length] == WEOF) break;
		length++;
	}
	fclose(fp);
	temp[length] = "\0";
	return temp;
}