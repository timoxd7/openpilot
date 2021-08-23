#include "car.h"

namespace {
#define DIM 8
#define EDIM 8
#define MEDIM 8
typedef void (*Hfun)(double *, double *, double *);

double mass;

void set_mass(double x){ mass = x;}

double rotational_inertia;

void set_rotational_inertia(double x){ rotational_inertia = x;}

double center_to_front;

void set_center_to_front(double x){ center_to_front = x;}

double center_to_rear;

void set_center_to_rear(double x){ center_to_rear = x;}

double stiffness_front;

void set_stiffness_front(double x){ stiffness_front = x;}

double stiffness_rear;

void set_stiffness_rear(double x){ stiffness_rear = x;}
const static double MAHA_THRESH_25 = 3.8414588206941227;
const static double MAHA_THRESH_24 = 5.991464547107981;
const static double MAHA_THRESH_30 = 3.8414588206941227;
const static double MAHA_THRESH_26 = 3.8414588206941227;
const static double MAHA_THRESH_27 = 3.8414588206941227;
const static double MAHA_THRESH_29 = 3.8414588206941227;
const static double MAHA_THRESH_28 = 5.991464547107981;

/******************************************************************************
 *                      Code generated with sympy 1.7.1                       *
 *                                                                            *
 *              See http://www.sympy.org/ for more information.               *
 *                                                                            *
 *                         This file is part of 'ekf'                         *
 ******************************************************************************/
void err_fun(double *nom_x, double *delta_x, double *out_656386073162142696) {
   out_656386073162142696[0] = delta_x[0] + nom_x[0];
   out_656386073162142696[1] = delta_x[1] + nom_x[1];
   out_656386073162142696[2] = delta_x[2] + nom_x[2];
   out_656386073162142696[3] = delta_x[3] + nom_x[3];
   out_656386073162142696[4] = delta_x[4] + nom_x[4];
   out_656386073162142696[5] = delta_x[5] + nom_x[5];
   out_656386073162142696[6] = delta_x[6] + nom_x[6];
   out_656386073162142696[7] = delta_x[7] + nom_x[7];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_6364770466875885701) {
   out_6364770466875885701[0] = -nom_x[0] + true_x[0];
   out_6364770466875885701[1] = -nom_x[1] + true_x[1];
   out_6364770466875885701[2] = -nom_x[2] + true_x[2];
   out_6364770466875885701[3] = -nom_x[3] + true_x[3];
   out_6364770466875885701[4] = -nom_x[4] + true_x[4];
   out_6364770466875885701[5] = -nom_x[5] + true_x[5];
   out_6364770466875885701[6] = -nom_x[6] + true_x[6];
   out_6364770466875885701[7] = -nom_x[7] + true_x[7];
}
void H_mod_fun(double *state, double *out_5784827875755482895) {
   out_5784827875755482895[0] = 1.0;
   out_5784827875755482895[1] = 0.0;
   out_5784827875755482895[2] = 0.0;
   out_5784827875755482895[3] = 0.0;
   out_5784827875755482895[4] = 0.0;
   out_5784827875755482895[5] = 0.0;
   out_5784827875755482895[6] = 0.0;
   out_5784827875755482895[7] = 0.0;
   out_5784827875755482895[8] = 0.0;
   out_5784827875755482895[9] = 1.0;
   out_5784827875755482895[10] = 0.0;
   out_5784827875755482895[11] = 0.0;
   out_5784827875755482895[12] = 0.0;
   out_5784827875755482895[13] = 0.0;
   out_5784827875755482895[14] = 0.0;
   out_5784827875755482895[15] = 0.0;
   out_5784827875755482895[16] = 0.0;
   out_5784827875755482895[17] = 0.0;
   out_5784827875755482895[18] = 1.0;
   out_5784827875755482895[19] = 0.0;
   out_5784827875755482895[20] = 0.0;
   out_5784827875755482895[21] = 0.0;
   out_5784827875755482895[22] = 0.0;
   out_5784827875755482895[23] = 0.0;
   out_5784827875755482895[24] = 0.0;
   out_5784827875755482895[25] = 0.0;
   out_5784827875755482895[26] = 0.0;
   out_5784827875755482895[27] = 1.0;
   out_5784827875755482895[28] = 0.0;
   out_5784827875755482895[29] = 0.0;
   out_5784827875755482895[30] = 0.0;
   out_5784827875755482895[31] = 0.0;
   out_5784827875755482895[32] = 0.0;
   out_5784827875755482895[33] = 0.0;
   out_5784827875755482895[34] = 0.0;
   out_5784827875755482895[35] = 0.0;
   out_5784827875755482895[36] = 1.0;
   out_5784827875755482895[37] = 0.0;
   out_5784827875755482895[38] = 0.0;
   out_5784827875755482895[39] = 0.0;
   out_5784827875755482895[40] = 0.0;
   out_5784827875755482895[41] = 0.0;
   out_5784827875755482895[42] = 0.0;
   out_5784827875755482895[43] = 0.0;
   out_5784827875755482895[44] = 0.0;
   out_5784827875755482895[45] = 1.0;
   out_5784827875755482895[46] = 0.0;
   out_5784827875755482895[47] = 0.0;
   out_5784827875755482895[48] = 0.0;
   out_5784827875755482895[49] = 0.0;
   out_5784827875755482895[50] = 0.0;
   out_5784827875755482895[51] = 0.0;
   out_5784827875755482895[52] = 0.0;
   out_5784827875755482895[53] = 0.0;
   out_5784827875755482895[54] = 1.0;
   out_5784827875755482895[55] = 0.0;
   out_5784827875755482895[56] = 0.0;
   out_5784827875755482895[57] = 0.0;
   out_5784827875755482895[58] = 0.0;
   out_5784827875755482895[59] = 0.0;
   out_5784827875755482895[60] = 0.0;
   out_5784827875755482895[61] = 0.0;
   out_5784827875755482895[62] = 0.0;
   out_5784827875755482895[63] = 1.0;
}
void f_fun(double *state, double dt, double *out_4784948249018072058) {
   out_4784948249018072058[0] = state[0];
   out_4784948249018072058[1] = state[1];
   out_4784948249018072058[2] = state[2];
   out_4784948249018072058[3] = state[3];
   out_4784948249018072058[4] = state[4];
   out_4784948249018072058[5] = dt*((-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]))*state[6] + stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*state[1]) + (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*state[4])) + state[5];
   out_4784948249018072058[6] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*state[4])) + state[6];
   out_4784948249018072058[7] = state[7];
}
void F_fun(double *state, double dt, double *out_7213482438976527624) {
   out_7213482438976527624[0] = 1;
   out_7213482438976527624[1] = 0;
   out_7213482438976527624[2] = 0;
   out_7213482438976527624[3] = 0;
   out_7213482438976527624[4] = 0;
   out_7213482438976527624[5] = 0;
   out_7213482438976527624[6] = 0;
   out_7213482438976527624[7] = 0;
   out_7213482438976527624[8] = 0;
   out_7213482438976527624[9] = 1;
   out_7213482438976527624[10] = 0;
   out_7213482438976527624[11] = 0;
   out_7213482438976527624[12] = 0;
   out_7213482438976527624[13] = 0;
   out_7213482438976527624[14] = 0;
   out_7213482438976527624[15] = 0;
   out_7213482438976527624[16] = 0;
   out_7213482438976527624[17] = 0;
   out_7213482438976527624[18] = 1;
   out_7213482438976527624[19] = 0;
   out_7213482438976527624[20] = 0;
   out_7213482438976527624[21] = 0;
   out_7213482438976527624[22] = 0;
   out_7213482438976527624[23] = 0;
   out_7213482438976527624[24] = 0;
   out_7213482438976527624[25] = 0;
   out_7213482438976527624[26] = 0;
   out_7213482438976527624[27] = 1;
   out_7213482438976527624[28] = 0;
   out_7213482438976527624[29] = 0;
   out_7213482438976527624[30] = 0;
   out_7213482438976527624[31] = 0;
   out_7213482438976527624[32] = 0;
   out_7213482438976527624[33] = 0;
   out_7213482438976527624[34] = 0;
   out_7213482438976527624[35] = 0;
   out_7213482438976527624[36] = 1;
   out_7213482438976527624[37] = 0;
   out_7213482438976527624[38] = 0;
   out_7213482438976527624[39] = 0;
   out_7213482438976527624[40] = dt*(stiffness_front*(-state[2] - state[3] + state[7])/(mass*state[1]) + (-stiffness_front - stiffness_rear)*state[5]/(mass*state[4]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[6]/(mass*state[4]));
   out_7213482438976527624[41] = -dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*pow(state[1], 2));
   out_7213482438976527624[42] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_7213482438976527624[43] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_7213482438976527624[44] = dt*((-1 - (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*pow(state[4], 2)))*state[6] - (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*pow(state[4], 2)));
   out_7213482438976527624[45] = dt*(-stiffness_front*state[0] - stiffness_rear*state[0])/(mass*state[4]) + 1;
   out_7213482438976527624[46] = dt*(-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]));
   out_7213482438976527624[47] = dt*stiffness_front*state[0]/(mass*state[1]);
   out_7213482438976527624[48] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front - pow(center_to_rear, 2)*stiffness_rear)*state[6]/(rotational_inertia*state[4]));
   out_7213482438976527624[49] = -center_to_front*dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*pow(state[1], 2));
   out_7213482438976527624[50] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_7213482438976527624[51] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_7213482438976527624[52] = dt*(-(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*pow(state[4], 2)) - (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*pow(state[4], 2)));
   out_7213482438976527624[53] = dt*(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(rotational_inertia*state[4]);
   out_7213482438976527624[54] = dt*(-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])/(rotational_inertia*state[4]) + 1;
   out_7213482438976527624[55] = center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_7213482438976527624[56] = 0;
   out_7213482438976527624[57] = 0;
   out_7213482438976527624[58] = 0;
   out_7213482438976527624[59] = 0;
   out_7213482438976527624[60] = 0;
   out_7213482438976527624[61] = 0;
   out_7213482438976527624[62] = 0;
   out_7213482438976527624[63] = 1;
}
void h_25(double *state, double *unused, double *out_6070939476778450913) {
   out_6070939476778450913[0] = state[6];
}
void H_25(double *state, double *unused, double *out_3635882763779488203) {
   out_3635882763779488203[0] = 0;
   out_3635882763779488203[1] = 0;
   out_3635882763779488203[2] = 0;
   out_3635882763779488203[3] = 0;
   out_3635882763779488203[4] = 0;
   out_3635882763779488203[5] = 0;
   out_3635882763779488203[6] = 1;
   out_3635882763779488203[7] = 0;
}
void h_24(double *state, double *unused, double *out_5018193019904744090) {
   out_5018193019904744090[0] = state[4];
   out_5018193019904744090[1] = state[5];
}
void H_24(double *state, double *unused, double *out_1486972335290855686) {
   out_1486972335290855686[0] = 0;
   out_1486972335290855686[1] = 0;
   out_1486972335290855686[2] = 0;
   out_1486972335290855686[3] = 0;
   out_1486972335290855686[4] = 1;
   out_1486972335290855686[5] = 0;
   out_1486972335290855686[6] = 0;
   out_1486972335290855686[7] = 0;
   out_1486972335290855686[8] = 0;
   out_1486972335290855686[9] = 0;
   out_1486972335290855686[10] = 0;
   out_1486972335290855686[11] = 0;
   out_1486972335290855686[12] = 0;
   out_1486972335290855686[13] = 1;
   out_1486972335290855686[14] = 0;
   out_1486972335290855686[15] = 0;
}
void h_30(double *state, double *unused, double *out_2433489948524428563) {
   out_2433489948524428563[0] = state[4];
}
void H_30(double *state, double *unused, double *out_5196962398980880133) {
   out_5196962398980880133[0] = 0;
   out_5196962398980880133[1] = 0;
   out_5196962398980880133[2] = 0;
   out_5196962398980880133[3] = 0;
   out_5196962398980880133[4] = 1;
   out_5196962398980880133[5] = 0;
   out_5196962398980880133[6] = 0;
   out_5196962398980880133[7] = 0;
}
void h_26(double *state, double *unused, double *out_3415574041859726675) {
   out_3415574041859726675[0] = state[7];
}
void H_26(double *state, double *unused, double *out_9071067793250047733) {
   out_9071067793250047733[0] = 0;
   out_9071067793250047733[1] = 0;
   out_9071067793250047733[2] = 0;
   out_9071067793250047733[3] = 0;
   out_9071067793250047733[4] = 0;
   out_9071067793250047733[5] = 0;
   out_9071067793250047733[6] = 0;
   out_9071067793250047733[7] = 1;
}
void h_27(double *state, double *unused, double *out_1069266209117605268) {
   out_1069266209117605268[0] = state[3];
}
void H_27(double *state, double *unused, double *out_3909380411144254821) {
   out_3909380411144254821[0] = 0;
   out_3909380411144254821[1] = 0;
   out_3909380411144254821[2] = 0;
   out_3909380411144254821[3] = 1;
   out_3909380411144254821[4] = 0;
   out_3909380411144254821[5] = 0;
   out_3909380411144254821[6] = 0;
   out_3909380411144254821[7] = 0;
}
void h_29(double *state, double *unused, double *out_2568183319136417082) {
   out_2568183319136417082[0] = state[1];
}
void H_29(double *state, double *unused, double *out_1373163629852048180) {
   out_1373163629852048180[0] = 0;
   out_1373163629852048180[1] = 1;
   out_1373163629852048180[2] = 0;
   out_1373163629852048180[3] = 0;
   out_1373163629852048180[4] = 0;
   out_1373163629852048180[5] = 0;
   out_1373163629852048180[6] = 0;
   out_1373163629852048180[7] = 0;
}
void h_28(double *state, double *unused, double *out_4730952811712112891) {
   out_4730952811712112891[0] = state[5];
   out_4730952811712112891[1] = state[6];
}
void H_28(double *state, double *unused, double *out_8504804813527350552) {
   out_8504804813527350552[0] = 0;
   out_8504804813527350552[1] = 0;
   out_8504804813527350552[2] = 0;
   out_8504804813527350552[3] = 0;
   out_8504804813527350552[4] = 0;
   out_8504804813527350552[5] = 1;
   out_8504804813527350552[6] = 0;
   out_8504804813527350552[7] = 0;
   out_8504804813527350552[8] = 0;
   out_8504804813527350552[9] = 0;
   out_8504804813527350552[10] = 0;
   out_8504804813527350552[11] = 0;
   out_8504804813527350552[12] = 0;
   out_8504804813527350552[13] = 0;
   out_8504804813527350552[14] = 1;
   out_8504804813527350552[15] = 0;
}
#include <eigen3/Eigen/Dense>
#include <iostream>

