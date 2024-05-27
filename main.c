#include <stdio.h>
#include <stdlib.h>
#include <libpq-fe.h>
#include "data_collector.h"
#include "data_preprocessor.h"
#include "feature_engineer.h"
#include "recommendation_engine.h"
#include "config.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <config file>\n", argv[0]);
        exit(1);
    }

    DBConfig config;
    if (read_config(argv[1], &config) != 0) {
        exit(1);
    }

    char conninfo[512];
    snprintf(conninfo, sizeof(conninfo), "dbname=%s user=%s password=%s hostaddr=%s port=%s",
             config.dbname, config.user, config.password, config.host, config.port);

    PGconn *conn = PQconnectdb(conninfo);

    if (PQstatus(conn) != CONNECTION_OK) {
        fprintf(stderr, "Connection to database failed: %s\n", PQerrorMessage(conn));
        PQfinish(conn);
        exit(1);
    }

    DatabaseMetrics *metrics = collect_data(conn);
    int metrics_count = get_metrics_count();

    DatabaseMetrics *processed_metrics = preprocess_data(metrics, metrics_count);
    int processed_metrics_count = get_processed_metrics_count();

    DatabaseFeatures *features = engineer_features(processed_metrics, processed_metrics_count);
    int features_count = get_features_count();

    char **recommendations = generate_recommendations(features, features_count);
    int recommendations_count = get_recommendations_count();

    for (int i = 0; i < recommendations_count; i++) {
        printf("%s\n", recommendations[i]);
        free(recommendations[i]);
    }
    free(recommendations);

    PQfinish(conn);
    return 0;
}
