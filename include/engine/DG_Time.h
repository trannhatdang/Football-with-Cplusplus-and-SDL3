#ifndef DG_TIME_H_
#define DG_TIME_H_

#include <chrono>

void DGTime_recordDeltaTime();
void DGTime_stopRecordDeltaTime();
float DGTime_deltaTime();
float DGTime_fixedDeltaTime();

#endif
