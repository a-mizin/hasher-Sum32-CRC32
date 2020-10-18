#include <fstream>
#include <exception>

#include "../hashlib/hash.h"
#include "app.h"

Application::Application(int argc, char** argv) :
        mode(Mode::None), error(Errors::None)
{

    if (argc == 2 && std::strcmp(argv[1], "-h") == 0)
        mode = Mode::Help;

    else if (argc == 4) {
        for (int i = 1; i < argc; ++i) {
            if (std::strcmp(argv[i], "-m") == 0)
                parseMode(argc, argv, i);
            else
                parseFilePath(argv, i);
        }
    }

    if (filePath.empty() && mode != Mode::Help)
        error = Errors::NoFilePath;
    else if (mode == Mode::None && error == Errors::None)
        error = Errors::NoModeParameter;
}

bool Application::helpMode() {
    if (mode == Mode::Help) {
        printHelp(std::cout);
        return true;
    }

    return false;
}

int Application::someErrors() {
    switch (error) {
        case Errors::None:
            return 0;
        case Errors::NoModeParameter:
            std::cerr << "Hashing mode is not specified.\n";
            printHelp(std::cerr);
            return -2;
        case Errors::ManyModeParameters:
            std::cerr << "There are several hashing methods specified.\n";
            printHelp(std::cerr);
            return -3;
        case Errors::UnknownModeParameter:
            std::cerr << "Unknown -m parameter.\n";
            printHelp(std::cerr);
            return -4;
        case Errors::ModeWithoutParameter:
            std::cerr << "-m without parameter.\n";
            printHelp(std::cerr);
            return -5;
        case Errors::NoFilePath:
            std::cerr << "No file path.\n";
            printHelp(std::cerr);
            return -6;
        case Errors::ManyFiles:
            std::cerr << "Too many files.\n";
            printHelp(std::cerr);
            return -7;
    }
}

uint32_t Application::run() {
    std::ifstream in(filePath, std::ios_base::binary);
    if (!in)
        throw std::exception((std::string("Can't open the file ") + filePath).c_str());

    switch (mode) {
        case Mode::Sum32:
            return getSum32(in);
        case Mode::CRC32:
            return getCRC32(in);
        default:
            throw std::exception("Incorrect mode.");
    }
}

void Application::printHelp(std::ostream& os) const {
    os << "\n"
       << "-h                   -- outputs \"help\" to the stream.\n"
       << "-m [crc32/sum32]     -- sets the type of Hash to be calculated.\n"
       << "[file-path]          -- hash file path.\n";
}

void Application::parseMode(int argc, char **argv, int &i) {
    ++i;
    if (i != argc) {
        if (std::strcmp(argv[i], "crc32") == 0)
            mode = Mode::CRC32;
        else if (std::strcmp(argv[i], "sum32") == 0)
            mode = Mode::Sum32;
        else
            error = Errors::UnknownModeParameter; // ошибка! Неизвестный параметр -m
    } else {
        error = Errors::ModeWithoutParameter; // ошибка! ожидался параметр для -m, а встречен конец строки.
    }
}

void Application::parseFilePath(char** argv, int i) {
    if (filePath.empty())
        filePath = argv[i];
    else
        error = Errors::ManyFiles;
}
