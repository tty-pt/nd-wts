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

XY_MODULE_API void
xy_install(void)
{
	/* nd_put returns the new entry's index, so reporting the last one proves
	 * the registrations actually landed in the engine's table rather than
	 * being accepted and dropped -- which is the whole content of this
	 * module, and all a test can observe from outside it. */
	unsigned n;
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
	n = nd_put(HD_WTS, NULL, "hobble");

	WARN("nd-wts: xy_install, 11 HD_WTS words, last index %u\n", n);
}
