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

	game_over_exception() noexcept
		: illegal_action_exception(
			"Can't apply action because the game is over.")
	{}

	virtual ~game_over_exception() = default;
};

} //namespace othello

#endif //GAME_OVER_EXCEPTION_HPP_
