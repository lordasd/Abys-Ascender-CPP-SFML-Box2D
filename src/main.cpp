#include "GameController.h"

int main() {
	srand(static_cast<unsigned>(time(nullptr)));
	GameController().run();
}