typedef Eigen::Matrix<double, DIM, DIM, Eigen::RowMajor> DDM;
typedef Eigen::Matrix<double, EDIM, EDIM, Eigen::RowMajor> EEM;
typedef Eigen::Matrix<double, DIM, EDIM, Eigen::RowMajor> DEM;

void predict(double *in_x, double *in_P, double *in_Q, double dt) {
  typedef Eigen::Matrix<double, MEDIM, MEDIM, Eigen::RowMajor> RRM;

  double nx[DIM] = {0};
  double in_F[EDIM*EDIM] = {0};

  // functions from sympy
  f_fun(in_x, dt, nx);
  F_fun(in_x, dt, in_F);


  EEM F(in_F);
  EEM P(in_P);
  EEM Q(in_Q);

  RRM F_main = F.topLeftCorner(MEDIM, MEDIM);
  P.topLeftCorner(MEDIM, MEDIM) = (F_main * P.topLeftCorner(MEDIM, MEDIM)) * F_main.transpose();
  P.topRightCorner(MEDIM, EDIM - MEDIM) = F_main * P.topRightCorner(MEDIM, EDIM - MEDIM);
  P.bottomLeftCorner(EDIM - MEDIM, MEDIM) = P.bottomLeftCorner(EDIM - MEDIM, MEDIM) * F_main.transpose();

  P = P + dt*Q;

  // copy out state
  memcpy(in_x, nx, DIM * sizeof(double));
  memcpy(in_P, P.data(), EDIM * EDIM * sizeof(double));
}

