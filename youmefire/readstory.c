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

int ReadStory(int section) {
	WCHAR sectionList[2][10] = {L"INTRO", L"PROLOGUE"};
	wprintf(L"%s", sectionList[section]);

	Layer background = { true, 0, L"image", L"images/solid/101010.bmp", 0, 0, 100 };
	Layer hider = { true, 9, L"image", L"images/solid/101010.bmp", 0, 0, 100 };
	Layer dialog = { true, 7, L"image", L"images/dialog/dialog.bmp", 72, 700, 80 };
	Layer nameTag = { true, 8, L"image", L"images/dialog/viichan.bmp", 120, 671, 100 };
	Layer hoverText = { true, 10, L"text", L"Pretendard Bold", 960, 540, 100, L"", 50, 400, 0, TA_CENTER, 1, RGB(255, 255, 255) };
	Layer dialogText = { true, 10, L"text", L"Pretendard SemiBold", 110, 760, 100, L"", 50, 400, 0, TA_LEFT, 0, RGB(0, 0, 0) };
	easyImage.reset(&easyImage);

	WCHAR* story = ReadStoryFile();

	WCHAR* bufferLine;
	WCHAR* splitLine = wcstok(story, L"\n", &bufferLine);

	bool started = false;
	while (splitLine != NULL) {
		splitLine = wcstok(NULL, L"\n", &bufferLine);

		WCHAR* buffer;
		WCHAR* command = wcstok(splitLine, L":", &buffer);

		if (!started) {
			if (wcscmp(command, L"#SECTION") == 0) {
				WCHAR* sectionName = wcstok(NULL, L":", &buffer);
				if (wcscmp(sectionName, sectionList[section]) == 0) {
					started = true;
				}
			}
			continue;
		}
		if (wcscmp(command, L"#START") == 0) {
			printf("START\n");
		}
		else if (wcscmp(command, L"#END") == 0) {
			return 0;
		}
		else if (wcscmp(command, L"#IMAGE") == 0) {
			WCHAR* type = wcstok(NULL, L":", &buffer);
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
		else if (wcscmp(command, L"#TEXT") == 0) {
			WCHAR* type = wcstok(NULL, L":", &buffer);
			Layer* target = NULL;
			if (wcscmp(type, L"HOVER") == 0) {
				target = &hoverText;
			}
			else if (wcscmp(type, L"DIALOG") == 0) {
				target = &dialogText;
			}
			if (target) {
				WCHAR* content = wcstok(NULL, L":", &buffer);

				WCHAR* pwc = wcsstr(content, L"|N");
				if (pwc) {
					wcsncpy(pwc, name, 2);
				}

				target->enable = true;
				StepPrint(content, *target);
			}
		}
		else if (wcscmp(command, L"#AUDIO") == 0) {
			WCHAR* alias = wcstok(NULL, L":", &buffer);
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
			else if (wcscmp(command, L"STOP") == 0) {
				StopAudio(alias);
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
		else if (wcscmp(command, L"#CLICK") == 0) {
			WaitClick();
		}
		else if (wcscmp(command, L"#SLEEP") == 0) {
			int sleep = _wtoi(wcstok(NULL, L":", &buffer));
			Sleep(sleep);
		}
	}

	Sleep(1000000);
}