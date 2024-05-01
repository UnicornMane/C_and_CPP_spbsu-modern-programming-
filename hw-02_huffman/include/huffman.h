#pragma once

#include <iostream>
#include <cstddef>
#include <map>
#include <vector>
#include <memory>
#include <utility>
#include <map>
#include <string>
#include <tuple>
#include <filesystem>
#include <vector>
#include <exception>

namespace huffman_exceptions
{
    class HuffmanException : public std::exception
    {
    private:
        std::string _message{};
    public:
        explicit HuffmanException(std::string message);

        const char *what() const noexcept override;
    };
}

namespace huffman_constants
{
    const std::string STR_ZERO = "0";
    const std::string STR_ONE = "1";
    const char CHAR_ZERO = '0';
    const char CHAR_ONE = '1';
    const std::size_t BITS_IN_ONE_BYTE = 8;
    const std::size_t SIZE_T_ZERO = 0;
    const std::size_t SIZE_T_ONE = 1;
    const std::string STR_EMPTY{};
    const char CHAR_EMPTY{};
}

namespace huffman_compression
{
    struct frequency_table;

    class huffman;

    class node;

    class tree;

    class huffman
    {
    public:
        static std::tuple<std::size_t, std::size_t, std::size_t>
        Compress(std::ifstream &in, std::ofstream &out);

        static std::tuple<std::size_t, std::size_t, std::size_t>
        Decompress(std::ifstream &in, std::ofstream &out);

    private:
        static void GetDataFromFile(std::ifstream &in, std::vector<char> &data);

        static std::pair<std::size_t, std::size_t>
        WriteCompressedDataToFile(std::ofstream &out, std::vector<char> &data);

        static void ReadFrequencyTable(std::ifstream &in, std::map<char, std::size_t> &table);

        static std::size_t
        ReadEncodedDataToString(std::istream &in, std::string &data, std::map<std::string, char> &decodedMap);

        static std::size_t GetSizeOfFile(std::ifstream &in);
    };

    struct frequency_table
    {
        std::map<char, std::size_t> _table;

        frequency_table() = default;

        explicit frequency_table(std::map<char, std::size_t> table);

        explicit frequency_table(const std::vector<char> &bytes);

        std::size_t operator[](char value);

        std::size_t GetSizeOfTable() const;
    };

    class node
    {
    private:
        char _value;
        std::size_t _frequency;

        std::shared_ptr<node> _left;
        std::shared_ptr<node> _right;

    public:
        node() : _value(0), _frequency(0), _left(nullptr), _right(nullptr)
        {}

        node(char value, std::size_t frequency) : _value(value), _frequency(frequency), _left(nullptr),
                                                  _right(nullptr)
        {}

        node(std::shared_ptr<node> left,
             std::shared_ptr<node> right) : _value(0), _frequency(left->_frequency + right->_frequency),
                                            _left(std::move(left)),
                                            _right(std::move(right))
        {}

        char GetValue() const;

        void SetValue(char value);

        std::size_t GetFrequency() const;

        void SetFrequency(std::size_t frequency);

        std::shared_ptr<node> GetLeft() const;

        void SetLeft(std::shared_ptr<node> left);

        std::shared_ptr<node> GetRight() const;

        void SetRight(std::shared_ptr<node> right);
    };

    class tree
    {
    private:
        std::shared_ptr<node> _root = nullptr;
        std::map<char, std::string> huffman_codes_for_bytes;
        std::map<std::string, char> bytes_for_huffman_codes;

        void ObtainHuffmanCodes(const std::shared_ptr<node> &node, const std::string &code);

    public:
        tree();

        explicit tree(const frequency_table &table);

        std::shared_ptr<node> GetRoot() const;

        std::string GetHuffmanCodeForByte(char value);

        char GetByteForHuffmanCode(const std::string &code);

        std::map<std::string, char> &GetMapBytesForHuffmanCodes();
    };
}
