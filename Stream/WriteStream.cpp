#include "WriteStream.hpp"


void WriteStream::WriteBuffer() {
    if (buffer_pos > 0 && file) {
        int symb = fwrite(buffer, sizeof(char), buffer_pos, file);
        if (symb != buffer_pos) throw ErrorCode::WRITE_FAILED;
        buffer_pos = 0;
    }
}

WriteStream::WriteStream(const std::string& f_name):
file_name(f_name), file(nullptr), is_open(false),stream_pos(0), buffer_pos(0), buffer_capacity(0) {}

WriteStream::~WriteStream() {
    Close();
}

void WriteStream::Open() {
    if (is_open) return;
    if (file_name.empty()) throw ErrorCode::EMPTY_NAME;

    file = fopen(file_name.c_str(), "wb");
    if (!file) throw ErrorCode::COULDNT_OPEN_FILE;

    is_open = true; 
    stream_pos = 0;
}

void WriteStream::Close() {
    if (is_open && file) {
        fclose(file);
        file = nullptr;
        is_open = false;
        stream_pos = 0;
        buffer_pos = buffer_capacity = 0;
    }
}

int WriteStream::Seek(int i) {
    if (!is_open || !file) throw ErrorCode::FILE_ISNT_OPENED;
    if (i > GetSize() || i < 0) throw ErrorCode::INDEX_OUT_OF_RANGE;
    
    int res = fseek(file, i, SEEK_SET);
    if (res != 0) throw ErrorCode::SEEK_FAIL;

    stream_pos = i;
    return stream_pos;
}

bool WriteStream::IsOpen() const{
    return is_open;
}

bool WriteStream::IsEnd() const{
    if (!is_open || !file) {
        return true;
    }
    if (buffer_pos < buffer_capacity) {
        return false;
    }

    int ch = fgetc(file);
    if (ch == EOF) {
        return true;
    } else {
        ungetc(ch, file);
        return false;
    }
}

long WriteStream::GetSize() const{
    if (!is_open || !file) return 0;
    
    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    fseek(file, 0, stream_pos);
    return size;
}

long WriteStream::GetPos() const{
    return stream_pos;
}

std::string WriteStream::GetFileName() const{
    return file_name;
}

void WriteStream::WriteChar(char data) {
    if (!is_open || !file) throw ErrorCode::COULDNT_OPEN_FILE;
    
    buffer[buffer_pos] = data;
    buffer_pos++;
    WriteBuffer();
    stream_pos++;
}

void WriteStream::WriteStr(std::string str){
    if (!is_open || !file) throw ErrorCode::COULDNT_OPEN_FILE;
    
    for (int i = 0; i < str.size(); i++) {
        WriteChar(str[i]);
    }
}