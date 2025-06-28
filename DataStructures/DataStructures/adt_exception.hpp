#ifndef ADTEXCEPTION_HPP
#define ADTEXCEPTION_HPP

#include <exception>
#include <ostream>
#include <string>

using std::ostream;
using std::wstring;
using std::string;
using std::copy;

namespace data_structures
{
	class AdtException final : public std::exception
	{
	public:
		explicit AdtException(const char* what) : exception(what) { }

		const wchar_t* Message() const
		{
			string str = exception::what();
			wstring wide_str(str.length(), L' ');

			copy(str.begin(), str.end(), wide_str.begin());

			return wide_str.c_str(); // NOLINT(clang-diagnostic-return-stack-address)
		}

		friend ostream& operator<<(ostream& stream, const AdtException& exception)
		{
			stream << exception.what() << "\n";
			return stream;
		}
	};
}


#endif