#ifndef AUTOCLICKER_UTILS_H
#define AUTOCLICKER_UTILS_H

#include <iostream>

using namespace std;

int getRootWindowInfo(string grep) {
    FILE *fp;
    char path[64];

    fp = popen(("xwininfo -root | grep \"" + grep + "\"").c_str(), "r");
    if (fp == NULL) {
        cout << ">>Failed to run a command." << endl;
        exit(EXIT_FAILURE);
    }

    while (fgets(path, sizeof(path) - 1, fp) != NULL) {
        stringstream ss(path);
        string temp;
        int width;
        ss >> temp >> width;
        return width;
    }
    pclose(fp);

    return -1;
}

int screenWidth() {
    return getRootWindowInfo("Width: ");
}

int screenHeight() {
    return getRootWindowInfo("Height: ");
}

#endif