#include <iostream>
#include <list>
#include <cstring>
#include <algorithm>
#include <memory>

using namespace std;

class Buffer
{
public:
  typedef size_t size_type;
  typedef unsigned char value_type;
  typedef const unsigned char const_value_type;
public:
  Buffer(const char * buf) 
  {
    size_type size = strlen(buf);
    if (size)
    {
      begin_ = new value_type[size];
      end_ = begin_ + size;
      copy_n((value_type *)buf, size, begin_);
    }
  }

  explicit Buffer (size_type size = 0)
    :begin_ (size ? new value_type[size] : nullptr)
    ,end_ (begin_ + size)
  {
  }

  Buffer(const Buffer & rhs)
  {
    size_type size = rhs.size();
    if (size)
    {
      begin_ = new value_type[size];
      end_ = begin_ + size;
      copy(rhs.begin_, rhs.end_, this->begin_);
    }
  }


  Buffer(Buffer && rhs)
    :Buffer(size_t(0))
  {
    swap(*this, rhs); 
  }


  Buffer & operator=(Buffer && rhs)
  {
    if (this != & rhs)
    {
      // non throwing, so exception safe
      delete [] begin_;
      begin_ = rhs.begin_;
      end_ = rhs.end_;
      rhs.begin_ = rhs.end_ = nullptr;
    }
    return *this;
  }

  Buffer & operator=(Buffer rhs)
  {
    swap(*this, rhs);
    return *this;
  }

  void resize(size_type new_size)
  {
    size_type old_size = size();
    if (new_size == old_size) return;
    value_type * new_begin = new value_type[new_size];
    if (new_size > old_size)
    {
      copy(begin_, end_, new_begin);
    } 
    else if (new_size < old_size)
    {
      copy_n(begin_, new_size, new_begin);
    }
    delete [] begin_;
    begin_ = new_begin;
    end_ = begin_ + new_size;
  }

  size_type size() const
  {
    return (size_type)(end_ - begin_);
  }

  friend void swap (Buffer & lhs, Buffer & rhs)
  {
    using std::swap;
    swap(lhs.begin_, rhs.begin_);
    swap(lhs.end_, rhs.end_);
  }

  value_type & operator[](size_type pos)
  {
    return begin_[pos];
  }

  const_value_type & operator[](size_type pos) const
  {
    return begin_[pos];
  }

  value_type * begin()
  {
    return begin_;
  }

  value_type * end()
  {
    return end_;
  }


  const_value_type * begin() const
  {
    return begin_;
  }

  const_value_type * end() const
  {
    return end_;
  }

  virtual ~Buffer() {
    delete [] begin_;
    begin_ = end_ = nullptr;
  }


  friend ostream & operator<<(ostream & os, const Buffer & rhs);

private:
  value_type * begin_ = nullptr;
  value_type * end_ = nullptr;
};


ostream & operator<<(ostream & os, const Buffer & rhs)
{
  for (auto i : rhs)
  {
    os << i;
  }
  return os;
}


int main(int argc, char * argv[])
{
  Buffer bf1("hello world");
  Buffer bf2 = bf1;
  bf1.resize(5);
  cout << bf1 << endl;
  cout << bf2 << endl;

  list<Buffer> buf_list;
  buf_list.push_back(Buffer("bf1"));
  buf_list.push_back(Buffer("bf2"));
  for (auto i : buf_list)
  {
    std::cout << i << std::endl;
  }
  Buffer bf3;

}
