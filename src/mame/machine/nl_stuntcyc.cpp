// license:BSD-3-Clause
// copyright-holders:Ryan Holtz

/***************************************************************************

  Netlist (stuntcyc) included from atarittl.cpp

***************************************************************************/

#include "netlist/devices/net_lib.h"

NETLIST_START(stuntcyc)

	SOLVER(Solver, 48000)
	PARAM(Solver.PARALLEL, 0) // Don't do parallel solvers
	PARAM(Solver.ACCURACY, 1e-4) // works and is sufficient
	PARAM(NETLIST.USE_DEACTIVATE, 1)

	ANALOG_INPUT(V5, 5)

	TTL_INPUT(high, 1)
	TTL_INPUT(low, 0)

	MAINCLOCK(main_clk, 14318181.8)
	ALIAS(Y1, main_clk)

#if 0
	TTL_7404_INVERT(N3_6, main_clk)
	ALIAS(HF_CLOCK, N3_6.Q)

	ALIAS(P, high)
	ALIAS(GND, low)

	TTL_7474(N4_2, N3_6.Q, N4_2.QQ, P, P)
	ALIAS(CLOCK,  N4_2.Q)
	ALIAS(CLOCK_Q, N4_2.QQ)

	TTL_9316(M4, N4_2.Q,     P, P, P, J6_1.Q, GND, GND, GND, GND)
	TTL_9316(L4, N4_2.Q, M4.RC, P, P, J6_1.Q, GND, GND, GND, GND)
	ALIAS(  1H, M4.QA)
	ALIAS(  2H, M4.QB)
	ALIAS(  4H, M4.QC)
	ALIAS(  8H, M4.QD)
	ALIAS( 16H, L4.QA)
	ALIAS( 32H, L4.QB)
	ALIAS( 64H, L4.QC)
	ALIAS(128H, L4.QD)

	TTL_74107(K4_1, 128H, P, P, P)
	ALIAS(256H,  K4_1.Q)
	ALIAS(256H_Q, K4_1.QQ)

	TTL_7420_NAND(J6_1, 8H, 64H, 128H, 256H)
	ALIAS(HRESET_Q, J6_1.Q)

	TTL_7404_INVERT(H6_3, HRESET_Q)
	ALIAS(HRESET, H6_3.Q)

	TTL_7493(L3, HRESET, L3.QA, VRESET, VRESET)
	TTL_7493(K3, L3.QD,  K3.QA, VRESET, VRESET)
	ALIAS(  1V, L3.QA)
	ALIAS(  2V, L3.QB)
	ALIAS(  4V, L3.QC)
	ALIAS(  8V, L3.QD)
	ALIAS( 16V, K3.QA)
	ALIAS( 32V, K3.QB)
	ALIAS( 64V, K3.QC)
	ALIAS(128V, K3.QD)

	TTL_74107(K4_2, 128V, P, P, VRESETQ)
	ALIAS(256V, K4_2.Q)
	ALIAS(256V_Q, K4_2.QQ)

	TTL_7410_NAND(M5_3, 256V, 2V, 1V)
	TTL_7474(M3_2, HRESET, M5_3.Q, P, P)
	ALIAS(VRESET, M3_2.QQ)
	ALIAS(VRESETQ, M3_2.Q)

	TTL_7402_NOR(J5_2, H6_3.Q, J5_1.Q)
	TTL_7402_NOR(J5_1, 32H,    J5_2.Q)
	TTL_7402_NOR(J5_3,  8V,    J5_4.Q)
	TTL_7402_NOR(J5_4, VRESET, J5_3.Q)
	ALIAS(HSYNC,  J5_1.Q)
	ALIAS(HSYNC_Q, J5_2.Q)
	ALIAS(VSYNC,  J5_3.Q)
	ALIAS(VSYNC_Q, J5_4.Q)

	TTL_7486_XOR(J4_1, HSYNC, VSYNC_Q)
	ALIAS(COMPSYNC_Q, J4_1.Q)

	TTL_7474(N4_1, HWINDOW, HSYNC, RAMP_WINDOW_HIT_Q, N4_1.QQ)
	TTL_7474(M3_1, N4_1.Q, M3_1.QQ, CYCLE_RESETQ, P)
	ALIAS(DIRECTION, M3_1.Q)
	ALIAS(DIRECTION_Q, M3_1.QQ)

	TTL_7404_INVERT(N3_3, 32V)
	TTL_7474(J2_2, N3_3.Q, J2_1.Q, P, P)
	TTL_7474(J2_1, N4_1.Q, P, J2_2.QQ, P)

	TTL_7408_AND(H5_2, 256V_Q, VSYNC_Q)
	TTL_9316(K1, HSYNC,     P, H5_2.Q,  V_COUNTER_RESETQ, L2_3.Q,  Av,  Bv,  Cv,  Dv)
	TTL_9316(K2, HSYNC, K1.RC, J2_2.QQ, V_COUNTER_RESETQ, L2_3.Q, GND, GND, GND, GND)
	TTL_7400_NAND(L2_3, K1.RC, K2.RC)

	TTL_7402_NOR(D4_3, DIRECTION, H6)
	TTL_7408_AND(B5_1, DIRECTION, H5H6)
	TTL_7402_NOR(D4_4, D4_3.Q, B5_1.Q)
	TTL_7400_NAND(H2_1, HSYNC_Q, D4_4.Q)
	TTL_7400_NAND(H2_2, HSYNC_Q, H5)

	TTL_9322(J1, HSYNC, V4, P, V3, 4V, V1, 1V, V2, 2V, GND)
	PROM_82S115(HF1, P, GND, J1.Y3, J1.Y4, J1.Y2, J1.Y1, H2_2.Q, H2_1.Q, R2, R3, R4, P)

	TTL_7404_INVERT(D3_5, H1)
	TTL_74194(E1, D3_5.Q, MS1, MS2, GND,   HF1.O1, HF1.O2, HF1.O3, HF1.O4, E2.QA, CYCLE_RESET_A_Q)
	TTL_74194(E2, D3_5.Q, MS1, MS2, E1.QD, HF1.O4, HF1.O5, HF1.O6, HF1.O7, GND,   CYCLE_RESET_A_Q)

	TTL_74165(F2, CLOCK, GND, HSYNC_Q, F2.QH, HF1.O1, HF1.O2, HF1.O3, HF1.O4, HF1.O5, HF1.O6, HF1.O7, HF1.O8)
	TTL_7474(D2_1, CLOCK, F2.QH, OBJECT_ZONE, P)

	TTL_7450_ANDORINVERT(D1_1, E1.QA, DIRECTION, E2.QD, DIRECTION_Q)
	TTL_7474(D2_2, H1, D1_1.Q, P, V_WINDOW)
	ALIAS(CYCLE, D2_2.QQ)
	ALIAS(CYCLE_Q, D2_2.Q)

	/* Coin circuitry */
	TTL_7404_INVERT(K8_6, K8_5.Q)
	TTL_7404_INVERT(K8_5, K8_6.Q)

	DIODE(D20, "1N4001")
	DIODE(D21, "1N914")
	DIODE(D22, "1N914")

	SWITCH2(coinsw)
	NET_C(K8_6.Q, coinsw.1)
	NET_C(D21.K, coinsw.2)
	NET_C(coinsw.Q, GND)

	NET_C(K8_6.Q, D21.A)
	NET_C(K8_6.Q, D22.A)
	NET_C(D21.K, D20.A)
	NET_C(D20.K, V5)
	NET_C(D22.K, V5)

	TTL_7474(H8_2, 64V, K8_5.Q, K8_5.Q, P)

	SWITCH2(creditsw)
	NET_C(creditsw.1, GND)
	NET_C(creditsw.2, P)

	/* Start buttons, etc. */
	SWITCH(START1)
	RES(R11, RES_K(1))
	NET_C(START1.2, GND)
	NET_C(R11.1, V5)
	NET_C(START1.1, R11.2)
	TTL_7410_NAND(H9_1, 2_PLAYER_CREDIT, START, R11.2)

	SWITCH(START2)
	RES(R12, RES_K(1))
	NET_C(START2.2, GND)
	NET_C(R12.1, V5)
	NET_C(START2.1, R12.2)
	TTL_7410_NAND(H9_2, H9_1.Q, START, R12.2)

	TTL_7400_NAND(J8_2, FREE_COIN_Q, H8_2.QQ)
	TTL_74107(J9_2, 64V, J8_2.Q, J9_1.QQ, J8_2.Q)
	TTL_7450_ANDORINVERT(K9_2, creditsw.Q, K8_5.Q, FREE_COIN, 2_PLAYER_MODE_Q)
	TTL_7400_NAND(J8_1, K9_2.Q, J9_2.QQ)
	TTL_74107(J9_1, 64V, J8_1.Q, GND, J8_2.Q)

	TTL_7402_NOR(F9_4, END_GAME, QQ)
	TTL_7474(D9_2, 256V, START, F9_4.Q, ATTRACT)
	ALIAS(ATTRACT, D9_2.QQ)
	ALIAS(ATTRACT_Q, D9_2.Q)

	TTL_7402_NOR(F9_1, R11.2, R12.2)
	TTL_7427_NOR(D8_1, J8_2.Q, CREDIT_Q, ATTRACT_Q)
	TTL_7474(D9_1, 256V, F9_1.Q, P, D8_1.Q)
	ALIAS(START, D9_1.QQ)
	ALIAS(START_Q, D9_1.Q)

	TTL_7474(H8_1, ATTRACT, GND, H9_2.Q, H9_1.Q)
	ALIAS(2_PLAYER_MODE, H8_1.Q)
	ALIAS(2_PLAYER_MODE_Q, H8_1.QQ)
	TTL_7400_NAND(J8_4, 2_PLAYER_MODE, V_RAMPS)
	TTL_7400_NAND(J8_3, START, J8_4.Q)

	TTL_74193(E8, P, P, P, P, QQ, E8.CARRYQ, COIN_Q, J8_3.Q)
	TTL_7427_NOR(D8_2, E8.QB, E8.QC, E8.QD)
	TTL_7404_INVERT(K8_4, D8_2.Q)
	ALIAS(2_PLAYER_CREDIT, K8_4.Q)
	TTL_7402_NOR(F9_3, E8.QA, 2_PLAYER_CREDIT)
	ALIAS(CREDIT_Q, F9_3.Q)
	TTL_7402_NOR(F9_2, CREDIT_Q, CREDIT_Q)
	ALIAS(CREDIT, F9_2.Q)
#endif
NETLIST_END()