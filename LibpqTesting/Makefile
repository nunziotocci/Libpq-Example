CFLAGS=-I`pg_config --includedir`
LDFLAGS=-L`pg_config --libdir` -lpq

all:
	$(CC) libpqtesting.c $(CFLAGS) $(LDFLAGS) -o Libpq-Example

clean:
	rm Libpq-Example