// note: extra_args dim only correct when null space projecting
// otherwise 1
template <int ZDIM, int EADIM, bool MAHA_TEST>
void update(double *in_x, double *in_P, Hfun h_fun, Hfun H_fun, Hfun Hea_fun, double *in_z, double *in_R, double *in_ea, double MAHA_THRESHOLD) {
  typedef Eigen::Matrix<double, ZDIM, ZDIM, Eigen::RowMajor> ZZM;
  typedef Eigen::Matrix<double, ZDIM, DIM, Eigen::RowMajor> ZDM;
  typedef Eigen::Matrix<double, Eigen::Dynamic, EDIM, Eigen::RowMajor> XEM;
  //typedef Eigen::Matrix<double, EDIM, ZDIM, Eigen::RowMajor> EZM;
  typedef Eigen::Matrix<double, Eigen::Dynamic, 1> X1M;
  typedef Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> XXM;

  double in_hx[ZDIM] = {0};
  double in_H[ZDIM * DIM] = {0};
  double in_H_mod[EDIM * DIM] = {0};
  double delta_x[EDIM] = {0};
  double x_new[DIM] = {0};


  // state x, P
  Eigen::Matrix<double, ZDIM, 1> z(in_z);
  EEM P(in_P);
  ZZM pre_R(in_R);

  // functions from sympy
  h_fun(in_x, in_ea, in_hx);
  H_fun(in_x, in_ea, in_H);
  ZDM pre_H(in_H);

  // get y (y = z - hx)
  Eigen::Matrix<double, ZDIM, 1> pre_y(in_hx); pre_y = z - pre_y;
  X1M y; XXM H; XXM R;
  if (Hea_fun){
    typedef Eigen::Matrix<double, ZDIM, EADIM, Eigen::RowMajor> ZAM;
    double in_Hea[ZDIM * EADIM] = {0};
    Hea_fun(in_x, in_ea, in_Hea);
    ZAM Hea(in_Hea);
    XXM A = Hea.transpose().fullPivLu().kernel();


    y = A.transpose() * pre_y;
    H = A.transpose() * pre_H;
    R = A.transpose() * pre_R * A;
  } else {
    y = pre_y;
    H = pre_H;
    R = pre_R;
  }
  // get modified H
  H_mod_fun(in_x, in_H_mod);
  DEM H_mod(in_H_mod);
  XEM H_err = H * H_mod;

  // Do mahalobis distance test
  if (MAHA_TEST){
    XXM a = (H_err * P * H_err.transpose() + R).inverse();
    double maha_dist = y.transpose() * a * y;
    if (maha_dist > MAHA_THRESHOLD){
      R = 1.0e16 * R;
    }
  }

  // Outlier resilient weighting
  double weight = 1;//(1.5)/(1 + y.squaredNorm()/R.sum());

  // kalman gains and I_KH
  XXM S = ((H_err * P) * H_err.transpose()) + R/weight;
  XEM KT = S.fullPivLu().solve(H_err * P.transpose());
  //EZM K = KT.transpose(); TODO: WHY DOES THIS NOT COMPILE?
  //EZM K = S.fullPivLu().solve(H_err * P.transpose()).transpose();
  //std::cout << "Here is the matrix rot:\n" << K << std::endl;
  EEM I_KH = Eigen::Matrix<double, EDIM, EDIM>::Identity() - (KT.transpose() * H_err);

  // update state by injecting dx
  Eigen::Matrix<double, EDIM, 1> dx(delta_x);
  dx  = (KT.transpose() * y);
  memcpy(delta_x, dx.data(), EDIM * sizeof(double));
  err_fun(in_x, delta_x, x_new);
  Eigen::Matrix<double, DIM, 1> x(x_new);

  // update cov
  P = ((I_KH * P) * I_KH.transpose()) + ((KT.transpose() * R) * KT);

  // copy out state
  memcpy(in_x, x.data(), DIM * sizeof(double));
  memcpy(in_P, P.data(), EDIM * EDIM * sizeof(double));
  memcpy(in_z, y.data(), y.rows() * sizeof(double));
}




}
extern "C" {

void car_update_25(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_25, H_25, NULL, in_z, in_R, in_ea, MAHA_THRESH_25);
}
void car_update_24(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<2, 3, 0>(in_x, in_P, h_24, H_24, NULL, in_z, in_R, in_ea, MAHA_THRESH_24);
}
void car_update_30(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_30, H_30, NULL, in_z, in_R, in_ea, MAHA_THRESH_30);
}
void car_update_26(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_26, H_26, NULL, in_z, in_R, in_ea, MAHA_THRESH_26);
}
void car_update_27(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_27, H_27, NULL, in_z, in_R, in_ea, MAHA_THRESH_27);
}
void car_update_29(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_29, H_29, NULL, in_z, in_R, in_ea, MAHA_THRESH_29);
}
void car_update_28(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<2, 3, 0>(in_x, in_P, h_28, H_28, NULL, in_z, in_R, in_ea, MAHA_THRESH_28);
}
void car_err_fun(double *nom_x, double *delta_x, double *out_656386073162142696) {
  err_fun(nom_x, delta_x, out_656386073162142696);
}
void car_inv_err_fun(double *nom_x, double *true_x, double *out_6364770466875885701) {
  inv_err_fun(nom_x, true_x, out_6364770466875885701);
}
void car_H_mod_fun(double *state, double *out_5784827875755482895) {
  H_mod_fun(state, out_5784827875755482895);
}
void car_f_fun(double *state, double dt, double *out_4784948249018072058) {
  f_fun(state,  dt, out_4784948249018072058);
}
void car_F_fun(double *state, double dt, double *out_7213482438976527624) {
  F_fun(state,  dt, out_7213482438976527624);
}
void car_h_25(double *state, double *unused, double *out_6070939476778450913) {
  h_25(state, unused, out_6070939476778450913);
}
void car_H_25(double *state, double *unused, double *out_3635882763779488203) {
  H_25(state, unused, out_3635882763779488203);
}
void car_h_24(double *state, double *unused, double *out_5018193019904744090) {
  h_24(state, unused, out_5018193019904744090);
}
void car_H_24(double *state, double *unused, double *out_1486972335290855686) {
  H_24(state, unused, out_1486972335290855686);
}
void car_h_30(double *state, double *unused, double *out_2433489948524428563) {
  h_30(state, unused, out_2433489948524428563);
}
void car_H_30(double *state, double *unused, double *out_5196962398980880133) {
  H_30(state, unused, out_5196962398980880133);
}
void car_h_26(double *state, double *unused, double *out_3415574041859726675) {
  h_26(state, unused, out_3415574041859726675);
}
void car_H_26(double *state, double *unused, double *out_9071067793250047733) {
  H_26(state, unused, out_9071067793250047733);
}
void car_h_27(double *state, double *unused, double *out_1069266209117605268) {
  h_27(state, unused, out_1069266209117605268);
}
void car_H_27(double *state, double *unused, double *out_3909380411144254821) {
  H_27(state, unused, out_3909380411144254821);
}
void car_h_29(double *state, double *unused, double *out_2568183319136417082) {
  h_29(state, unused, out_2568183319136417082);
}
void car_H_29(double *state, double *unused, double *out_1373163629852048180) {
  H_29(state, unused, out_1373163629852048180);
}
void car_h_28(double *state, double *unused, double *out_4730952811712112891) {
  h_28(state, unused, out_4730952811712112891);
}
void car_H_28(double *state, double *unused, double *out_8504804813527350552) {
  H_28(state, unused, out_8504804813527350552);
}
void car_predict(double *in_x, double *in_P, double *in_Q, double dt) {
  predict(in_x, in_P, in_Q, dt);
}
void car_set_mass(double x) {
  set_mass(x);
}
void car_set_rotational_inertia(double x) {
  set_rotational_inertia(x);
}
void car_set_center_to_front(double x) {
  set_center_to_front(x);
}
void car_set_center_to_rear(double x) {
  set_center_to_rear(x);
}
void car_set_stiffness_front(double x) {
  set_stiffness_front(x);
}
void car_set_stiffness_rear(double x) {
  set_stiffness_rear(x);
}
}

