//from first answer on https://stackoverflow.com/questions/16749723/how-i-can-find-value-in-priority-queue

#include <queue>
template<
	class T,
	class Container = std::vector<T>,
	class Compare = std::less<typename Container::value_type>
> class PriorityQueue : public std::priority_queue<T, Container, Compare>
{
public:
	typedef typename
		std::priority_queue<
		T,
		Container,
		Compare>::container_type::const_iterator const_iterator;

	const_iterator find(const T&val) const
	{
		auto first = this->c.cbegin();
		auto last = this->c.cend();
		while (first != last) {
			if (*first == val) return first;
			++first;
		}
		return last; 
	}
	const_iterator end() const
	{
		return this->c.cend();
	}
};