#include "./include/uapi/verb.h"
#include <nd/nd.h>

// TODO change this module's name to "verb"

SIC_DEF(int, verb, unsigned, player_ref,
		unsigned, wt, char *, extra);

SIC_DEF(int, verb_to, unsigned, player_ref,
		unsigned, target_ref, unsigned, wt,
		char *, extra);

int
verb(unsigned player_ref, unsigned wt, char *extra) {
	OBJ player;
	char wts[BUFSIZ], *wts_plural;

	nd_get(HD_OBJ, &player, &player_ref);
	nd_get(HD_WTS, wts, &wt);

	nd_writef(player_ref, "You %s%s\n", wts, extra);

	wts_plural = plural(wts);
	nd_owritef(player_ref, "%s %s%s\n", player.name, wts_plural, extra);
	return 0;
}

int
verb_to(unsigned player_ref, unsigned target_ref, unsigned wt, char *extra) {
	char buf[BUFSIZ * 3];
	unsigned tmp_ref;
	OBJ player, target;
	nd_cur_t c;
	size_t len;
	char wts[BUFSIZ], *wts_plural;

	nd_get(HD_OBJ, &player, &player_ref);
	nd_get(HD_OBJ, &target, &target_ref);
	nd_get(HD_WTS, wts, &wt);

	nd_writef(player_ref, "You %s %s%s\n", wts, target.name, extra);

	wts_plural = plural(wts);
	len = snprintf(buf, sizeof(buf), "%s %s %s%s\n", player.name, wts_plural, target.name, extra);

	char posessive[BUFSIZ];
	*posessive = '\0';

	if (extra[0] == '\'' && extra[1] == 's') {
		snprintf(posessive, sizeof(posessive), "%s%s",
				"r", extra + 2);
		extra = posessive;
	}

	nd_writef(target_ref, "%s %s you%s\n", player.name, wts_plural, extra);

	c = nd_iter(HD_CONTENTS, &player.location);

	while (nd_next(&player.location, &tmp_ref, &c)) {
		OBJ tmp;

		if (tmp_ref == player_ref || tmp_ref == target_ref)
			continue;

		nd_get(HD_OBJ, &tmp, &tmp_ref);
		if (tmp.flags != OF_PLAYER)
			nd_write(tmp_ref, buf, len);
	}

	return 0;
}

void mod_install(void *arg __attribute__((unused))) {
#if 0
	nd_put(HD_WTS, NULL, "peck");
	nd_put(HD_WTS, NULL, "slash");
	nd_put(HD_WTS, NULL, "bite");

	/* PHYSICAL things combined with special effects */
	nd_put(HD_WTS, NULL, "heal");
	nd_put(HD_WTS, NULL, "bleed");
	nd_put(HD_WTS, NULL, "haste");
	nd_put(HD_WTS, NULL, "stun");
	nd_put(HD_WTS, NULL, "leer");
	nd_put(HD_WTS, NULL, "focus");
	nd_put(HD_WTS, NULL, "distract");
	nd_put(HD_WTS, NULL, "evade");
	nd_put(HD_WTS, NULL, "hobble");
#endif
}
