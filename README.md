# axil-nd-wts

`nd-wts` for [axil-nd](../axil-nd), ported from SIC to libxylem.

Registers the weapon/special-effect ("what") vocabulary that the fight system
looks words up by. It implements no events at all — this module exists only to
populate a table, so it is the smallest complete port in the tree and doubles as
the test that `xy_install` runs and `nd_put(HD_*, NULL, ...)` survives the bus.

## Install

```sh
make install
```

Installs one file:

```
lib/libnd-wts.so
```

There is deliberately no `lib/nd-wts.so` symlink. `xy_load()` appends `.so`
itself and does not retry with a `lib` prefix, so the engine's `mods.load` names
this module `libnd-wts` and `dlopen`s `libnd-wts.so`. A soname symlink would also
have been silently dropped from the OpenBSD package: `tty-pt/ci` builds the
packing list from `find usr -type f`, which never lists a symlink, so the package
would have shipped the library under one name and asked the loader for another.

Also packaged for deb, apk, rpm, brew and openbsd from a `v*` tag.

It installs no header because it exports no API — every symbol it defines is
discovered by the engine, not called by another module.

## Build from source

```sh
make
```

Needs [libxylem](https://github.com/tty-pt/libxylem) (headers already in
`$(PREFIX)/include`) and the engine's game API, `<nd/xy.h>`, from either an
`axil-nd` checkout beside this repo or an installed `axil-nd`:

```sh
git clone https://github.com/tty-pt/nd-wts && cd nd-wts
git clone https://github.com/tty-pt/axil-nd ../axil-nd
make
```

`<nd/xy.h>` installs to `$(PREFIX)/include/nd/`, the same directory that already
carries `<ttypt/xy.h>`, so an **installed** engine needs no `-I` of its own here.
Against a checkout beside this repo it is `-I../axil-nd/include`; both paths are
on `CFLAGS` at once and a missing `-I` is ignored, so the same command works
either way.

## What it does

* `xy_install()` registers 11 `HD_WTS` words: three physical attacks (`peck`,
  `slash`, `bite`) and eight special effects (`heal`, `bleed`, `haste`, `stun`,
  `leer`, `focus`, `distract`, `evade`, `hobble`).
* It reports the index returned by the last `nd_put`. `nd_put` returns the new
  entry's index, so logging it proves the registrations actually landed in the
  engine's table rather than being accepted and dropped — which is the whole
  content of this module, and all a test can observe from outside it.

## Testing

There is no `test.sh` here. Behaviour is asserted by the engine's own suite,
which builds every module in its `mods.load`, boots, and greps stderr:

```sh
cd ../axil-nd
make && ./test.sh
```

nd-wts is not yet in the engine's `mods.load` (MODS.md §9 records it as ported
but neither loaded nor asserted), so no suite assertion covers it yet. Its
`xy_install` logs `nd-wts: xy_install, 11 HD_WTS words, last index %u`, which is
the line such an assertion would grep for.

## Notes from the port

* **The include changed spelling.** It was `"papi/nd-xy.h"`, a file that no
  longer exists in any checkout: the engine moved its module-facing tree from
  `papi/` to `nd/`, and `papi/` now holds only `nd.h`. The module could not
  compile until this was fixed.
* `mod_install` and `mod_open` collapsed into one `xy_install`. The original was
  513 bytes of `mod_install` and nothing else; there was no `mod_open`, so there
  is no second entry point to collapse.
* No `XY_IMPL` and no `include/nd/wts.h`, because no handler means nothing for a
  consumer to declare.

## License

BSD 2-Clause, carried over from `tty-pt/nd-wts`. See `LICENSE`.
