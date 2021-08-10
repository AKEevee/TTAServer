#include <mongoc/mongoc.h>
#include <string.h>
#include <bson/bson.h>
#include <iostream>
#include <ctime>
#include <random>
#include <windows.h>
using namespace std;
int
main (int argc, char *argv[]) {
    const char *uri_string = "mongodb://34.126.108.92:27017";
    mongoc_uri_t *uri;
    mongoc_client_t *client;
    mongoc_database_t *database;
    mongoc_collection_t *collection1, *collection2, *collection3;
    bson_t *command, reply, *insert;
    bson_error_t error;
    char *str;
    bool retval;
    bson_t *insert2;
    mongoc_cursor_t *cursor;
    const bson_t *doc;
    bson_t *query, *opts;
    char *str2;
    std::string str3;

    /*
     * Required to initialize libmongoc's internals
     */
    mongoc_init();

    /*
     * Optionally get MongoDB URI from command line
     */
    if (argc > 1) {
        uri_string = argv[1];
    }

    /*
     * Safely create a MongoDB URI object from the given string
     */
    uri = mongoc_uri_new_with_error(uri_string, &error);
    if (!uri) {
        fprintf(stderr,
                "failed to parse URI: %s\n"
                "error message:       %s\n",
                uri_string,
                error.message);
        return EXIT_FAILURE;
    }

    /*
     * Create a new client instance
     */
    client = mongoc_client_new_from_uri(uri);
    if (!client) {
        return EXIT_FAILURE;
    }

    /*
     * Register the application name so we can track it in the profile logs
     * on the server. This can also be done from the URI (see other examples).
     */
    mongoc_client_set_appname(client, "connect-AKEevee");

    /*
     * Get a handle on the database "db1" and collections
     */
    database = mongoc_client_get_database(client, "db1");
    //collection1 = mongoc_client_get_collection(client, "db1", "coordinates");
    collection1 = mongoc_client_get_collection(client, "TtaDb", "coordinates");
    collection2 = mongoc_client_get_collection(client, "TtaDb", "matches");
    collection3 = mongoc_client_get_collection(client, "TtaDb", "cases");

    /*
     * Do work. This example pings the database, prints the result as JSON and
     * performs an insert
     */
    command = BCON_NEW ("ping", BCON_INT32(1));

    retval = mongoc_client_command_simple(
            client, "admin", command, NULL, &reply, &error);

    if (!retval) {
        fprintf(stderr, "%s\n", error.message);
        return EXIT_FAILURE;
    }

    str = bson_as_json(&reply, NULL);
    printf("%s\n", str);


    //for(int i=0; i<7; i++) {
        //insert = BCON_NEW ("Lo", BCON_DOUBLE(0.0945));
        //insert2 = BCON_NEW ("La", BCON_DOUBLE(0.0894));
/*
        double lower_bound = 0;
        double upper_bound = 10000;
        std::uniform_real_distribution<double> unif(lower_bound, upper_bound);
        std::default_random_engine re;
        double Lo = unif(re);
        double La = unif(re);
        Lo = (time(0)) / Lo;
        La = (time(0)) / La;
*/

/*      insert2 = bson_new();
        BSON_APPEND_INT64  (insert2, "time", time(0))
        BSON_APPEND_DOUBLE (insert2, "lat", La);
        BSON_APPEND_DOUBLE (insert2, "longt", Lo);
        */

//inserting data
        /*if (!mongoc_collection_insert_one(collection1, insert2, NULL, NULL, &error)) {
            fprintf(stderr, "%s\n", error.message);
        }*/
        //Sleep(3000);
    //}

    query = bson_new();
    int64_t input;
    //cin>>input;
    opts = BCON_NEW ("projection", "{",
                     "time", BCON_BOOL (true),
                     "lat", BCON_BOOL (true),
                     "longt", BCON_BOOL (true),
                     "clientId", BCON_BOOL (true),
                     "}");

    //query = insert2;
    //cursor = mongoc_collection_find_with_opts(collection1, query, opts, NULL);
   // for (int i=-100; i<100; i++) {
        //std::cout<<i<<" ";
        query = bson_new();
        //BSON_APPEND_INT64(query, "time", input+i);cursor = mongoc_collection_find_with_opts(collection1, query, NULL, NULL);
        cursor = mongoc_collection_find_with_opts(collection1, query, opts, NULL);
        while (mongoc_cursor_next(cursor, &doc)) {
            str2 = bson_as_canonical_extended_json(doc, NULL);
            printf("%s\n", str2);
            //insert to "matches" collection
            /*if (!mongoc_collection_insert_one(collection2, doc, NULL, NULL, &error)) {
                fprintf(stderr, "%s\n", error.message);
            }*/



            bson_iter_t iter2;
            bson_iter_t val;
            int64_t x;

            //iterate thru data and (store them to c varibles in the future)

            if ( bson_iter_init(&iter2, doc) &&
                bson_iter_find_descendant(&iter2, "clientId", &val) ) {
                cout<< "clientId = " << bson_iter_utf8(&val,NULL) << endl;
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
   // }

    int64_t count;
    count = mongoc_collection_count_documents (collection1,query, NULL, 0, NULL, &error);
    std::cout<<std::endl<<count<<std::endl;

    //bson_destroy (insert);
    bson_destroy (&reply);
    bson_destroy (command);
    bson_free (str);

    /*
     * Release our handles and clean up libmongoc
     */
    mongoc_collection_destroy (collection2);
    mongoc_collection_destroy (collection1);
    mongoc_database_destroy (database);
    mongoc_uri_destroy (uri);
    mongoc_client_destroy (client);
    mongoc_cleanup();

    return EXIT_SUCCESS;
}
