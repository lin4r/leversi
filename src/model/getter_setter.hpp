/*******************************************************
 * Copyright (C) 2014-2015 Linus Narva
 * linus.narva@gmail.com
 * 
 * This file is part of othello-assignment.
 * 
 * othello-assignment can not be copied and/or
 * distributed without the express permission of Linus
 * Narva.
 *******************************************************/

/*
 * Useful macros for creating getters and setters.
 *
 * Linus Narva.
 */
#ifndef GETTER_SETTER_HPP_
#define GETTER_SETTER_HPP_

#define GETTER(type,member) \
	virtual type get_##member() const noexcept \
	{ \
		return member; \
	}

#define SETTER(type,member) \
	virtual void set_##member(type newVal) noexcept \
	{ \
		member = newVal; \
	}

#define GETTERSETTER(type,member) \
	SETTER(type,member) \
	GETTER(type,member)

#endif //GETTER_SETTER_HPP_
