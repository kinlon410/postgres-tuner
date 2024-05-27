#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libpq-fe.h>
#include "data_collector.h"

static int metrics_count = 0;

DatabaseMetrics* collect_data(PGconn *conn) {
    const char *query = "SELECT pg_stat_activity.datname, pg_stat_activity.query, pg_stat_activity.query_start, "
                        "pg_stat_activity.state_change, pg_stat_activity.state, pg_stat_activity.wait_event, "
                        "pg_stat_activity.wait_event_type, pg_stat_activity.backend_type, pg_stat_activity.query_id, "
                        "pg_stat_activity.application_name, pg_stat_activity.client_addr, pg_stat_activity.client_hostname, "
                        "pg_stat_activity.client_port, pg_stat_activity.backend_xid, pg_stat_activity.backend_xmin, "
                        "pg_stat_activity.pid, pg_stat_statements.calls, pg_stat_statements.total_time, pg_stat_statements.rows, "
                        "pg_stat_statements.shared_blks_hit, pg_stat_statements.shared_blks_read, pg_stat_statements.shared_blks_dirtied, "
                        "pg_stat_statements.shared_blks_written, pg_stat_statements.local_blks_hit, pg_stat_statements.local_blks_read, "
                        "pg_stat_statements.local_blks_dirtied, pg_stat_statements.local_blks_written, pg_stat_statements.temp_blks_read, "
                        "pg_stat_statements.temp_blks_written, pg_stat_statements.blk_read_time, pg_stat_statements.blk_write_time, "
                        "pg_stat_user_tables.seq_scan, pg_stat_user_tables.idx_scan "
                        "FROM pg_stat_activity "
                        "JOIN pg_stat_statements ON pg_stat_activity.query_id = pg_stat_statements.query_id "
                        "LEFT JOIN pg_stat_user_tables ON pg_stat_statements.relid = pg_stat_user_tables.relid "
                        "WHERE pg_stat_activity.state != 'idle'";

    PGresult *res = PQexec(conn, query);

    if (PQresultStatus(res) != PGRES_TUPLES_OK) {
        fprintf(stderr, "Data collection failed: %s\n", PQerrorMessage(conn));
        PQclear(res);
        PQfinish(conn);
        exit(1);
    }

    metrics_count = PQntuples(res);
    DatabaseMetrics *metrics = (DatabaseMetrics *)malloc(metrics_count * sizeof(DatabaseMetrics));

    for (int i = 0; i < metrics_count; i++) {
        metrics[i].databaseName = strdup(PQgetvalue(res, i, 0));
        metrics[i].query = strdup(PQgetvalue(res, i, 1));
        metrics[i].totalTime = atof(PQgetvalue(res, i, 17));
        metrics[i].calls = atol(PQgetvalue(res, i, 16));
        metrics[i].sharedBlksRead = atol(PQgetvalue(res, i, 19));
        metrics[i].sharedBlksWritten = atol(PQgetvalue(res, i, 22));
        metrics[i].tempBlksRead = atol(PQgetvalue(res, i, 28));
        metrics[i].tempBlksWritten = atol(PQgetvalue(res, i, 29));
        metrics[i].seqScan = atol(PQgetvalue(res, i, 31));
        metrics[i].idxScan = atol(PQgetvalue(res, i, 32));
        metrics[i].waitEvent = strdup(PQgetvalue(res, i, 5));
        metrics[i].cpuTime = 0; // 实际应从查询结果中提取
        metrics[i].memoryUsage = 0; // 实际应从查询结果中提取
        metrics[i].ioWaitTime = 0; // 实际应从查询结果中提取
        metrics[i].transactionTime = 0; // 实际应从查询结果中提取
        metrics[i].updateCount = 0; // 实际应从查询结果中提取
        metrics[i].tableBloat = 0; // 实际应从查询结果中提取
        metrics[i].unexpectedShutdown = 0; // 实际应从查询结果中提取
    }

    PQclear(res);
    return metrics;
}

int get_metrics_count() {
    return metrics_count;
}
