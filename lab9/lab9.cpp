/*
Q4
Write any program that demonstrates the use of multiple catch handling, re-throwing an exception, and catching all exceptions.
*/
#include <iostream>
namespace Q4 {
	using namespace std;

	int main() {

		return 0;
	}
}


/*
Q3
Modify the stack class given in the previous lab to add the exception when a user tries to add an item while the stack is full 
and when the user tries to add the item while the stack is empty. 
Throw exceptions in both of the cases and handle these exceptions.
*/
#include <iostream>
namespace Q3 {

	using namespace std;
	struct Error{
		enum StackError {
			STACK_EMPTY_NO_DELETE,
			STACK_FULL_NO_ADD
		} stack;
		void print() const {
			switch (stack) {
			case STACK_EMPTY_NO_DELETE:
				cout << "Sorry, stack is empty, cannot remove any elements.\n";
				break;
			case STACK_FULL_NO_ADD:
				cout << "Sorry, stack is full, cannot add more elements .\n";
			}
		}
	};
	template <typename T = int, unsigned max_size = 20>
	class Stack {
	private:
		T m_arr[max_size];
		int m_top;
	public:
		Stack() {
			m_top = -1;
		}
		T& push(T val) {
			if (m_top + 1 >= max_size)
				throw Error{ Error::STACK_FULL_NO_ADD };
			return (m_arr[++m_top] = val);
		}
		T pop() {
			if (m_top < 0)
				throw Error{ Error::STACK_EMPTY_NO_DELETE };
			return (m_arr[m_top--]);
		}
	};

	int main() {
		Stack<> iStack;
				

		try {
			iStack.push(7);
			cout << iStack.pop() << " ";
			cout << iStack.pop();
		}
		catch (Error err) {
			err.print();
		}
		Stack<double, 2> dStack;
		try {
			cout << endl << dStack.push(4.567) << " ";
			cout << dStack.push(-3.4576) << " ";
			cout << dStack.push(0) << endl;
		}
		catch (Error err) {
			err.print();
		}
		return 0;

	}
}

/*
Q2
Write a class template for queue class. Assume the programmer using the queue won't make mistakes, 
like exceeding the capacity of the queue or trying to remove an item when the queue is empty. 
Define several queues of different data types and insert and remove data from them.
*/
#include <iostream>
namespace Q2 {
	using namespace std;
	template <typename T =int , unsigned max_size = 20>
	class Queue {
	private:
		T m_arr[max_size];
		unsigned m_size;
		unsigned m_front;
	public:
		Queue() {
			m_size = 0;
			m_front = 0;
		}
		T& insert(T data) {
			++m_size;
			m_arr[m_size + m_front - 1] = data;
			return m_arr[m_size + m_front - 1];
		}
		T remove() {
			--m_size;
			return m_arr[m_front++];
		}
	};

	int main() {
		Queue <float, 4> fQueue;
		fQueue.insert(3.546);
		fQueue.insert(0);
		fQueue.insert(-96.74);
		cout << fQueue.remove() << " ";
		fQueue.insert(67e24);
		cout << fQueue.remove() << " ";
		cout << fQueue.remove() << " ";

		Queue<> iQueue;
		iQueue.insert(3);
		cout << iQueue.remove() << " ";
		iQueue.insert(8);
		iQueue.insert(9);
		cout << iQueue.remove() << " ";


		return 0;

	}

}

/*
Q1
Create a function called sum() that returns the sum of the elements of an array. 
Make this function into a template so it will work with any numerical type. 
Write a program that applies this function to data of various types.
*/

#include <iostream>
namespace Q1 {
	using namespace std;
	template <unsigned size, class T>
	T getSum(T arr[size]) {
		T sum = 0;
		for (unsigned i = 0; i < size; i++) {
			sum += arr[i];
		}
		return sum;
	}
	int main() {
		int iarr[6] = { 1,2,3,4,5,6 };
		double darr[4] = { 2,3,-4.5,-0.00002 };
		int isum = getSum<6>(iarr);
		double dsum = getSum<3, double>(darr);
		cout << "Sum of 6 integer elements of size 6 is : " << isum << endl;
		cout << "Sum of 3 double elements of size 4 is : " << dsum << endl;
		return 0;
	}
}



#include <iostream>
#include <cstdlib>

using namespace std;

int main(){

	Q1::main();
	system("pause");
	std::cout << std::endl;

	
	Q2::main();
	system("pause");
	std::cout << std::endl;

	
	Q3::main();
	system("pause");
	std::cout << std::endl;

	
	Q4::main();
	system("pause");
	std::cout << std::endl;





}