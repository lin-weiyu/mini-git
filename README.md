# MiniGit

A simplified git implementation written in C++.

## Feature

- init
- add
- commit
- log
- checkout


## Build

### Requirements

- C++17
- CMake >= 3.10

```bash
mkdir build
cd build
cmake ..
make
```

## Usage

### init

```bash
./build/mini-git init
```

### add

```bash
./build/mini-git add <file>
```

### commit

```bash
./build/mini-git commit -m <message>
```

### log

```bash
./build/mini-git log
```

## project schedule

- complete init, add, commit, log and checkout feture
- the lack the github actions
- the program has not been properly encapsulated
- the first version can currently only manage files at the same level as .mygit using ./mini-git. It is not yet capable of managing directories and the files within them