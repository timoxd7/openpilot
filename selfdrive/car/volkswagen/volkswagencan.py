# CAN controls for MQB platform Volkswagen, Audi, Skoda and SEAT.
# PQ35/PQ46/NMS, and any future MLB, to come later.

def create_mqb_steering_control(packer, bus, apply_steer, idx, lkas_enabled):
  values = {
    "SET_ME_0X3": 0x3,
    "Assist_Torque": abs(apply_steer),
    "Assist_Requested": lkas_enabled,
    "Assist_VZ": 1 if apply_steer < 0 else 0,
    "HCA_Available": 1,
    "HCA_Standby": not lkas_enabled,
    "HCA_Active": lkas_enabled,
    "SET_ME_0XFE": 0xFE,
    "SET_ME_0X07": 0x07,
  }
  return packer.make_can_msg("HCA_01", bus, values, idx)

def create_mqb_hud_control(packer, bus, enabled, steering_pressed, hud_alert, left_lane_visible, right_lane_visible,
                           ldw_lane_warning_left, ldw_lane_warning_right, ldw_side_dlc_tlc, ldw_dlc, ldw_tlc,
                           standstill, left_lane_depart, right_lane_depart):
  # Lane color reference:
  # 0 (LKAS disabled) - off
  # 1 (LKAS enabled, no lane detected) - dark gray
  # 2 (LKAS enabled, lane detected) - light gray on VW, green or white on Audi depending on year or virtual cockpit.  On a color MFD on a 2015 A3 TDI it is white, virtual cockpit on a 2018 A3 e-Tron its green.
  # 3 (LKAS enabled, lane departure detected) - white on VW, red on Audi

  values = {
    "LDW_Status_LED_gelb": 1 if enabled and steering_pressed else 0,
    "LDW_Status_LED_gruen": 1 if enabled and not steering_pressed else 0,
    "LDW_Lernmodus_links": 3 if left_lane_depart else 1 + left_lane_visible,
    "LDW_Lernmodus_rechts": 3 if right_lane_depart else 1 + right_lane_visible,
    "LDW_Texte": hud_alert,
    "LDW_SW_Warnung_links": ldw_lane_warning_left,
    "LDW_SW_Warnung_rechts": ldw_lane_warning_right,
    "LDW_Seite_DLCTLC": ldw_side_dlc_tlc,
    "LDW_DLC": ldw_dlc,
    "LDW_TLC": ldw_tlc
  }
  return packer.make_can_msg("LDW_02", bus, values)

def create_mqb_acc_buttons_control(packer, bus, buttonStatesToSend, CS, idx):
  values = {
    "GRA_Hauptschalter": CS.graHauptschalter,
    "GRA_Abbrechen": buttonStatesToSend["cancel"],
    "GRA_Tip_Setzen": buttonStatesToSend["setCruise"],
    "GRA_Tip_Hoch": buttonStatesToSend["accelCruise"],
    "GRA_Tip_Runter": buttonStatesToSend["decelCruise"],
    "GRA_Tip_Wiederaufnahme": buttonStatesToSend["resumeCruise"],
    "GRA_Verstellung_Zeitluecke": 3 if buttonStatesToSend["gapAdjustCruise"] else 0,
    "GRA_Typ_Hauptschalter": CS.graTypHauptschalter,
    "GRA_Codierung": 2,
    "GRA_Tip_Stufe_2": CS.graTipStufe2,
    "GRA_ButtonTypeInfo": CS.graButtonTypeInfo
  }
  return packer.make_can_msg("GRA_ACC_01", bus, values, idx)

def create_mqb_acc_control(packer, bus, acc_status, apply_accel, stop_req, standstill, idx):
  values = {
    "ACC_Typ": 2,  # FIXME: locked to stop and go, need to tweak for cars that only support follow-to-stop
    "ACC_Status_ACC": acc_status,
    "ACC_StartStopp_Info": 1 if acc_status == 3 and not standstill else 0,
    "ACC_Sollbeschleunigung_02": apply_accel if acc_status == 3 else 3.01,
    "ACC_zul_Regelabw_unten": 0.25 if acc_status == 3 and not stop_req else 0,  # FIXME: need comfort regulation logic here
    "ACC_zul_Regelabw_oben": 0.25 if acc_status == 3 and not stop_req else 0,  # FIXME: need comfort regulation logic here
    "ACC_neg_Sollbeschl_Grad_02": 5.0 if acc_status == 3 else 0,  # FIXME: need gradient regulation logic here
    "ACC_pos_Sollbeschl_Grad_02": 5.0 if acc_status == 3 else 0,  # FIXME: need gradient regulation logic here
    "ACC_Anfahren": 0,  # NOTE: set briefly when preparing for start from standstill, probably predictive engine start
    "ACC_Anhalten": acc_status == 3 and stop_req
  }

  return packer.make_can_msg("ACC_06", bus, values, idx)

