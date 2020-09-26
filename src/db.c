#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <libpq-fe.h>

#include "../include/db.h"

/*
 * -----------------------------------------------------------------------------
 * function: libdbc_db_query
 * -----------------------------------------------------------------------------
 * params:   
 *         > query          - constant char*
 *         > query_params   - constant pointer pointing to constant char pointer
 *         > num_of_queries - constant integer
 * -----------------------------------------------------------------------------
 * returns:  pointer to PGresult type
 * -----------------------------------------------------------------------------
 */
PGresult* libdbc_db_query(PGconn* conn,
                          const char* query,
                          const char* const* query_params,
                          const int num_of_queries)
{
  if (!conn)
  {
    printf("ERROR:: libdbc - Failed to connect to postgres db.\n");
    exit(1);
  }

  //PGresult* res = (PGresult*) malloc(sizeof(struct PGresult));
  PGresult* res = PQexec(conn, "BEGIN");
  if (PQresultStatus(res) != PGRES_COMMAND_OK)
  {
    PQclear(res);
    libdbc_db_disconnect(conn);
    exit(1);
  }

  PQclear(res);

  res = PQexecParams(conn, query,
                    num_of_queries, NULL,
                    query_params, NULL,
                    NULL, 0);

  if (PQresultStatus(res) != PGRES_TUPLES_OK)
  {
    printf("ERROR:: libdbc - %s\n", PQerrorMessage(conn));
    PQclear(res);
    libdbc_db_disconnect(conn);
    exit(1);
  }

  PGresult* response = (PGresult*) malloc(sizeof(res));
  if (!response)
  {
    printf("ERROR:: libdbc - Failed to allocate memory for postgres response in libdbc_db_query\n");
    libdbc_db_disconnect(conn);
    free((char*)query_params);
    exit(1);
  }

  memcpy(response, res, sizeof(struct PGresult*));

  // disconnect from db
  libdbc_db_disconnect(conn);

  return res;
};


/*
 * --------------------------------------------------------------------
 * function: libdbc_db_query_by_id
 * --------------------------------------------------------------------
 * params:   query_params - constant pointer pointing to constant char*
 * --------------------------------------------------------------------
 * returns:  pointer to PGresult type
 * --------------------------------------------------------------------
 */
PGresult* libdbc_db_query_by_id(const char* const* query_params, const char* sql_info, const char* query)
{
  // check for query params
  if (!query_params)
  {
    printf("ERROR:: libdbc - Query params data is invalid..\n");
    exit(1);
  }

  // connect to db
  PGconn* conn = PQconnectdb(sql_info);
  if (!conn)
  {
    printf("ERROR:: libdbc - Failed to connect to database..\n");
    exit(1);
  }

  // query db for employee
  PGresult* res = libdbc_db_query(conn, query, query_params, 1);

  // check status of postman response
  if (!res)
  {
    printf("ERROR:: libdbc - Failed to get PQ response..\n");
    PQclear(res);
    free(res);
    libdbc_db_disconnect(conn);
    exit(1);
  }

  return res;
};

/*
 *
 *
 *
 *
 *
 */
PGresult* libdbc_db_query_post(PGresult* res, const char* const* query_params, const char* sql_info, const char* query)
{
  PGconn* conn = PQconnectdb(sql_info);

  if (!conn)
  {
    printf("ERROR:: libdbc - Failed to connect to database..\n");
    exit(1);
  }

  if (!query_params)
  {
    printf("ERROR:: libdbc - Query data is invalid..\n");
    libdbc_db_disconnect(conn);
    exit(1);
  }

  res = libdbc_db_query(conn, query, query_params, 1);

  if (!res)
  {
    printf("ERROR:: libdbc - Failed to get PQ response..\n");
    PQclear(res);
    free(res);
    libdbc_db_disconnect(conn);
    exit(1);
  }

  return res;
};

/*
 * ---------------------------------------
 * function: libdbc_db_disconnect
 * ---------------------------------------
 * params  : conn - pointer to PGconn type
 * ---------------------------------------
 * Destroys a connection to a database.
 * ---------------------------------------
 */
void libdbc_db_disconnect(PGconn* conn) {
  PQfinish(conn);
};

/*
 * ------------------------------------------
 * function: libdbc_db_clean_up
 * ------------------------------------------
 * params  : 
 *          > conn - pointer to PGconn type
 *          > res  - pointer to PGresult type
 * ------------------------------------------
 * Destroys a response,
 * and a connection to a database
 * ------------------------------------------
 */
void libdbc_db_clean_up(PGconn* conn, PGresult* res) {
  PQclear(res);
  libdbc_db_disconnect(conn);
};

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
char** libdbc_db_convert_pq_data(char** data_pointer, PGresult* res, const int row)
{
  for (int col = 0; col < 11; col++) {
    const char* current_pq = PQgetvalue(res, row, col);
    unsigned long int current_pq_length = strlen(current_pq);
    char* current_string = (char*) malloc(sizeof(char) * (current_pq_length + 1));

    strcpy(current_string, current_pq);
    *(data_pointer + col) = current_string;
 }

  return data_pointer;
};


