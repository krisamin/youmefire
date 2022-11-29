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
	WCHAR sectionList[3][15] = {L"INTRO", L"PROLOGUE-J", L"PROLOGUE-V" };
	wprintf(L"%s", sectionList[section]);

	Layer background = { true, 0, L"image", L"images/solid/101010.bmp", 0, 0, 100 };
	Layer dialog = { true, 3, L"image", L"images/dialog/dialog.bmp", 72, 700, 80 };
	Layer nameTag = { true, 4, L"image", L"images/dialog/viichan.bmp", 120, 671, 100 };
	Layer dialogText = { true, 5, L"text", L"Pretendard SemiBold", 110, 760, 100, L"", 50, 400, 0, TA_LEFT, 0, RGB(0, 0, 0) };
	Layer hider = { true, 19, L"image", L"images/solid/101010.bmp", 0, 0, 100 };
	Layer hoverText = { true, 20, L"text", L"Pretendard Bold", 960, 540, 100, L"", 50, 400, 0, TA_CENTER, 1, RGB(255, 255, 255) };
	easyImage.reset(&easyImage);

	WCHAR* story = ReadStoryFile();

	WCHAR* bufferLine;
	WCHAR* splitLine = wcstok(story, L"\n", &bufferLine);

	WCHAR* jump = NULL;
	bool started = false;
	int select = 0;
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
		else if (jump) {
			if (wcscmp(command, L"#POINT") == 0) {
				WCHAR* point = wcstok(NULL, L":", &buffer);
				if (wcscmp(point, jump) == 0) {
					jump = NULL;
				}
			}
		}
		else if (wcscmp(command, L"#JUMP") == 0) {
			WCHAR* type = wcstok(NULL, L":", &buffer);
			if (wcscmp(type, L"@SELECT") == 0) {
				if (select == 1) jump = L"@1";
				else if (select == 2) jump = L"@2";
				else if (select == 3) jump = L"@3";
			}
			else {
				jump = type;
			}
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
		else if (wcscmp(command, L"#SELECT") == 0) {
			int count = _wtoi(wcstok(NULL, L":", &buffer));
			WCHAR* selectList[5];
			for (int i = 0; i < count; i++) {
				selectList[i] = wcstok(NULL, L":", &buffer);
			}

			while (true) {
				if (count == 1) {
					Layer option1 = { true, 11, L"image", L"images/dialog/select.bmp", 160, 493, 60 };
					Layer option1Text = { true, 16, L"text", L"Pretendard SemiBold", 960, 493 + 22, 100, selectList[0], 50, 400, 0, TA_CENTER, 2, RGB(255, 255, 255) };
					int hover = 0;
					if (IsInPixel(360, 493, 1200, 94)) {
						option1.opacity = 100;
						if (mouseC && mouseS) {
							select = 1;
							break;
						}
					}
					easyImage.setLayer(&easyImage, option1);
					easyImage.setLayer(&easyImage, option1Text);
					easyImage.render(&easyImage);
				}
				if (count == 2) {
					Layer option1 = { true, 11, L"image", L"images/dialog/select.bmp", 160, 421, 60 };
					Layer option2 = { true, 12, L"image", L"images/dialog/select.bmp", 160, 565, 60 };
					Layer option1Text = { true, 16, L"text", L"Pretendard SemiBold", 960, 421 + 22, 100, selectList[0], 50, 400, 0, TA_CENTER, 2, RGB(255, 255, 255) };
					Layer option2Text = { true, 17, L"text", L"Pretendard SemiBold", 960, 565 + 22, 100, selectList[1], 50, 400, 0, TA_CENTER, 2, RGB(255, 255, 255) };
					int hover = 0;
					if (IsInPixel(360, 421, 1200, 94)) {
						option1.opacity = 100;
						if (mouseC && mouseS) {
							select = 1;
							break;
						}
					}
					else if (IsInPixel(360, 565, 1200, 94)) {
						option2.opacity = 100;
						if (mouseC && mouseS) {
							select = 2;
							break;
						}
					}
					easyImage.setLayer(&easyImage, option1);
					easyImage.setLayer(&easyImage, option2);
					easyImage.setLayer(&easyImage, option1Text);
					easyImage.setLayer(&easyImage, option2Text);
					easyImage.render(&easyImage);
				}
				if (count == 3) {
					Layer option1 = { true, 11, L"image", L"images/dialog/select.bmp", 160, 349, 60 };
					Layer option2 = { true, 12, L"image", L"images/dialog/select.bmp", 160, 493, 60 };
					Layer option3 = { true, 13, L"image", L"images/dialog/select.bmp", 160, 637, 60 };
					Layer option1Text = { true, 16, L"text", L"Pretendard SemiBold", 960, 349 + 22, 100, selectList[0], 50, 400, 0, TA_CENTER, 2, RGB(255, 255, 255) };
					Layer option2Text = { true, 17, L"text", L"Pretendard SemiBold", 960, 493 + 22, 100, selectList[1], 50, 400, 0, TA_CENTER, 2, RGB(255, 255, 255) };
					Layer option3Text = { true, 18, L"text", L"Pretendard SemiBold", 960, 637 + 22, 100, selectList[2], 50, 400, 0, TA_CENTER, 2, RGB(255, 255, 255) };
					int hover = 0;
					if (IsInPixel(360, 349, 1200, 94)) {
						option1.opacity = 100;
						if (mouseC && mouseS) {
							select = 1;
							break;
						}
					}
					else if (IsInPixel(360, 493, 1200, 94)) {
						option2.opacity = 100;
						if (mouseC && mouseS) {
							select = 2;
							break;
						}
					}
					else if (IsInPixel(360, 637, 1200, 94)) {
						option3.opacity = 100;
						if (mouseC && mouseS) {
							select = 3;
							break;
						}
					}
					easyImage.setLayer(&easyImage, option1);
					easyImage.setLayer(&easyImage, option2);
					easyImage.setLayer(&easyImage, option3);
					easyImage.setLayer(&easyImage, option1Text);
					easyImage.setLayer(&easyImage, option2Text);
					easyImage.setLayer(&easyImage, option3Text);
					easyImage.render(&easyImage);
				}
			}
			PlayAudio(L"effect/button", false);
			mouseS = false;
			int index = 11;
			while (index < 20) {
				Layer reset = { false, index ++, L"image", L"", 0, 0, 0 };
				easyImage.setLayer(&easyImage, reset);
			}
			easyImage.render(&easyImage);
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
		else if (wcscmp(command, L"#MACRO") == 0) {
			WCHAR* type = wcstok(NULL, L":", &buffer);
			if (wcscmp(type, L"DIALOG") == 0) {
				type = wcstok(NULL, L":", &buffer);
				if (wcscmp(type, L"JINGBURGER") == 0 || wcscmp(type, L"VIICHAN") == 0 || wcscmp(type, L"JURURU") == 0) {
					dialog.enable = true;
					nameTag.enable = true;
					if (wcscmp(type, L"VIICHAN") == 0) {
						nameTag.name = L"images/dialog/viichan.bmp";
					}
					else if (wcscmp(type, L"JINGBURGER") == 0) {
						nameTag.name = L"images/dialog/jingburger.bmp";
					}
					else if (wcscmp(type, L"JURURU") == 0) {
						nameTag.name = L"images/dialog/jururu.bmp";
					}
					easyImage.setLayer(&easyImage, dialog);
					easyImage.setLayer(&easyImage, nameTag);
				}
				else if (wcscmp(type, L"HIDE") == 0) {
					dialog.enable = false;
					dialogText.enable = false;
					nameTag.enable = false;
					easyImage.setLayer(&easyImage, dialog);
					easyImage.setLayer(&easyImage, dialogText);
					easyImage.setLayer(&easyImage, nameTag);
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
}