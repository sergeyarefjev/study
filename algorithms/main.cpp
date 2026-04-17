# include <iostream>
# include <cmath>
# include <vector>
# include <list>
# include <string>
# include <cstdlib>
# include <chrono>
# include <queue>
# include <unordered_map>
# include <stack>
# include <unordered_set>

using namespace std;

struct node {
	int s;
	node* next;
};


void copy(int* arr_1, int* arr_2, int length);

class My_list {
public:
	node* head;
	int length;


	My_list():length(0) {}

	My_list(int len) : length(len){
		head = new node{ 0, nullptr };
		node* nd = head;
		for (int i = 1; i < length; i++) {
			nd->next = new node{ i, nullptr };
			nd = nd->next;
		}
	}

	~My_list(){
		node* nd = head;
		for (int i = 0; i < length; i++) {
			node* nd_new = nd->next;
			delete nd;
			nd = nd_new;
		}
	}

	int operator[](int idx) {
		node* nd = head;
		for (int i = 0; i < idx; i++) {
			nd = nd->next;
		}
		return nd->s;
	}

	void push_front(int elem) {
		node* nd = new node;
		nd = head;
		node* nd_head = new node;
		nd_head->s = elem;
		nd_head->next = nd;
		head = nd_head;
		length++;
	}

	void push_back(int elem) {
		node* nd = head;
		for (int i = 0; i < length - 1; i++) {
			nd = nd->next;
		}
		node* nd_end = new node{elem, nullptr};
		nd->next = nd_end;
		length++;
	}


	int pop_front() {
		int s = head->s;
		node* first = head->next;
		delete head;
		head = first;
		length--;
		return s;
	}
};

int search_middle(My_list& list) {
	node* ptr_slow = list.head;
	node* ptr_fast = list.head;
	while (ptr_fast != nullptr && ptr_fast->next != nullptr) {
		ptr_slow = ptr_slow->next;
		ptr_fast = ptr_fast->next->next;
	}
	return ptr_slow->s;
}

class My_stack_vector {
private:
	vector<int> arr;
public:
	int length;


	My_stack_vector(int len) : length(len) {
		for (int i = 0; i < length; i++) {
			arr.push_back(i);
		}
	}

	~My_stack_vector() {}

	void push(int elem) {
		arr.push_back(elem);
		length++;
	}

	int pop() {
		if (arr.empty()) { cout << "stack - empty!\n"; }
		else {
			int end = this->give_back();
			arr.pop_back();
			length--;
			return end;
		}
		return -1;
	}

	int give_back() {
		return arr[length - 1];
	}

	int operator[] (int idx) {
		return arr[idx];
	}

};


class My_stack_list {
private:
	My_list list;
public:
	int length;

	My_stack_list(int len) : length(len) {
		for (int i = 0; i < length; i++) {
			list.push_front(i);
		}
	}

	~My_stack_list() {}

	void push(int elem) {
		length++;
		list.push_front(elem);
	}

	int pop() {
		if (length > 0) {
			length--;
			return list.pop_front();
		}
		else { cout << "stack - empty!"; }
	}

	int operator[](int idx) {
		return list[idx];
	}
};


class My_queue {
private:
	int* arr;
	int* head;
	int* tail;
	int size;
	int capacity;
public:

	My_queue(int len): capacity(len) {
		arr = new int[capacity];
		head = arr;
		tail = head;
		size = 0;
	}

	~My_queue() {
		delete[] arr;
	}

	int Get_capacity() { return capacity; }
	int* Get_array() { return arr; }
	int* Get_head() { return head; }
	int* Get_tail() { return tail; }
	int Get_size() { return size; }

