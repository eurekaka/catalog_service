#include <string.h>
#include <stdio.h>

#include "postgres.h"
#include "libpq-fe.h"

#define MAX_QUERY_LENGTH 1024
#define MAX_DBNAME_LENGTH 64

void FindMyDatabase_cs_cli(const char *name, Oid *db_id, Oid *db_tablespace);

static bool connection_made = false;
static PGconn *conn = NULL;

static void
teardown_connection()
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
		teardown_connection();
		elog(ERROR, "Connection to database failed");
	}
	connection_made = true;
}

void
FindMyDatabase_cs_cli(const char *name, Oid *db_id, Oid *db_tablespace)
{
	initialize_connection();

	char query[MAX_QUERY_LENGTH];
	char *errMsg;
	PGresult *res;

	if (strlen(name) > MAX_DBNAME_LENGTH)
		elog(ERROR, "database name too long");
	if (sprintf(query, "SELECT * FROM udf_cs_findmydatabase('%s') as (db_id oid, db_tablespace oid)", name) < 0)
		elog(ERROR, "building query failed");
	res = PQexec(conn, (const char *) query);
	if (PQresultStatus(res) != PGRES_TUPLES_OK)
	{
		PQclear(res);
		errMsg = pstrdup(PQerrorMessage(conn));
		teardown_connection();
		elog(ERROR, "query failed: %s", errMsg);
	}

	if (PQnfields(res) != 2 || PQntuples(res) != 1)
		elog(ERROR, "wrong results returned");

	*db_id = (Oid) atoi(PQgetvalue(res, 0, 0));
	*db_tablespace = (Oid) atoi(PQgetvalue(res, 0, 1));

	PQclear(res);
}
