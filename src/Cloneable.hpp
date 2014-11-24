/* The Cloneable aka. Virtual Constructor design pattern. Its useful when an
 * interface is used to hold polymorfic reference to various instances.
 */
#ifndef CLONEABLE_HPP_
#define CLONEABLE_HPP_

#include <memory>

namespace othello {

template<typename T>
class Cloneable
{
	virtual std::unique_ptr<T> clone() const = 0;
};

} //namespace othello

#endif //CLONEABLE_HPP_
