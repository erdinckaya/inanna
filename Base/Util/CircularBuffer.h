//
// Created by misterdortnal on 27.01.2019.
//

#ifndef INANNA_CIRCULARBUFFER_H
#define INANNA_CIRCULARBUFFER_H

#include <vector>


namespace Inanna {
    template<typename C>
    struct CircularBuffer {

        explicit CircularBuffer(int capacity = 1) : capacity(capacity), buffer(static_cast<unsigned long>(capacity)),
                                                    begin_index(0), end_index(0), _size(0) {}

        C &operator[](int x) {
            return buffer[(begin_index + x + capacity) % capacity];
        }

        int begin() const {
            return begin_index;
        }

        int end() const {
            return end_index;
        }

        int size() const {
            return _size;
        }

        void push_front(C c) {
            begin_index = decrease(begin_index);
            buffer[begin_index] = c;
            if (begin_index == end_index) {
                end_index = decrease(end_index);
            }
            increase_size();
        }

        void push_back(C c) {
            buffer[end_index] = c;
            if (begin_index == end_index) {
                begin_index = increase(begin_index);
            }
            end_index = increase(end_index);
            increase_size();
        }

        C front() {
            return buffer[begin_index];
        }

        C back() {
            return buffer[(end_index - 1 + capacity) % capacity];
        }

        C pop_front() {
            if (size() > 0) {
                begin_index = increase(begin_index);
                decrease_size();
            }
        }

        C pop_back() {
            if (size() > 0) {
                end_index = decrease(end_index);
                decrease_size();
            }
        }

        bool empty() {
            return size() == 0;
        }

        std::vector<C> to_vector() {
            std::vector<C> result(buffer.size());
            for (int i = begin_index; i < _size; ++i) {
                result.push_back(this[i]);
            }
            return result;
        }

        C* to_array() {
            C result[_size];
            for (int i = begin_index; i < _size; ++i) {
                result[i] = this[i];
            }

            return result;
        }

    private:
        int increase(int index) {
            return (index + 1) % capacity;
        }

        int decrease(int index) {
            return (index - 1 + capacity) % capacity;
        }

        void increase_size() {
            _size++;
            if (_size > capacity) {
                _size = capacity;
            }
        }

        void decrease_size() {
            _size--;
            if (_size < 0) {
                _size = 0;
            }
        }

        int begin_index;
        int end_index;
        int capacity;
        int _size;
        std::vector<C> buffer;

    };
}

#endif //INANNA_CIRCULARBUFFER_H
