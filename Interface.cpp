#include "Interface.hpp"

std::string file_name;
WriteStream* write_stream = nullptr;
ReadStream* read_stream = nullptr;

void Menu() {
    while (true) {
        std::cout << "\n=== Main Menu ==="
                  << "\n1. Enter file name"
                  << "\n2. Stream operations"
                  << "\n3. Run Test"
                  << "\n4. Exit"
                  << "\nSelect: ";
        
        int choice;
        std::cin >> choice;

        switch (choice) {
            case 1: FileNameAdd(); break;
            case 2: StreamOperations(); break;
            case 3: TestAll(); break;
            case 4: return;
            default: std::cout << "Invalid choice!\n";
        }
    }
}

void FileNameAdd() {
    std::cout << "Enter file name: ";
    std::cin >> file_name;
}

void StreamOperations() {
    if (read_stream == nullptr) read_stream = new ReadStream(file_name);
    if (write_stream == nullptr) write_stream = new WriteStream(file_name);

    while (true) {
        std::cout << "\n=== Stream Operations ==="
                  << "\n1. Open stream for read"
                  << "\n2. Open stream for write"
                  << "\n3. Close stream"
                  << "\n4. Seek"
                  << "\n5. Read char"
                  << "\n6. Read Text"
                  << "\n7. Write char"
                  << "\n8. Write String"
                  << "\n9. Delete Stream"
                  << "\n10. Exit"
                  << "\nSelect: ";
        
        int choice;
        std::cin >> choice;
        try {
        switch (choice) {
            case 1:
                read_stream->Open();
                std::cout << "\nRead stream opened";
                break;
            case 2:
                write_stream->Open();
                std::cout << "\nWrite stream opened";
                break;
            case 3:
                read_stream->Close();
                write_stream->Close();
                std::cout << "\nStream closed";
                break;
            case 4:
                if (!read_stream->IsOpen() && write_stream->IsOpen()) {std::cout << "\nStream isn't opened"; break;}

                int i;
                std::cout << "\nEnter seek index: ";
                std::cin >> i;
                if (read_stream->IsOpen()) read_stream->Seek(i);
                if (write_stream->IsOpen()) write_stream->Seek(i);
                std::cout << "\nSeek completed successfuly";
                break;
            case 5:
                if (!read_stream->IsOpen()) {std::cout << "\nStream isn't opened"; break;}

                std::cout << "\nReaded char:" << read_stream->ReadCharFromBuffer();
                break;
            case 6: 
                if (!read_stream->IsOpen()) {std::cout << "\nStream isn't opened"; break;}

                std::cout << "\nReaded Text:" << read_stream->ReadCharFromBuffer();
                break;
            case 7:
                if (!write_stream->IsOpen()) {std::cout << "\nStream isn't opened"; break;}
                
                char ch;
                std::cout << "\nEnter char: ";
                std::cin >> ch;
                write_stream->WriteChar(ch);
                break;
            case 8: {
                if (!write_stream->IsOpen()) {std::cout << "\nStream isn't opened"; break;}
                
                std::string str_in;
                std::cout << "\nEnter str: ";
                std::cin >> str_in;
                write_stream->WriteStr(str_in);
                break;}
            case 9:
                if (read_stream != nullptr) {delete read_stream; read_stream = nullptr;}
                if (write_stream != nullptr) {delete write_stream; write_stream = nullptr;}
                break;
            case 10: 
                read_stream->Close();
                write_stream->Close();
                std::cout << "\nStream closed";
                return;
            default: std::cout << "Invalid choice!\n";
        }
        } catch(ErrorCode error) {ErrorsOutput(error);}
    }
}