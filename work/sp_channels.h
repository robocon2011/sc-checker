/*
 * sp_channels.h
 *
 *  Created on: 11.12.2011
 *      Author: ew08b033
 */

#ifndef SP_CHANNELS_H_
#define SP_CHANNELS_H_

#include "global.h"

/******************************************************************/

class handshake_generation_if: public sc_interface
{
public:
	virtual void notify() = 0;
	virtual void notify(sc_time t) = 0;
};

class handshake_event_if: public sc_interface
{
public:
	virtual const sc_event& default_event() const = 0;
};

class handshake
: public sc_prim_channel
, public handshake_generation_if
, public handshake_event_if
{
public:
	explicit handshake()
	: sc_prim_channel( sc_gen_unique_name("handshake"))
	{}

	explicit handshake(sc_module_name nm)
	: sc_prim_channel (nm)
	{}

	void notify ()
	{
		e_handshake.notify();
	}

	void notify (sc_time t)
	{
		e_handshake.notify(t);
	}

	const sc_event& default_event() const
	{
		return e_handshake;
	}

private:
	sc_event e_handshake;

	// copy constructor
	handshake (const handshake& rhs)
	{}
};

#endif /* SP_CHANNELS_H_ */
