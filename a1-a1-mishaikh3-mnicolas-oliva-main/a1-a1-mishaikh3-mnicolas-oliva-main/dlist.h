/********************************************************************/
/*                                                                  */
/*  A1 Part 2: DList starter file                                   */
/*                                                                  */
/*  Author1 Name: Marc Nicolas Oliva                                */
/*      - Constructor, Destructor Copy and Move operations          */
/*      - Insert and Search                                         */
/*      - Sorting                                                   */
/*  Author2 Name: Mohammedamaan Shaikh                              */
/*      - const_iterator and iterator                               */
/*      - Erase, empty and size                                     */
/*      - begin(), end(), cbegin(), cend()                          */
/*                                                                  */
/********************************************************************/
#include <math.h>
#include <iostream>
template <typename T>
class DList {
    struct Node {
        T data_;
        Node* next_;
        Node* prev_;
        Node(const T& data = T{}, Node* next = nullptr, Node* prev = nullptr) {
            data_ = data;
            next_ = next;
            prev_ = prev;
        }
    };
    Node* front_;
    Node* back_;
    const int THRESHOLD = 16;
public:
    class const_iterator {
        friend class DList;
        Node* curr_;
        const DList* list_;
        const_iterator(Node* curr, const DList* temp) {
            curr_ = curr;
            list_ = temp;
        }
    public:
        const_iterator() {
            list_ = nullptr;
            curr_ = nullptr;
        }
        const_iterator operator++() {
            if (curr_) {
                curr_ = curr_->next_;
            }
            return *this;
        }
        const_iterator operator++(int) {
            const_iterator a = *this;
            if (curr_) {
                curr_ = curr_->next_;
            }
            return a;
        }
        const_iterator operator--() {
            if (curr_) {
                curr_ = curr_->prev_;
            }
            else {
                if (list_->back_) {
                    curr_ = list_->back_;
                }
            }
            return *this;
        }
        const_iterator operator--(int) {
            const_iterator a = *this;
            if (curr_) {
                curr_ = curr_->prev_;
            }
            else {
                if (list_->back_) {
                    curr_ = list_->back_;
                }
            }
            return a;
        }
        T& operator[](int x) {
            x = (x < 0) ? 0 : x;
            for (int i = 0; i < x; i++) {
                if (curr_)
                    this->operator++();
            }
            return *this->curr_->data_;
        }
        bool operator==(const_iterator rhs) {
            return (list_ == rhs.list_ && curr_ == rhs.curr_);
        }
        bool operator!=(const_iterator rhs) {
            return (list_ != rhs.list_ || curr_ != rhs.curr_);
        }
        const T& operator*()const {
            return curr_->data_;
        }
    };
    class iterator :public const_iterator {
        friend class DList;
        iterator(Node* curr, const DList* temp) :const_iterator(curr, temp) {}
    public:
        iterator() :const_iterator() {}
        iterator operator++() {
            if (this->curr_) {
                this->curr_ = this->curr_->next_;
            }
            return *this;
        }
        iterator operator++(int) {
            iterator a = *this;
            if (this->curr_) {
                this->curr_ = this->curr_->next_;
            }
            return a;
        }
        iterator operator--() {
            if (this->curr_) {
                this->curr_ = this->curr_->prev_;
            }
            else {
                if (this->list_->back_) {
                    this->curr_ = this->list_->back_;
                }
            }
            return *this;
        }
        iterator operator--(int) {
            iterator a = *this;
            if (this->curr_) {
                this->curr_ = this->curr_->prev_;
            }
            else {
                if (this->list_->back_) {
                    this->curr_ = this->list_->back_;
                }
            }
            return a;
        }
        T& operator*() {
            return this->curr_->data_;
        }
        const T& operator*()const {
            return this->curr_->data_;
        }
        bool operator==(iterator rhs) {
            return rhs.curr_ == this->curr_;
        }
        bool operator!=(iterator rhs) {
            return rhs.curr_ != this->curr_;
        }
    };
    DList();
    ~DList();
    DList(const DList& rhs);
    DList& operator=(const DList& rhs);
    DList(DList&& rhs);
    DList& operator=(DList&& rhs);
    iterator insert(iterator it, const T& data);
    iterator search(const T& data);
    iterator erase(iterator it);
    void sort(iterator first, iterator last);
    bool empty() const;
    int size() const;

    const_iterator cbegin() const {
        return const_iterator(front_, this);
    }
    iterator begin() {
        return iterator(front_, this);
    }
    const_iterator cend() const {
        return const_iterator(nullptr, this);
    }
    iterator end() {
        return iterator(nullptr, this);
    }

protected:
    void insertionSort(iterator, iterator, int);
};

