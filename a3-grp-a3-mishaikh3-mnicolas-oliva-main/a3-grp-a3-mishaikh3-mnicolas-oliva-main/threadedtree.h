#include <iostream>
#include <queue>
using namespace std;
template <class T>
class ThreadedTree {
	struct Node {
		T data_;
		Node* left_;
		Node* right_;
		bool leftisThread;
		bool rightisThread;
		Node(const T& data = T{}, Node* left = nullptr, Node* right = nullptr) {
			data_ = data;
			left_ = left;
			right_ = right;
			leftisThread = false;
			rightisThread = false;
		}
	};
	Node* root_;
	int size_;
public:
	class const_iterator {
	protected:
		Node* tnode;
		const ThreadedTree* ttree;
		const_iterator(Node* n, const ThreadedTree* t) {
			tnode = n;
			ttree = t;
		}
	public:
		const_iterator() {
			tnode = nullptr;
			ttree = nullptr;
		}
		const_iterator operator++(int) {
			const_iterator cit = *this;
			if (this->tnode->rightisThread) {
				this->tnode = this->tnode->right_;
			}
			else {
				if (this->tnode->right_ != nullptr) {
					this->tnode = this->tnode->right_;
					while (this->tnode->left_ && !this->tnode->leftisThread) {
						this->tnode = this->tnode->left_;
					}
				}
			}
			return cit;
		}
		const_iterator operator--(int) {
			const_iterator cit = *this;
			if (!this->tnode) {
				this->tnode = this->ttree->root_;
				while (this->tnode->right_) {
					this->tnode = this->tnode->right_;
				}
			}
			else {
				if (this->tnode->leftisThread) {
					this->tnode = this->tnode->left_;
				}
				else {
					if (this->tnode->left_ != nullptr) {
						this->tnode = this->tnode->left_;
						while (this->tnode->right_ && this->tnode->rightisThread == false) {
							this->tnode = this->tnode->right_;
						}
					}
				}
			}
			return cit;
		}
		const_iterator operator++() {
			if (this->tnode->rightisThread) {
				this->tnode = this->tnode->right_;
			}
			else {
				if (this->tnode->right_ != nullptr) {
					this->tnode = this->tnode->right_;
					while (this->tnode->left_ && !this->tnode->leftisThread) {
						this->tnode = this->tnode->left_;
					}
				}
			}
			return *this;
		}
		const_iterator operator--() {
			if (this->tnode) {
				if (this->tnode->leftisThread) {
					this->tnode = this->tnode->left_;
				}
				else {
					if (this->tnode->left_ != nullptr) {
						this->tnode = this->tnode->left_;
						while (this->tnode->right_ && this->tnode->rightisThread == false) {
							this->tnode = this->tnode->right_;
						}
					}
				}
			}
			else {
				this->tnode = this->ttree->root_;
				while (this->tnode->right_) {
					this->tnode = this->tnode->right_;
				}
			}
			return *this;
		}
		const T& operator*() const {
			return tnode->data_;
		}
		bool operator==(const const_iterator& rhs) const {
			return tnode == rhs.tnode;
		}
		bool operator!=(const const_iterator& rhs) const {
			return tnode != rhs.tnode;
		}
		friend class ThreadedTree;
	};
	class iterator :public const_iterator {
		iterator(Node* n, ThreadedTree* t) :const_iterator(n, t) { }
	public:
		iterator() :const_iterator() {
		}
		const T& operator*() const {
			return this->tnode->data_;
		}
		T& operator*() {
			return this->tnode->data_;
		}
		iterator operator++(int) {
			iterator it = *this;
			if (this->tnode->rightisThread) {
				this->tnode = this->tnode->right_;
			}
			else {
				if (this->tnode->right_ != nullptr) {
					this->tnode = this->tnode->right_;
					while (this->tnode->left_ && this->tnode->leftisThread == false) {
						this->tnode = this->tnode->left_;
					}
				}
			}
			return it;
		}
		iterator operator--(int) {
			iterator it = *this;
			if (this->tnode) {
				if (this->tnode->leftisThread) {
					this->tnode = this->tnode->left_;
					}
				else {
					if (this->tnode->left_ != nullptr) {
						this->tnode = this->tnode->left_;
						while (this->tnode->right_ && this->tnode->rightisThread == false) {
							this->tnode = this->tnode->right_;
						}
					}
				}
			}
			else {
				this->tnode = this->ttree->root_;
				while (this->tnode->right_) {
					this->tnode = this->tnode->right_;
				}
			}
			return it;

		}
		iterator operator++() {
			if (this->tnode->rightisThread) {
				this->tnode = this->tnode->right_;
				}
			else {
				if (this->tnode->right_ != nullptr) {
					this->tnode = this->tnode->right_;
					while (this->tnode->left_ && this->tnode->leftisThread == false) {
						this->tnode = this->tnode->left_;
					}
				}
			}
			return *this;
		}
		iterator operator--() {
			if (this->tnode) {
				if (this->tnode->leftisThread) {
					this->tnode = this->tnode->left_;
				}
				else {
					if (this->tnode->left_ != nullptr) {
						this->tnode = this->tnode->left_;
						while (this->tnode->right_ && this->tnode->rightisThread == false) {
							this->tnode = this->tnode->right_;
						}
					}
				}
			}
			else {
				this->tnode = this->ttree->root_;
				while (this->tnode->right_) {
					this->tnode = this->tnode->right_;
				}
			}
			return *this;
		}

