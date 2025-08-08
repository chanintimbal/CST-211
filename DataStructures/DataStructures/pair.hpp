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

		bool operator==(const Pair& other) const noexcept;
		bool operator!=(const Pair& other) const noexcept;

	private:
		TFirst first_{ };
		TSecond second_{ };
	};

	template <class TFirst, class TSecond>
	Pair<TFirst, TSecond>::Pair(TFirst first, TSecond second) : first_(first), second_(second)
	{
	}

	template <class TFirst, class TSecond>
	TFirst& Pair<TFirst, TSecond>::First() noexcept
	{
		return first_;
	}

	template <class TFirst, class TSecond>
	TSecond& Pair<TFirst, TSecond>::Second() noexcept
	{
		return second_;
	}

	template <class TFirst, class TSecond>
	const TFirst& Pair<TFirst, TSecond>::First() const noexcept
	{
		return first_;

	}

	template <class TFirst, class TSecond>
	const TSecond& Pair<TFirst, TSecond>::Second() const noexcept
	{
		return second_;

	}

	template <class TFirst, class TSecond>
	void Pair<TFirst, TSecond>::First(const TFirst& first) noexcept
	{
		first_ = first;
	}

	template <class TFirst, class TSecond>
	void Pair<TFirst, TSecond>::Second(const TSecond& second) noexcept
	{
		second_ = second;
	}
	template <class TFirst, class TSecond>
	bool Pair<TFirst, TSecond>::operator==(const Pair& other) const noexcept
	{
		return first_ == other.first_ && second_ == other.second_;
	}

	template <class TFirst, class TSecond>
	bool Pair<TFirst, TSecond>::operator!=(const Pair& other) const noexcept
	{
		return !(*this == other);
	}

}

#endif