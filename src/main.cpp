#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "rapidjson/document.h"

using namespace std;

class MotionParser {
private:
    string xlFolderPath;

public:
    MotionParser(const string& path) : xlFolderPath(path) {}

    void parseMovie(int movieId) {
        string moviePath = xlFolderPath + "/motion_movie/" + to_string(movieId) + ".json";
        ifstream movieFile(moviePath);
        if (!movieFile.is_open()) {
            cout << "File movie " << movieId << ".json tidak ditemukan." << endl;
            return;
        }

        stringstream buffer;
        buffer << movieFile.rdbuf();

        rapidjson::Document movieDoc;
        movieDoc.Parse(buffer.str().c_str());

        // Memeriksa properti motion_unit
        if (!movieDoc.HasMember("motion_unit") || !movieDoc["motion_unit"].IsArray() || movieDoc["motion_unit"].Empty()) {
            cout << "Property 'motion_unit' tidak ditemukan di file movie." << endl;
            return;
        }

        // Mengambil rujukan unit pertama
        const auto& unitRef = movieDoc["motion_unit"][0];
        int unitId = unitRef["id"].GetInt();
        double speed = unitRef.HasMember("speed") ? unitRef["speed"].GetDouble() : 1.0;
        int loop = unitRef.HasMember("loop") ? unitRef["loop"].GetInt() : 1;

        string unitPath = xlFolderPath + "/motion_unit/" + to_string(unitId) + ".json";
        ifstream unitFile(unitPath);
        if (!unitFile.is_open()) {
            cout << "File unit " << unitId << ".json tidak ditemukan." << endl;
            return;
        }

        stringstream unitBuffer;
        unitBuffer << unitFile.rdbuf();

        rapidjson::Document unitDoc;
        unitDoc.Parse(unitBuffer.str().c_str());

        cout << "\n=== HASIL PARSING MOTION ===" << endl;
        cout << "ID Unit Rujukan : " << unitId << endl;
        cout << "Speed (Movie)   : " << speed << endl;
        cout << "Loop (Movie)    : " << loop << endl;

        if (unitDoc.HasMember("name")) {
            cout << "Nama Unit       : " << unitDoc["name"].GetString() << endl;
        }
        if (unitDoc.HasMember("total_frame")) {
            cout << "Total Frame     : " << unitDoc["total_frame"].GetInt() << endl;
        }
        if (unitDoc.HasMember("frames") && unitDoc["frames"].IsArray()) {
            cout << "Daftar Frame    :" << endl;
            const auto& frames = unitDoc["frames"];
            for (rapidjson::SizeType i = 0; i < frames.Size(); i++) {
                cout << "  Frame " << i + 1 << endl;
            }
        }
    }
};

int main() {
    int movieId;
    cout << "Masukkan ID Motion Movie: ";
    cin >> movieId;

    MotionParser parser("XL");
    parser.parseMovie(movieId);

    return 0;
}