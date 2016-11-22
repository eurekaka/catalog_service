#include <string.h>
#include <stdio.h>

#include "postgres.h"
#include "libpq-fe.h"

static bool connection_made = false;
static PGconn *conn = NULL;

static void
cleanup_connection()
{
	PQfinish(conn);
}

static void
initialize_connection()
{
	if (connection_made)
		return;

	const char *conninfo;

	conninfo = "hostaddr = 127.0.0.1 dbname = postgres port = 15432";

	/* Make a connection to the database */
	conn = PQconnectdb(conninfo);

	/* Check to see that the backend connection was successfully made */
	if (PQstatus(conn) != CONNECTION_OK)
	{
		cleanup_connection();
		ereport(ERROR, "Connection to database failed");
	}
	connection_made = true;
}

bool
FindMyDatabase_cs_cli(const char *name, Oid *db_id, Oid *db_tablespace)
{
	initialize_connection();

	char *query;
	char *errMsg;
	PGresult *res;
	int nFields, i;

	if (strlen(name) > 200)
		elog(ERROR, "database name too long");
	if (sprintf(query, "SELECT * FROM CS_UDF_db_exist('%s')", name) < 0)
		elog(ERROR, "building query failed");
	res = PQexec(conn, (const char *) query);
	if (PQresultStatus(res) != PGRES_TUPLES_OK)
	{
		PQclear(res);
		errMsg = pstrdup(PQerrorMessage(conn));
		cleanup_connection();
		elog(ERROR, "query failed: %s", errMsg);
	}

	if (PQnfields(res) != 1 || PQntuples(res) != 1)
		elog(ERROR, "wrong results returned");

	bool exist = strcmp(PQgetvalue(res, 0, 0), "t") == 0;

	PQclear(res);

	return exist;
}
