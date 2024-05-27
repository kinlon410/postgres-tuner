CC = gcc
CFLAGS = -I/usr/include/postgresql -I. -Wall -Wextra
LDFLAGS = -L/usr/lib -lpq

OBJS = main.o data_collector.o data_preprocessor.o feature_engineer.o recommendation_engine.o config.o

postgres_tuner: $(OBJS)
	$(CC) -o postgres_tuner $(OBJS) $(LDFLAGS)

main.o: main.c data_collector.h data_preprocessor.h feature_engineer.h recommendation_engine.h config.h
	$(CC) $(CFLAGS) -c main.c

data_collector.o: data_collector.c data_collector.h
	$(CC) $(CFLAGS) -c data_collector.c

data_preprocessor.o: data_preprocessor.c data_preprocessor.h
	$(CC) $(CFLAGS) -c data_preprocessor.c

feature_engineer.o: feature_engineer.c feature_engineer.h
	$(CC) $(CFLAGS) -c feature_engineer.c

recommendation_engine.o: recommendation_engine.c recommendation_engine.h
	$(CC) $(CFLAGS) -c recommendation_engine.c

config.o: config.c config.h
	$(CC) $(CFLAGS) -c config.c

clean:
	rm -f postgres_tuner $(OBJS)
