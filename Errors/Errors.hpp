#pragma once
#include <iostream>

enum class ErrorCode {
    OK,
    EMPTY_NAME,
    COULDNT_OPEN_FILE,
    FILE_ISNT_OPENED,
    INDEX_OUT_OF_RANGE,
    SEEK_FAIL
};

void ErrorsOutput(ErrorCode error);