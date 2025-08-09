#ifndef FILEREADER_H
#define FILEREADER_H

#include <string>
#include <fstream>
#include <stdexcept>

class FileReader
{
public:
    FileReader() = default;
    explicit FileReader(const std::string& filename)
    {
        Open(filename);
    }

    void Open(const std::string& filename)
    {
        if (fileStream_.is_open())
            fileStream_.close();

        fileStream_.open(filename);

        if (!fileStream_)
            throw std::runtime_error("Failed to open file: " + filename);
    }

    void Close()
    {
        if (fileStream_.is_open())
            fileStream_.close();
    }

    bool ReadLine(std::string& line)
    {
        if (!fileStream_.is_open())
            return false;

        return static_cast<bool>(std::getline(fileStream_, line));
    }

    bool IsOpen() const
    {
        return fileStream_.is_open();
    }

private:
    std::ifstream fileStream_;
};

#endif
