#include "PastaSim.h"



PastaSim::PastaSim() : 
	l_noise(0,0.003),
	v_noise(0,1.5)
{
	b_dldt = 0.001;
	v_dldt = 0.003;
	klin = 7;
	//h = 13000;
	h = 0;
	l = .2;
	freq = 20;
	gen.seed(std::time(0));
	//gen.seed(1);
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