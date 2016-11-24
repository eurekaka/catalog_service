#include "postgres.h"
#include "fmgr.h"
#include "utils/flatfiles.h"
#include "storage/fd.h"
#include "access/tupdesc.h"
#include "catalog/pg_type.h"
#include "funcapi.h"
#include "libpq/hba.h"

Datum UDF_CS_FindMyDatabase(PG_FUNCTION_ARGS);

Datum
UDF_CS_FindMyDatabase(PG_FUNCTION_ARGS)
{
	char *dbname = PG_GETARG_CSTRING(0);
	char *filename;
	FILE *db_file;
	Oid db_id, db_tablespace;
	char thisname[NAMEDATALEN];
	TransactionId db_frozenxid;

	filename = database_getflatfilename();
	db_file = AllocateFile(filename, "r");
	if (db_file == NULL)
		ereport(ERROR,
				(errcode_for_file_access(),
				errmsg("could not open file \"%s\": %m", filename)));

	TupleDesc tupdesc;
	tupdesc = CreateTemplateTupleDesc(2, false);
	TupleDescInitEntry(tupdesc, (AttrNumber) 1, "db_id", OIDOID, -1, 0);
	TupleDescInitEntry(tupdesc, (AttrNumber) 2, "db_tablespace", OIDOID, -1, 0);
	tupdesc = BlessTupleDesc(tupdesc);
	Assert(tupdesc != NULL);

	Datum values[2];
	char nulls[2];
	HeapTuple tuple;

	while (read_pg_database_line(db_file, thisname, &db_id, &db_tablespace, &db_frozenxid))
	{
		if (strcmp(thisname, dbname) == 0)
		{
			Assert(db_id > 0 && db_tablespace > 0);
			values[0] = ObjectIdGetDatum(db_id);
			nulls[0] = ' ';
			values[1] = ObjectIdGetDatum(db_tablespace);
			nulls[1] = ' ';

			tuple = heap_formtuple(tupdesc, values, nulls);
			PG_RETURN_DATUM(HeapTupleGetDatum(tuple));
		}
	}

	ereport(ERROR,
			(errcode(ERRCODE_UNDEFINED_DATABASE),
			 errmsg("database does not exist")));
}
