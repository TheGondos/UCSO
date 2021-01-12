// ==============================================================
//                 ORBITER MODULE: ShuttlePB
//                  Part of the ORBITER SDK
//          Copyright (C) 2002-2004 Martin Schweiger
//                   All rights reserved
//          UCSO integration by Abdullah Radwan
//
// ShuttlePB.h
// Class interface for ShuttlePB vessel class
//
// ==============================================================

#pragma once
#include <UCSO/Vessel.h>

// ==============================================================
// Shuttle-PB class interface
// ==============================================================

class ShuttlePB : public VESSEL4 
{
public:
	ShuttlePB(OBJHANDLE hVessel, int flightmodel);
	~ShuttlePB();

	void clbkSetClassCaps(FILEHANDLE cfg);
	int clbkConsumeBufferedKey(DWORD key, bool down, char* kstate);
	bool clbkDrawHUD(int mode, const HUDPAINTSPEC* hps, oapi::Sketchpad* skp);
	void clbkPreStep(double simt, double simdt, double mjd);

private:
	// transformations for control surface animations
	static MGROUP_ROTATE trans_Laileron, trans_Raileron;
	static MGROUP_ROTATE trans_Lelevator, trans_Relevator;

	UCSO::Vessel* ucso;
	ATTACHMENTHANDLE attachmentHandle = nullptr;

	int cargoIndex = 0;  // For the cargo selection on the HUD
	char buffer[256];    // To draw on the HUD
	const char* message; // To show messages on the HUD
	double timer = 0;    // To show the messages for 5 seconds on the HUD

	void SetStatusLanded();

	static void vlift(VESSEL* v, double aoa, double M, double Re,
		void* context, double* cl, double* cm, double* cd);
	static void hlift(VESSEL* v, double aoa, double M, double Re,
		void* context, double* cl, double* cm, double* cd);
};

// ==============================================================
// Some vessel parameters
// ==============================================================
const double  PB_SIZE = 3.5;             // mean radius [m]
const VECTOR3 PB_CS = { 10.5,15.0,5.8 }; // x,y,z cross sections [m^2]
const VECTOR3 PB_PMI = { 2.28,2.31,0.79 };// principal moments of inertia (mass-normalised) [m^2]
const VECTOR3 PB_RD = { 0.025,0.025,0.02 };//{0.05,0.1,0.05};  // rotation drag coefficients
const double  PB_EMPTYMASS = 500.0;           // empty vessel mass [kg]
const double  PB_FUELMASS = 750.0;           // max fuel mass [kg]
const double  PB_ISP = 5e4;             // fuel-specific impulse [m/s]
const VECTOR3 PB_COP = { 0,0,0 };//{0,0,-0.1};      // centre of pressure for airfoils [m]
const double  PB_VLIFT_C = 2.0;             // chord length [m]
const double  PB_VLIFT_S = 2.0;             // wing area [m^2]
const double  PB_VLIFT_A = 2.5;             // wing aspect ratio
const double  PB_HLIFT_C = 2.0;             // chord length [m]
const double  PB_HLIFT_S = 1.5;             // wing area [m^2]
const double  PB_HLIFT_A = 2.0;             // wing aspect ratio

const double  PB_MAXMAINTH = 3e4;
const double  PB_MAXHOVERTH = 1.5e4;
const double  PB_MAXRCSTH = 2e2;

const VECTOR3 PB_DOCK_POS = { 0,1.3,-1 };      // docking port location [m]
const VECTOR3 PB_DOCK_DIR = { 0,1,0 };         // docking port approach direction
const VECTOR3 PB_DOCK_ROT = { 0,0,-1 };        // docking port alignment direction

// Define impact convex hull
static const DWORD ntdvtx = 12;
static TOUCHDOWNVTX tdvtx[ntdvtx] =
{
	{_V(0,  -1.5, 2), 2e4, 1e3, 1.6, 1},
	{_V(-1,  -1.5,-1.5), 2e4, 1e3, 3.0, 1},
	{_V(1,  -1.5,-1.5), 2e4, 1e3, 3.0, 1},
	{_V(-0.5,-0.75,3), 2e4, 1e3, 3.0},
	{_V(0.5,-0.75,3), 2e4, 1e3, 3.0},
	{_V(-2.6,-1.1,-1.9), 2e4, 1e3, 3.0},
	{_V(2.6,-1.1,-1.9), 2e4, 1e3, 3.0},
	{_V(-1,   1.3, 0), 2e4, 1e3, 3.0},
	{_V(1,   1.3, 0), 2e4, 1e3, 3.0},
	{_V(-1,   1.3,-2), 2e4, 1e3, 3.0},
	{_V(1,   1.3,-2), 2e4, 1e3, 3.0},
	{_V(0,   0.3,-3.8), 2e4, 1e3, 3.0}
};

// Calculate lift coefficient [Cl] as a function of aoa (angle of attack) over -Pi ... Pi
// Implemented here as a piecewise linear function
double LiftCoeff(double aoa)
{
	int i;
	const int nlift = 9;
	static const double AOA[nlift] = { -180 * RAD,-60 * RAD,-30 * RAD,-1 * RAD,15 * RAD,20 * RAD,25 * RAD,60 * RAD,180 * RAD };
	static const double CL[nlift] = { 0,      0,   -0.1,     0,   0.2,  0.25,   0.2,     0,      0 };
	static const double SCL[nlift] = { (CL[1] - CL[0]) / (AOA[1] - AOA[0]), (CL[2] - CL[1]) / (AOA[2] - AOA[1]),
									  (CL[3] - CL[2]) / (AOA[3] - AOA[2]), (CL[4] - CL[3]) / (AOA[4] - AOA[3]),
									  (CL[5] - CL[4]) / (AOA[5] - AOA[4]), (CL[6] - CL[5]) / (AOA[6] - AOA[5]),
									  (CL[7] - CL[6]) / (AOA[7] - AOA[6]), (CL[8] - CL[7]) / (AOA[8] - AOA[7]) };
	for (i = 0; i < nlift - 1 && AOA[i + 1] < aoa; i++);
	return CL[i] + (aoa - AOA[i]) * SCL[i];
}

// animation transformation definitions
static UINT GRP_LWING = 2;
static UINT GRP_RWING = 3;
static VECTOR3 LWING_REF = { -1.3,-0.725,-1.5 };
static VECTOR3 LWING_AXIS = { -0.9619,-0.2735,0 };
static VECTOR3 RWING_REF = { 1.3,-0.725,-1.5 };
static VECTOR3 RWING_AXIS = { 0.9619,-0.2735,0 };
static float AILERON_RANGE = (float)(20.0 * RAD);
static float ELEVATOR_RANGE = (float)(30.0 * RAD);
MGROUP_ROTATE ShuttlePB::trans_Laileron(0, &GRP_LWING, 1, LWING_REF, LWING_AXIS, AILERON_RANGE);
MGROUP_ROTATE ShuttlePB::trans_Raileron(0, &GRP_RWING, 1, RWING_REF, RWING_AXIS, AILERON_RANGE);
MGROUP_ROTATE ShuttlePB::trans_Lelevator(0, &GRP_LWING, 1, LWING_REF, LWING_AXIS, -ELEVATOR_RANGE);
MGROUP_ROTATE ShuttlePB::trans_Relevator(0, &GRP_RWING, 1, RWING_REF, RWING_AXIS, ELEVATOR_RANGE);
