#include <string.h>
#include <stdio.h>

#include "postgres.h"
#include "libpq-fe.h"

#define MAX_QUERY_LENGTH 1024
#define MAX_DBNAME_LENGTH 64

bool FindMyDatabase_cs_cli(const char *name, Oid *db_id, Oid *db_tablespace);

static bool connection_made = false;
static PGconn *conn = NULL;

static void
teardown_connection()
{
	PQfinish(conn);
}

static bool
initialize_connection()
{
	if (connection_made)
		return true;

	const char *conninfo;

	conninfo = "hostaddr = 127.0.0.1 dbname = postgres port = 5432";

	/* Make a connection to the database */
	conn = PQconnectdb(conninfo);

	/* Check to see that the backend connection was successfully made */
	if (PQstatus(conn) != CONNECTION_OK)
	{
		teardown_connection();
		elog(WARNING, "Connection to database failed");
		return false;
	}
	connection_made = true;
	return true;
}

bool
FindMyDatabase_cs_cli(const char *name, Oid *db_id, Oid *db_tablespace)
{
	if (!initialize_connection())
		return false;

	char query[MAX_QUERY_LENGTH];
	char *errMsg;
	PGresult *res;

	if (strlen(name) > MAX_DBNAME_LENGTH)
	{
		elog(WARNING, "database name too long");
		return false;
	}
	if (sprintf(query, "SELECT * FROM udf_cs_findmydatabase('%s') as (db_id oid, db_tablespace oid)", name) < 0)
	{
		elog(WARNING, "building query failed");
		return false;
	}
	res = PQexec(conn, (const char *) query);
	if (PQresultStatus(res) != PGRES_TUPLES_OK)
	{
		PQclear(res);
		errMsg = pstrdup(PQerrorMessage(conn));
		teardown_connection();
		elog(WARNING, "query failed: %s", errMsg);
		return false;
	}

	if (PQnfields(res) != 2 || PQntuples(res) != 1)
	{
		elog(WARNING, "wrong results returned");
		return false;
	}

	*db_id = (Oid) atoi(PQgetvalue(res, 0, 0));
	*db_tablespace = (Oid) atoi(PQgetvalue(res, 0, 1));

	PQclear(res);
	return true;
}