	void push(int elem) {
		if (size < capacity) {
			*tail = elem;
			if (tail == arr + capacity - 1) {
				tail = arr;
			}
			else { tail++;}
		}
		else {
			int flag;
			int* arr_new = new int[2 * capacity];
			int j = 0;
			for (int* i = head; i < arr + capacity; i++) {
				arr_new[j] = *i;
				flag = j;
				j++;
			}
			for (int* i = arr; i < tail; i++) {
				arr_new[j] = *i;
				j++;
			}
			delete[] arr;
			arr = arr_new;
			head = arr;
			tail = arr + capacity;
			*tail = elem;
			tail++;
			capacity *= 2;
		}
		size++;
	}

	int pop() {
		if (size == 0) {
			cout << "Queue - empty!" << endl;
		}
		else {
			int elem = *head;
			if (head == arr + capacity) {
				head = arr;
			}
			else {
				head++;
			}
			size--;
			return elem;
		}
	}

	int operator[](int idx) {
		if (idx > size) {
			cout << "You're very bad man!";
		}
		if (head + idx < arr + capacity) {
		}
		else {
			idx = arr - head + capacity;
		}
		return *(head + idx);
	}
};

/*
ostream& operator << (ostream& os, My_queue& q) {
	for (int i = 0; i < q.Get_capacity(); i++) {
		os << q.Get_array()[i] << ' ';
	}
	return os;
}*/

ostream& operator << (ostream& os, My_queue& q) {
	if (q.Get_size() == 0) { 
		os << "Queue - empty!";
		return os;
	}
	else {
		if (q.Get_head() >= q.Get_tail()) {
			for (int* ptr = q.Get_head(); ptr < q.Get_array() + q.Get_capacity(); ptr++) {
				os << *ptr << ' ';
			}
			for (int* ptr = q.Get_array(); ptr < q.Get_tail(); ptr++) {
				os << *ptr << ' ';
			}
		}
		else {
			for (int* ptr = q.Get_head(); ptr < q.Get_tail(); ptr++) {
				os << *ptr << ' ';
			}
		}
	}
	return os;
}

struct my_pair {
	int key;
	int value;
};



class Hash_table_list {
private:
	int capacity;
	int size;
	list<my_pair>* table_start;

	int hash_function(int key) {
		return key % capacity;
	}

	void check_rehash() {
		if (float(size) / capacity > 0.85) {
			capacity *= 2;
			list<my_pair>* table_start_new = new list<my_pair>[capacity];
			for (int i = 0; i < capacity / 2; i++) {
				for (auto iter = table_start[i].begin(); iter != table_start[i].end(); iter++) {
					int idx = hash_function(iter->key);
					table_start_new[idx].push_front(*iter);
				}
			}
			delete[] table_start;
			table_start = table_start_new;
		}
	}
public:

	Hash_table_list():capacity(0), size(0) {
		this->table_start = nullptr;
	}

	Hash_table_list(int cap):capacity(cap), size(0) {
		table_start = new list<my_pair>[capacity];
	}

	~Hash_table_list() {
		delete[] table_start;
	}


	void insert(int key, int value) {
		int idx = hash_function(key);
		my_pair pair = { key, value };
		table_start[idx].push_back(pair);
		size++;
		check_rehash();
	}

	int get(int key) {
		int idx = hash_function(key);
		for (auto iter = table_start[idx].begin(); iter != table_start[idx].end(); iter++) {
			if (iter->key == key) { return iter->value; }
		}
		return -1;
	}

	bool remove(int key) {
		int idx = hash_function(key);
		for (auto iter = table_start[idx].begin(); iter != table_start[idx].end(); iter++) {
			if (iter->key == key) { table_start[idx].erase(iter); size--;  return true; }
		}
		return false;
	//	cerr << "Key " << key << " not found!";
	}



	list<my_pair>& operator [] (int idx) {
		return table_start[idx];
	}

	int Get_capacity() {return capacity;}
};

ostream& operator << (ostream& os, Hash_table_list& ht) {
	for (int i = 0; i < ht.Get_capacity(); i++) {
		cout << i << '\t';
		for (auto iter = ht[i].begin(); iter != ht[i].end(); iter++) {
			cout << '<' << iter->key << ", " << iter->value << ">; ";
		}
		cout << endl;
	}
	return os;
}


