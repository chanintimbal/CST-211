#ifndef PAIR_HPP
#define PAIR_HPP

#include <utility>

namespace data_structures
{
	template <class TFirst, class TSecond>
	class Pair
	{
	public:
		Pair() = default;
		Pair(TFirst first, TSecond second);

		TFirst& First() noexcept;
		TSecond& Second() noexcept;

		const TFirst& First() const noexcept;
		const TSecond& Second() const noexcept;

		void First(const TFirst& first) noexcept;
		void Second(const TSecond& second) noexcept;

	private:
		TFirst first_{ };
		TSecond second_{ };
	};

	
}

#endif