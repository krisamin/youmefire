#include "easyDefine.h"

WCHAR* ReadStoryFile() {
	WCHAR* temp = (WCHAR*)malloc(sizeof(WCHAR) * 0);
	FILE* fp;
	fopen_s(&fp, "story.txt", "r,ccs=UTF-8");

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

int ReadStory() {
	Layer background = { true, 0, L"image", L"images/solid/101010.bmp", 0, 0, 100 };
	Layer hider = { true, 9, L"image", L"images/solid/101010.bmp", 0, 0, 100 };
	Layer dialog = { true, 7, L"image", L"images/dialog/dialog.bmp", 72, 700, 60 };
	Layer nameTag = { true, 8, L"image", L"images/dialog/viichan.bmp", 120, 671, 100 };
	Layer hoverText = { true, 10, L"text", L"Pretendard Bold", 960, 540, 100, L"", 50, 400, 0, TA_CENTER, 1, RGB(255, 255, 255) };
	Layer dialogText = { true, 10, L"text", L"Pretendard SemiBold", 110, 760, 100, L"", 50, 400, 0, TA_LEFT, 0, RGB(0, 0, 0) };
	easyImage.reset(&easyImage);

	WCHAR* story = ReadStoryFile();

	WCHAR* bufferLine;
	WCHAR* splitLine = wcstok(story, L"\n", &bufferLine);
	while (splitLine != NULL) {
		bool ok = true;
		if (wcscmp(splitLine, L"#START") == 0) {
			printf("START\n");
		}
		else if (wcscmp(splitLine, L"#END") == 0) {
			return 0;
		}
		else if (wcscmp(splitLine, L"#IMAGE") == 0) {
			splitLine = wcstok(NULL, L"\n", &bufferLine);

			WCHAR* buffer;
			WCHAR* type = wcstok(splitLine, L":", &buffer);
			Layer* target = NULL;
			if (wcscmp(type, L"RENDER") == 0) {
				easyImage.render(&easyImage);
			}
			else if (wcscmp(type, L"HIDER") == 0) {
				target = &hider;
			}
			else if (wcscmp(type, L"BACKGROUND") == 0) {
				target = &background;
			}
			else if (wcscmp(type, L"HOVERTEXT") == 0) {
				target = &hoverText;
			}
			else if (wcscmp(type, L"DIALOGTEXT") == 0) {
				target = &dialogText;
			}
			else if (wcscmp(type, L"DIALOG") == 0) {
				target = &dialog;
			}
			else if (wcscmp(type, L"NAMETAG") == 0) {
				target = &nameTag;
			}
			if (target) {
				type = wcstok(NULL, L":", &buffer);
				if (wcscmp(type, L"OPACITY") == 0) {
					type = wcstok(NULL, L":", &buffer);
					if (wcscmp(type, L"SET") == 0) {
						int opacity = _wtoi(wcstok(NULL, L":", &buffer));
						target->opacity = opacity;
						easyImage.setLayer(&easyImage, *target);
						easyImage.render(&easyImage);
					}
					else if (wcscmp(type, L"FADE") == 0) {
						int from = _wtoi(wcstok(NULL, L":", &buffer));
						int to = _wtoi(wcstok(NULL, L":", &buffer));
						FadeImage(from, to, target);
					}
				}
				else if (wcscmp(type, L"PATH") == 0) {
					WCHAR* path = wcstok(NULL, L":", &buffer);
					target->name = path;
					easyImage.setLayer(&easyImage, *target);
				}
				else if (wcscmp(type, L"ENABLE") == 0) {
					target->enable = true;
					easyImage.setLayer(&easyImage, *target);
				}
				else if (wcscmp(type, L"DISABLE") == 0) {
					target->enable = false;
					easyImage.setLayer(&easyImage, *target);
				}
			}
		}
		else if (wcscmp(splitLine, L"#TEXT") == 0) {
			splitLine = wcstok(NULL, L"\n", &bufferLine);

			WCHAR* buffer;
			WCHAR* command = wcstok(splitLine, L":", &buffer);
			Layer* target = NULL;
			if (wcscmp(command, L"HOVER") == 0) {
				target = &hoverText;
			}
			else if (wcscmp(command, L"DIALOG") == 0) {
				target = &dialogText;
			}
			if (target) {
				WCHAR* content = wcstok(NULL, L":", &buffer);
				target->enable = true;
				StepPrint(content, *target);
			}
		}
		else if (wcscmp(splitLine, L"#AUDIO") == 0) {
			splitLine = wcstok(NULL, L"\n", &bufferLine);

			WCHAR* buffer;
			WCHAR* alias = wcstok(splitLine, L":", &buffer);
			WCHAR* command = wcstok(NULL, L":", &buffer);
			if (wcscmp(command, L"START") == 0) {
				WCHAR* type = wcstok(NULL, L":", &buffer);
				if (wcscmp(type, L"BGM") == 0) {
					PlayAudio(alias, true);
				}
				else if (wcscmp(type, L"EFFECT") == 0) {
					PlayAudio(alias, false);
				}
			}
			else if (wcscmp(command, L"VOLUME") == 0) {
				WCHAR* type = wcstok(NULL, L":", &buffer);
				if (wcscmp(type, L"SET") == 0) {
					int volume = _wtoi(wcstok(NULL, L":", &buffer));
					VolumeAudio(alias, volume);
				}
				else if (wcscmp(type, L"FADE") == 0) {
					int from = _wtoi(wcstok(NULL, L":", &buffer));
					int to = _wtoi(wcstok(NULL, L":", &buffer));
					FadeAudio(alias, from, to);
				}
			}
		}
		else if (wcscmp(splitLine, L"#CLICK") == 0) {
			WaitClick();
		}
		else if (wcscmp(splitLine, L"#SLEEP") == 0) {
			int sleep = _wtoi(wcstok(NULL, L"\n", &bufferLine));
			Sleep(sleep);
		}
		else {
			ok = false;
		}
		//if (ok) Sleep(100);
		splitLine = wcstok(NULL, L"\n", &bufferLine);
	}

	Sleep(1000000);
}