/*************************************************************/
/*                                                           */
/*  Starter file for a2                                      */
/*                                                           */
/*  Author1: Marc Nicolas Oliva                              */
/*      -  Chaining Table                                    */
/*  Author2 Name: Mohammedamaan Shaikh                       */
/*      - LPTable                                            */
/*                                                           */
/*************************************************************/
#include <string>
#include <utility>
#include <functional>
#include "mylist.h"

template <class TYPE>
class Table {
public:
    Table() {}
    virtual bool update(const std::string& key, const TYPE& value) = 0;
    virtual bool remove(const std::string& key) = 0;
    virtual bool find(const std::string& key, TYPE& value) = 0;
    virtual int numRecords() const = 0;
    virtual bool isEmpty() const = 0;
    virtual int capacity() const = 0;
    virtual ~Table() {}
};

template <class TYPE>
class SimpleTable :public Table<TYPE> {

    struct Record {
        TYPE data_;
        std::string key_;
        Record(const std::string& key, const TYPE& data) {
            key_ = key;
            data_ = data;
        }
    };

    Record** records_;   //the table
    int capacity_;       //capacity of the array


public:
    SimpleTable(int capacity);
    SimpleTable(const SimpleTable& rhs);
    SimpleTable(SimpleTable&& rhs);
    virtual bool update(const std::string& key, const TYPE& value);
    virtual bool remove(const std::string& key);
    virtual bool find(const std::string& key, TYPE& value);
    virtual const SimpleTable& operator=(const SimpleTable& rhs);
    virtual const SimpleTable& operator=(SimpleTable&& rhs);
    virtual ~SimpleTable();
    virtual bool isEmpty() const { return numRecords() == 0; }
    virtual int numRecords() const;
    virtual int capacity() const { return capacity_; }

};

template <class TYPE>
int SimpleTable<TYPE>::numRecords() const {
    int rc = 0;
    for (int i = 0; records_[i] != nullptr; i++) {
        rc++;
    }
    return rc;
}

template <class TYPE>
SimpleTable<TYPE>::SimpleTable(int capacity) : Table<TYPE>() {
    records_ = new Record * [capacity + 1];
    capacity_ = capacity;
    for (int i = 0; i < capacity_ + 1; i++) {
        records_[i] = nullptr;
    }
}

template <class TYPE>
SimpleTable<TYPE>::SimpleTable(const SimpleTable<TYPE>& rhs) {
    records_ = new Record * [rhs.capacity_ + 1];
    capacity_ = rhs.capacity_;
    for (int i = 0; i < capacity_ + 1; i++) {
        records_[i] = nullptr;
    }
    for (int i = 0; i < rhs.numRecords(); i++) {
        update(rhs.records_[i]->key_, rhs.records_[i]->data_);
    }
}
template <class TYPE>
SimpleTable<TYPE>::SimpleTable(SimpleTable<TYPE>&& rhs) {
    capacity_ = rhs.capacity_;
    records_ = rhs.records_;
    rhs.records_ = nullptr;
    rhs.capacity_ = 0;
}

template <class TYPE>
bool SimpleTable<TYPE>::update(const std::string& key, const TYPE& value) {
    int idx = -1;
    int sz = numRecords();
    bool rc = true;
    for (int i = 0; i < sz; i++) {
        if (records_[i]->key_ == key) {
            idx = i;
        }
    }
    if (idx == -1) {
        if (sz < capacity_) {
            records_[numRecords()] = new Record(key, value);
            for (int i = numRecords() - 1; i > 0 && records_[i]->key_ < records_[i - 1]->key_; i--) {
                Record* tmp = records_[i];
                records_[i] = records_[i - 1];
                records_[i - 1] = tmp;
            }
        }
        else {
            rc = false;
        }
    }
    else {
        records_[idx]->data_ = value;
    }
    return rc;
}

