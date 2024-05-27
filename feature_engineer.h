#ifndef FEATURE_ENGINEER_H
#define FEATURE_ENGINEER_H

#include "data_collector.h"

typedef struct {
    char *databaseName;
    char *query;
    double totalTime;
    long calls;
    long sharedBlksRead;
    long sharedBlksWritten;
    long tempBlksRead;
    long tempBlksWritten;
    long seqScan;
    long idxScan;
    char *waitEvent;
    double cpuTime;
    double memoryUsage;
    double ioWaitTime;
    double transactionTime;
    long updateCount;
    long tableBloat;
    int unexpectedShutdown;
} DatabaseFeatures;

DatabaseFeatures* engineer_features(DatabaseMetrics *metrics, int metrics_count);
int get_features_count();

#endif
