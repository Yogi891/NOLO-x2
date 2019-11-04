#ifndef KF_RANDOM_HEADER
#define KF_RANDOM_HEADER

namespace kf
{
	class MTRand_int32 
	{ // Mersenne Twister random number generator
		public:
		// default constructor: uses default seed only if this is the first instance
		MTRand_int32() { if (!init) seed(5489UL); init = true; }
		// constructor with 32 bit int as seed
		MTRand_int32(unsigned long s) { seed(s); init = true; }
		// constructor with array of size 32 bit ints as seed
		MTRand_int32(const unsigned long* array, int size) { seed(array, size); init = true; }
		// the two seed functions
		void seed(unsigned long); // seed with 32 bit integer
		void seed(const unsigned long*, int size); // seed with array
		// overload operator() to make this a generator (functor)
		unsigned long operator()() { return rand_int32(); }
		// 2007-02-11: made the destructor virtual; thanks "double more" for pointing this out
		virtual ~MTRand_int32() {} // destructor
		protected: // used by derived classes, otherwise not accessible; use the ()-operator
		unsigned long rand_int32(); // generate 32 bit random integer
		private:
		static const int n = 624, m = 397; // compile time constants
		// the variables below are static (no duplicates can exist)
		static unsigned long state[n]; // state vector array
		static int p; // position in state array
		static bool init; // true if init function is called
		// private functions used to generate the pseudo random numbers
		unsigned long twiddle(unsigned long, unsigned long); // used by gen_state()
		void gen_state(); // generate new state
		// make copy constructor and assignment operator unavailable, they don't make sense
		MTRand_int32(const MTRand_int32&); // copy constructor not defined
		void operator=(const MTRand_int32&); // assignment operator not defined
	};

	// inline for speed, must therefore reside in header file
	inline unsigned long MTRand_int32::twiddle(unsigned long u, unsigned long v) 
	{
		return (((u & 0x80000000UL) | (v & 0x7FFFFFFFUL)) >> 1)
		^ ((v & 1UL) ? 0x9908B0DFUL : 0x0UL);
	}

	inline unsigned long MTRand_int32::rand_int32() 
	{ // generate 32 bit random int
		if (p == n) gen_state(); // new state vector needed
		// gen_state() is split off to be non-inline, because it is only called once
		// in every 624 calls and otherwise irand() would become too big to get inlined
		unsigned long x = state[p++];
		x ^= (x >> 11);
		x ^= (x << 7) & 0x9D2C5680UL;
		x ^= (x << 15) & 0xEFC60000UL;
		return x ^ (x >> 18);
	}

	double random(double maxVal);
	unsigned int randomI(unsigned int maxVal);
	double randomRange(double minVal, double maxVal);
	unsigned int randomRangeI(unsigned int minVal, unsigned int maxVal);
	void randomSeed(unsigned int s);
	void randomSeed();
}
#endif
