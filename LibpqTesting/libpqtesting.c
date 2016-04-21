#include <stdio.h>
#include <stdlib.h>
#include <libpq-fe.h>

#ifdef _WIN32
	#ifdef _WIN64
		#pragma comment(lib, "lib/x64/libpq.lib")
	#else
		#pragma comment(lib, "lib/x86/libpq.lib")
	#endif
#endif

static void exit_nicely(PGconn *conn) {
	PQfinish(conn);
	exit(1);
}

int main(int argc, char *argv[]) {
	char connstring[151] = { 0 };
	printf("Enter your connection string:\n> ");
	fgets(connstring, 150, stdin);

	int i, j, nFields;
	PGresult *res = NULL;
	PGconn *conn = PQconnectdb(connstring);
	if (PQstatus(conn) != CONNECTION_OK) {
		printf("%s\n", PQerrorMessage(conn));
		PQfinish(conn);
		getchar();
		return 1;
	}

	res = PQexec(conn, "SELECT table_schema, table_name FROM information_schema.tables LIMIT 10");
	if (PQresultStatus(res) != PGRES_TUPLES_OK) {
		fprintf(stderr, "SELECT failed: %s", PQerrorMessage(conn));
		PQclear(res);
		getchar();
		exit_nicely(conn);
	}

	// first, print out the attribute names
	nFields = PQnfields(res);
	for (i = 0; i < nFields; i++) {
		printf("%-15s", PQfname(res, i));
	}
	printf("\n");

	// next, print out the rows
	for (i = 0; i < PQntuples(res); i++) {
		for (j = 0; j < nFields; j++) {
			printf("%-15s", PQgetvalue(res, i, j));
		}
		printf("\n");
	}

	PQclear(res);

	PQfinish(conn);

	getchar();

	return 0;
}
