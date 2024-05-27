#ifndef DATA_PREPROCESSOR_H
#define DATA_PREPROCESSOR_H

#include "data_collector.h"

DatabaseMetrics* preprocess_data(DatabaseMetrics *metrics, int metrics_count);
int get_processed_metrics_count();

#endif
