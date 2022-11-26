# shelf

## Usage

```bash
# Create new scrathcpad
$ echo "Hello, World!" | shelf new hello

# Show scratchpad contents
$ shelf show hello
Hello, World!

# Edit scratchpad using preffered editor
# launches the program EDITOR env var is set to, if not set, VISUAL is used
$ shelf edit hello

# List scratchpads
$ shelf list
hello

# Remove scratchpad
$ shelf remove hello
```

## Building

clone repository

```bash
git clone https://github.com/adamjedrzejewski/shelf
```

build using make

```bash
make
```

## TODOs

- error handling
- refactoring
- multiuser support
- shelf remove should be able to remove multiple scratchpads (with globing or listing multiple at a time)
