#include "easyDefine.h"

void InitImage(int count) {
	easyImage = DEFAULT_EASY_IMAGE;
	easyImage.initialize(&easyImage);

	easyImage.count = count;
	Layer* layer = (Layer*)malloc(sizeof(Layer) * easyImage.count);
	easyImage.layer = layer;

	easyImage.reset(&easyImage);
	easyImage.render(&easyImage);
}