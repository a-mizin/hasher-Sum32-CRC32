#include <iostream>

#include "applib/app.h"

int main(int argc, char** argv) {
    Application application(argc, argv);
    
    if (int error = application.someErrors(); error == 0) {
        if (!application.helpMode()) {
            try {
                std::cout << application.run();
            }
            catch (std::exception& e) {
                std::cerr << e.what() << "\n";
                return -1;
            }
        }
    } else {
        return error;
    }

    return 0;
}