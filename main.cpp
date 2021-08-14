#include <mongoc/mongoc.h>
#include <string.h>
#include <bson/bson.h>
#include <iostream>
#include <ctime>
#include <random>
#include <windows.h>
#include "TTAprocessing.h"
using namespace std;
using namespace TTA;
int
main (int argc, char *argv[]) {
    bool retval;
    bson_t *insert2;
    char *str2;
    //initialise variables
    const char *uri_string = "mongodb://34.126.108.92:27017";
    mongoc_uri_t *uri;
    mongoc_client_t *client;
    mongoc_database_t *database;
    mongoc_collection_t *collection1, *collection2, *collection3;
    bson_t *command, reply, *insert;
    bson_error_t error;
    char *str;
    mongoc_cursor_t *cursor;
    const bson_t *doc;
    bson_t *query, *opts;

    //Required to initialize libmongoc's internals
    mongoc_init();

    //Optionally get MongoDB URI from command line
    if (argc > 1) uri_string = argv[1];

    //Safely create a MongoDB URI object from the given string
    uri = mongoc_uri_new_with_error(uri_string, &error);
    if (!uri) {
        fprintf(stderr,"failed to parse URI: %s\n""error message: %s\n",uri_string,error.message);
        return EXIT_FAILURE;
    }

    //Create a new client instance
    client = mongoc_client_new_from_uri(uri);
    if (!client) {
        return EXIT_FAILURE;
    }

    /* Register the application name so we can track it in the profile logs
    on the server. This can also be done from the URI (see other examples). */

    mongoc_client_set_appname(client, "connect-AKEevee");

    //Get a handle on the database "TtaDb" and its collections
    database = mongoc_client_get_database(client, "db1");
    collection1 = mongoc_client_get_collection(client, "TtaDb", "coordinates");
    collection2 = mongoc_client_get_collection(client, "TtaDb", "matches");
    collection3 = mongoc_client_get_collection(client, "TtaDb", "cases");

    //Do work. This test pings the database, prints the result as JSON and
    command = BCON_NEW ("ping", BCON_INT32(1));
    retval = mongoc_client_command_simple(client, "admin", command, NULL, &reply, &error);

    if (!retval) {
        fprintf(stderr, "%s\n", error.message);
        return EXIT_FAILURE;
    }

    str = bson_as_json(&reply, NULL);
    printf("%s\n", str);


/*      creating data to insert if wanted
        insert2 = bson_new();
        BSON_APPEND_INT64  (insert2, "time", time(0))
        BSON_APPEND_DOUBLE (insert2, "lat", La);
        BSON_APPEND_DOUBLE (insert2, "longt", Lo); */

//inserting data
        //if (!mongoc_collection_insert_one(collection1, insert2, NULL, NULL, &error))
        //fprintf(stderr, "%s\n", error.message);

    char *confirmedClient;
    cout<<"Key in clientId of confirmed case: ";
    cin>>confirmedClient;

        opts = BCON_NEW ("projection", "{",
                         "time", BCON_BOOL (true),
                         "lat", BCON_BOOL (true),
                         "longt", BCON_BOOL (true),
                         "clientId", BCON_BOOL (true),
                         "}");

        query = bson_new(); //empty query to query all data in collection
        cursor = mongoc_collection_find_with_opts(collection1, query, opts, NULL);
        while (mongoc_cursor_next(cursor, &doc)) {
            //str2 = bson_as_canonical_extended_json(doc, NULL);
            //print bson data that has been read
            //printf("%s\n", str2);

            //insert to "matches" collection
            /*if (!mongoc_collection_insert_one(collection2, doc, NULL, NULL, &error)) {
                fprintf(stderr, "%s\n", error.message);
            }*/

            bson_iter_t iter2, val;
            int64_t x;
            const char *str3;

            //iterate thru data (and store them to c variables in the future)

            if ( bson_iter_init(&iter2, doc) &&
                bson_iter_find_descendant(&iter2, "clientId", &val) ) {
                str3 = bson_iter_utf8(&val,nullptr);
                cout<< "clientId = " << str3 << endl;
            }

            if ( bson_iter_init(&iter2, doc) &&
                bson_iter_find_descendant(&iter2, "lat", &val) ) {
                cout.precision(10);
                cout<< "lat = " << bson_iter_as_double(&val) << endl;
            }

            if ( bson_iter_init(&iter2, doc) &&
                 bson_iter_find_descendant(&iter2, "lat", &val) ) {
                cout.precision(10);
                cout<< "longt = " << bson_iter_as_double(&val) << endl;
            }

            if ( bson_iter_init(&iter2, doc) &&
                bson_iter_find_descendant(&iter2, "time", &val) ) {
                cout<< "time = " << bson_iter_as_int64(&val) << endl;
            }

            bson_free(str2);
        }

    //count number of datasets
    int64_t count;
    count = mongoc_collection_count_documents (collection1,query, nullptr, 0, nullptr, &error);
    cout<<"Number of datasets: "<<count<<endl;

    //bson_destroy (insert);
    bson_destroy (&reply);
    bson_destroy (command);
    bson_free (str);

    //Release our handles and clean up libmongoc (unsafe for now)
    mongoc_collection_destroy (collection2);
    mongoc_collection_destroy (collection1);
    mongoc_database_destroy (database);
    mongoc_uri_destroy (uri);
    mongoc_client_destroy (client);
    mongoc_cleanup();

    return EXIT_SUCCESS;
}
