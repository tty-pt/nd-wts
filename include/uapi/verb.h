#ifndef WTS_H
#define WTS_H

#include <stdarg.h>

#include <nd/type.h>

SIC_DECL(int, verb, unsigned, player_ref,
		unsigned, wt, char *, extra);

SIC_DECL(int, verb_to, unsigned, player_ref,
		unsigned, target_ref, unsigned, wt,
		char *, extra);

#endif