template <class TYPE>
bool SimpleTable<TYPE>::remove(const std::string& key) {
    int idx = -1;
    for (int i = 0; records_[i] != nullptr; i++) {
        if (records_[i]->key_ == key) {
            idx = i;
        }
    }
    if (idx != -1) {
        delete records_[idx];

        for (int i = idx; i < numRecords() - 1; i++) {
            records_[i] = records_[i + 1];
        }
        records_[this.size - 1] = nullptr;
        return true;
    }
    else {
        return false;
    }
}

template <class TYPE>
bool SimpleTable<TYPE>::find(const std::string& key, TYPE& value) {
    int idx = -1;
    for (int i = 0; i < numRecords(); i++) {
        if (records_[i]->key_ == key) {
            idx = i;
        }
    }
    if (idx == -1)
        return false;
    else {
        value = records_[idx]->data_;
        return true;
    }
}

template <class TYPE>
const SimpleTable<TYPE>& SimpleTable<TYPE>::operator=(const SimpleTable<TYPE>& rhs) {
    if (this != &rhs) {
        if (records_) {
            while (numRecords() != 0) {
                remove(records_[0]->key_);
            }
            delete[] records_;
        }
        records_ = new Record * [rhs.capacity_ + 1];
        capacity_ = rhs.capacity_;
        for (int i = 0; i < capacity_; i++) {
            records_[i] = nullptr;
        }
        for (int i = 0; i < rhs.numRecords(); i++) {
            update(rhs.records_[i]->key_, rhs.records_[i]->data_);
        }

    }
    return *this;
}
template <class TYPE>
const SimpleTable<TYPE>& SimpleTable<TYPE>::operator=(SimpleTable<TYPE>&& rhs) {
    if (records_) {
        while (numRecords() != 0) {
            remove(records_[0]->key_);
        }
        delete[] records_;
    }
    records_ = rhs.records_;
    capacity_ = rhs.capacity_;
    rhs.records_ = nullptr;
    rhs.capacity_ = 0;

    return *this;
}
template <class TYPE>
SimpleTable<TYPE>::~SimpleTable() {
    if (records_) {
        int sz = numRecords();
        for (int i = 0; i < sz; i++) {
            remove(records_[0]->key_);
        }
        delete[] records_;
    }
}

template <class TYPE>
class ChainingTable :public Table<TYPE> {
private:
    struct Record {
        TYPE data_;
        std::string key_;
        Record(const std::string& key, const TYPE& data) {
            key_ = key;
            data_ = data;
        }
	    Record(const std::string& key) {
            key_ = key;
            data_ = {};
        }
        Record() {
            key_ = "";
            data_ = {};
        }
        bool operator==(const Record& rhs) {
            if (this == nullptr) return false;
            return this->key_ == rhs.key_;
        }
        bool operator!=(const Record& rhs) {
            if (this == nullptr) return false;
            return this->key_ != rhs.key_;
        }
        bool operator<(const Record& rhs) {
            if (this == nullptr) return false;
            return this->key_ < rhs.key_;
        }
        void operator=(const Record& rhs) {
            this->data_ = rhs.data_;
            this->key_ = rhs.key_;
        }
    };
    int capacity_, numRec_;
    DList<Record>** records_;
    std::hash<std::string> hashFunction;
public:
    ChainingTable(int maxExpected);
    ChainingTable(const ChainingTable& other);
    ChainingTable(ChainingTable&& other);
    double loadFactor() const;
    virtual bool update(const std::string& key, const TYPE& value);
    virtual bool remove(const std::string& key);
    virtual bool find(const std::string& key, TYPE& value);
    virtual const ChainingTable& operator=(const ChainingTable& other);
    virtual const ChainingTable& operator=(ChainingTable&& other);
    virtual ~ChainingTable();
    virtual bool isEmpty() const;
    virtual int numRecords() const;
    virtual int capacity() const;
};