class Hash_table_address {
private:
	int capacity;
	int size;
	my_pair REMOVED = { -2, 0 }, FREE = {-1, 0};
	my_pair* table_start;

	int hash_function(int key) {
		return key % capacity;
	}

	void check_rehash() {
		if (float(size) / capacity > 0.75) {
			capacity *= 2;
			my_pair* table_start_new = new my_pair[capacity];
			for (int i = 0; i < capacity; i++) {
				table_start_new[i] = FREE;
			}
			for (int i = 0; i < capacity / 2; i++) {
				int idx = hash_function(table_start[i].key);
				idx = find_next_free(idx, table_start_new);
				table_start_new[idx] = table_start[i];
			}
			delete[] table_start;
			table_start = table_start_new;
		}

	}
public:
	Hash_table_address(): capacity(0), size(0) { table_start = nullptr; }

	Hash_table_address(int cap): capacity(cap), size(0) {
		table_start = new my_pair[capacity];
		for(int i = 0; i < capacity; i++){
			table_start[i] = FREE;
		}
	}

	~Hash_table_address() { delete[] table_start; }

	int find_next_free(int idx, my_pair* ts) {
		int idx_add = 0;
		//low written full shittt
		while (//(table_start[idx + idx_add].key != REMOVED.key || table_start[idx + idx_add].value != REMOVED.value) && I'm think this wrong criterion
			(ts[idx + idx_add].key != FREE.key || ts[idx + idx_add].value != FREE.value) && idx + idx_add < capacity) {
			idx_add++;
		}
		if (idx + idx_add == capacity) {
			idx_add -= capacity;
			while (//(table_start[idx + idx_add].key != REMOVED.key || table_start[idx + idx_add].value != REMOVED.value) && I'm think this wrong criterion
				(ts[idx + idx_add].key != FREE.key || ts[idx + idx_add].value != FREE.value) && idx_add < 0) {
				idx_add++;
			}
		}
		return idx + idx_add;
	}

	int find_from_key(int key) {
		int idx = hash_function(key);
		int idx_add = 0;
		while (//(table_start[idx + idx_add].key != REMOVED.key || table_start[idx + idx_add].value != REMOVED.value) && I'm think this wrong criterion
			(table_start[idx + idx_add].key != FREE.key || table_start[idx + idx_add].value != FREE.value) && idx + idx_add < capacity) {
			if (table_start[idx + idx_add].key == key) { return idx + idx_add; }
			if (table_start[idx + idx_add].key == FREE.key && table_start[idx + idx_add].value == FREE.value) { break; }
			idx_add++;
		}
		if (idx + idx_add == capacity) {
			idx_add -= capacity;
			while (//(table_start[idx + idx_add].key != REMOVED.key || table_start[idx + idx_add].value != REMOVED.value) && I'm think this wrong criterion
				(table_start[idx + idx_add].key != FREE.key || table_start[idx + idx_add].value != FREE.value) && idx_add < 0) {
				if (table_start[idx + idx_add].key == key) { return idx + idx_add; }
				idx_add++;
			}
		}
		return -1;
	
	}


	void insert(int key, int value) {
		int idx = find_next_free(hash_function(key), this->table_start);
		my_pair pair = { key, value };
		table_start[idx] = pair;
		size++;
		check_rehash();
	}


	int get(int key) {
		int idx = find_from_key(key);
		if (idx == -1) {
			cerr << "Wrong key!" << endl;
		}
		else { return table_start[idx].value; }
	}

	bool remove(int key) {
		int idx = find_from_key(key);
		if (idx == -1) { return false; }
		table_start[idx] = REMOVED;
		size--;
		return true;
	}


	my_pair operator[](int idx) {
		return table_start[idx];
	}

