using namespace std;
namespace TTA
{
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


    class TTAP
    {
    public:
        bool static timeContact(int t1, int t2) {
            if(abs(t1-t2)<=259200) return true;
            else return false;
        }
        bool static latContact(double x1, double x2){
            if(abs(x1-x2)<=0.002) return true;
            else return false;
        }
        bool static longtContact(double x1, double x2){
            if(abs(x1-x2)<=0.002) return true;
            else return false;

        }
    };

}
