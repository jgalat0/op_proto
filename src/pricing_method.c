#include <stdlib.h>

#include <common.h>
#include "pricing_method.h"
#include "pricing_method_internal.h"
#include <debug.h>

struct pricing_method_ {
  price_f       option_price;
  pp_f          option_price_precision;
  prices_f      option_prices;
  delta_f       delta;
  gamma_f       gamma;
  theta_f       theta;
  rho_f         rho;
  vega_f        vega;
  impl_vol_f    ivf;
  pricing_data  pricing_data;
  void          *pm_data;
  delete_f      delete;
  pm_settings   pm_settings;
};

pricing_method new_pricing_method(method_id id, volatility v, risk_free_rate r,
  dividend d) {
  pricing_data pd = new_pricing_data(v, r, d);
  if (!pd)
    return NULL;
  switch (id) {
    case EU_ANALYTIC:
      return new_european_analytic(pd);
    case AM_FD_UG:
      return new_american_finite_difference_uniform_grid(pd);
    case AM_FD_NUG:
      return new_american_finite_difference_non_uniform_grid(pd);
    default:
      __DEBUG("Invalid method id");
      break;
  }
  return NULL;
}

pricing_method new_pricing_method_(price_f pf, pp_f ppf, prices_f psf, delta_f df,
  gamma_f gf, theta_f tf, rho_f rf, vega_f vf, impl_vol_f ivf,
  delete_f dlf, pricing_data pd, void *pm_d) {
  pricing_method pm = (pricing_method) malloc(sizeof(struct pricing_method_));
  if (pm) {
    pm->option_price = pf;
    pm->option_price_precision = ppf;
    pm->option_prices = psf;
    pm->delta = df;
    pm->gamma = gf;
    pm->theta = tf;
    pm->rho = rf;
    pm->vega = vf;
    pm->ivf = ivf;
    pm->pricing_data = pd;
    pm->pm_data = pm_d;
    pm->delete = dlf;
    pm->pm_settings = NULL;
  }
  return pm;
}

void delete_pricing_method(pricing_method pm) {
  if (pm) {
    if (pm->delete)
      pm->delete((void*) pm->pm_data);
    delete_pricing_data(pm->pricing_data);
  }
  free(pm);
}

static const char *__PM_NULL =
  "Pricing method is NULL";

static const char *__PM_METHOD_NOT_IMPL =
  "Method isn't implemented";

static const char *__PM_VOLATILITY_REQUIRED =
  "Volatility is required for this method";

int pm_set_settings(pricing_method pm, pm_settings pms) {
  if (!pm) {
    __DEBUG(__PM_NULL);
    return -1;
  }
  pm->pm_settings = pms;
  return 0;
}

int pm_option_price(pricing_method pm, option_data od, double S, result r) {
  if (!pm) {
    __DEBUG(__PM_NULL);
    return -1;
  }
  if (pd_null_volatility(pm->pricing_data)) {
    __DEBUG(__PM_VOLATILITY_REQUIRED);
    return -1;
  }
  if (pm->option_price)
    return pm->option_price(od, pm->pricing_data, S, r, pm->pm_settings,
      pm->pm_data);
  __DEBUG(__PM_METHOD_NOT_IMPL);
  return -1;
}

int pm_option_price_precision(pricing_method pm, option_data od, double V,
  double S, result r) {
  if (!pm) {
    __DEBUG(__PM_NULL);
    return -1;
  }
  if (pd_null_volatility(pm->pricing_data)) {
    __DEBUG(__PM_VOLATILITY_REQUIRED);
    return -1;
  }
  if (pm->option_price_precision)
    return pm->option_price_precision(od, pm->pricing_data, V, S, r,
      pm->pm_settings, pm->pm_data);
  __DEBUG(__PM_METHOD_NOT_IMPL);
  return -1;
}

int pm_option_prices(pricing_method pm, option_data od, int size,
  double *Ss, result r) {
  if (!pm) {
    __DEBUG(__PM_NULL);
    return -1;
  }
  if (pd_null_volatility(pm->pricing_data)) {
    __DEBUG(__PM_VOLATILITY_REQUIRED);
    return -1;
  }
  if (pm->option_prices)
    return pm->option_prices(od, pm->pricing_data, size, Ss, r,
      pm->pm_settings, pm->pm_data);
  __DEBUG(__PM_METHOD_NOT_IMPL);
  return -1;
}

int pm_delta(pricing_method pm, option_data od, double S, result r) {
  if (!pm) {
    __DEBUG(__PM_NULL);
    return -1;
  }
  if (pd_null_volatility(pm->pricing_data)) {
    __DEBUG(__PM_VOLATILITY_REQUIRED);
    return -1;
  }
  if (pm->delta)
    return pm->delta(od, pm->pricing_data, S, r, pm->pm_settings,
      pm->pm_data);
  __DEBUG(__PM_METHOD_NOT_IMPL);
  return -1;
}

int pm_gamma(pricing_method pm, option_data od, double S, result r) {
  if (!pm) {
    __DEBUG(__PM_NULL);
    return -1;
  }
  if (pd_null_volatility(pm->pricing_data)) {
    __DEBUG(__PM_VOLATILITY_REQUIRED);
    return -1;
  }
  if (pm->gamma)
    return pm->gamma(od, pm->pricing_data, S, r, pm->pm_settings,
      pm->pm_data);
  __DEBUG(__PM_METHOD_NOT_IMPL);
  return -1;
}

int pm_theta(pricing_method pm, option_data od, double S, result r) {
  if (!pm) {
    __DEBUG(__PM_NULL);
    return -1;
  }
  if (pd_null_volatility(pm->pricing_data)) {
    __DEBUG(__PM_VOLATILITY_REQUIRED);
    return -1;
  }
  if (pm->theta)
    return pm->theta(od, pm->pricing_data, S, r, pm->pm_settings, pm->pm_data);
  __DEBUG(__PM_METHOD_NOT_IMPL);
  return -1;
}

int pm_rho(pricing_method pm, option_data od, double S, result r) {
  if (!pm) {
    __DEBUG(__PM_NULL);
    return -1;
  }
  if (pd_null_volatility(pm->pricing_data)) {
    __DEBUG(__PM_VOLATILITY_REQUIRED);
    return -1;
  }
  if (pm->rho)
    return pm->rho(od, pm->pricing_data, S, r, pm->pm_settings, pm->pm_data);
  __DEBUG(__PM_METHOD_NOT_IMPL);
  return -1;
}

int pm_vega(pricing_method pm, option_data od, double S, result r) {
  if (!pm) {
    __DEBUG(__PM_NULL);
    return -1;
  }
  if (pd_null_volatility(pm->pricing_data)) {
    __DEBUG(__PM_VOLATILITY_REQUIRED);
    return -1;
  }
  if (pm->vega)
    return pm->vega(od, pm->pricing_data, S, r, pm->pm_settings, pm->pm_data);
  __DEBUG(__PM_METHOD_NOT_IMPL);
  return -1;
}

int pm_ivf(pricing_method pm, option_data od, double V, double S, result r) {
  if (!pm) {
    __DEBUG(__PM_NULL);
    return -1;
  }
  if (pm->ivf)
    return pm->ivf(od, pm->pricing_data, V, S, r,
      pm->pm_settings, pm->pm_data);
  __DEBUG(__PM_METHOD_NOT_IMPL);
  return -1;
}
