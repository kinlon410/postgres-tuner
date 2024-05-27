#include <stdlib.h>
#include "data_preprocessor.h"

static int processed_metrics_count = 0;

DatabaseMetrics* preprocess_data(DatabaseMetrics *metrics, int metrics_count) {
    DatabaseMetrics *processed_metrics = (DatabaseMetrics *)malloc(metrics_count * sizeof(DatabaseMetrics));
    processed_metrics_count = 0;

    for (int i = 0; i < metrics_count; i++) {
        if (metrics[i].totalTime > 0) { // 过滤掉总时间为0的SQL语句
            processed_metrics[processed_metrics_count++] = metrics[i];
        }
    }

    return processed_metrics;
}

int get_processed_metrics_count() {
    return processed_metrics_count;
}
