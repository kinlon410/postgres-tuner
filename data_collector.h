#ifndef DATA_COLLECTOR_H
#define DATA_COLLECTOR_H

#include <libpq-fe.h>

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
} DatabaseMetrics;

DatabaseMetrics* collect_data(PGconn *conn);
int get_metrics_count();

#endif
