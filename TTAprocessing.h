using namespace std;
namespace TTA
{

    //class TTAP {
    //public:
        bool static timeContact(int64_t time1, int64_t time2) {
            if (abs(time1 - time2) <= 259200) return true;
            else return false;
        }

        bool static latContact(double lat1, double lat2) {
            if (abs(lat1 - lat2) <= 0.002) return true;
            else return false;
        }

        bool static longtContact(double longt1, double longt2) {
            if (abs(longt1 - longt2) <= 0.002) return true;
            else return false;
        }

        bool static sameClient(const char *clientId1, const char *clientId2) {
            if (clientId1 == clientId2) return true;
            else return false;
        }
    //};

}
