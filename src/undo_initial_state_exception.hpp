/* Thrown if one tries to undo the initial state of the game.
 *
 * Linus Narva
 */
#ifndef UNDO_INITIAL_STATE_EXCEPTION_HPP_
#define UNDO_INITIAL_STATE_EXCEPTION_HPP_

#include <exception>

namespace reversi {

class undo_initial_state_exception : std::exception
{
public:

	virtual ~undo_initial_state_exception() = default;

	virtual const char* what() const noexcept override
		{ return "The initial state of the game can not be undone."; }
};

} //namespace reversi

#endif //UNDO_INITIAL_STATE_EXCEPTION_HPP_