	int Get_capacity() { return capacity; }
};

ostream& operator << (ostream& os, Hash_table_address& ht) {
	for (int i = 0; i < ht.Get_capacity(); i++) {
		if (ht[i].key == -2 && ht[i].value == 0) { cout << "REMOVED" << endl; }
		else {
			if (ht[i].key == -1 && ht[i].value == 0) { cout << "FREE" << endl; }
			else {
				cout << i << " <" << ht[i].key << ", " << ht[i].value << ">;" << endl;
			}
		}
	}

	return os;
}

struct node_tree {
	int value;
	node_tree* left;
	node_tree* right;
};

ostream& operator << (ostream& os, node_tree* nt) {
	os << "\t" << nt->value << "\t" << endl;
	if (nt->left == nullptr) {
		os << "\t";
	}
	else { os << nt->left->value; }
	os << "\t" << "\t";
	if (nt->right == nullptr) {
		os << "\t";
	}
	else { os << nt->right->value; }
	os << endl;
	return os;
}

class Bin_tree {
private:
	node_tree* root_start;
	//int n_count;

public:

	Bin_tree():root_start(nullptr) {}

	void delete_node_tree(node_tree* ndt) {
		if (ndt->left != nullptr) {
			delete_node_tree(ndt->left);
		}
		if (ndt->right != nullptr) {
			delete_node_tree(ndt->right);
		}
		delete ndt;
	}

	~Bin_tree() {
		if (root_start != nullptr) {
			delete_node_tree(root_start);
		}
	}

	node_tree* find_min(node_tree* start_find) {
		node_tree* current_node = start_find;
		while (current_node->left != nullptr) {
			current_node = current_node->left;
		}
		return current_node;
	}

	node_tree* find_max(node_tree* start_find) {
		node_tree* current_node = start_find;
		while (current_node->right != nullptr) {
			current_node = current_node->right;
		}
		return current_node;

	}

	void push_item(int elem, node_tree*& current_node) {
		current_node->value = elem;
		current_node->left = nullptr;
		current_node->right = nullptr;
	}

	void insert(int elem) {
		if (root_start == nullptr) {
			root_start = new node_tree;
			push_item(elem, root_start);
			return;
		}
		node_tree* current_node = root_start;
		while (true) {
			if (elem >= current_node->value) {
				if (current_node->right == nullptr) {
					current_node->right = new node_tree;
					push_item(elem, current_node->right);
					return;
				}
				current_node = current_node->right;
			}
			else {
				if (current_node->left == nullptr) {
					current_node->left = new node_tree;
					push_item(elem, current_node->left);
					return;
				}
				current_node = current_node->left;
			}
		}

	}

	node_tree* find(int elem) {
		node_tree* current_node = root_start;
		while (current_node->value != elem) {
			if (elem >= current_node->value) {
				if (current_node->right == nullptr) {
					cout << "Lacking element" << endl;
					node_tree nt{ 123, nullptr, nullptr };
					return &nt;
				}
				current_node = current_node->right;
			}
			else {
				if (current_node->left == nullptr) {
					cout << "Lacking element" << endl;
					node_tree nt{ 123, nullptr, nullptr };
					return &nt;
				}
				current_node = current_node->left;
			}
		}
		return current_node;

	}

	struct flag_node_tree {
		node_tree* nd_before;
		node_tree* nd_this;
		bool flag;
	};

	flag_node_tree find_before(int elem, node_tree* node_before, node_tree* node_next) {
		node_tree* current_node = node_before;
		node_tree* pop_node = node_next;
		bool flag; //false - left, true - right

		while (current_node->left != nullptr || current_node->right != nullptr) {
			if (elem >= current_node->value) {
				if (current_node->right != nullptr && current_node->right->value == elem) {
					pop_node = current_node->right;
					flag = true;
					break;
				}
				current_node = current_node->right;
			}
			else {
				if (current_node->left != nullptr && current_node->left->value == elem) {
					pop_node = current_node->left;
					flag = false;
					break;
				}
				current_node = current_node->left;
			}
		}
	//	if (flag != false && flag != true) { cout << "Lacking element" << endl; }
		flag_node_tree fnt{ current_node, pop_node, flag };
		return fnt;
	}


