#ifdef WINDOWS

#include "selftest_local.h".

void Test_TuyaMCU_Basic() {
	// reset whole device
	CMD_ExecuteCommand("clearAll", 0);

	CMD_ExecuteCommand("startDriver TuyaMCU", 0);

	// This will map TuyaMCU fnID 2 of type Value to channel 15
	CMD_ExecuteCommand("linkTuyaMCUOutputToChannel 2 val 15",0);
	SELFTEST_ASSERT_CHANNEL(15, 0);
	// This packet sets fnID 2 of type Value to 100
	CMD_ExecuteCommand("tuyaMcu_fakeHex 55AA0307000802020004000000647D", 0);
	// above command will just put into buffer - need at least a frame to parse it
	Sim_RunFrames(1000);
	// Now, channel 15 should be set to 100...
	SELFTEST_ASSERT_CHANNEL(15, 100);

	// This packet sets fnID 2 of type Value to 90
	CMD_ExecuteCommand("tuyaMcu_fakeHex 55AA03070008020200040000005A73", 0);
	// above command will just put into buffer - need at least a frame to parse it
	Sim_RunFrames(1000);
	// Now, channel 15 should be set to 10...
	SELFTEST_ASSERT_CHANNEL(15, 90);

	// cause error
	SELFTEST_ASSERT_CHANNEL(15, 666);
}

#endif
