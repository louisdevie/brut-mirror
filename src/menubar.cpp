#include "utils.cpp"

#define NTABS 6

AnimatedInt menuBarButtonX[NTABS];
int menuBarButtonY;
AnimatedInt menuBarButtonW[NTABS];
int menuBarButtonH;

int menuBarTexSize[NTABS];
AnimatedInt menuBarTexW[NTABS];
SDL_Rect menuBarTexSrc[NTABS];
SDL_Rect menuBarTexDst[NTABS];
int menuBarFocus;
int prevMenuBarFocus;

void menuBarInit() {
	menuBarFocus = -1;
	prevMenuBarFocus = -2;

	menuBarButtonY = 10;
	menuBarButtonH = 50;
	for (int i=0; i<NTABS; i++) {
		menuBarTexSrc[i].x = 0;
		menuBarTexSrc[i].y = 0;
	}
}

bool menuBarMouseMotion(int mouseX, int mouseY) {
	menuBarFocus = -1;
	for (int i=0; i<NTABS; i++) {
		if (isBoundedToRect(mouseX, mouseY, menuBarButtonX[i].get(), menuBarButtonY, menuBarButtonW[i].get(), menuBarButtonH)) {
			menuBarFocus = i;
			return true;
		}
	}
	return false;
}

void menuBarUpdate(int W, int H) {
	if (menuBarFocus != prevMenuBarFocus) {
		if (menuBarFocus == -1) {
			for (int i=0; i<NTABS; i++) {
				menuBarButtonX[i].goTo(10+((W-20)/NTABS)*i);
				menuBarButtonW[i].goTo((W-20)/NTABS);
				menuBarTexW[i].goTo(32);
			}
		} else {
			for (int i=0; i<NTABS; i++) {
				if (i == menuBarFocus) {
					menuBarButtonX[i].goTo(10+80*i);
					menuBarButtonW[i].goTo(W+60-(80*NTABS));
					menuBarTexW[i].goTo(menuBarTexSize[i]);
				} else {
					if (i < menuBarFocus) {
						menuBarButtonX[i].goTo(10+80*i);
						menuBarButtonW[i].goTo(80);
					} else {
						menuBarButtonX[i].goTo(W-10-(80*(NTABS-i)));
						menuBarButtonW[i].goTo(80);
					}
					menuBarTexW[i].goTo(32);
				}
			}
		}
	}
	if (menuBarFocus == -1) {
		for (int i=0; i<NTABS; i++) {
			menuBarButtonX[i].fastForward();
			menuBarButtonW[i].fastForward();
			menuBarTexW[i].fastForward();
		}
	} else {
		for (int i=0; i<NTABS; i++) {
			menuBarButtonX[i].update(20);
			menuBarButtonW[i].update(20);
			menuBarTexW[i].update(20);
		}
	}
	for (int i=0; i<NTABS; i++) {
		menuBarTexSrc[i].w = menuBarTexW[i].get();
		menuBarTexDst[i].x = menuBarButtonX[i].get() + menuBarButtonW[i].get()/2 - menuBarTexW[i].get()/2;
		menuBarTexDst[i].w = menuBarTexW[i].get();
	}
	
	prevMenuBarFocus = menuBarFocus;
}

SDL_Rect menuBarGetButtonRect(int i) {
	return {menuBarButtonX[i].get(), menuBarButtonY, menuBarButtonW[i].get()+1, menuBarButtonH};
}

void menuBarTextureSize(int i, int w) {
	menuBarTexSize[i] = w;

	menuBarTexSrc[i].h = 32;
	menuBarTexDst[i].h = 32;
	menuBarTexDst[i].y = menuBarButtonY + menuBarButtonH/2 - 16;
}

SDL_Rect *menuBarGetSrcRect(int i) {
	return &menuBarTexSrc[i];
}

SDL_Rect *menuBarGetDstRect(int i) {
	return &menuBarTexDst[i];
}

int menuBarFocused() {
	return menuBarFocus;
}