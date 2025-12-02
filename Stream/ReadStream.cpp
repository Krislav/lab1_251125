#include "ReadStream.hpp"


void ReadStream::buffer_refill() {
    if (!file) return;
    buffer_capacity = fread(buffer, sizeof(char), BUFFER_SIZE, file);
    buffer_pos = 0;
}

ReadStream::ReadStream(const std::string& f_name = ""):
file_name(f_name), file(nullptr), is_open(false),stream_pos(0), buffer_pos(0), buffer_capacity(0) {}

void ReadStream::Open() {
    if (is_open) return;
    if (file_name.empty()) throw ErrorCode::EMPTY_NAME;

    file = fopen(file_name.c_str(), "rb");
    if (!file) throw ErrorCode::COULDNT_OPEN_FILE;

    is_open = true; 
    stream_pos = 0;
    buffer_refill();
}

void ReadStream::Close() {
    if (!file) throw ErrorCode::FILE_ISNT_OPENED;
    if (is_open && file) {
        fclose(file);
        file = nullptr;
        is_open = false;
        stream_pos = 0;
        buffer_pos = buffer_capacity = 0;
    }
}

int ReadStream::Seek(int i) {
    if (!file) throw ErrorCode::FILE_ISNT_OPENED;
    if (i > GetSize() || i < 0) throw ErrorCode::INDEX_OUT_OF_RANGE;
    
    int res = fseek(file, i, SEEK_SET);
    if (res != 0) throw ErrorCode::SEEK_FAIL;

    stream_pos = i;
    buffer_refill();
    return stream_pos;
}