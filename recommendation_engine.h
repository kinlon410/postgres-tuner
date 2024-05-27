#ifndef RECOMMENDATION_ENGINE_H
#define RECOMMENDATION_ENGINE_H

#include "feature_engineer.h"

char** generate_recommendations(DatabaseFeatures *features, int features_count);
int get_recommendations_count();

#endif