template <class TYPE>
ChainingTable<TYPE>::ChainingTable(int capacity) : Table<TYPE>() {
    records_ = new DList<Record>*[capacity + 1];
    capacity_ = capacity;
    numRec_ = 0;
    for (int i = 0; i < capacity_ + 1; i++) {
        records_[i] = new DList<Record>;
    }
}

template <class TYPE>
ChainingTable<TYPE>::ChainingTable(const ChainingTable<TYPE>& other) {
    records_ = nullptr;
    *this = other;
}
template <class TYPE>
ChainingTable<TYPE>::ChainingTable(ChainingTable<TYPE>&& other) {
    records_ = nullptr;
    *this = std::move(other);
}
template <class TYPE>
bool ChainingTable<TYPE>::update(const std::string& key, const TYPE& value) {
    size_t hash = hashFunction(key);
    size_t idx = hash % capacity_;
    Record rhs(key, value);
    auto found = records_[idx]->search(rhs);

    if (*found == rhs) {
        records_[idx]->insert(found, Record(key, value));
        records_[idx]->erase(found++);
        return true;
    }
    else {
        records_[idx]->insert(records_[idx]->begin(), Record(key, value));
        numRec_++;
        return true;
    }
    return false;
}

template <class TYPE>
bool ChainingTable<TYPE>::remove(const std::string& key) {
    size_t hash = hashFunction(key);
    size_t idx = hash % capacity_;
    Record rhs(key);

    auto found = records_[idx]->search(key);

    if (*found == rhs) {
        records_[idx]->erase(found);
        numRec_--;
        return true;
    }

    return false;
}

template <class TYPE>
bool ChainingTable<TYPE>::find(const std::string& key, TYPE& value) {
    size_t hash = hashFunction(key);
    size_t idx = hash % capacity_;
    Record rhs(key);
    auto found = records_[idx]->search(rhs);
    
    if (*found == rhs) {
        Record result = *found;
        value = result.data_;
        return true;
    }

    return false;
}

template <class TYPE>
const ChainingTable<TYPE>& ChainingTable<TYPE>::operator=(const ChainingTable<TYPE>& other) {
    if (this != &other) {
        this->capacity_ = other.capacity_;
        this->numRec_ = other.numRec_;

        delete[] records_;
        records_ = new DList<Record>*[other.capacity_+1];
        for (int i = 0; i < capacity_; i++) {
            auto curr = other.records_[i]->begin();
            
            records_[i] = new DList<Record>();
            auto currNew = records_[i]->begin();

            while (curr != other.records_[i]->end()) {    
                Record curRec = *curr;
                records_[i]->insert(currNew, Record(curRec.key_, curRec.data_));
                currNew++;
                curr++;
            }
        }
    }
    return *this;
}

template <class TYPE>
const ChainingTable<TYPE>& ChainingTable<TYPE>::operator=(ChainingTable<TYPE>&& other) {
    if (this != &other) {
        capacity_ = other.capacity();
        other.capacity_ = 0;

        this->numRec_ = other.numRec_;
        other.numRec_ = 0;
        
        delete[] records_;
        records_ = other.records_;
        other.records_ = nullptr;

    }
    return *this;
}

template <class TYPE>
ChainingTable<TYPE>::~ChainingTable() {

    delete[] records_;
}

template <class TYPE>
bool ChainingTable<TYPE>::isEmpty() const {
    return !(this->numRecords());
}

template <class TYPE>
int ChainingTable<TYPE>::numRecords() const {
    return numRec_;
}
template <class TYPE>
int ChainingTable<TYPE>::capacity() const {
    return this->capacity_;
}

template <class TYPE>
double ChainingTable<TYPE>::loadFactor() const {
    return this->numRecords() / this->capacity();
}

