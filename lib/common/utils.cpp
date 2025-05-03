#include "utils.h"
#include <chrono>
#include <ctime>

string timestamp() {
    time_t now = time(nullptr);
    char buf[64];
    strftime(buf, sizeof(buf), "%F %T", localtime(&now));
    return string(buf);
}

void log(const string &prefix, const string &msg) {
    cout << "[" << prefix << "] " << timestamp() << ": " << msg << endl;
}
