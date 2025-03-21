#include <algorithm>
#include <cassert>
#include <cctype>
#include <cmath>
#include <exception>
#include <iomanip>
#include <iostream>
#include <istream>
#include <iterator>
#include <limits>
#include <numeric>
#include <ostream>
#include <stdexcept>
#include <string>
#include <string_view>
#include <type_traits>
#include <vector>

using namespace std::literals;

//  ================================================================================================

class Big_Int
{
public:

	using digit_t = long long;

public:

	Big_Int() : m_is_negative(false), m_n_digits(1), m_digits(size, 0) {}

	Big_Int(digit_t number) : Big_Int() 
	{ 
		parse(std::to_string(number)); 
	}

	Big_Int(std::string_view string) : Big_Int() 
	{ 
		parse(string); 
	}

private:

	void parse(std::string_view string)
	{
		if (string[0] == '+' || string[0] == '-' || std::isdigit(string[0]))
		{
			if (!std::isdigit(string[0]) && std::size(string) == 1)
			{
				throw std::runtime_error("invalid data");
			}

			std::ranges::for_each(std::next(std::begin(string)), std::end(string), [](auto c)
			{ 
				if (!std::isdigit(c)) 
				{
					throw std::runtime_error("invalid data"); 
				}
			});

			m_is_negative = (string[0] == '-'); m_n_digits = 0;

			for (auto i = static_cast < int > (std::size(string)) - 1; i >= 0; i -= step)
			{
				auto start = i - step + 1;

				if (start <= 0) 
				{
					start = m_is_negative ? 1 : 0;
				}

				auto digit = string.substr(start, i - start + 1);

				m_digits[m_n_digits++] = std::stoll(static_cast < std::string > (digit));
			}

			reduce();
		}
		else 
		{
			throw std::runtime_error("invalid data");
		}
	}

	void reduce()
	{
		for (; m_n_digits > 1 && !m_digits[m_n_digits - 1]; --m_n_digits);
	}

public:

	void swap(Big_Int & other)
	{
		using std::swap; 

		swap(m_is_negative, other.m_is_negative);
		swap(m_n_digits,    other.m_n_digits   );
		swap(m_digits,      other.m_digits     );
	}

public:

	friend auto & operator>>(std::istream & stream, Big_Int & big_int)
	{
		std::string string; stream >> string; big_int = Big_Int(string); 
		
		return stream;
	}

	friend auto & operator<<(std::ostream & stream, const Big_Int & big_int)
	{
		if (big_int.m_is_negative) 
		{
			stream << '-';
		}

		stream << big_int.m_digits[big_int.m_n_digits - 1];

		for (auto i = static_cast < int > (big_int.m_n_digits) - 2; i >= 0; --i)
		{
			stream << std::setw(step) << std::setfill('0') << std::right << big_int.m_digits[i];
		}

		return stream;
	}

public:

	auto & operator+=(Big_Int other)
	{
		if ((!m_is_negative && !other.m_is_negative) ||
			( m_is_negative &&  other.m_is_negative))
		{
			this->add(other);
		}
		else if (!m_is_negative &&  other.m_is_negative)
		{
			if (this->less(other))
			{
				*this = std::move(other.subtract(*this)); 
				
				m_is_negative = true;
			}
			else 
			{
				this->subtract(other);
			}
		}
		else if (m_is_negative && !other.m_is_negative)
		{
			if (this->less(other))
			{
				*this = std::move(other.subtract(*this));
			}
			else 
			{ 
				this->subtract(other); m_is_negative = true; 
			}
		}

		return *this;
	}

	auto & operator-=(Big_Int other)
	{
		other.m_is_negative = !other.m_is_negative;

		return *this += other;
	}

private:

	Big_Int & add(const Big_Int & other)
	{
		m_n_digits = std::max(m_n_digits, other.m_n_digits);

		for (auto i = 0uz; i < m_n_digits; ++i)
		{
			if (m_digits[i] += other.m_digits[i]; m_digits[i] >= Big_Int::base)
			{
				if (m_digits[i] -= Big_Int::base; i < size - 1)
				{
					++m_digits[i + 1];
				}
				else 
				{
					throw std::runtime_error("arithmetic overflow");
				}
			}
		}

		m_n_digits += m_digits[m_n_digits];

		return *this;
	}