template <class TYPE>
class LPTable :public Table<TYPE> {
    struct Record {
        TYPE data_;
        std::string key_;
        std::string stat;
        Record() {
            data_ = {};
            key_ = "";
            stat = "empty";
        }
        Record(const std::string& key, const TYPE& data, const std::string status) {
            key_ = key;
            data_ = data;
            stat = status;
        }
    };
    std::hash<std::string> hashFunction;
    Record* records;
    int cap;
    int size;
public:
    LPTable(int maxExpected);
    LPTable(const LPTable& other);
    LPTable(LPTable&& other);
    double loadFactor() const;
    virtual bool update(const std::string& key, const TYPE& value);
    virtual bool remove(const std::string& key);
    virtual bool find(const std::string& key, TYPE& value);
    virtual const LPTable& operator=(const LPTable& other);
    virtual const LPTable& operator=(LPTable&& other);
    virtual ~LPTable();
    virtual bool isEmpty() const;
    virtual int numRecords() const;
    virtual int capacity() const;

};
template <class TYPE>
LPTable<TYPE>::LPTable(int capacity) : Table<TYPE>() {
    records = new Record[capacity];
    cap = capacity;
    size = 0;
}

template <class TYPE>
LPTable<TYPE>::LPTable(const LPTable<TYPE>& other) {
    records = nullptr;
    *this = other;
}
template <class TYPE>
LPTable<TYPE>::LPTable(LPTable<TYPE>&& other) {
    records = nullptr;
    *this = std::move(other);

}
template <class TYPE>
bool LPTable<TYPE>::update(const std::string& key, const TYPE& value) {
    bool ok = false;
    size_t index = hashFunction(key) % cap;
    size_t i = index;
    do {
        if (records[index].stat == "empty") {
            break;
        }
        else if (records[index].key_.compare(key) == 0) {
            records[index].data_ = value;
            return true;
        }
        index = (index + 1) % cap;
    } while (index != i);
    if (ok == false && size < cap - 1) {
        records[index] = Record(key, value, "full");
        size++;
        return true;
    }
    return false;
}

template <class TYPE>
bool LPTable<TYPE>::remove(const std::string& key) {
    size_t index = hashFunction(key) % cap;
    size_t i = index;
    do {
        if (records[index].stat == "empty") {
            return false;
        }
        else if (records[index].stat == "full" && records[index].key_.compare(key) == 0) {
            records[index].stat = "deleted";
            size--;
            return true;
        }
        index = (index + 1) % cap;
    } while (i != index);
    return false;
}

template <class TYPE>
bool LPTable<TYPE>::find(const std::string& key, TYPE& value) {
    size_t index = hashFunction(key) % cap;
    size_t i = index;
    do {
        if (records[index].stat == "empty") {
            return false;
        }
        else if (records[index].stat == "full" && records[index].key_.compare(key) == 0) {
            value = records[index].data_;
            return true;
        }
        index = (index + 1) % cap;
    } while (i != index);
    return false;
}

template <class TYPE>
const LPTable<TYPE>& LPTable<TYPE>::operator=(const LPTable<TYPE>& other) {
    if (this != &other) {
        delete[] records;
        cap = other.cap;
        size = other.size;
        records = new Record[cap];
        for (int i = 0; i < cap; i++) {
            records[i] = other.records[i];
        }
    }
    return *this;
}
template <class TYPE>
const LPTable<TYPE>& LPTable<TYPE>::operator=(LPTable<TYPE>&& other) {
    if (this != &other) {
        records = other.records;
        cap = other.cap;
        size = other.size;
        other.records = nullptr;
        other.cap = other.size = 0;
    }
    return *this;
}

template <class TYPE>
LPTable<TYPE>::~LPTable() {
    delete[] records;
}

template <class TYPE>
bool LPTable<TYPE>::isEmpty() const {
    return size == 0;
}

template <class TYPE>
int LPTable<TYPE>::numRecords() const {
    return size;
}
template <class TYPE>
int LPTable<TYPE>::capacity() const {
    return cap;
}
template <class TYPE>
double LPTable<TYPE>::loadFactor() const {
    return size / cap;
}