template <typename T>
DList<T>::DList() {
    front_ = nullptr;
    back_ = nullptr;
}

template <typename T>
DList<T>::~DList() {
    Node* a = nullptr;
    while (front_) {
        a = front_;
        front_ = front_->next_;
        delete a;
    }
}
template <typename T>
DList<T>::DList(const DList& rhs) {
    front_ = nullptr;
    back_ = nullptr;
    Node* a = rhs.front_;
    while (a) {
        insert(end(), a->data_);
        a = a->next_;
    }
}
template <typename T>
DList<T>& DList<T>::operator=(const DList& rhs) {
    if (this != &rhs) {
        Node* a = nullptr;
        while (front_) {
            a = front_;
            front_ = front_->next_;
            delete a;
        }
        front_ = nullptr;
        back_ = nullptr;
        for (Node* n = rhs.front_; n != nullptr; n = n->next_) {
            insert(end(), n->data_);
        }
    }
    return *this;
}
template <typename T>
DList<T>::DList(DList&& rhs) {
    front_ = rhs.front_;
    back_ = rhs.back_;
    rhs.front_ = nullptr;
    rhs.back_ = nullptr;
}

template <typename T>
DList<T>& DList<T>::operator=(DList&& rhs) {
    if (this != &rhs) {
        Node* a = nullptr;
        while (!empty()) {
            a = front_;
            front_ = front_->next_;
            delete a;
        }
        front_ = rhs.front_;
        back_ = rhs.back_;
        rhs.front_ = nullptr;
        rhs.back_ = nullptr;
    }
    return *this;
}


template <typename T>
typename DList<T>::iterator DList<T>::insert(iterator it, const T& data) {
    Node* a = new Node(data);
    if (it.curr_ == nullptr) {
        if (front_ == nullptr) {
            front_ = a;
            back_ = a;
        }
        else {
            a->prev_ = back_;
            back_->next_ = a;
            back_ = a;
        }
    }
    else {
        if (it.curr_ == front_) {
            a->next_ = front_;
            front_->prev_ = a;
            front_ = a;
        }
        else {
            a->next_ = it.curr_;
            a->prev_ = it.curr_->prev_;
            it.curr_->prev_->next_ = a;
            it.curr_->prev_ = a;
        }
    }
    return iterator(a, this);
}

template <typename T>
typename DList<T>::iterator DList<T>::search(const T& data) {
    for (auto i = begin(); i != end(); i++) {
        if (*i == data) {
            return i;
        }
    }
    return end();
}


template <typename T>
typename DList<T>::iterator DList<T>::erase(iterator it) {
    if (it.curr_ == nullptr) {
        return end();
    }
    else {
        if (it.curr_ == front_) {
            front_ = front_->next_;
            front_->prev_ = nullptr;
        }
        else {
            it.curr_->prev_->next_ = it.curr_->next_;
            if (it.curr_ == back_) {
                back_ = it.curr_->prev_;
            }
            else {
                it.curr_->next_->prev_ = it.curr_->prev_;
            }
        }
        Node* a = it.curr_;
        it.curr_ = it.curr_->next_;
        delete a;
        return it;
    }
}

