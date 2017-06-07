#ifndef __PRICING_DATA_H__
#define __PRICING_DATA_H__

#include <parameter.h>
#include <dividend.h>

typedef struct pricing_data_ * pricing_data;

struct pricing_data_ {
  volatility vol;
  risk_free_rate r;
  dividend d;
};

pricing_data new_pricing_data(volatility, risk_free_rate, dividend);

void delete_pricing_data(pricing_data);

#endif /* __PRICING_DATA_H__ */
