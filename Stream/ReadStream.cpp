#include "ReadStream.hpp"


void ReadStream::BufferRefill() {
    if (!file) return;
    buffer_capacity = fread(buffer, sizeof(char), BUFFER_SIZE, file);
    buffer_pos = 0;
}

ReadStream::ReadStream(const std::string& f_name):
file_name(f_name), file(nullptr), is_open(false),stream_pos(0), buffer_pos(0), buffer_capacity(0) {}

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
    BufferRefill();
}

void ReadStream::Close() {
    if (is_open && file) {
        fclose(file);
        file = nullptr;
        is_open = false;
        stream_pos = 0;
        buffer_pos = buffer_capacity = 0;
    }
}

int ReadStream::Seek(int i) {
    if (!is_open || !file) throw ErrorCode::FILE_ISNT_OPENED;
    if (i > GetSize() || i < 0) throw ErrorCode::INDEX_OUT_OF_RANGE;
    
    int res = fseek(file, i, SEEK_SET);
    if (res != 0) throw ErrorCode::SEEK_FAIL;

    stream_pos = i;
    BufferRefill();
    return stream_pos;
}

bool ReadStream::IsOpen() const{
    return is_open;
}

bool ReadStream::IsEnd() const{
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

long ReadStream::GetSize() const{
    if (!is_open || !file) return 0;
    
    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    fseek(file, 0, stream_pos);
    return size;
}

long ReadStream::GetPos() const{
    return stream_pos;
}

std::string ReadStream::GetFileName() const{
    return file_name;
}

char ReadStream::ReadChar() {
    if (!is_open || !file) throw ErrorCode::FILE_ISNT_OPENED;
    
    if (buffer_pos >= buffer_capacity) {
        BufferRefill();
        if (buffer_capacity == 0) throw ErrorCode::INDEX_OUT_OF_RANGE;
    }
    
    char ch = buffer[buffer_pos];
    buffer_pos++;
    stream_pos++;
    return ch;
}

bool VectorCheck(std::vector<char>& symbols, char ch) {
    for (int i = 0; i < symbols.size(); i++){
        if (symbols[i] == ch) return i;
    }
    return symbols.size();
}

void MakeStopList(std::vector<int>& shift, std::vector<char>& symbols, const std::string& str) {// Создание стоп-листа
    int l = str.length();
    shift.clear();
    symbols.clear();
    shift.push_back(l);
    shift.push_back(l);
    symbols.push_back('*');
    symbols.push_back(str[l-1]);

    for (int i = l-2; i >= 0; i--) {
        if (VectorCheck(symbols, str[i]) != symbols.size()) {
            shift.push_back(l-i-1);
            symbols.push_back(str[i]);
        }
    }

    return;
}

int ReadStream::FindStr(const std::string& str){
    long size = GetSize();
    int l = str.length();
    int count = 0;
    if (l > size) return 0;
    std::vector<int> shift;
    std::vector<char> symbols;
    MakeStopList(shift, symbols, str);
    std::string original;
    for (int i = 0; i < l; i++) {
        original += ReadChar();
    }

    
    int i = l-1;
    while (i < size) {
        for (int j = l-1; j >= 0; j--) {
            if (original[j] != str[j]) {
                for (int h = 0; h < shift[VectorCheck(symbols, original[j])] - (l-1 - j); i++){
                    original.erase(0, 1);
                    original += ReadChar();
                }
                break;
            }
            if (j == 0) count++;
        }
    }

    return count;
}