#ifndef __LIBDBC_DB_H__
#define __LIBDBC_DB_H__

#include <libpq-fe.h>

extern const char SEARCH_BY_ID_QUERY[];

PGresult* libdbc_db_query(PGconn* conn,
                  const char* query,
                  const char* const* queryParams,
                  const int num_of_queries);

PGresult* libdbc_db_query_by_id(const char* const* query_params, const char* sql_info, const char* query);

PGresult* libdbc_db_query_post(PGresult* res, const char* const* query_params, const char* sql_info, const char* query);

void libdbc_db_clean_up(PGconn* conn, PGresult* res);

void libdbc_db_disconnect(PGconn* conn);

/*
 * ------------------------------------------
 * function: libdbc_db_convert_pq_data
 * ------------------------------------------
 * params  : 
 *          > conn - pointer to PGconn type
 *          > res  - pointer to PGresult type
 * ------------------------------------------
 * Destroys a response,
 * and a connection to a database
 * ------------------------------------------
 */
char** libdbc_db_convert_pq_data(char** data_pointer, PGresult* res, const int row);

#endif


