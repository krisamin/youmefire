#include "../headers/easyDefine.h"

// 메인 프로세스
int MainProcess() {
	// 기본적인 설정
	initialize();
	InitAudio();
	InitMouse();
	InitImage(30);

	// 게임 인트로
	GameIntro();

	// 리턴값이 0일때 까지 계속 반복(다시시작)
	while (true) {
		int type = Index();
		if (!type) return 0;
	}
}

// 시작
int main() {
	MainProcess();
}