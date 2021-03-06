#ifndef __COMMON_H__
#define __COMMON_H__

#include <result.h>
#include <option_data_internal.h>
#include <pricing_data.h>
#include <pm_settings.h>

/**
 * Common type of price and greeks calculation functions
 */
typedef int (*common_f) (option_data, pricing_data, double S, result,
  pm_settings, void*);

typedef common_f price_f;
typedef common_f delta_f;
typedef common_f gamma_f;
typedef common_f theta_f;
typedef common_f rho_f;
typedef common_f vega_f;


typedef int (*common_f_) (option_data, pricing_data, int size, double *Ss,
  result, pm_settings, void*);

typedef common_f_ prices_f;

/**
 * Type of implied volatility calculation and price precision functions
 */
typedef int (*common_v_f) (option_data, pricing_data, double V, double S,
  result, pm_settings, void*);

typedef common_v_f impl_vol_f;
typedef common_v_f pp_f;

/**
 * Common type of a delete function
 */
typedef void (*delete_f) (void*);

#endif /* __COMMON_H__ */