	Big_Int & subtract(const Big_Int & other)
	{
		for (auto i = 0uz; i < m_n_digits; ++i)
		{
			if (m_digits[i] -= other.m_digits[i]; m_digits[i] < 0)
			{
				m_digits[i] += Big_Int::base;

				m_digits[i + 1]--;
			}
		}

		reduce(); 
		
		return *this;
	}

public:

	auto & operator*=(Big_Int other)
	{
		if (m_n_digits + other.m_n_digits > size) 
		{
			throw std::runtime_error("arithmetic overflow");
		}

		Big_Int result;

		result.m_is_negative = m_is_negative ^ other.m_is_negative;

		for (auto i = 0uz; i < m_n_digits; ++i)
		{
			digit_t r = 0;

			for (auto j = 0uz; (j < other.m_n_digits) || r; ++j)
			{
				result.m_digits[i + j] += (m_digits[i] * other.m_digits[j] + r);

				r = result.m_digits[i + j] / Big_Int::base;

				result.m_digits[i + j] -= (r * Big_Int::base);
			}
		}

		result.m_n_digits = m_n_digits + other.m_n_digits;

		swap(result); 
		
		reduce(); 
		
		return *this;
	}

	auto & operator/=(Big_Int other)
	{
		if (other.m_n_digits == 1 && other.m_digits.front() == 0)
		{
			throw std::runtime_error("invalid operand");
		}

		Big_Int result; result.m_n_digits = m_n_digits;

		result.m_is_negative = m_is_negative ^ other.m_is_negative; other.m_is_negative = false;

		Big_Int current;

		for (auto i = static_cast < int > (m_n_digits) - 1; i >= 0; --i)
		{
			current *= Big_Int::base; current.m_digits[0] = m_digits[i];

			digit_t l = 0, r = Big_Int::base, value = 0;

			while (l <= r)
			{
				if (auto m = std::midpoint(l, r); other * m <= current)
				{
					l = m + 1; value = m;
				}
				else
				{
					r = m - 1;
				}
			}

			result.m_digits[i] = value; current -= other * value;
		}

		swap(result); 
		
		reduce(); 
		
		return *this;
	}

//  ------------------------------------------------------------------------------------------------

	const auto   operator++(int) { auto copy(*this); *this += 1; return  copy; }
	      auto & operator++(   ) { 				     *this += 1; return *this; }
	const auto   operator--(int) { auto copy(*this); *this -= 1; return  copy; }
	      auto & operator--(   ) { 				     *this -= 1; return *this; }

//  ------------------------------------------------------------------------------------------------

	friend auto multiply(const Big_Int & x, const Big_Int & y)
	{
		auto n = std::max(x.m_n_digits, y.m_n_digits);

		if (n == 1) 
		{
			return x * y;
		}

		auto k = n / 2;

		Big_Int xr; xr.m_n_digits =     k;
		Big_Int xl; xl.m_n_digits = n - k;

		for (auto i = 0uz; i < k; ++i) { xr.m_digits[i    ] = x.m_digits[i]; }
		for (auto i = k  ; i < n; ++i) { xl.m_digits[i - k] = x.m_digits[i]; }

		Big_Int yr; yr.m_n_digits =     k;
		Big_Int yl; yl.m_n_digits = n - k;

		for (auto i = 0uz; i < k; ++i) { yr.m_digits[i    ] = y.m_digits[i]; }
		for (auto i = k  ; i < n; ++i) { yl.m_digits[i - k] = y.m_digits[i]; }

		auto p1 = multiply(xl,      yl     );
		auto p2 = multiply(xr,      yr     );
		auto p3 = multiply(xl + xr, yl + yr);

		Big_Int base = Big_Int::base;

		for (auto i = 1uz; i < k; ++i) 
		{
			base *= Big_Int::base;
		}

		auto result = (p1 * base * base + (p3 - p2 - p1) * base + p2);

		result.m_is_negative = x.m_is_negative ^ y.m_is_negative; 

		return result;
	}

//  ------------------------------------------------------------------------------------------------

