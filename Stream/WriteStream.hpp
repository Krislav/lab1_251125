#pragma once
#include <iostream>
#include <string>
#include "..\Errors\Errors.hpp"

class WriteStream {
private:
    std::string file_name;
    FILE* file;
    bool is_open;
    int stream_pos;

    static const int BUFFER_SIZE = 10;
    char buffer[BUFFER_SIZE];
    int buffer_pos;
    int buffer_capacity;

    void WriteBuffer();
    
public:
    WriteStream(const std::string& f_name = "");
    ~WriteStream();

    void Open();
    void Close();
    int Seek(int i);

    bool IsOpen() const;
    bool IsEnd() const;
    long GetSize() const;
    long GetPos() const;
    std::string GetFileName() const;

    void WriteChar(char data);
    void WriteStr(std::string str);
};