	void pop(int elem) {
		//flag: false - left, true - right
		flag_node_tree fnt = find_before(elem, this->root_start, this->root_start);

		//This node - leaf
		if (fnt.nd_this->left == nullptr && fnt.nd_this->right == nullptr) {
			if (fnt.flag == false) {
				fnt.nd_before->left = nullptr;
			}
			else { fnt.nd_before->right = nullptr; }
			delete fnt.nd_this;
			return;
		}

		//Node has two descendant
		if (fnt.nd_this->left != nullptr && fnt.nd_this->right != nullptr) {
			node_tree* support = find_min(fnt.nd_this->right);
			fnt.nd_this->value = support->value;
			fnt = find_before(support->value, fnt.nd_this, fnt.nd_this->right);
			if (fnt.flag == false) {
				fnt.nd_before->left = nullptr;
			}
			else { fnt.nd_before->right = nullptr; }
			delete fnt.nd_this;
			return;
		}

		//Node has one descendant
		if (fnt.nd_this->left != nullptr) {
			if (fnt.flag == false) {
				fnt.nd_before->left = fnt.nd_this->left;
			}
			else { fnt.nd_before->left = fnt.nd_this->left; }
		}
		else {
			if (fnt.flag == false) {
				fnt.nd_before->left = fnt.nd_this->right;
			}
			else { fnt.nd_before->right = fnt.nd_this->right; }
		}
		delete fnt.nd_this;
	}


	vector<int> breadth_tree() {
		vector<int> result;
		queue<node_tree*> q;
		node_tree* current_node;
		q.push(root_start);

		while (!q.empty()) {
			result.push_back(q.front()->value);
			if (q.front()->left != nullptr) { q.push(q.front()->left); }
			if (q.front()->right != nullptr) { q.push(q.front()->right); }
			q.pop();
		}
		return result;
	}

	vector<int> dept_tree() {
		vector<int> result;

		dept_tree_support(root_start, result);
		return result;
	}

	void dept_tree_support(node_tree* current_node, vector<int> &result) {
		if (current_node == nullptr) { return; }

		dept_tree_support(current_node->left, result);
		result.push_back(current_node->value);
		dept_tree_support(current_node->right, result);
	}
};

class Max_Heap {
public:
	vector<int> vec;

	Max_Heap(vector<int> vector): vec(vector){
		for (int i = vec.size() / 2 - 1; i >= 0; i--) {
			sift_down(i);
		}
	}

	~Max_Heap() {}
	void sift_down(int idx) {
		int idx_largest = idx, idx_left = 2 * idx + 1, idx_right = 2 * idx + 2;

		if (idx_left < vec.size() && vec[idx_largest] < vec[idx_left]) { idx_largest = idx_left; }
		if (idx_right < vec.size() && vec[idx_largest] < vec[idx_right]) { idx_largest = idx_right; }

		if (idx_largest != idx) {
			int support;
			support = vec[idx];
			vec[idx] = vec[idx_largest];
			vec[idx_largest] = support;

			sift_down(idx_largest);
		}
	}

	void push(int elem) {
		vec.push_back(elem);
		int i = vec.size() - 1;
		while (i - 1 >= 0) {
			if (vec[i] > vec[(i - 1) / 2]) {
				swap(vec[i], vec[(i - 1) / 2]);
				i = (i - 1) / 2;
			}
			else { break; }
		}
	}

	int operator[] (int idx) {
		return vec[idx];
	}

	void pop() {
		vec[0] = vec[vec.size() - 1];
		vec.pop_back();

		sift_down(0);
	}
};

