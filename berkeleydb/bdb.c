// Copyright 2013 Matt Butcher
// MIT License
// This file contains a number of wrapper functions that make it
// possible for Go to call the method-style functions on BerkeleyDB
// structs.

#include <db.h> 
#include <string.h>

int go_db_open(DB *dbp, DB_TXN *txnid, char *filename, char *dbname, DBTYPE type, u_int32_t flags, int mode) {
  return dbp->open(dbp, txnid, filename, dbname, type, flags, mode);
}

int go_db_close(DB *dbp, u_int32_t flags) {
  if (dbp == NULL) return 0;

  return dbp->close(dbp, flags);
}

int go_db_get_open_flags(DB *dbp, u_int32_t *open_flags) {
  return dbp->get_open_flags(dbp, open_flags);
}

int go_db_remove(DB *dbp, char *filename) {
  // dbp->close(dbp, 0);
  return dbp->remove(dbp, filename, NULL, 0);
}

int go_db_rename(DB *dbp, char *oldname, char *newname) {
  return dbp->rename(dbp, oldname, NULL, newname, 0);
}

int go_env_open(DB_ENV *env, char *dirname, u_int32_t flags, u_int32_t mode) {
	return env->open(env, dirname, flags, mode);
}

int go_env_close(DB_ENV *env, u_int32_t flags) {
	return env->close(env, flags);
}

int go_db_put_string(DB *dbp, char *name, char *value, u_int32_t flags) {

	// Create two DB records and initialize them.
	DBT key, data;
	memset(&key, 0, sizeof(DBT));
	memset(&data, 0, sizeof(DBT));

	// Store the two strings in the DBT records
	key.data = name;
	key.size = strlen(name) + 1;

	data.data = value;
	data.size = strlen(value) + 1;

	// Put the record into the database.
	return dbp->put(dbp, NULL, &key, &data, flags);
}

int go_db_get_string(DB *dbp, char *name, char *value) {
	int ret;
	// Create two DB records and initialize them.
	DBT key, data;
	memset(&key, 0, sizeof(DBT));
	memset(&data, 0, sizeof(DBT));

	key.data = name;
	key.size = strlen(name) + 1;

	ret = dbp->get(dbp, NULL, &key, &data, 0);

	value = data.data;

    return ret;
}

int go_db_del_string(DB *dbp, char *name) {
	DBT key;
	memset(&key, 0, sizeof(DBT));

	key.data = name;
	key.size = strlen(name) + 1;

	return dbp->del(dbp, NULL, &key, 0);
}
	
