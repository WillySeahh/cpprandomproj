//
// Created by Willy Seah on 9/2/23.
//
#include <cstring>
#include <atomic>


template<typename Element, int Size>
class CircularFifo{
public:
    enum { Capacity = Size+1 };

    CircularFifo() {
        _tail = 0;
        _head = 0;
        std::cout << "creating circular fifo " << std::endl;
    }
    ~CircularFifo() {
        std::cout << "destroying circular fifo " << std::endl;

    }

    bool push(Element& item_) {
        auto current_tail = _tail.load();
        auto next_tail = increment(current_tail);
        if(next_tail != _head.load())
        {
            _array[current_tail] = item_;
            _tail.store(next_tail);
            return true;
        }

        return false;  // full queue
    }

    /* Consumer only: updates head index after retrieving the element */
    bool pop(Element& item) {
        const auto current_head = _head.load();
        if(current_head == _tail.load())
            return false;   // empty queue

        item = _array[current_head];
        _head.store(increment(current_head));
        return true;
    }

    //bool wasEmpty() const;
    bool wasEmpty() const {
        return (_head.load() == _tail.load());
    }
    bool wasFull() const
    {
        const auto next_tail = increment(_tail.load());
        return (next_tail == _head.load());
    }
    bool isLockFree() const;

private:
    size_t increment(size_t idx) const
    {
        return (idx + 1) % Capacity;
    }

    std::atomic<size_t>  _tail;
    Element              _array[Capacity];
    std::atomic<size_t>  _head;
};