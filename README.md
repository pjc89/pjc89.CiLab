# cilab

Lab repo for GitHub Actions cache settings. It mirrors the DocSynth CI
mechanics on a build that takes minutes, not an hour.

## The design under test

- `deps.yml` is the only workflow that saves the vcpkg binary cache.
  It runs on `main` only. Actions caches saved on the default branch are
  restorable from every branch, tag and PR. Caches saved on a tag are
  restorable from that tag only (this scoping caused the cold runs).
- `ci.yml` and `release.yml` restore the cache and never save it.
  `fail-on-cache-miss: true` makes a cold run fail in seconds instead of
  compiling dependencies from source.
- Every job has `timeout-minutes` as a hard backstop.

## Test matrix

| # | Action | Expected |
|---|--------|----------|
| A | dispatch `deps.yml` on main | builds zlib, saves main-scoped cache |
| B | push a commit to main | `ci` restores the cache, no compile |
| C | push tag `v0.0.1` | `release` restores the main-scoped cache |
| D | delete all caches, push tag `v0.0.2` | `release` fails in seconds (guard works) |
| E | dispatch `deps.yml`, re-run the failed release | restore hits, run goes green |

## Recovery rule

If `ci` or `release` fails at the restore step: `gh workflow run deps.yml`,
wait for green, re-run the failed run.

Gate B: cache-hit push test.