template <typename T>
void DList<T>::sort(iterator first, iterator last) {
    insertionSort(first, last, this->size());
}
template <typename T>
bool DList<T>::empty() const {
    return front_ == nullptr;
}
template <typename T>
int DList<T>::size() const {
    int retval = 0;
    for (auto i = cbegin(); i != cend(); i++) {
        retval++;
    }
    return retval;
}
template<typename T>
inline void DList<T>::insertionSort(iterator first, iterator last, int colSize) {
    Node* curr;
    iterator it = first;
    it++;
    iterator it2;

    Node* smNumNext = nullptr;
    Node* smallNum = nullptr;
    Node* smNumPrev = nullptr;

    Node* hgNumNext = nullptr;
    Node* highNum = nullptr;
    Node* hgNumPrev = nullptr;
    //If the collection only has two values a simple swap is required
    if (colSize == 2 && it.curr_->prev_->data_.count_ > it.curr_->data_.count_) {
        highNum = it.curr_->prev_;
        smallNum = it.curr_;

        front_ = smallNum;
        highNum->next_ = smallNum->next_;
        smallNum->prev_ = highNum->prev_;
        highNum->prev_ = smallNum;
        smallNum->next_ = highNum;
        back_ = highNum;
    }
    if (colSize > 2 && last.curr_ == nullptr && first.curr_->prev_ == nullptr) {
        //it is the next number after first so we can compare with previous
        for (it = it++; it != last; it++) {
            curr = it.curr_;
            for (it2 = it; it2.curr_->prev_ != nullptr && it2.curr_->prev_->data_.count_ > curr->data_.count_;) {
                //This operation is performed here because if the previous Node data is smaller we don't want
                //to keep going backwards on the collection
                it2--;
                smallNum = it2.curr_->next_;
                highNum = it2.curr_;
                if (highNum->data_.count_ > smallNum->data_.count_) {
                    smNumPrev = it.curr_->prev_;
                    smNumNext = smallNum->next_;

                    hgNumNext = it2.curr_->next_;
                    hgNumPrev = it2.curr_->prev_;

                    highNum->next_ = smNumNext;
                    if (smNumNext != nullptr)
                        smNumNext->prev_ = highNum;
                    else
                        back_ = highNum;
                }
            }
            //At this point, we have to insert the curr element that was stripped from the collection before.
            //It is inserted in between the smaller and the higher closer numbers (ex: 22 -> 24 and curr = 23,
            // 22 -> 23 -> 24)
            if (it2.curr_ != curr) {
                curr->prev_ = it2.curr_->prev_;
                curr->next_ = it2.curr_;
                it2.curr_->prev_ = curr;
                if (curr->prev_ == nullptr)
                    front_ = curr;
                else
                    curr->prev_->next_ = curr;
            }
        }
    }
    else if (first.curr_->prev_ != nullptr) {
        //if (last.curr_ != nullptr) last++;
        first--;
        //it is the next number after first so we can compare with previous
        for (it = first; it != last; it++) {
            curr = it.curr_;
            for (it2 = it; it2.curr_->prev_ != first.curr_
                && it.curr_->prev_ != nullptr
                && it2.curr_->prev_->data_.count_ > curr->data_.count_;) {
                //This operation is performed here because if the previous Node data is smaller we don't want
                //to keep going backwards on the collection
                it2--;
                smallNum = it2.curr_->next_;
                highNum = it2.curr_;
                if (highNum->data_.count_ > smallNum->data_.count_) {
                    smNumPrev = it.curr_->prev_;
                    smNumNext = smallNum->next_;

                    hgNumNext = it2.curr_->next_;
                    hgNumPrev = it2.curr_->prev_;

                    highNum->next_ = smNumNext;
                    if (smNumNext != nullptr)
                        smNumNext->prev_ = highNum;
                    else
                        back_ = highNum;
                }
            }
            //At this point, we have to insert the curr element that was stripped from the collection before.
            //It is inserted in between the smaller and the higher closer numbers (ex: 22 -> 24 and curr = 23,
            // 22 -> 23 -> 24)
            if (it2.curr_ != curr) {
                curr->prev_ = it2.curr_->prev_;
                curr->next_ = it2.curr_;
                it2.curr_->prev_ = curr;
                if (curr->prev_ == nullptr)
                    front_ = curr;
                else
                    curr->prev_->next_ = curr;
            }
        }
    }
    else {
        //it is the next number after first so we can compare with previous
        for (it = first; it != last; it++) {
            curr = it.curr_;
            for (it2 = it; it.curr_ != first.curr_
                && it2.curr_->prev_ != nullptr
                && it2.curr_->prev_->data_.count_ > curr->data_.count_;) {
                //This operation is performed here because if the previous Node data is smaller we don't want
                //to keep going backwards on the collection
                it2--;
                smallNum = it2.curr_->next_;
                highNum = it2.curr_;
                if (highNum->data_.count_ > smallNum->data_.count_) {
                    smNumPrev = it.curr_->prev_;
                    smNumNext = smallNum->next_;

                    hgNumNext = it2.curr_->next_;
                    hgNumPrev = it2.curr_->prev_;

                    highNum->next_ = smNumNext;
                    if (smNumNext != nullptr)
                        smNumNext->prev_ = highNum;
                    else
                        back_ = highNum;
                }
            }
            //At this point, we have to insert the curr element that was stripped from the collection before.
            //It is inserted in between the smaller and the higher closer numbers (ex: 22 -> 24 and curr = 23,
            // 22 -> 23 -> 24)
            if (it2.curr_ != curr) {
                curr->prev_ = it2.curr_->prev_;
                curr->next_ = it2.curr_;
                it2.curr_->prev_ = curr;
                if (curr->prev_ == nullptr)
                    front_ = curr;
                else
                    curr->prev_->next_ = curr;
            }
        }
    }
}