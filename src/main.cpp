#include <cpr/cpr.h>
#include <iostream>

int main(int argc, char** argv) {
    std::cout << "Program started!" << std::endl;
    std::cout.flush();  // Force immediate output

    cpr::Response r = cpr::Get(
        cpr::Url{"https://api.themoviedb.org/3/movie/now_playing?language=en-US&page=1"},
        cpr::Header{{"Accept", "application/json"}}
    );

    std::cout << "Status: " << r.status_code << "\n";
    std::cout << "Body length: " << r.text.length() << "\n";
    std::cout << r.text << "\n";
}