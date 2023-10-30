#ifndef A_EXCEPTION_H_FILE
#define A_EXCEPTION_H_FILE

#include <iostream>
#include <exception>

using namespace std;

namespace Errors
{
	class ContactException : public exception
	{

	private:
		string cause;

	public:
		ContactException(string cause) : cause(cause) {}
		~ContactException() throw()
		{
			// cout << endl << "Destroy ContactException Object" << this << endl;
		}

		const char *what() const throw()
		{
			return cause.c_str();
		}
	};

}

#endif // A_EXCEPTION_H_FILE
