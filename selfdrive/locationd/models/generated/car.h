#pragma once
#include "rednose/helpers/common_ekf.h"
extern "C" {
void car_update_25(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_24(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_30(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_26(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_27(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_29(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_28(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_err_fun(double *nom_x, double *delta_x, double *out_656386073162142696);
void car_inv_err_fun(double *nom_x, double *true_x, double *out_6364770466875885701);
void car_H_mod_fun(double *state, double *out_5784827875755482895);
void car_f_fun(double *state, double dt, double *out_4784948249018072058);
void car_F_fun(double *state, double dt, double *out_7213482438976527624);
void car_h_25(double *state, double *unused, double *out_6070939476778450913);
void car_H_25(double *state, double *unused, double *out_3635882763779488203);
void car_h_24(double *state, double *unused, double *out_5018193019904744090);
void car_H_24(double *state, double *unused, double *out_1486972335290855686);
void car_h_30(double *state, double *unused, double *out_2433489948524428563);
void car_H_30(double *state, double *unused, double *out_5196962398980880133);
void car_h_26(double *state, double *unused, double *out_3415574041859726675);
void car_H_26(double *state, double *unused, double *out_9071067793250047733);
void car_h_27(double *state, double *unused, double *out_1069266209117605268);
void car_H_27(double *state, double *unused, double *out_3909380411144254821);
void car_h_29(double *state, double *unused, double *out_2568183319136417082);
void car_H_29(double *state, double *unused, double *out_1373163629852048180);
void car_h_28(double *state, double *unused, double *out_4730952811712112891);
void car_H_28(double *state, double *unused, double *out_8504804813527350552);
void car_predict(double *in_x, double *in_P, double *in_Q, double dt);
void car_set_mass(double x);
void car_set_rotational_inertia(double x);
void car_set_center_to_front(double x);
void car_set_center_to_rear(double x);
void car_set_stiffness_front(double x);
void car_set_stiffness_rear(double x);
}