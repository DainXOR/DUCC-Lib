#pragma once

enum test_enum {
	HMMM,
	OK,
	NO
};

class test_class {
	int v1;
	static int v2;

public:
	test_class() {
		v1 = 0;
		v2 = 0;
	}

	void set_v1(int v) {
		int aux = v;
		v1 = aux;
	}
	static void set_v2(int v) {
		static int aux = v;
		v2 = aux;
	}

};