void sift_down(int*& arr, int length, int idx){
	int idx_largest = idx, idx_left = 2 * idx + 1, idx_right = 2 * idx + 2;

	if (idx_left < length && arr[idx_largest] < arr[idx_left]) { idx_largest = idx_left; }
	if (idx_right < length && arr[idx_largest] < arr[idx_right]) { idx_largest = idx_right; }

	if (idx_largest != idx) {
		int support;
		support = arr[idx];
		arr[idx] = arr[idx_largest];
		arr[idx_largest] = support;

		sift_down(arr, length, idx_largest);
	}
}

void build_max_heap(int* &arr, int length) {

	for (int i = length / 2 - 1; i >= 0; i--) {
		sift_down(arr, length, i);
	}
}


int find_min_idx(int* arr, int length, int start) {
	int min = start;
	for (int i = start; i < length; i++) {
		if (arr[min] > arr[i]) {
			min = i;
		}
	}
	return min;
}

//return - индекс поседнего вхождения или индекс, перед которым должен стоять elem
int bin_finding(int* arr, int length, int elem) {
	int start = 0, finish = length - 1;
	int middle = (start + finish) / 2;
	if (length == 1) {
		if (arr[start] > elem) { return -1; }
		else { return 0; }
	}

	if (length == 2) {
		if (arr[start] > elem) { return -1; }
		if (arr[finish] < elem) { return 1; }
		else { return 0; }
	}

	//length > 2
	while (start + 1 != finish) {

		middle = (start + finish) / 2;

		if (arr[middle] > elem) { finish = middle; }
		else { start = middle; }
	}
	if (arr[finish] == arr[start] && arr[finish] == elem) { return finish; }
	if (start == 0 && arr[start] > elem) { return -1; }
	return start;
}


void insert(int* arr, int idx_elem, int idx_insert) {
	int support_one, support_two = arr[idx_elem];
	for (int i = idx_insert; i < idx_elem + 1; i++) {
		support_one = arr[i];
		arr[i] = support_two;
		support_two = support_one;
	}
}


void sort_choosing(int* arr, int length) {
	int min, support;
	for (int i = 0; i < length; i++) {
		min = find_min_idx(arr, length, i);
		support = arr[i];
		arr[i] = arr[min];
		arr[min] = support;
	}
}

void sort_inserting(int* arr, int length) {
	int idx_insert;
	for (int i = 1; i < length; i++) {
		if (arr[i] < arr[i - 1]) {
			idx_insert = bin_finding(arr, i, arr[i]);
			insert(arr, i, idx_insert + 1);
		}
	}

}

void sort_bubble(int* arr, int length) {
	int support, j = 0;
	bool flag = false;
	while (!flag) {
		flag = true;
		for (int i = 0; i < length - 1 - j; i++) {
			if (arr[i + 1] < arr[i]) {
				support = arr[i + 1];
				arr[i + 1] = arr[i];
				arr[i] = support;
				flag = false;
			}
		}
		j++;
	}

}

void sort_shell(int* arr, int length) {;
	int k = int(log(length + 1));
	int gap = pow(2, k) - 1;
	//int gap = length / 2;
	bool flag = false;
	int support;

	while (gap > 0) {
		flag = true;
		for (int i = gap; i < length; i++) {
			for (int j = 1; i - j * gap >= 0 && arr[i - (j - 1) * gap] < arr[i - j * gap]; j++) {
				support = arr[i - (j - 1) * gap];
				arr[i - (j - 1) * gap] = arr[i - j * gap];
				arr[i - j * gap] = support;
				flag = false;
			}
		}
		k--;
		gap = pow(2, k) - 1;
	}
}

