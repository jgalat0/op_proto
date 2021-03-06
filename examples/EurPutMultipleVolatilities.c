#include <stdio.h>
#include <libop.h>

/**
 * Opción put europea con precio de strike $20 y tiempo a la expiración de un año.
 * Posee un dividendo continuo del 10% y una tasa libre de riesgo de 9%.
 * Se calcula el precio de la opción para un precio de subyacente de $21
 * y para una volatilidad de 40% y para otra de 25%.
 */

int main(int argc, char const *argv[]) {

  double  underlying = 21,
          strike = 20;
  volatility sigma = new_volatility(0.4);
  risk_free_rate r = new_risk_free_rate(0.09);
  dividend d = new_continuous_dividend(0.1);

  time_period tp = new_time_period_365d();

  option opt = new_option(OPTION_PUT, EU_EXERCISE, DAYS(tp, 365), strike);
  pricing_method pm = new_pricing_method(EU_ANALYTIC, sigma, r, d);

  option_set_pricing_method(opt, pm);

  result result = new_result();

  option_price(opt, underlying, result);

  double price40 = result_get_price(result);

  printf("Option price (Vol: 40%%) = %lf\n", price40);

  vol_set_value(sigma, 0.25);

  option_price(opt, underlying, result);

  double price25 = result_get_price(result);

  printf("Option price (Vol: 25%%) = %lf\n", price25);

  delete_result(result);
  delete_time_period(tp);
  delete_pricing_method(pm);
  delete_risk_free_rate(r);
  delete_volatility(sigma);
  delete_dividend(d);
  delete_option(opt);
  return 0;
}