	friend auto sqrt(const Big_Int & x)
	{
		if (x.m_is_negative) 
		{
			throw std::runtime_error("invalid operand");
		}

		auto position = (static_cast < int > (x.m_n_digits) + 1) / 2;

    	Big_Int result; result.m_n_digits = position;
    	
    	for (--position; position >= 0; --position)
    	{
      		digit_t l = 0, r = Big_Int::base, value = 0;

      		while (l <= r)
      		{
        		if (auto m = result.m_digits[position] = std::midpoint(l, r); result * result <= x)
        		{
          			l = m + 1; value = std::min(m, Big_Int::base - 1);
        		}
        		else
				{
					r = m - 1;
				}				
      		}

      		result.m_digits[position] = value;
    	}

		result.reduce(); 
		
		return result; 
	}

//  ---------------------------------------------------------------------------------------

	friend Big_Int operator+(Big_Int lhs, Big_Int rhs) { return lhs += rhs; }
	friend Big_Int operator-(Big_Int lhs, Big_Int rhs) { return lhs -= rhs; }
	friend Big_Int operator*(Big_Int lhs, Big_Int rhs) { return lhs *= rhs; }
	friend Big_Int operator/(Big_Int lhs, Big_Int rhs) { return lhs /= rhs; }

//  ---------------------------------------------------------------------------------------

	friend bool operator< (const Big_Int & lhs, const Big_Int & rhs)
	{
		if (lhs.m_is_negative != rhs.m_is_negative) { return lhs.m_is_negative; }

		if (lhs.m_is_negative && rhs.m_is_negative) 
		{
			return rhs.less(lhs);
		}
		else
		{
			return lhs.less(rhs);
		}
	}

	friend bool operator> (const Big_Int & lhs, const Big_Int & rhs)
	{
		return  (rhs < lhs);
	}

	friend bool operator<=(const Big_Int & lhs, const Big_Int & rhs)
	{
		return !(rhs < lhs);
	}

	friend bool operator>=(const Big_Int & lhs, const Big_Int & rhs)
	{
		return !(lhs < rhs);
	}

	friend bool operator==(const Big_Int & lhs, const Big_Int & rhs)
	{
		if ((lhs.m_is_negative != rhs.m_is_negative) || (lhs.m_n_digits != rhs.m_n_digits))
		{
			return false;
		}

		for (auto i = 0uz; i < lhs.m_n_digits; ++i)
		{
			if (lhs.m_digits[i] != rhs.m_digits[i]) 
			{
				return false;
			}
		}

		return true;
	}

private:

	bool less(const Big_Int & other) const
	{
		if (m_n_digits != other.m_n_digits) 
		{
			return m_n_digits < other.m_n_digits;
		}

		for (auto i = static_cast < int > (m_n_digits) - 1; i >= 0; --i)
		{
			if (m_digits[i] != other.m_digits[i]) 
			{
				return m_digits[i] < other.m_digits[i];
			}
		}

		return false;
	}

private:

	static inline auto size = 1'000uz;

	static inline auto step = std::numeric_limits < digit_t > ::digits10 / 2;

	static inline auto base = static_cast < digit_t > (std::pow(10, step));

//  -----------------------------------------------------------------------

	bool m_is_negative = false;

	std::size_t m_n_digits = 0;

	std::vector < digit_t > m_digits;

//  ================================================================================================

public:

  Big_Int & operator%=(Big_Int other)
  {
      if (other.m_n_digits == 1 && other.m_digits.front() == 0)
      {
          throw std::runtime_error("Division by 0");
      }

      *this -= (*this / other) * other;
      return *this;
  }

  friend Big_Int operator%(Big_Int lhs, Big_Int rhs)
  {
      return lhs %= rhs;
  }

};

//  ================================================================================================

int main()
{
    try
    {
        Big_Int a = "+73640854127382725310948206095647"sv;
        Big_Int b = "+8581424947372244"sv;

        Big_Int c = a % b;

        std::cout << c << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
