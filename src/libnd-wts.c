/* main.c — nd-wts, ported to libxylem.
 *
 * Registers the weapon/special-effect ("what") vocabulary the fight system
 * looks words up by. It implements no events at all: this module exists only
 * to populate a table, so it is the smallest complete port in the tree and
 * doubles as the test that `xy_install` runs and `nd_put(HD_*, NULL, ...)`
 * survives the bus. (MODS.md §7, Wave 1.)
 *
 * The original was 513 bytes of `mod_install` and nothing else. There was no
 * `mod_open`, so there is no second entry point to collapse, and no handler
 * means no `XY_IMPL` and no `include/nd/wts.h`.
 */

#include <ttypt/xy-mod.h>

#include <nd/xy.h>

static unsigned last_n;

static int
wts_row(const char *const *f, size_t n, void *user)
{
	(void)user;
	if (n < 1 || !f[0][0])
		return 0;
	last_n = (unsigned)nd_put(HD_WTS, NULL, (void *)f[0]);
	return 0;
}

XY_MODULE_API void
xy_install(void)
{
	if (nd_table_load("nd-wts", "wts", wts_row, NULL) < 0) {
		nd_put(HD_WTS, NULL, "peck");
		nd_put(HD_WTS, NULL, "slash");
		nd_put(HD_WTS, NULL, "bite");
		nd_put(HD_WTS, NULL, "heal");
		nd_put(HD_WTS, NULL, "bleed");
		nd_put(HD_WTS, NULL, "haste");
		nd_put(HD_WTS, NULL, "stun");
		nd_put(HD_WTS, NULL, "leer");
		nd_put(HD_WTS, NULL, "focus");
		nd_put(HD_WTS, NULL, "distract");
		nd_put(HD_WTS, NULL, "evade");
		last_n = (unsigned)nd_put(HD_WTS, NULL, "hobble");
	}

	WARN("nd-wts: xy_install, HD_WTS words loaded, last index %u\n", last_n);
}
