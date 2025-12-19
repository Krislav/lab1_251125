#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "FindSupport.hpp"
#include "..\Errors\Errors.hpp"

class ReadStream {
private:
    std::string file_name;
    FILE* file;
    bool is_open;
    int stream_pos;
    
public:
    static const int BUFFER_SIZE = 5;
    char buffer[BUFFER_SIZE];
    int buffer_pos;
    int number_of_characters_read;
    void BufferRead();

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

    char ReadCharFromBuffer();
    std::string ReadTextFromBuffer();
    int FindStr(const std::string& pattern);
};