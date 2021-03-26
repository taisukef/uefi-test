typedef unsigned int uint;

uint rndn[4];

static inline uint rnd() {
	uint t = rndn[0] ^ (rndn[0] << 11);
	rndn[0] = rndn[1];
	rndn[1] = rndn[2];
	rndn[2] = rndn[3];
	return rndn[3] = (rndn[3] ^ (rndn[3] >> 19)) ^ (t ^ (t >> 8));
}

static inline void random_seed(int n) {
	rndn[0] = n;
	rndn[1] = 362436069;
	rndn[2] = 521288629;
	rndn[3] = 88675123;
}
static inline void random_init() {
	random_seed(123456789);
}
