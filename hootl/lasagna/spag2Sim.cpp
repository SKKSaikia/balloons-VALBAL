#include <iostream>
#include <fstream>
#include <iomanip>
#include "alias.h"
#include "LasagnaController.h"
#include "SpaghettiController2.h"
#include "header.h"
#include "PastaSim.h"


#define FREQ 20
#define CONTROLLER SpaghettiController2
#define LAS LasagnaController
#define SPAG SpaghettiController2

using namespace std;


CONTROLLER::Constants getDefaultConstants();
CONTROLLER::Constants DefaultConstants();


int main ()
{
	fstream f ("data.bin", std::fstream::in | std::fstream::binary);
	fstream o ("output.bin", std::fstream::out | std::fstream::binary);
	
	PastaSim sim;
	CONTROLLER las;
	CONTROLLER::Constants con;
	las.updateConstants(con);
	printf("Spag2 to the rescue\n");
	miniframe data;
	float v_cmd = 0;
	int dur = 100*60*60*FREQ;
	int act_sum = 0;
	for(int i = 0; i < 60*60*20*4; i++){
		CONTROLLER::Input input;
		input.h = sim.h;		
		las.update(input);
	}
	for(int i = 0; i < dur; i++){
		CONTROLLER::Input input;
		input.h = sim.evolve(double(las.getAction()));
		las.update(input);
		CONTROLLER::State state = las.getState();
		act_sum += state.action;
		if(i%(FREQ) == 0){
			float buf[2] = {sim.h, state.effort};
			o.write((char*)&buf, sizeof(float)*2);
			o.write((char*)&act_sum,sizeof(act_sum));
		}
		if(i%(FREQ*60*60) == 0){
			float t = float(i)/FREQ/60/60;
			printf("%f, %f, %f \n", t, sim.h, state.effort);
		}
	}
}