//arr_one and arr_two - neighbour and arr_one - first, arr_one - second
int* merge(int* arr_one, int length_one, int* arr_two, int length_two, int* arr_support) {
	int i = 0, j = 0;
	int* arr_1 = arr_support;
	int* arr_2 = arr_1 + length_one;
	copy(arr_one, arr_1, length_one);
	copy(arr_two, arr_2, length_two);
	while (i < length_one && j < length_two) {
		if (arr_1[i] <= arr_2[j]) {
			arr_one[i + j] = arr_1[i];
			i++;
		}
		else {
			arr_one[i + j] = arr_2[j];
			j++;
		}
	}
	for (int k = i; k < length_one; k++) {
		arr_one[k + j] = arr_1[k];
	}
	for (int k = j; k < length_two; k++) {
		arr_one[i + k] = arr_2[k];
	}

	return arr_one;
}

int* merge_sort_1(int* arr, int length, int* arr_support) {
	if (length == 1) { return arr; }
	int middle = length / 2;
	int* arr_new = arr + middle;
	return merge(merge_sort_1(arr, middle, arr_support), middle, merge_sort_1(arr_new, length - middle, arr_support), length - middle, arr_support);
}

void merge_sort(int* arr, int length) {
	int middle = length / 2;
	int* arr_new = arr + middle;
	int* arr_support = new int[length];
	merge(merge_sort_1(arr, middle, arr_support), middle, merge_sort_1(arr_new, length - middle, arr_support), length - middle, arr_support);
	delete[] arr_support;
}

int idx_median(int* arr, int length) {
	int* arr_support = arr;
	sort_inserting(arr_support, length);
	return arr_support[length / 2];
}

void quick_sort(int* arr, int length) {
//	int arr_rand[3] = { arr[rand() % length], arr[rand() % length], arr[rand() % length] };
//	int target = idx_median(arr_rand, 3);
	int target = arr[rand() % length];
	int i = 0, j = length - 1;
	int support;

	while (i <= j) {
		while (arr[i] < target) { i++; }
		while (target < arr[j]) { j--; }
		if (i <= j) {
			support = arr[i];
			arr[i] = arr[j];
			arr[j] = support;
			i++, j--;
		}
	}

	if (i < length) { quick_sort(arr + i, length - i); }
	if (j > 0) { quick_sort(arr, j + 1); }
}

void pyramid_sort(int* arr, int length) {
	build_max_heap(arr, length);
	for (int i = length; i >= 2; i--) {
		int support = arr[i - 1];
		arr[i - 1] = arr[0];
		arr[0] = support;

		sift_down(arr, i - 1, 0);
	}
}

void copy(int* arr_1, int* arr_2, int length) {
	for (int i = 0; i < length; i++) {
		arr_2[i] = arr_1[i];
	}
}

bool check_sort(int* arr, int length) {
	for (int i = 0; i < length - 1; i++) {
		if (arr[i] > arr[i + 1]) { return false; }
	}
	return true;
}

double mean_vector(vector<double> vec) {
	double mean = 0;
	int N = vec.size();
	for (int i = 0; i < N; i++) {
		mean += vec[i] / N;
	}
	return mean;
}

bool check_equal(int* arr_one, int* arr_two, int length) {
	for (int i = 0; i < length; i++) {
		if (arr_one[i] != arr_two[i]) { return false; }
	}
	return true;
}

