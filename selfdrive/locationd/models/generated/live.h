#pragma once
#include "rednose/helpers/common_ekf.h"
extern "C" {
void live_update_3(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void live_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void live_update_9(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void live_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void live_update_12(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void live_update_31(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void live_update_32(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void live_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void live_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void live_update_19(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void live_H(double *in_vec, double *out_4233302688709425266);
void live_err_fun(double *nom_x, double *delta_x, double *out_4273520066785401603);
void live_inv_err_fun(double *nom_x, double *true_x, double *out_4826103417296251508);
void live_H_mod_fun(double *state, double *out_7792921849896927623);
void live_f_fun(double *state, double dt, double *out_7869216496498970073);
void live_F_fun(double *state, double dt, double *out_6631631348585393411);
void live_h_3(double *state, double *unused, double *out_8998705670573364883);
void live_H_3(double *state, double *unused, double *out_2064290846329223401);
void live_h_4(double *state, double *unused, double *out_2756800075984724049);
void live_H_4(double *state, double *unused, double *out_3482317657312440221);
void live_h_9(double *state, double *unused, double *out_6060726641280678760);
void live_H_9(double *state, double *unused, double *out_5886217175193272574);
void live_h_10(double *state, double *unused, double *out_4206508064086815672);
void live_H_10(double *state, double *unused, double *out_8155068646903260766);
void live_h_12(double *state, double *unused, double *out_4399637049474057946);
void live_H_12(double *state, double *unused, double *out_5670267143061626173);
void live_h_31(double *state, double *unused, double *out_7952378525658436416);
void live_H_31(double *state, double *unused, double *out_2995177367918206352);
void live_h_32(double *state, double *unused, double *out_8191949464342438162);
void live_H_32(double *state, double *unused, double *out_8169338586421979186);
void live_h_13(double *state, double *unused, double *out_7266635863376956358);
void live_H_13(double *state, double *unused, double *out_4152505283217795255);
void live_h_14(double *state, double *unused, double *out_6060726641280678760);
void live_H_14(double *state, double *unused, double *out_5886217175193272574);
void live_h_19(double *state, double *unused, double *out_7293144340774564380);
void live_H_19(double *state, double *unused, double *out_8127847047413847861);
void live_predict(double *in_x, double *in_P, double *in_Q, double dt);
}