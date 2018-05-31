#ifndef PID_H
#define PID_H
#include <iostream>
#include <vector>
 #include <math.h>

class PID {
public:
  /*
  * Errors
  */
  double p_error;
  double i_error;
  double d_error;

  /*
  * Coefficients
  */ 
  //double Kp;
  //double Ki;
  //double Kd;

  std::vector<double> coeffs;

  /*
  * Twiddle Specific
  */ 

  std::vector<double> dCoeffs;
  bool twiddle_enabled;
  int current_step;
  int settle_step_count;
  int error_step_count;
  double total_error;
  double best_error;
  bool additive_step;
  bool subtractive_step;
  int current_param_index;
  int twiddle_step;

  /*
  * Constructor
  */
  PID();

  /*
  * Destructor.
  */
  virtual ~PID();

  /*
  * Initialize PID.
  */
  void Init(double Kp, double Ki, double Kd, bool twid);

  /*
  * Update the PID error variables given cross track error.
  */
  void UpdateError(double cte);

  /*
  * Calculate the total PID error.
  */
  double TotalError();
};

#endif /* PID_H */
