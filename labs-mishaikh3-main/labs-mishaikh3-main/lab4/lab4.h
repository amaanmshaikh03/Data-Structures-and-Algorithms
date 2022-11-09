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
public:
	DList() {
		front_ = nullptr;
		back_ = nullptr;
	}
	void push_front(const T& data);
	~DList();

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
			if (this->curr_) {
				this->curr_ = this->curr_->next_;
			}
			return *this;
		}
		const_iterator operator++(int) {
			const_iterator a = *this;
			if (this->curr_) {
				this->curr_ = this->curr_->next_;
			}
			return a;
		}
		const_iterator operator--() {
			if (this->curr_) {
				this->curr_ = this->curr_->prev_;
			}
			else {
				this->curr_ = this->list_->back_;
			}
			return *this;
		}
		const_iterator operator--(int) {
			const_iterator a = *this;
			if (this->curr_) {
				this->curr_ = this->curr_->prev_;
			}
			else {
				this->curr_ = this->list_->back_;
			}
			return a;
		}
		bool operator==(const_iterator rhs) {
			return (list_ == rhs.list_ && curr_ == rhs.curr_);
		}
		bool operator!=(const_iterator rhs) {
			return (list_ != rhs.list_ || curr_ != rhs.curr_);
		}
		const T& operator*()const {
			return this->curr_->data_;
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
				this->curr_ = this->list_->back_;
			}
			return *this;
		}
		iterator operator--(int) {
			iterator a = *this;
			if (this->curr_) {
				this->curr_ = this->curr_->prev_;
			}
			else {
				this->curr_ = this->list_->back_;
			}
			return a;
		}
		T& operator*() {
			return this->curr_->data_;
		}
		const T& operator*()const {
			return this->curr_->data_;
		}
	};
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
};

template <typename T>
void DList<T>::push_front(const T& data) {
	Node* n = new Node(data, front_);
	if (front_) {
		front_->prev_ = n;
	}
	else {
		back_ = n;
	}
	front_ = n;
}


template <typename T>
DList<T>::~DList() {
	delete front_;
	delete back_;
}

template <typename T>
class Sentinel {
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
public:
	Sentinel() {
		front_ = new Node();
		back_ = new Node();
		front_->next_ = back_;
		back_->prev_ = front_;
	}
	void push_front(const T& data);
	~Sentinel();

	class const_iterator {
		friend class Sentinel;
		Node* curr_;
		const_iterator(Node* n) {
			curr_ = n;
		}
	public:
		const_iterator() {
			curr_ = nullptr;
		}
		const_iterator operator++() {
			curr_ = curr_->next_;
			return *this;
		}
		const_iterator operator++(int) {
			const_iterator a = *this;
			curr_ = curr_->next_;
			return a;
		}
		const_iterator operator--() {
			curr_ = curr_->prev_;
			return *this;
		}
		const_iterator operator--(int) {
			const_iterator a = *this;
			curr_ = curr_->prev_;
			return a;
		}
		bool operator==(const_iterator rhs) {
			return curr_ == rhs.curr_;
		}

		bool operator!=(const_iterator rhs) {
			return curr_ != rhs.curr_;
		}
		const T& operator*() const {
			return curr_->data_;
		}
	};
	class iterator :public const_iterator {
		friend class Sentinel;
		iterator(Node* n) :const_iterator(n) {
		}
	public:
		iterator() :const_iterator() {}
		iterator operator++() {
			this->curr_ = this->curr_->next_;
			return *this;
		}
		iterator operator++(int) {
			iterator a = *this;
			this->curr_ = this->curr_->next_;
			return a;
		}
		iterator operator--() {
			this->curr_ = this->curr_->prev_;
			return *this;
		}
		iterator operator--(int) {
			iterator a = *this;
			this->curr_ = this->curr_->prev_;
			return a;
		}
		T& operator*() {
			return this->curr_->data_;
		}
		const T& operator*()const {
			return this->curr_->data_;
		}
	};
	const_iterator cbegin() const {
		return const_iterator(front_->next_);
	}

	iterator begin() {
		return iterator(front_->next_);
	}

	const_iterator cend() const {
		return const_iterator(back_);
	}

	iterator end() {
		return iterator(back_);
	}
};
template <typename T>
void Sentinel<T>::push_front(const T& data) {
	Node* n = new Node(data, front_->next_, front_);
	front_->next_->prev_ = n;
	front_->next_ = n;
}


template <typename T>
Sentinel<T>::~Sentinel() {
	delete front_;
	delete back_;
}
