# Basic Statistics Calculator — Multi-Paradigm Implementation

A basic statistics calculator that computes **mean**, **median**, and **mode** for a list of integers, implemented in three languages across three programming paradigms.

| Language | Paradigm | Folder |
|----------|----------|--------|
| C | Procedural | `c/` |
| OCaml | Functional | `ocaml/` |
| Python | Object-Oriented | `python/` |

---

## Features

- Calculates mean, median, and mode for any list of integers
- Handles multiple modes (bimodal, trimodal, etc.)
- Detects when all values appear equally (no dominant mode)
- Accepts integers separated by spaces or newlines
- Input validation and error handling in all three implementations

---

## Project Structure

```
.
├── c/
│   ├── stats.c          # C procedural implementation
│   └── Makefile         # Build system for C
├── ocaml/
│   ├── stats.ml         # OCaml functional implementation
│   └── Makefile         # Build system for OCaml
├── python/
│   ├── stats.py         # Python OOP implementation
│   └── Makefile         # Build system for Python
└── README.md            # This file
```

---

## Required Software

Before building or running any of the programs, make sure the following tools are installed.

### C — GCC

- **Linux (Debian/Ubuntu):**
  ```bash
  sudo apt update && sudo apt install gcc make
  ```
- **macOS:** Install via Xcode Command Line Tools:
  ```bash
  xcode-select --install
  ```
- **Windows:** Install [MinGW-w64](https://www.mingw-w64.org/) or use [WSL](https://learn.microsoft.com/en-us/windows/wsl/).
- **Verify:**
  ```bash
  gcc --version
  ```

### OCaml — OCaml Compiler

Both `ocamlopt` (native) and `ocamlc` (bytecode) are used by the Makefile.

- **Linux (Debian/Ubuntu):**
  ```bash
  sudo apt update && sudo apt install ocaml make
  ```
- **macOS (via Homebrew):**
  ```bash
  brew install ocaml
  ```
- **Windows:** Use the [OCaml for Windows installer](https://fdopen.github.io/opam-repository-mingw/) or WSL.
- **Verify:**
  ```bash
  ocamlopt --version && ocamlc --version
  ```

### Python — Python 3

Python 3.7 or higher is required. No third-party packages are needed — only the standard library (`collections` module).

- **Linux (Debian/Ubuntu):**
  ```bash
  sudo apt update && sudo apt install python3
  ```
- **macOS (via Homebrew):**
  ```bash
  brew install python3
  ```
- **Windows:** Download from [python.org](https://www.python.org/downloads/).
- **Verify:**
  ```bash
  python3 --version
  ```

---

## Build & Run

Each language has its own subfolder with its own Makefile. `cd` into the folder first, then use `make`.

---

### C — `c/`

```bash
cd c
```

| Command | Description |
|---------|-------------|
| `make` or `make all` | Compile `stats.c` into the `stats` executable |
| `make run` | Compile (if needed) and run interactively |
| `make test` | Run automated test with input `1 3 2 3 4` (n=5) |
| `make clean` | Remove the compiled `stats` binary |

**Manually (without make):**
```bash
gcc -std=c11 -Wall -Wextra -pedantic -o stats stats.c
./stats
```

---

### OCaml — `ocaml/`

```bash
cd ocaml
```

| Command | Description |
|---------|-------------|
| `make` or `make all` | Compile `stats.ml` to a native executable (`stats.native`) |
| `make native` | Same as above — explicitly build the native binary |
| `make byte` | Compile to a bytecode executable (`stats.byte`) instead |
| `make run` | Compile (if needed) and run the native executable interactively |
| `make test` | Run automated test with input `1 3 2 3 4` (n=5) |
| `make clean` | Remove all compiled files (`*.native`, `*.byte`, `*.cmi`, `*.cmo`, `*.cmx`, `*.o`) |

**Manually (without make):**
```bash
# Native (faster, recommended)
ocamlopt -o stats.native stats.ml
./stats.native

# Bytecode (more portable)
ocamlc -o stats.byte stats.ml
./stats.byte
```

---

### Python — `python/`

```bash
cd python
```

| Command | Description |
|---------|-------------|
| `make run` | Run `stats.py` with `python3` |
| `make test` | Run automated test with input `1 3 2 3 4` (n=5) |

> Python has no compilation step, so there is no `make all` or `make clean` target.

**Manually (without make):**
```bash
python3 stats.py
```

---

## Usage

All three programs follow the same interactive flow:

```
Enter the number of integers: 6
Enter 6 integers separated by spaces or newlines:
4 1 2 2 3 3

=== Results ===
Original numbers: 4 1 2 2 3 3
Mean:   2.50
Median: 2.50
Mode:   2 3
```

Numbers can be entered all on one line or spread across multiple lines — all three implementations accept both formats.

---

## Paradigm Highlights

### C — Procedural
- Functions operate on raw integer arrays passed as pointers
- Manual memory management: every `malloc` has a matching `free`
- Sorting is done on a copied buffer to preserve the original input
- `qsort` with a custom comparator handles ordering

### OCaml — Functional
- No mutable state anywhere — all transformations return new lists
- `List.fold_left`, `List.filter`, and `List.map` drive all calculations
- The `|>` pipe operator chains operations without temporary variables
- All I/O uses `input_line` exclusively to avoid Scanf buffer conflicts

### Python — Object-Oriented
- `StatisticsCalculator` class encapsulates data and all statistical methods
- `sorted()` is non-destructive; `collections.Counter` handles frequencies
- `display()` composes output from the class's own methods
- Input parsing is isolated in a standalone `get_user_input()` function

---

## Error Handling

All implementations handle:
- Non-integer input
- Count ≤ 0
- Count > 1,000,000
- Insufficient numbers provided

---

## License

This project was created for educational purposes.