def create_mqb_acc_hud_control(packer, bus, acc_status, speed_visible, set_speed, idx):
  values = {
    "ACC_Status_Anzeige": acc_status,
    "ACC_Wunschgeschw": set_speed if speed_visible else 327.36,
    "ACC_Gesetzte_Zeitluecke": 3,
    "ACC_Display_Prio": 3
  }

  return packer.make_can_msg("ACC_02", bus, values, idx)

def create_pq_steering_control(packer, bus, apply_steer, idx, lkas_enabled):
  values = {
    "HCA_Zaehler": idx,
    "LM_Offset": abs(apply_steer),
    "LM_OffSign": 1 if apply_steer < 0 else 0,
    "HCA_Status": 5 if (lkas_enabled and apply_steer != 0) else 3,
    "Vib_Freq": 16,
  }

  dat = packer.make_can_msg("HCA_1", bus, values)[2]
  values["HCA_Checksumme"] = dat[1] ^ dat[2] ^ dat[3] ^ dat[4]
  return packer.make_can_msg("HCA_1", bus, values)

def create_pq_hud_control(packer, bus, hca_enabled, steering_pressed, hud_alert, left_lane_visible, right_lane_visible,
                          ldw_lane_warning_left, ldw_lane_warning_right, ldw_side_dlc_tlc, ldw_dlc, ldw_tlc,
                          standstill, left_lane_depart, right_lane_depart):
  if hca_enabled:
    left_lane_hud = 3 if left_lane_depart else 1 + left_lane_visible
    right_lane_hud = 3 if right_lane_depart else 1 + right_lane_visible
  else:
    left_lane_hud = 0
    right_lane_hud = 0

  values = {
    "Right_Lane_Status": right_lane_hud,
    "Left_Lane_Status": left_lane_hud,
    "SET_ME_X1": 1,
    "Kombi_Lamp_Orange": 1 if hca_enabled and steering_pressed else 0,
    "Kombi_Lamp_Green": 1 if hca_enabled and not steering_pressed else 0,
  }
  return packer.make_can_msg("LDW_1", bus, values)

def create_pq_acc_buttons_control(packer, bus, buttonStatesToSend, CS, idx):
  values = {
    "GRA_Neu_Zaehler": idx,
    "GRA_Sender": CS.graSenderCoding,
    "GRA_Abbrechen": 1 if (buttonStatesToSend["cancel"] or CS.buttonStates["cancel"]) else 0,
    "GRA_Hauptschalt": CS.graHauptschalter,
  }

  dat = packer.make_can_msg("GRA_Neu", bus, values)[2]
  values["GRA_Checksum"] = dat[1] ^ dat[2] ^ dat[3]
  return packer.make_can_msg("GRA_Neu", bus, values)

def create_pq_acc_control(packer, bus, acc_status, apply_accel, stop_req, standstill, idx):
  values = {
    "ACS_Zaehler": idx,
    "ACS_Typ_ACC": 2,  # FIXME: locked to stop and go, need to tweak for cars that only support follow-to-stop
    "ACS_Sta_ADR": acc_status,  # TODO: NOT SURE
    "ACS_StSt_Info": 1 if acc_status == 3 and not standstill else 0,
    "ACS_Sollbeschl": apply_accel if acc_status == 3 else 3.01,
    "ACS_Anhaltewunsch": acc_status == 3 and stop_req,
    "ACS_FreigSollB": 0,  # TODO: NOT SURE
    "ACS_Fehler": 0,  # TODO: NOT SURE
    "ACS_MomEingriff": 0,  # TODO: NOT SURE
    "ACS_Schubabsch": 0,  # TODO: NOT SURE
    "ACS_ADR_Schub": 1,  # TODO: NOT SURE
    "ACS_zul_Regelabw": 0.25 if acc_status == 3 and not stop_req else 0,  # FIXME: need comfort regulation logic here
    "ACS_max_AendGrad": 0.25 if acc_status == 3 and not stop_req else 0,  # FIXME: need comfort regulation logic here
  }

  dat = packer.make_can_msg("ACC_System", bus, values)[2]
  values["ACS_Checksum"] = dat[1] ^ dat[2] ^ dat[3] ^ dat[4] ^ dat[5] ^ dat[6] ^ dat[7]
  return packer.make_can_msg("ACC_System", bus, values)

def create_pq_acc_hud_control(packer, bus, acc_status, speed_visible, set_speed, idx):
  values = {
    "ACA_Zaehler": idx,
    "ACA_StaACC": acc_status,
    "ACA_V_Wunsch": set_speed if speed_visible else 327.36,
    "ACA_Zeitluecke": 3,
    "ACA_PrioDisp": 1,
  }

  dat = packer.make_can_msg("ACC_GRA_Anziege", bus, values)[2]
  values["ACA_Checksum"] = dat[1] ^ dat[2] ^ dat[3] ^ dat[4] ^ dat[5] ^ dat[6] ^ dat[7]
  return packer.make_can_msg("ACC_GRA_Anziege", bus, values)
