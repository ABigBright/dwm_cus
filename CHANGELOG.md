# Changelog

## 2026-06-04

### Bug Fix
- **pertag curtag UB crash**: Fixed undefined behavior in `toggleview()` that
  caused dwm to crash after prolonged use of `Mod+0` (view all tags).
  When `curtag == 0` (the "all tags viewed" state), the expression
  `1 << (curtag - 1)` evaluates to `1 << -1`, which is undefined behavior
  in C (shifting by a negative amount). This UB could corrupt memory over
  time and eventually crash the window manager.
  Fix: check `curtag == 0` before the shift, using short-circuit `||` to
  ensure the UB expression is never evaluated when `curtag` is zero.
  When `curtag == 0`, the code finds the lowest set bit in `newtagset` and
  sets `curtag` to the corresponding tag index (1-9).