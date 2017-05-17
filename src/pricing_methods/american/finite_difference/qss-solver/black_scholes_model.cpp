#include <qss-solver/engine/common/model.h>
#include <qss-solver/engine/classic/classic_model.h>

#include "black_scholes_model.h"

// void
// MOD_settings (SD_simulationSettings settings) {
//   return;
// }
//
// void
// CLC_initializeDataStructs (CLC_simulator simulator) {
//   return;
// }

BlackScholesModel::BlackScholesModel() {}

BlackScholesModel::~BlackScholesModel() {}

void BlackScholesModel::initializeDataStructs(CLC_simulator simulator) {}

void BlackScholesModel::settings(SD_simulationSettings settings) {}

void BlackScholesModel::definition(double *x, double *d, double *alg, double t, double *dx) {}

void BlackScholesModel::zeroCrossing(int i, double *x, double *d, double *alg, double t, double *zc) {}

void BlackScholesModel::handlerPos(int i, double *x, double *d, double *alg, double t) {}