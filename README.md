# Minishell

A fully-functional Unix shell implementation developed as a collaborative software engineering project. This project demonstrates proficiency in systems programming, process management, and software development best practices.

**Score: 100/100** | **42 Core Curriculum**

## Overview

Minishell is a bash-compatible shell written in C that implements core shell functionality including command parsing and execution, built-in commands, redirections, pipes, and environment variable expansion. The project provides hands-on experience with essential systems programming concepts including process forking, file descriptors, and inter-process communication.

## Key Features

- **Command Execution**: Execute external programs and built-in commands with proper argument parsing
- **Built-in Commands**: Implemented `cd`, `echo`, `env`, `export`, `unset`, `pwd`, and `exit`
- **I/O Redirections**: Full support for input/output redirection operators (`>`, `>>`, `<`)
- **Pipes**: Execute multiple commands in sequence with pipeline operators (`|`)
- **Heredoc Support**: Implement `<<` operator for multi-line input
- **Environment Variables**: Full variable expansion and substitution
- **Quote Handling**: Proper management of single and double quotes with special character escaping
- **Signal Handling**: Clean handling of interrupt signals (SIGINT, SIGQUIT)

## Technical Highlights

- **Language**: C (POSIX-compliant)
- **Architecture**: Modular design with separate subsystems for parsing, execution, and utility functions
- **Parser**: Custom lexer and recursive descent parser for tokenization and AST construction
- **Process Management**: Fork/exec model with proper file descriptor manipulation
- **Memory Management**: Careful attention to dynamic memory allocation and cleanup

## Project Structure

```
minishell/
├── src/
│   ├── parsing/          # Lexer, parser, and quote/redirection handling
│   ├── exec/             # Command execution, path resolution, heredoc
│   ├── builtin/          # Built-in command implementations
│   ├── error_and_clean/  # Error handling and memory cleanup
│   └── utils/            # Helper utilities and data structures
├── includes/
│   └── minishell.h       # Main header with data structures
└── Makefile              # Build configuration
```

## Building & Running

### Prerequisites
- GCC compiler
- Make
- Standard C library (libc)

### Build
```bash
make                # Compile the project
make clean          # Remove object files
make fclean         # Remove all generated files
```

### Run
```bash
./minishell         # Start the interactive shell
```

## Development Approach

This project was developed using structured collaboration:

- **Agile Methodology**: Task-based development with Trello for project management
- **Separation of Concerns**: One developer focused on the parsing pipeline while the other owned the execution engine
- **Iterative Development**: Each feature was fully tested before moving to the next
- **Version Control**: Professional git workflow with meaningful commit messages
- **Code Quality**: Comprehensive testing, error handling, and edge case validation

## Key Learnings

Through this project, I deepened my understanding of:

- **Systems Programming**: Process management, file descriptors, and signal handling
- **Software Architecture**: Modular design patterns and separation of concerns
- **Collaboration**: Effective communication, code review, and git-based workflows
- **Low-level I/O**: Pipe operations, redirections, and file descriptor manipulation
- **Memory Safety**: Leak detection, proper cleanup, and resource management
- **Parser Design**: Tokenization, syntax analysis, and error recovery

## Testing

The project has been thoroughly tested against Bash functionality. Reference testing framework:
- [minishell_tester](https://github.com/LucasKuhn/minishell_tester) - Comprehensive test suite

## Resources

- [Shell Program Explained](https://www.youtube.com/watch?v=ubt-UjcQUYg&ab_channel=hhp3) - Excellent systems programming overview
- 42 School Curriculum

## License

This project is part of the 42 School curriculum. All work is original and collaboratively developed.
