#include "ReadStream.hpp"


void ReadStream::BufferRead() {
    if (!file) return;
    number_of_characters_read = fread(buffer, sizeof(char), BUFFER_SIZE, file);
    buffer_pos = 0;
}

ReadStream::ReadStream(const std::string& f_name):
file_name(f_name), file(nullptr), is_open(false),stream_pos(0), buffer_pos(0), number_of_characters_read(0) {}

ReadStream::~ReadStream(){
    Close();
}

void ReadStream::Open() {
    if (is_open) return;
    if (file_name.empty()) throw ErrorCode::EMPTY_NAME;

    file = fopen(file_name.c_str(), "rb");
    if (!file) throw ErrorCode::COULDNT_OPEN_FILE;

    is_open = true; 
    stream_pos = 0;
    BufferRead();
}

void ReadStream::Close() {
    if (is_open && file) {
        fclose(file);
        file = nullptr;
        is_open = false;
        stream_pos = 0;
        buffer_pos = number_of_characters_read = 0;
    }
}

int ReadStream::Seek(int i) {
    if (!is_open || !file) throw ErrorCode::FILE_ISNT_OPENED;
    if (i > GetSize() || i < 0) throw ErrorCode::INDEX_OUT_OF_RANGE;
    
    int res = fseek(file, i, SEEK_SET);
    if (res != 0) throw ErrorCode::SEEK_FAIL;

    stream_pos = i;
    BufferRead();
    return stream_pos;
}

bool ReadStream::IsOpen() const{
    return is_open;
}

bool ReadStream::IsEnd() const{
    if (!is_open || !file) {
        return true;
    }
    if (buffer_pos < number_of_characters_read) {
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

long ReadStream::GetSize() const{
    if (!is_open || !file) return 0;
    
    int current_pos = ftell(file);
    fseek(file, 0, SEEK_END);
    int size = ftell(file);
    fseek(file, current_pos, SEEK_SET);
    return size;
}

long ReadStream::GetPos() const{
    return stream_pos;
}

std::string ReadStream::GetFileName() const{
    return file_name;
}

char ReadStream::ReadCharFromBuffer() {
    if (!is_open || !file) throw ErrorCode::FILE_ISNT_OPENED;
    
    if (buffer_pos >= number_of_characters_read) {
        BufferRead();
        if (number_of_characters_read == 0) throw ErrorCode::INDEX_OUT_OF_RANGE;
    }
    
    char ch = buffer[buffer_pos];
    buffer_pos++;
    stream_pos++;
    return ch;
}

std::string ReadStream::ReadTextFromBuffer(){
    if (!is_open || !file) throw ErrorCode::FILE_ISNT_OPENED;

    std::string text;
    try {
        while(!IsEnd()) {
            text += ReadCharFromBuffer();
        }
    } catch (const ErrorCode ex) {
    if (ex != ErrorCode::INDEX_OUT_OF_RANGE) throw;
    }
            
    return text;
}

int ReadStream::FindStr(const std::string& pattern){
    if (!is_open || !file) throw ErrorCode::FILE_ISNT_OPENED;
    long size = GetSize();
    int l = pattern.length();
    int count = 0;
    if (l > size) return 0;
    std::vector<int> shift;
    std::vector<char> symbols;
    MakeStopList(shift, symbols, pattern);
    std::string substr = "";
    for (int z = 0; z < l; z++) {
        substr += ReadCharFromBuffer();
    }

    try{
    while (stream_pos <= size) {
        bool is_dif = false;
        for (int j = l-1; j >= 0; j--) {
            if (substr[j] != pattern[j] && !is_dif) {
                is_dif = true;
                std::cout << substr << " error\n";
                if (VectorCheck(symbols, substr[l-1]) != -1) {
                    int hh = shift[VectorCheck(symbols, substr[l-1])];
                    substr = substr.substr(hh, l-hh);
                    for (int h = 0; h < hh; h++) substr += ReadCharFromBuffer();
                }
                else {
                    substr.clear();
                    for (int h = 0; h < l; h++) substr += ReadCharFromBuffer();
                }
            }
        }
        if (!is_dif) {
            count++;
            int hh = shift[VectorCheck(symbols, substr[l-1])];
            if (l-hh == 0) substr = substr.substr(hh, l-hh);
            else substr = "";
            for (int h = 0; h < hh; h++) substr += ReadCharFromBuffer();
        }
    }
    } catch(ErrorCode ex) {
        if (ex != ErrorCode::INDEX_OUT_OF_RANGE) throw;
    }   

    return count;
}