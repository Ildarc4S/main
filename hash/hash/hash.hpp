#pragma once

#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

namespace hash
{
	using Q = std::size_t;
	using H = std::uint64_t;
	using S = std::string;

	constexpr std::uint8_t cardinality = 52;
	constexpr std::int8_t shift = 1 - 'A';

	H getHash(const S& line);

	using Qs = std::vector<Q>;
	using Ss = std::vector<S>;

	struct Pair
	{
		H h;
		Q i;
	};

	using P = Pair;
	using Ps = std::vector<P>;

	void sort(Ps& pairs);

	void swap(P& l, P& r);

	std::vector<Qs> getSameLineIndices(hash::Ss& lines);
}

hash::H hash::getHash(const S& line)
{
	H h = 0;
	H p = 1;


	const auto size = line.size();
	for (Q i(0); i < line.size(); ++i)
	{
		h += (line[i] + shift) * p;
		p *= cardinality;
	}
	return h;
}

void hash::sort(Ps& pairs)
{
	const auto size = pairs.size();
	for (Q i(0); i < size; ++i)
	{
		for (Q j(0); j < size - 1; ++j)
		{
			auto& l = pairs[i], & r = pairs[i + 1];
			if (l.h > r.h)
			{
				swap(l, r);
			}
		}
	}
}

void hash::swap(P& l, P& r)
{
	const P tmp = l;
	l = r;
	r = tmp;
}


std::vector<hash::Qs> hash::getSameLineIndices(hash::Ss& lines)
{
	const int size = lines.size();
	std::vector<Qs> indices;
	Ps pairs(size);

	pairs.push_back({ getHash(lines[0]), 0 });

	for (Q i(0); i < size; ++i)
	{
		pairs[i] = { getHash(lines[i]), i };
	}

	sort(pairs);

	indices.push_back(Qs{ pairs[0].i });
	for (Q i(1); i < size; ++i)
	{
		if (pairs[i].h != pairs[i - 1].h)
		{
			indices.push_back(Qs());
		}
		indices.back().push_back(i); //curr
	}


	return indices;
}
