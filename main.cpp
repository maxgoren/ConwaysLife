#include <iostream>
#include "app.hpp"
using namespace std;

int main(int argc, char* argv[]) {
    srand(time(0));
    App app;
    app.start();
    return 0;
}