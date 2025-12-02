#pragma once
#include <iostream>
#include <string>
#include "..\Errors\Errors.hpp"

class ReadStream {
private:
    std::string file_name;
    FILE* file;
    bool is_open;
    int stream_pos;

    static const int BUFFER_SIZE = 500;
    char buffer[BUFFER_SIZE];
    int buffer_pos;
    int buffer_capacity;

    void buffer_refill();
    
public:
    ReadStream(const std::string& f_name = "");
    ~ReadStream() = default;

    void Open();
    void Close();
    int Seek(int i);

    bool IsOpen() {
        return is_open;
    }
    bool IsEnd() {}
    long GetSize() {}
    long GetPos() {}
    std::string GetFileName(){}

    char ReadChar(){}

    void PrintFile(){}
};