#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "..\Errors\Errors.hpp"

class ReadStream {
private:
    std::string file_name;
    FILE* file;
    bool is_open;
    int stream_pos;

    static const int BUFFER_SIZE = 10;
    char buffer[BUFFER_SIZE];
    int buffer_pos;
    int buffer_capacity;

    void BufferRefill();
    
public:
    ReadStream(const std::string& f_name = "");
    ~ReadStream();

    void Open();
    void Close();
    int Seek(int i);

    bool IsOpen() const;
    bool IsEnd() const;
    long GetSize() const;
    long GetPos() const;
    std::string GetFileName() const;

    char ReadChar();
    int FindStr(const std::string& str);
};