void check_time_sort() {

	int length = 100000;
	int* arr = new int[length];
	int* arr_support = new int[length];
	vector<double> time_choosing;
	vector<double> time_inserting;
	vector<double> time_bubble;
	vector<double> time_shell;
	vector<double> time_merge;
	vector<double> time_quick;
	vector<double> time_pyramid;
	srand(time(0));



	for (int i = 0; i < 10; i++) {
		for (int i = 0; i < length; i++) {
			arr[i] = rand();
		}
		copy(arr, arr_support, length);

		auto start = chrono::high_resolution_clock::now();
		sort_choosing(arr, length);
		auto end = chrono::high_resolution_clock::now();
		std::chrono::duration<double, std::micro> durat_1 = end - start;
		time_choosing.push_back(durat_1.count());
		copy(arr_support, arr, length);

		start = chrono::high_resolution_clock::now();
		sort_inserting(arr, length);
		end = chrono::high_resolution_clock::now();
		std::chrono::duration<double, std::micro> durat_2 = end - start;
		time_inserting.push_back(durat_2.count());
		copy(arr_support, arr, length);

		start = chrono::high_resolution_clock::now();
		sort_bubble(arr, length);
		end = chrono::high_resolution_clock::now();
		std::chrono::duration<double, std::micro> durat_3 = end - start;
		time_bubble.push_back(durat_3.count());
		copy(arr_support, arr, length);

		start = chrono::high_resolution_clock::now();
		sort_shell(arr, length);
		end = chrono::high_resolution_clock::now();
		std::chrono::duration<double, std::micro> durat_4 = end - start;
		time_shell.push_back(durat_4.count());
		copy(arr_support, arr, length);

		start = chrono::high_resolution_clock::now();
		merge_sort(arr, length);
		end = chrono::high_resolution_clock::now();
		std::chrono::duration<double, std::micro> durat_5 = end - start;
		time_merge.push_back(durat_5.count());
		copy(arr_support, arr, length);

		start = chrono::high_resolution_clock::now();
		quick_sort(arr, length);
		end = chrono::high_resolution_clock::now();
		std::chrono::duration<double, std::micro> durat_6 = end - start;
		time_quick.push_back(durat_6.count());
		copy(arr_support, arr, length);

		start = chrono::high_resolution_clock::now();
		pyramid_sort(arr, length);
		end = chrono::high_resolution_clock::now();
		std::chrono::duration<double, std::micro> durat_7 = end - start;
		time_pyramid.push_back(durat_7.count());
	}

	cout << "Choosing sort: " << mean_vector(time_choosing) << endl;
	cout << "Inserting sort: " << mean_vector(time_inserting) << endl;
	cout << "Bubble sort: " << mean_vector(time_bubble) << endl;
	cout << "Shell sort: " << mean_vector(time_shell) << endl;
	cout << "Merge sort: " << mean_vector(time_merge) << endl;
	cout << "Quick sort: " << mean_vector(time_quick) << endl;
	cout << "Pyramid sort: " << mean_vector(time_pyramid) << endl;



	delete[] arr;
	delete[] arr_support;
}

bool check_in_vector(int elem, vector<int> v) {
	for (int i = v.size() - 1; i >= 0; i--) {
		if (v[i] == elem) { return true; }
	}
	return false;
}

vector<int> dfs_graph(unordered_map<int, vector<int>> graph, int start) {
	vector<int> result;
	stack<int> memory;
	unordered_set<int> visited;

	int elem = start;
	do {
		if (visited.find(elem) == visited.end()) {
			memory.push(elem);
			result.push_back(elem);
			visited.insert(elem);

		}
		else {memory.pop(); elem = memory.top();}
		for (int i = 0; i < graph[elem].size(); i++) {
			if (visited.find(graph[elem][i]) == visited.end()) { elem = graph[elem][i]; break; }
		}
	} while (elem != start);
	return result;


}

vector<int> bfs_graph(unordered_map<int, vector<int>> graph, int start) {
	vector<int> result;
	queue<int> q;
	unordered_set<int> visited;
	q.push(start);
	result.push_back(start);
	visited.insert(start);
	int elem;
	while (!q.empty()) {
		elem = q.front();
		q.pop();
		for (int i = 0; i < graph[elem].size(); i++) {
			if (visited.find(graph[elem][i]) == visited.end()) {
				q.push(graph[elem][i]);
				result.push_back(graph[elem][i]);
				visited.insert(graph[elem][i]);
			}
		}
	}
	return result;
}

int
main() {
	cout << pow(3, pow(4, pow(5, pow(6, 7)))) % 193;
	return 0;
}
