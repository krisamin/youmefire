#include "../headers/easyDefine.h"

void ReadStory(WCHAR* startSection) {
	/*WCHAR sectionList[5][15] = {L"INTRO", L"PROLOGUE-J", L"PROLOGUE-V", L"INTERLUDE", L"HEROINE" };
	wprintf(L"%s", sectionList[section]);*/

	Layer background = { true, 0, L"image", L"images/solid/101010.bmp", 0, 0, 100 };
	Layer dialog = { true, 3, L"image", L"images/dialog/dialog.bmp", 72, 700, 80 };
	Layer nameTag = { true, 4, L"image", L"images/dialog/viichan.bmp", 120, 671, 100 };
	Layer dialogText = { true, 5, L"text", L"Pretendard SemiBold", 110, 760, 100, L"", 50, 400, 0, TA_LEFT, 0, RGB(0, 0, 0) };
	Layer hider = { true, 19, L"image", L"images/solid/101010.bmp", 0, 0, 100 };
	Layer hoverText = { true, 20, L"text", L"Pretendard Bold", 960, 540, 100, L"", 50, 400, 0, TA_CENTER, 1, RGB(255, 255, 255) };
	easyImage.reset(&easyImage);

	WCHAR* story = GetReadFile("data/story.txt");

	WCHAR* bufferLine;
	WCHAR* splitLine = wcstok(story, L"\n", &bufferLine);

	WCHAR* jump = NULL;
	bool started = false;
	int select = 0;
	while (splitLine != NULL) {
		splitLine = wcstok(NULL, L"\n", &bufferLine);

		WCHAR* buffer;
		WCHAR* command = wcstok(splitLine, L":", &buffer);

		if (wcscmp(command, L"#STOP") == 0) {
			/*printf("Exit by #STOP");
			Sleep(2000);*/
			break;
		}

		if (!started) {
			if (wcscmp(command, L"#SECTION") == 0) {
				WCHAR* sectionName = wcstok(NULL, L":", &buffer);
				if (wcscmp(sectionName, startSection) == 0) {
					started = true;
				}
			}
			continue;
		}

		if (jump) {
			if (wcscmp(command, L"#POINT") == 0) {
				WCHAR* point = wcstok(NULL, L":", &buffer);
				if (wcscmp(point, jump) == 0) {
					jump = NULL;
				}
			}
		}
		else if (wcscmp(command, L"#END") == 0) {
			/*printf("Exit by #END");
			Sleep(2000);*/
			break;
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
		else if (wcscmp(command, L"#CREDIT") == 0) {
			Layer overHider = { true, 24, L"image", L"images/solid/101010.bmp", 0, 0, 100 };
			easyImage.setLayer(&easyImage, overHider);
			FadeImage(overHider, 0, 100);
			easyImage.reset(&easyImage);
			easyImage.setLayer(&easyImage, overHider);
			easyImage.render(&easyImage);
			Sleep(1000);

			WCHAR* type = wcstok(NULL, L":", &buffer);
			WCHAR* creditPath = (WCHAR*)malloc(sizeof(WCHAR) * 100);
			wsprintf(creditPath, L"images/credit/%s.bmp", type);
			Layer creditImage = { true, 25, L"image", creditPath, 0, 0, 100 };
			easyImage.setLayer(&easyImage, creditImage);
			FadeImage(creditImage, 0, 100);
			Sleep(5000);

			while (creditImage.y > -1960 - 1080) {
				if (mouseC) creditImage.y -= 10;
				else creditImage.y -= 2;
				if(creditImage.y <= -1960 - 1080) creditImage.y = -1960 - 1080;
				easyImage.setLayer(&easyImage, creditImage);
				easyImage.render(&easyImage);
			}

			WCHAR* bgmName = (WCHAR*)malloc(sizeof(WCHAR) * 100);
			wsprintf(bgmName, L"bgm/%sending", _wcslwr(type));
			FadeAudio(bgmName, 1000, 0);
			StopAudio(bgmName);

			/*printf("Exit by #CREDIT");
			Sleep(2000);*/
			break;
		}
		else if (wcscmp(command, L"#LAYER") == 0) {
			WCHAR* type = wcstok(NULL, L":", &buffer);
			Layer* target = NULL;
			if (wcscmp(type, L"RENDER") == 0) {
				easyImage.render(&easyImage);
			}
			else if (wcscmp(type, L"RESET") == 0) {
				easyImage.reset(&easyImage);
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
						FadeImage(target, from, to);
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
				if (wcscmp(type, L"JINGBURGER") == 0 || wcscmp(type, L"VIICHAN") == 0 || wcscmp(type, L"JURURU") == 0 || wcscmp(type, L"TEACHER") == 0 || wcscmp(type, L"UNKNOWN") == 0) {
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
					else if (wcscmp(type, L"TEACHER") == 0) {
						nameTag.name = L"images/dialog/teacher.bmp";
					}
					else if (wcscmp(type, L"UNKNOWN") == 0) {
						nameTag.name = L"images/dialog/unknown.bmp";
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
		else if (wcscmp(command, L"#HEROINE") == 0) {
			//printf("HEROINE SELECT");
			easyImage.reset(&easyImage);
			int heroineSelect = 0;
			int hovering = false;
			while (true) {
				if (IsInPixel(600, 377, 280, 366) && mouseC && mouseS) {
					mouseS = false;
					PlayAudio(L"effect/button", false);
					heroineSelect = 1;
				}
				else if (IsInPixel(1040, 377, 280, 366) && mouseC && mouseS) {
					mouseS = false;
					PlayAudio(L"effect/button", false);
					heroineSelect = 2;
				}
				if (IsInPixel(780, 843, 380, 91)) {
					hovering = true;
					if (mouseC && mouseS) {
						mouseS = false;
						PlayAudio(L"effect/button", false);
						if (heroineSelect == 1) {
							jump = L"STORY-V";
						}
						else if (heroineSelect == 2) {
							jump = L"STORY-J";
						}
						easyImage.reset(&easyImage);
						break;
					}
				}
				else {
					hovering = false;
				}
				WCHAR* imgPath = (WCHAR*)malloc(100);
				wsprintf(imgPath, L"images/screen/heroine/%d%d.bmp", heroineSelect, (hovering&& heroineSelect) ? 1 : 0);
				Layer background = { true, 0, L"image", imgPath, 0, 0, 100 };

				easyImage.setLayer(&easyImage, background);
				easyImage.render(&easyImage);
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

	free(story);
}