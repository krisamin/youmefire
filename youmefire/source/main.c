#include "../headers/easyDefine.h"

int MainProcess() {
	initialize();
	InitAudio();
	InitMouse();
	InitImage(30);

	GameIntro();
	while (true) {
		int type = Index();
		if (!type) return 0;
	}
}

int main() {
	MainProcess();
}