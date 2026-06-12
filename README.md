# DiamondGrid Cryptography System

A C++ command-line application that implements a unique encryption and decryption algorithm using multi-round grid-based transpositions and diamond patterns.

## Overview

The DiamondGrid Cryptography System obscures messages by embedding them into a dynamically generated 2D grid using a diamond-shaped coordinate pattern. The grid is then filled with random padding characters and transposed (read column-by-column) to generate the final encrypted string. To enhance security, the system supports multi-round encryption, where the output of one round is used as the input for the next, with deterministic but round-unique seeding.

## Features

- **Diamond Pattern Embedding**: Messages are inserted into a calculated diamond shape within a square grid, obscuring the message structure.
- **Multi-Round Encryption**: Apply the encryption algorithm multiple times for exponentially increased security.
- **Deterministic Seeding**: Uses a base seed combined with the round number to ensure permutations are securely reproducible during decryption.
- **Automatic Padding & Trimming**: Automatically pads messages with random characters and correctly trims the padding upon final decryption.

## Project Structure

- `main.cpp` - Application entry point.
- `cipher.cpp` / `.hpp` - Manages the multi-round encryption and decryption lifecycle.
- `cryptogrid.cpp` / `.hpp` - Handles the 2D grid logic, embedding the message, filling noise, and transposing the grid.
- `diamondgrid.cpp` / `.hpp` - Generates the mathematical diamond pattern coordinates based on message size.
- `menuhandler.cpp` / `.hpp` - Provides the interactive CLI menu for user input and workflow control.
- `utils.cpp` / `.hpp` - Helper utilities for input validation.

## How It Works

### Encryption
1. **Calculate Size**: The system calculates the minimum square grid size required to hold the message in a diamond pattern.
2. **Generate Diamond**: Generates diamond coordinate points.
3. **Embed & Pad**: The message is placed at the diamond coordinates. Remaining cells are filled with pseudo-random uppercase characters.
4. **Transpose**: The grid is serialized column-by-column, transforming rows into columns to scramble the original characters.
5. **Rounds**: This process repeats for the specified number of rounds.

### Decryption
1. **Reconstruct**: Calculates grid dimensions from the encrypted string's length.
2. **Reverse Transpose**: Fills the grid column-by-column.
3. **Extract Diamond**: Extracts the characters located at the diamond coordinates.
4. **Trim**: On the final decryption round, any padding (indicated by a `.` character in standard use) is stripped to reveal the original message.
