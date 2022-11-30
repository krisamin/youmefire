#include "utils.h"

// 파일 읽기
inline WCHAR* GetReadFile(const char* fileName) {
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

// 파일 존재 확인
inline bool CheckFileExists(const char* fileName) {
	FILE* file;
	if ((file = fopen(fileName, "r"))) {
		fclose(file);
		return true;
	}
	return false;
}

// 파일 저장
inline void SaveFile(const char* fileName, const WCHAR* content) {
	FILE* fp;
	fopen_s(&fp, fileName, "w,ccs=UTF-8");
	fputws(content, fp);
	fclose(fp);
}