#ifndef COMPARATOR_H_INCLUDED
#define COMPARATOR_H_INCLUDED

namespace UTILS
{
	template <typename T>
	class IComparator
	{
	private:
		const string TAG = "IComparator";

	public:
		virtual Uint8 compare(T t1, T t2);
		virtual Uint8 compareTo(T t);
	};
}

#endif // COMPARATOR_H_INCLUDED
