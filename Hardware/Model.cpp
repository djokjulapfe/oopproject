#include "Model.h"

Model *Model::Instance() {
	static Model instance;
	return &instance;
}

Model::Model() {
	Ts = 5;
	Tm = 10;
	Te = 15;
	Mw = 20;
	Mr = 15;
	Nw = 2;
	Nr = 1;
}
