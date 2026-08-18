# Modern C++ Tutorial — Reading Notes & Examples

This repository is my working notebook while reading **[_Modern C++ Tutorial: C++11/14/17/20 On the Fly_](https://github.com/changkun/modern-cpp-tutorial)** by **Changkun Ou (欧长坤)**. For each topic in the book I write a small, self-contained `.cpp` file that:

- restates the idea in my own words (as comments),
- shows the "before modern C++" way next to the "after" way where relevant, and
- exercises it in `main()` so it can actually be compiled and run, not just read.

> `modern-cpp.pdf` in this repo is my personal copy of the book, kept for offline reading while working through the examples. The book is distributed under the author's own license (CC BY-NC-ND) — if you fork or clone this repo, please get your own copy from the [official source](https://github.com/changkun/modern-cpp-tutorial) rather than relying on the PDF here, and don't use it commercially.

## Repository layout

Files are named `<chapter>-<section>-<topic>.cpp`, mirroring the book's own chapter/section numbering so a file and the pages it corresponds to are easy to match up. Within a section, files are plain kebab-case so they still sort alphabetically.

| # | File | Topic | What it covers |
|---|------|-------|-----------------|
| 1.1 | [01-1-deprecated-features.cpp](01-1-deprecated-features.cpp) | Deprecated features | Why assigning a string literal to `char*` is deprecated (use `const char*`), plus a peek at `std::ref` to capture an ostream by reference in a lambda. |
| 2.1 | [02-1-nullptr.cpp](02-1-nullptr.cpp) | `nullptr` vs `NULL` | Why `NULL` (usually `0` or `0L`) is a type-hazard in overload resolution, and how `nullptr` fixes it with its own type, `std::nullptr_t`. |
| 2.1 | [02-1-constexpr.cpp](02-1-constexpr.cpp) | `constexpr` | Compile-time vs run-time evaluation; `#define` vs `const` vs `constexpr`; recursive `constexpr` functions (Fibonacci); which array-size expressions the compiler accepts. |
| 2.2 | [02-2-if-with-initializer.cpp](02-2-if-with-initializer.cpp) | `if`/`for` with an initializer | The C++17 `if (init; condition)` form that scopes a temporary (e.g. an iterator) to the `if` statement instead of leaking it into the enclosing block. |
| 2.2 | [02-2-initializer-list.cpp](02-2-initializer-list.cpp) | `std::initializer_list` | How `{ ... }` construction works under the hood, constructor overload resolution between a normal constructor and an `initializer_list` one, why the elements are read-only, and why returning an `initializer_list` dangles. |
| 2.2 | [02-2-member-initializer-list.cpp](02-2-member-initializer-list.cpp) | Constructor member-initializer lists | Why `Ctor(...) : member(x) {}` is more efficient than assigning inside the constructor body, `const`/reference members that *require* it, base-class initialization order, and why member init order follows declaration order, not list order. |
| 2.2 | [02-2-structured-bindings.cpp](02-2-structured-bindings.cpp) | Structured bindings | Unpacking tuples, `pair`s, arrays, structs, and map entries into named variables with `auto [a, b] = ...`, plus the copy-vs-reference (`auto&`) and `const auto&` distinction. |
| 2.2 | [02-2-tuples.cpp](02-2-tuples.cpp) | `std::tuple` | When to reach for a `tuple` vs a named `struct`/`class`, `make_tuple`, `std::get`, `tuple_size`/`tuple_element`, lexicographic comparison, and nested tuples. |
| 2.3 | [02-3-type-inference.cpp](02-3-type-inference.cpp) | Type inference | `auto`, `decltype`, trailing return types (`auto f() -> decltype(...)`), `decltype(auto)`, and `auto` as a lambda parameter type. |
| 2.4 | [02-4-control-flow.cpp](02-4-control-flow.cpp) | Control flow | `if constexpr` for compile-time branch elimination in templates (and why it's needed, not just nice-to-have), plus range-based `for` with read-only vs. mutating access. |
| 2.5 | [02-5-templates-basics.cpp](02-5-templates-basics.cpp) | Templates: the basics | Function and class templates, template type deduction vs. explicit specification, multi-parameter templates, and where `vector`, `map`, smart pointers etc. fit in as templates themselves. |
| 2.5 | [02-5-extern-templates.cpp](02-5-extern-templates.cpp) | `extern template` | Why the same template instantiation (e.g. `square<int>`) gets compiled redundantly in every translation unit that uses it, and how `extern template` tells the compiler "someone else will instantiate this." |
| 2.5 | [02-5-alias-templates.cpp](02-5-alias-templates.cpp) | Alias templates | `typedef` vs the more readable `using`, function-pointer typedefs, and why `typedef` can't alias a template (only a concrete type) while `template<...> using X = ...` can. |
| 2.5 | [02-5-variadic-templates.cpp](02-5-variadic-templates.cpp) | Variadic templates | `Args...`, `sizeof...`, recursive parameter-pack expansion, C++17 fold expressions, non-type template parameters, and a first look at SFINAE / `enable_if` / concepts. |

## Building and running an example

Each file is standalone — no shared headers or build system needed. Compile any single example with:

```sh
g++ -std=c++20 -Wall -o /tmp/out 02-4-control-flow.cpp && /tmp/out
```

Use `-std=c++20` since a few examples use C++17/20 features (`if constexpr`, structured bindings, fold expressions, concepts syntax). Compiled binaries are intentionally left out of version control (see `.gitignore`) — build them locally as needed.

## Other files

- `playground.cpp` / `test.cpp` — scratch files for quick experiments, not tied to a specific chapter. Gitignored.
- `tempCodeRunnerFile.cpp` — a transient file the VSCode "Code Runner" extension writes on each run. Gitignored, safe to delete.

## Status

Currently through **Chapter 2 (Language Usability Enhancements)** of the book. More chapters (containers, smart pointers, regular expressions, parallelism, filesystem) will be added as I read further.
