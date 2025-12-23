#include <cpr/cpr.h>
#include <iostream>
#include <nlohmann/json.hpp>
#include <unordered_map>

const std::unordered_map<std::string, std::string> instruction_to_url = {
    {"playing", "https://api.themoviedb.org/3/movie/now_playing",},
    {"popular", "https://api.themoviedb.org/3/movie/popular",},
    {"top", "https://api.themoviedb.org/3/movie/top_rated",},
    {"upcoming", "https://api.themoviedb.org/3/movie/upcoming",},
};

std::string api_key;

void GetAPIKey() {
    std::ifstream file(".env");

    if (!file.is_open()) {
        throw std::runtime_error("Could not open the .env file!");
    } else {
        std::string line;
        std::getline(file, line);
        bool passed_equals = false;

        for (const char &c : line) {
            if (c == '=') {
                passed_equals = true;
            } else {
                if (!passed_equals) { continue; }

                api_key += c;
            }
        }
    }
}

void SendRequest(const std::string &command) {
    if (!instruction_to_url.count(command)) {
        throw std::runtime_error("Invalid command! The options are: playing, popular, top, and upcoming.");
    }

    cpr::Response r = cpr::Get(
        cpr::Url{instruction_to_url.at(command)},
        cpr::Parameters{
            {"api_key", api_key},
            {"language", "en-US"},
            {"page", "1"}
        },
        cpr::Header{{"accept", "application/json"}, {"Accept-Encoding", "identity"}}
    );

    using json = nlohmann::json;

    json results = json::parse(r.text)["results"];
    int i = 1;

    for (auto it = results.begin(); it != results.end(); it++) {
        auto val = it.value();

        std::cout << "#" << i << ":\n" << "Original Title: " << val["original_title"] << "\n" 
        << "Title: " << val["title"] << "\n"
        << "Overview: " << val["overview"] << "\n"
        << "Release Date: " << val["release_date"] << "\n"
        << "Vote average: " << val["vote_average"] << "/10" << " from a total of " << val["vote_count"] << " votes.\n"
        << "Maturity rating: This move is for" << (val["adult"] ? " adults\n" : " people of all ages.\n")
        << "\n\n";

        i++;
    }
}

int main(int argc, char** argv) {
    GetAPIKey();
    
    int i = 1;

    while (i < argc) {
        std::string command = argv[i];
        SendRequest(command);
        i++;
    }
}