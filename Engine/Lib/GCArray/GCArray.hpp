#ifndef E0920D85_4549_4E4B_B5EB_0AF38A5B399A
#define E0920D85_4549_4E4B_B5EB_0AF38A5B399A

#include <array>
#include <stack>

template<class _Type, std::size_t _n_size>
class GCArray
{
private:
    std::array<_Type, _n_size> _array {};
    std::stack<int> _stack {};
    std::array<bool, _n_size> _indexes;
    int count {0};
public:
    GCArray()
    {
        for (int i = _n_size-1; i >= 0; i--)
        {
            _stack.push(i);
        }
        
        _indexes.fill(false);
    };
    ~GCArray(){};

    inline std::array<_Type, _n_size> *GetArray() { return &_array; };
    inline std::stack<_Type> *GetStack() { return &_stack; };
    inline int Count() { return count; };

    _Type &operator[](int index)
    {
        return _array[index];
    };

    inline bool IsFull() { return _stack.empty(); };

    int Push(_Type element)
    {
        int t = _stack.top();
        _array[t] = element;
        _indexes[t] = true;
        _stack.pop();
        count++;
        return t;
    };

    void Remove(int index)
    {
        if(_indexes[index])
        {
            _stack.push(index);
            _indexes[index] = false;
            _array[index] = _Type();
            count--;
        }
    };
};


#endif /* E0920D85_4549_4E4B_B5EB_0AF38A5B399A */
