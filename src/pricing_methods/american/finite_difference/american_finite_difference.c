#include <stdio.h>
#include <stdlib.h>
#include <qss-solver/black_scholes_model.h>
#include "american_finite_difference.h"


static int option_price(option_data od, pricing_data pd,
  double S, date ttl, result ret, void *pm_data) {

  // (int grid_size, BSM_OT ot, double smax,
  //   double vol, double rfr, double strike, double cont_div, int discdiv_n,
  //   double *discdiv_date, double *discdiv_ammo,
  //   double end_time, double tol, double abs_tol)

  //test
  BSM bsm = new_BSM(100, CALL, 100, 0.4, 0.09, 20, 0.1, 0, NULL, NULL,
    1, 1e-9, 1e-12);

  fprintf(stderr, "<<%lg>>\n", BSM_v(bsm, 21, 365.0));

  delete_BSM(bsm);

  return 0;
}

pricing_method new_american_finite_difference(pricing_data pd) {
  return new_pricing_method_(option_price, pd, NULL);
}
