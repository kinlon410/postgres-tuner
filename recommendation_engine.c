#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "recommendation_engine.h"

static int recommendations_count = 0;

char** generate_recommendations(DatabaseFeatures *features, int features_count) {
    char **recommendations = (char **)malloc(features_count * sizeof(char *));
    recommendations_count = 0;

    for (int i = 0; i < features_count; i++) {
        // 慢查询优化建议
        if (features[i].totalTime > 1000) { 
            char *recommendation = (char *)malloc(256);
            snprintf(recommendation, 256, "Consider optimizing the following SQL query which has high execution time: %s", features[i].query);
            recommendations[recommendations_count++] = recommendation;
        }

        // 频繁调用的查询优化建议
        if (features[i].calls > 1000) { 
            char *recommendation = (char *)malloc(256);
            snprintf(recommendation, 256, "Consider optimizing the following SQL query which is called frequently: %s", features[i].query);
            recommendations[recommendations_count++] = recommendation;
        }

        // 高磁盘读取的查询优化建议
        if (features[i].sharedBlksRead > 1000) { 
            char *recommendation = (char *)malloc(256);
            snprintf(recommendation, 256, "Consider optimizing the following SQL query which has high disk read operations: %s", features[i].query);
            recommendations[recommendations_count++] = recommendation;
        }

        // 高磁盘写入的查询优化建议
        if (features[i].sharedBlksWritten > 500) { 
            char *recommendation = (char *)malloc(256);
            snprintf(recommendation, 256, "Consider optimizing the following SQL query which has high disk write operations: %s", features[i].query);
            recommendations[recommendations_count++] = recommendation;
        }

        // 高临时块操作的查询优化建议
        if (features[i].tempBlksRead > 100 || features[i].tempBlksWritten > 100) { 
            char *recommendation = (char *)malloc(256);
            snprintf(recommendation, 256, "Consider optimizing the following SQL query which uses a lot of temporary disk space: %s", features[i].query);
            recommendations[recommendations_count++] = recommendation;
        }

        // 无索引扫描的查询优化建议
        if (features[i].seqScan > 1000 && features[i].idxScan == 0) { 
            char *recommendation = (char *)malloc(256);
            snprintf(recommendation, 256, "Consider creating indexes to improve the performance of the following SQL query: %s", features[i].query);
            recommendations[recommendations_count++] = recommendation;
        }

        // 长时间等待事件的查询优化建议
        if (features[i].waitEvent != NULL && strcmp(features[i].waitEvent, "Lock") == 0) { 
            char *recommendation = (char *)malloc(256);
            snprintf(recommendation, 256, "Consider investigating lock contention issues for the following SQL query: %s", features[i].query);
            recommendations[recommendations_count++] = recommendation;
        }

        // 无效索引优化建议
        if (features[i].idxScan == 0 && features[i].seqScan == 0) { 
            char *recommendation = (char *)malloc(256);
            snprintf(recommendation, 256, "Consider dropping unused indexes to improve performance: %s", features[i].query);
            recommendations[recommendations_count++] = recommendation;
        }

        // 高CPU使用优化建议
        if (features[i].cpuTime > 1000) { 
            char *recommendation = (char *)malloc(256);
            snprintf(recommendation, 256, "Consider optimizing the following SQL query which has high CPU usage: %s", features[i].query);
            recommendations[recommendations_count++] = recommendation;
        }

        // 高内存使用优化建议
        if (features[i].memoryUsage > 1000) { 
            char *recommendation = (char *)malloc(256);
            snprintf(recommendation, 256, "Consider optimizing the following SQL query which has high memory usage: %s", features[i].query);
            recommendations[recommendations_count++] = recommendation;
        }

        // 高IO等待优化建议
        if (features[i].ioWaitTime > 100) { 
            char *recommendation = (char *)malloc(256);
            snprintf(recommendation, 256, "Consider optimizing the following SQL query which has high IO wait time: %s", features[i].query);
            recommendations[recommendations_count++] = recommendation;
        }

        // 长时间事务优化建议
        if (features[i].transactionTime > 1000) { 
            char *recommendation = (char *)malloc(256);
            snprintf(recommendation, 256, "Consider optimizing or breaking down the following long-running transaction: %s", features[i].query);
            recommendations[recommendations_count++] = recommendation;
        }

        // 频繁更新的表优化建议
        if (features[i].updateCount > 1000) { 
            char *recommendation = (char *)malloc(256);
            snprintf(recommendation, 256, "Consider partitioning or indexing the frequently updated table: %s", features[i].query);
            recommendations[recommendations_count++] = recommendation;
        }

        // 表膨胀优化建议
        if (features[i].tableBloat > 1000) { 
            char *recommendation = (char *)malloc(256);
            snprintf(recommendation, 256, "Consider performing VACUUM or rebuilding the bloated table: %s", features[i].query);
            recommendations[recommendations_count++] = recommendation;
        }

        // 非正常关闭检测建议
        if (features[i].unexpectedShutdown) { 
            char *recommendation = (char *)malloc(256);
            snprintf(recommendation, 256, "Check logs and configuration for the unexpected shutdown issue: %s", features[i].query);
            recommendations[recommendations_count++] = recommendation;
        }
    }

    return recommendations;
}

int get_recommendations_count() {
    return recommendations_count;
}
