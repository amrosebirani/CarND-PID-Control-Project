#include "PID.h"

using namespace std;

/*
* TODO: Complete the PID class.
*/

PID::PID() {}

PID::~PID() {}

void PID::Init(double Kpi, double Kii, double Kdi, bool twid) {
  coeffs.push_back(Kpi);
  coeffs.push_back(Kii);
  coeffs.push_back(Kdi);
  
  i_error = 0;
  p_error = 0;
  d_error = 0;

  dCoeffs.push_back(.2*Kpi);
  dCoeffs.push_back(.2*Kii);
  dCoeffs.push_back(.2*Kdi);
  twiddle_enabled = twid;
  current_step = 0;
  settle_step_count = 100;
  error_step_count = 300;
  total_error = 0.0;
  best_error = numeric_limits<double>::max();
  additive_step = false;
  subtractive_step = false;
  current_param_index = 0;
  twiddle_step = 0;
}

void PID::UpdateError(double cte) {
  i_error += cte;
  //std::cout<<"i_error: "<<i_error<<std::endl;
  d_error = cte - p_error;
  //std::cout<<"d_error: "<<d_error<<std::endl;
  p_error = cte;
  //std::cout<<"p_error: "<<p_error<<std::endl;
  if (current_step % (settle_step_count + error_step_count) > settle_step_count) {
    total_error += pow(cte, 2);
  }
  // std::cout<<"current step: "<<current_step<<std::endl;
  if (current_step != 0 && twiddle_enabled && current_step % (settle_step_count + error_step_count) == 0 ) {
    if (twiddle_step > 0) {
      if (!additive_step) {
        coeffs[current_param_index] += dCoeffs[current_param_index];
        additive_step = true;
      } else if (additive_step) {
        if (total_error < best_error && !subtractive_step) {
          best_error = total_error;
          dCoeffs[current_param_index] *= 1.1;
          additive_step = false;
          current_param_index = (current_param_index+1)%3;
        } else {
          if (!subtractive_step) {
            coeffs[current_param_index] -= 2 * dCoeffs[current_param_index];
            subtractive_step = true;
          } else if (subtractive_step) {
            if (total_error < best_error) {
              best_error = total_error;
              dCoeffs[current_param_index] *= 1.1;
            } else {
              coeffs[current_param_index] += dCoeffs[current_param_index];
              dCoeffs[current_param_index] *= 0.9;
            }
            additive_step = false;
            subtractive_step = false;
            current_param_index = (current_param_index+1)%3;
          }
        }
      }
    } else {
      best_error = total_error;
    }
    twiddle_step += 1;
    total_error = 0.0;
    std::cout<<"TWiddle step done"<<std::endl;
    std::cout<<"Kp: "<<coeffs[0]<<" Ki: "<<coeffs[1]<<" Kd: "<<coeffs[2]<<std::endl;
  }
  current_step += 1;

}

double PID::TotalError() {
  return -coeffs[0]*p_error -coeffs[2] * d_error -coeffs[1]*i_error;
}

