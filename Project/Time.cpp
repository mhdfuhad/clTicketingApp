
#include <iostream>
#include "Time.h"
#include "utils.h"
using namespace std;
namespace sdds {
	Time& Time::setToNow()
	{
		m_min = sdds::getTime();

		return *this;
	}
	Time::Time(unsigned int min)
	{
		m_min = min;
	}
	std::ostream& Time::write(std::ostream& ostr) const
	{
		int mins = m_min % 60;
		int hr = (m_min - mins) / 60;
		ostr.fill('0');
		ostr.width(2);
		ostr << hr << ':';
		ostr.width(2);
		ostr << mins;

		return ostr;
	}
	std::istream& Time::read(std::istream& istr)
	{
		int hr = 0;
		int mins = 0;
		char split = '\0';
		istr >> hr;
		if (hr < 0) istr.setstate(ios::failbit);

		istr.get(split);
		if (split != ':') istr.setstate(ios::failbit);

		istr >> mins;
		if (mins < 0) istr.setstate(ios::failbit);

		this->m_min = (hr * 60) + mins;
		return istr;
	}
	Time& Time::operator-=(const Time& D)
	{
		if (D.m_min > this->m_min) {
			unsigned int day = 1440;
			this->m_min += day;
			unsigned int remainder = D.m_min / day;
			this->m_min += day * remainder;
			this->m_min -= D.m_min;
		}
		else this->m_min -= D.m_min;



		return *this;
	}
	Time Time::operator-(const Time& D) const
	{
		unsigned int subtracted = m_min;
		
		if (D.m_min > subtracted) {
			unsigned int day = 1440;
			subtracted += day;
			unsigned int remainder = D.m_min / day;
			subtracted += day * remainder;
			subtracted -= D.m_min;
		}
		else subtracted -= D.m_min;

		Time A(subtracted);
		
		return A;
	}
	Time& Time::operator+=(const Time& D)
	{
		this->m_min += D.m_min;

		return *this;
	}
	Time Time::operator+(const Time& D) const
	{
		unsigned int added = m_min + D.m_min;
		Time A(added);

		return A;
	}
	Time& Time::operator=(unsigned int val)
	{
		this->m_min = val;

		return *this;
	}
	Time& Time::operator*=(unsigned int val)
	{
		this->m_min *= val;

		return *this;
	}
	Time& Time::operator/=(unsigned int val)
	{
		this->m_min /= val;

		return *this;
	}
	Time Time::operator*(unsigned int val) const
	{
		unsigned int multiplied = m_min * val;
		Time A(multiplied);

		return A;
	}
	Time Time::operator/(unsigned int val) const
	{
		unsigned int divided = m_min / val;
		Time A(divided);

		return A;
	}
	Time::operator unsigned int() const
	{
		return m_min;
	}
	Time::operator int() const
	{
		int val = m_min;
		return val;
	}
	std::ostream& operator<<(std::ostream& ostr, const Time& D)
	{
		return D.write(ostr);
	}
	std::istream& operator>>(std::istream& istr, Time& D)
	{
		return D.read(istr);
	}
}