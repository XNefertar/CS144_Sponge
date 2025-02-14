#include "byte_stream.hh"

// Dummy implementation of a flow-controlled in-memory byte stream.

// For Lab 0, please replace with a real implementation that passes the
// automated checks run by `make check_lab0`.

// You will need to add private members to the class declaration in `byte_stream.hh`

using namespace std;

ByteStream::ByteStream(const size_t capacity)
        :_byte_stream{},
        _capacity(capacity),
        _read_cnt(0),
        _write_cnt(0),
        _end_input(false)
    {}

size_t ByteStream::write(const string &data) {
    size_t size = data.size();
    if(_end_input) { return 0; }
    int write_size = std::min(size,remaining_capacity());
    for(int i = 0; i < write_size; i++) {
        _byte_stream.push_back(data[i]);
    }
    _write_cnt += write_size;
    return write_size;
}

//! \param[in] len bytes will be copied from the output side of the buffer
string ByteStream::peek_output(const size_t len) const {
    int peek_size = std::min(len,buffer_size());
    return string(_byte_stream.begin(), _byte_stream.begin() + peek_size);
}

//! \param[in] len bytes will be removed from the output side of the buffer
void ByteStream::pop_output(const size_t len) {
    int pop_size = std::min(len,buffer_size());
    for(int i = 0; i < pop_size; i++) {
        _byte_stream.pop_front();
    }
    _read_cnt += pop_size;
}

//! Read (i.e., copy and then pop) the next "len" bytes of the stream
//! \param[in] len bytes will be popped and returned
//! \returns a string
std::string ByteStream::read(const size_t len) {
    size_t read_size = std::min(len,buffer_size());
    std::string ans(peek_output(read_size));
    pop_output(read_size);
    return ans;
}

void ByteStream::end_input() {
    _end_input = true;
}

bool ByteStream::input_ended() const {
    return _end_input;
}

size_t ByteStream::buffer_size() const {
    return _byte_stream.size();
}

bool ByteStream::buffer_empty() const {
    return buffer_size() == 0;
}

bool ByteStream::eof() const {
    return input_ended() && buffer_empty();
}

size_t ByteStream::bytes_written() const {
    return _write_cnt;
}

size_t ByteStream::bytes_read() const {
    return _read_cnt;
}

size_t ByteStream::remaining_capacity() const {
    return _capacity - buffer_size();
}
