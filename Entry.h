#ifndef ENTRY_h
#define  ENTRY_h
  template <typename K, typename V>
  class Entry {						// a (key, value) pair
  public:						// public functions
    Entry(const K& k = K(), const V& v = V())		// constructor
      : _key(k), _value(v), next(nullptr),prev(nullptr) { }	
    const K& key() const { return _key; }		// get key
    const V& value() const { return _value; }		// get value
    void setKey(const K& k) { _key = k; }		// set key
    void setValue(const V& v) { _value = v; }		// set value
    Entry * getNext() const
    {
        return next;
    }

    void setNext(Entry *next) 
    {
        Entry::next = next;
    }
    Entry* getPrev() const
    {
        return prev;
    }
    void setPrev(Entry *prev)
    {
        Entry::prev = prev;
    }
  private:						// private data
    K _key;						// key
    V _value;						// value
    Entry *next;//used for chaining
    Entry* prev; //not really traditional but makes it easier
  };

#endif
