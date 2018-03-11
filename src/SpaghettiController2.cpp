
#include "SpaghettiController2.h"
#include <iostream>

SpaghettiController::SpaghettiController() :
  constants{0},
  /* do NOT fuck with these coefficents or you will crash valbal */

  /* first order lead compendator */
  compensator({{1, -0.30000000000000000, -0.4}, {2.8291628469154848e-05, -1.4117522606108269e-05, -1.4131668420342846e-05}}),

  h_filter({{1.1545084971874737, -1.9021130325903071, 0.84549150281252627}, {0.024471741852423234, 0.048943483704846469, 0.024471741852423234}}),
  v_filter({{1.0003141592601912, -1.9999999013039569, 0.99968584073980871}, {4.93480216e-07,   4.93480216e-07,  -4.93480216e-07,  -4.93480216e-07}})
{
  state.effort = 0;
  state.v_T = HUGE_VALF;
  state.b_T = HUGE_VALF;
  state.v_ctr = 0;
  state.b_ctr = 0;
  state.action = 0;
  ss_gain = compensator.getSSGain();
}

bool SpaghettiController::update(Input input){
  /* filter input to prevent alaising */
  float h_filt = h_filter.update(input.h);

  /* biquad for veloctiy */
  state.ascent_rate = v_filter.update(input.h);

  /* get effort from compensator */
  if(state.comp_ctr >= comp_freq*constants.freq){
    state.effort = compensator.update(constants.h_cmd - h_filt);
    state.comp_ctr = 0;
  }
  float rate = state.effort * constants.k;


  /* min/max thresholds*/
  if(abs(rate) < constants.rate_max) rate = ((0<rate) - (rate<0))*constants.rate_max;
  /* trying to balast */
  else if(rate > 0){
    float thresh = constants.ss_error_thresh_b * ss_gain * constants.k;
    if(rate < thresh) rate = 0;
    else rate = rate - thresh;
    if(state.ascent_rate > constants.ascent_rate_thresh) rate = 0;
  }
  /* trying to vent */
  else if(rate < 0) {
    float thresh = -constants.ss_error_thresh_v * ss_gain * constants.k;
    if(rate > thresh) rate = 0;
    else rate = rate - thresh;
    if(state.ascent_rate < -constants.ascent_rate_thresh) rate = 0;
  }

  /* calculate time intervals */
  state.v_T = rate < 0 ? abs(constants.v_dldt * constants.v_tmin / rate) : HUGE_VALF;
  state.b_T = rate > 0 ? abs(constants.b_dldt * constants.b_tmin / rate) : HUGE_VALF;

  /* reset counters if interval is inf*/
  state.v_ctr = state.v_T == HUGE_VALF ? 0 : state.v_ctr;
  state.b_ctr = state.b_T == HUGE_VALF ? 0 : state.b_ctr;

  /* check timers and act if necessary */
  if(float(state.v_ctr)/constants.freq >= state.v_T){
    state.action = -constants.v_tmin;
    state.v_ctr = 0;
  } else if(float(state.b_ctr)/constants.freq >= state.b_T){
    state.action = constants.b_tmin;
    state.b_ctr = 0;
  } else {
    state.action = 0;
  }

  /* increment counters */
  state.v_ctr++;
  state.b_ctr++;
  state.comp_ctr++;
  /* error checking is for the weak */
  return true;
}

void SpaghettiController::updateConstants(Constants constants){
  if(this->constants.h_cmd != constants.h_cmd){
    compensator.shiftBias(constants.h_cmd - this->constants.h_cmd);
  }
  this->constants = constants;
}

int SpaghettiController::getAction(){
  return state.action * 1000;
}

SpaghettiController::State SpaghettiController::getState(){
  return state;
}