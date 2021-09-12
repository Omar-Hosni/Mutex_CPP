/*
mutex job is to protect the data to be simultaneously accessed by multiple threads
it uses a function called locked_guard
this locked_guard opens the data when needed and locks it when has to
just to protect the data from being accessed by multiple threads at once
Data race: A data race is a situation, in which at least two threads access a shared variable at the same time.
At least one thread tries to modify the variable.
mutex prove mutual exclusive access for the same data for multiple threads
std::atomic<data_type> a = 0;
Atomic types are types that encapsulate a value whose access is guaranteed to not cause data races and can be used to synchronize memory accesses among different threads.
This header declares two C++ classes, atomic and atomic_flag , that implement all the features of atomic types in self-contained classes.
List is not built in thread safe data structure.
pushing an element to the list is not an atomic operation

*/

#include <iostream>
#include <mutex>
#include <list>
#include <thread>

using namespace std;

std::list<int> my_list;
std::mutex m;

void add_to_list(int const& x) {
	lock_guard<mutex> lg(m);
	my_list.push_front(x);

	
}

void print_size_and_elements() {
	m.lock(); //locks the data to prevent any new element into it
	int size = my_list.size();
	m.unlock(); // unlocks the data to let us print its size
	cout << "size of the list is: " << size << endl;

	cout << "the elements are: [";
	for (auto elements : my_list) {
			cout << elements << " ";
	}
	cout << "]";
}


int main() {
	thread t1(add_to_list, 4);
	thread t2(add_to_list, 11);
	
	thread t3(print_size_and_elements);

	t1.join();
	t2.join();
	t3.join();
}