		friend class ThreadedTree;
	};
	ThreadedTree() {
		root_ = nullptr;
		size_ = 0;
	}
	void insert(const T& data) {
		if (root_ != nullptr) {
			bool inserted = false;
			Node* temp = root_;
			bool small = true;
			bool large = true;
			Node* nsmall = root_;
			Node* nlarge = root_;
			while (!inserted) {
				if (data < temp->data_) {
					large = false;
					if (temp->data_ < nsmall->data_) {
						nsmall = temp;
					}
					nlarge = temp;

					if (temp->left_ && temp->leftisThread == false) {
						temp = temp->left_;
					}
					else {
						temp->left_ = new Node(data);
						temp->leftisThread = false;
						inserted = true;
						size_++;
						if (temp->left_) {
							temp->left_->right_ = nlarge;
							temp->left_->rightisThread = true;
							if (!small) {
								temp->left_->left_ = nsmall;
								temp->left_->leftisThread = true;
							}
						}

					}
				}
				else {
					nsmall = temp;
					small = false;
					if (nlarge->data_ < temp->data_)
						nlarge = temp;
					if (temp->rightisThread == false && temp->right_)
						temp = temp->right_;
					else {
						temp->right_ = new Node(data);
						temp->rightisThread = false;
						inserted = true;
						size_++;
						if (temp->right_) {
							temp->right_->left_ = nsmall;
							temp->right_->leftisThread = true;
							if (!large) {
								temp->right_->right_ = nlarge;
								temp->right_->rightisThread = true;
							}
						}
					}
				}
			}
		}
		else {
			root_ = new Node(data);
			size_++;
		}
	}
	iterator find(const T& key) {
		Node* temp = root_;   
		bool ok = false; 
		while (!ok && temp) {
			if (key < temp->data_) {
				if (temp->leftisThread == true)
					temp = nullptr;
				else
					temp = temp->left_;
			}
			else if (key == temp->data_) {
				ok = true;
			}
			else {
				if (temp->rightisThread == true)
					temp = nullptr;
				else
					temp = temp->right_;
			}
		}
		return iterator(temp, this);
	}
	const_iterator find(const T& key) const {
		Node* temp = root_;  
		bool ok = false;
		while (!ok && temp) {
			if (key < temp->data_) {
				if (temp->leftisThread == true)
					temp = nullptr;
				else
					temp = temp->left_;
			}
			else if (key == temp->data_) {
				ok = true;
			}
			else {
				if (temp->rightisThread == true)
					temp = nullptr;
				else
					temp = temp->right_;
			}
		}
		return const_iterator(temp, this);
	}
	iterator begin() {
		iterator it;
		if (root_) {
			it.tnode = root_;
			while (it.tnode->left_ != nullptr) {
				it.tnode = it.tnode->left_;
			}
		}
		return it;
	}
	iterator end() {
		iterator it(nullptr, this);
		return it;
	}
	const_iterator cbegin()const {
		const_iterator it;
		if (root_) {
			it.tnode = root_;
			while (it.tnode->left_ != nullptr) {
				it.tnode = it.tnode->left_;
			}
		}
		return it;
	}
	const_iterator cend() const {
		const_iterator it(nullptr, this);
		return it;
	}
	int size() const {
		return size_;
	}
	bool empty() const {
		return size_ == 0;
	}
	void dest(Node* root) {
		if (root && !root->leftisThread && !root->rightisThread) {
			dest(root->left_);
			dest(root->right_);
			delete root;
		}
	}
	~ThreadedTree() {
		dest(root_);
	}
};
