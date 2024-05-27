#include <stdlib.h>
#include "feature_engineer.h"

static int features_count = 0;

DatabaseFeatures* engineer_features(DatabaseMetrics *metrics, int metrics_count) {
    DatabaseFeatures *features = (DatabaseFeatures *)malloc(metrics_count * sizeof(DatabaseFeatures));
    features_count = 0;

    for (int i = 0; i < metrics_count; i++) {
        features[i].databaseName = metrics[i].databaseName;
        features[i].query = metrics[i].query;
        features[i].totalTime = metrics[i].totalTime;
        features[i].calls = metrics[i].calls;
        features[i].sharedBlksRead = metrics[i].sharedBlksRead;
        features[i].sharedBlksWritten = metrics[i].sharedBlksWritten;
        features[i].tempBlksRead = metrics[i].tempBlksRead;
        features[i].tempBlksWritten = metrics[i].tempBlksWritten;
        features[i].seqScan = metrics[i].seqScan;
        features[i].idxScan = metrics[i].idxScan;
        features[i].waitEvent = metrics[i].waitEvent;
        features[i].cpuTime = metrics[i].cpuTime;
        features[i].memoryUsage = metrics[i].memoryUsage;
        features[i].ioWaitTime = metrics[i].ioWaitTime;
        features[i].transactionTime = metrics[i].transactionTime;
        features[i].updateCount = metrics[i].updateCount;
        features[i].tableBloat = metrics[i].tableBloat;
        features[i].unexpectedShutdown = metrics[i].unexpectedShutdown;
        features_count++;
    }

    return features;
}

int get_features_count() {
    return features_count;
}
