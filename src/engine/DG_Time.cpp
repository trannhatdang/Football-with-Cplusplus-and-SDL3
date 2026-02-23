#include "engine/DG_Time.h"

float deltaTime = 0.016667f;
std::chrono::time_point<std::chrono::system_clock> start_point;


void DGTime_recordDeltaTime()
{
	start_point = std::chrono::system_clock::now();
}

void DGTime_stopRecordDeltaTime()
{
	deltaTime = (std::chrono::system_clock::now() - start_point).count() / 1000.0f;
}

float DGTime_deltaTime()
{
	return deltaTime;
}

float DGTime_fixedDeltaTime()
{
	return 0.016667f;
}
