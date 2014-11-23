/* Thrown if one applies an action after game over.
 *
 * Linus Narva
 */
#ifndef GAME_OVER_EXCEPTION_HPP_
#define GAME_OVER_EXCEPTION_HPP_

#include "illegal_action_exception.hpp"

namespace othello {

class game_over_exception : public illegal_action_exception
{
public:

	virtual ~game_over_exception() = default;

	virtual const char* what() const noexcept override
		{ return "Can't apply action because the game is over."; }
};

} //namespace othello

#endif //GAME_OVER_EXCEPTION_HPP_
