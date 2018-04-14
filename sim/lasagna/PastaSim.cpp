#include "PastaSim.h"



PastaSim::PastaSim() : 
	l_noise(0,0.002),
	v_noise(0,0.8)
{
	b_dldt = 0.0006;
	v_dldt = 0.0006;
	klin = 7;
	h = 14000;
	l = 0;
	freq = 20;
	gen.seed(std::time(0));
}

double PastaSim::evolve(double action){
	action = action/1000;
	double dldt = action > 0 ? action*b_dldt : action*v_dldt;

	l += dldt + 1*l_noise(gen)/freq ; 
	v = klin*l + 1*v_noise(gen)/freq;

	h += v/freq;

	//l -= v/freq*5e-5;
	return h;
}