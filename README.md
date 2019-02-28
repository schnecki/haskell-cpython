# Haskell CPython C bindings

[![Build status][travis-img]][travis]

Haskell package for a batteries-included python interface. Your point of entry
for integrating your existing python infrastructure into your future haskell
infrastructure.

## Quick start
### Using this package
In your stack project using the `lts-13.8` resolver, add `cpython` to the list
of dependencies under the line `- base >= 4.7 && < 5` in `package.yaml` in the
`dependencies` section.

In your source code, add `import qualified CPython as Py` to the imports
section.

### Developing this package
1. Install [Haskell](haskell)
2. Install [Stack](stack)
3. Git clone this repository
4. `cd haskell-cpython && stack build`
5. ???
6. Profit

[haskell]:     https://www.haskell.org/platform/
[stack]:       https://docs.haskellstack.org/en/stable/README/#how-to-install
[travis]:      https://travis-ci.org/zsedem/haskell-cpython
[travis-img]:  https://travis-ci.org/zsedem/haskell-cpython.svg?branch=3.7
