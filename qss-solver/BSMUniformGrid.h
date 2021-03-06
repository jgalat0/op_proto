#ifndef __BSM_UNIFORM_GRID_H__
#define __BSM_UNIFORM_GRID_H__

#include "BlackScholesModel.h"

#ifdef __cplusplus

class BSMUniformGrid : public BlackScholesModel {
  public:
    BSMUniformGrid(int grid_size, BSM_OT ot, double smax,
      double vol, double rfr, double strike, double cont_div, int discdiv_n,
      double *discdiv_date, double *discdiv_amo, double period,
      double end_time, double tol, double abs_tol);
    ~BSMUniformGrid();

    /* TODO errors (index, etc) */
    double v(int i);
    double delta(int i);
    double gamma(int i);
    double theta(int i);

  protected:
    void initializeDataStructs(void *CLC_simulator);
    void settings(SD_simulationSettings);
    void definition(double *x, double *d, double *alg, double t, double *dx);
    void zeroCrossing(int i, double *x, double *d, double *alg, double t, double *zc);
    void handlerPos(int i, double *x, double *d, double *alg, double t);
    void handlerNeg(int i, double *x, double *d, double *alg, double t);
    void output(int i, double *x, double *d, double *alg, double t, double *out);
    void outputAll(int i, double *x, double *d, double *alg, double t, double *out);

  private:
    double get_value(double*, int);

    SD_Solver _solver;
    SD_CommInterval _comm_interval;
    double _ft, _dqmin, _dqrel;
    double _period;

    int _g_size;
    BSM_OT _op_type;
    double _SMin, _SMax;
    double _sigma, _r, _K,
          _u0, _uN1, _ds,
          _cd,   //continuous dividend
          *_discdiv_date, //discrete dividend date
          *_discdiv_amo; //discrete dividend amount
    int   _discdiv_n, //number of discrete dividends
          _discdiv_i; //discrete dividend index

    double *_solution;
    double *_v, *_delta, *_gamma, *_theta;

    /* binds for the engine */
    MOD_settings bsms;
    InitializeDataStructs bsmids;
    SD_eq bsmo;
    CLC_eq bsmf;
    CLC_zc bsmzc;
    CLC_hnd bsmhp, bsmhn;

};
#endif /* __cplusplus */

#ifdef __cplusplus
extern "C" {
#endif

  typedef struct BSM_UG_ *BSM_UG;

  struct BSM_UG_;

  BSM_UG new_BSM_UG(int grid_size, BSM_OT ot, double smax,
    double vol, double rfr, double strike, double cont_div, int discdiv_n,
    double *discdiv_date, double *discdiv_amo, double period,
    double end_time, double tol, double abs_tol);

  void delete_BSM_UG(BSM_UG);

  typedef double (*BSM_UG_F) (BSM_UG, int);

  double BSM_UG_v(BSM_UG, int);
  double BSM_UG_delta(BSM_UG, int);
  double BSM_UG_gamma(BSM_UG, int);
  double BSM_UG_theta(BSM_UG, int);

#ifdef __cplusplus
}
#endif

#endif /* __BSM_UNIFORM_GRID_H__ */
