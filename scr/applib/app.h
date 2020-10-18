#pragma once

#include <iostream>
#include <cstring>

struct Application {
    Application(int argc, char** argv);

    bool helpMode();
    int someErrors();
    uint32_t run();


private:
    enum class Mode {
        CRC32,
        Sum32,
        Help,
        None,
    };

    enum class Errors {
        ManyModeParameters,
        UnknownModeParameter,
        ModeWithoutParameter,
        ManyFiles,
        NoFilePath,
        NoModeParameter,
        None,
    };

    void printHelp(std::ostream& os) const;

    void parseMode(int argc, char** argv, int& i);
    void parseFilePath(char** argv, int i);

    Errors error;
    Mode mode;
    std::string filePath;
};