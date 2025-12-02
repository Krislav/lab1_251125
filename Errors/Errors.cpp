#include "Errors.hpp"

void ErrorsOutput(ErrorCode error) {
    if (error == ErrorCode::OK){
        std::cout << "Successful completion\n";
    }
}