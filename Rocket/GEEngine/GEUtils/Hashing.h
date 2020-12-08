#pragma once
#include "GECore/Core.h"

struct H
{
	std::string s1, s2;
};

std::ostream& operator << (std::ostream& os, const H& h)
{
	os << h.s1 << "," << h.s2;
	return os;
}

namespace std
{
	template <> struct hash<H>
	{
		size_t operator()(const H& h) const
		{
			return hash<std::string>{}(h.s1) ^ (hash<std::string>{}(h.s2) << 1);
		}
	};
}