const EKF car = {
  .name = "car",
  .kinds = { 25, 24, 30, 26, 27, 29, 28 },
  .feature_kinds = {  },
  .f_fun = car_f_fun,
  .F_fun = car_F_fun,
  .err_fun = car_err_fun,
  .inv_err_fun = car_inv_err_fun,
  .H_mod_fun = car_H_mod_fun,
  .predict = car_predict,
  .hs = {
    { 25, car_h_25 },
    { 24, car_h_24 },
    { 30, car_h_30 },
    { 26, car_h_26 },
    { 27, car_h_27 },
    { 29, car_h_29 },
    { 28, car_h_28 },
  },
  .Hs = {
    { 25, car_H_25 },
    { 24, car_H_24 },
    { 30, car_H_30 },
    { 26, car_H_26 },
    { 27, car_H_27 },
    { 29, car_H_29 },
    { 28, car_H_28 },
  },
  .updates = {
    { 25, car_update_25 },
    { 24, car_update_24 },
    { 30, car_update_30 },
    { 26, car_update_26 },
    { 27, car_update_27 },
    { 29, car_update_29 },
    { 28, car_update_28 },
  },
  .Hes = {
  },
  .sets = {
    { "mass", car_set_mass },
    { "rotational_inertia", car_set_rotational_inertia },
    { "center_to_front", car_set_center_to_front },
    { "center_to_rear", car_set_center_to_rear },
    { "stiffness_front", car_set_stiffness_front },
    { "stiffness_rear", car_set_stiffness_rear },
  },
  .extra_routines = {
  },
};

ekf_init(car);
