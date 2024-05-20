<div align="center">
  <h1><code>Discord Token and MFA Finder</code></h1>
  <p>This Rust script searches for tokens and MFA keys for Discord app in specific directories based on the operating system. It scans files with .log and .ldb extensions within these directories and extracts tokens matching certain regular expressions.</p>
</div>

---

## Installation

To run the script, you need to have Rust installed. Then, you can add the required dependencies and run the script with the following commands:

```bash
cargo add regex
cargo run
```

---

## How It Works

The script performs the following steps:

1. Detect Operating System:

It determines the operating system using `std::env::consts::OS`.

2. Generate Target Directories:

Based on the detected operating system, it generates a list of directories to be searched. These directories include potential paths where applications like Discord, Google Chrome, Opera, Brave, Yandex, and others store their data.

3. Append leveldb Path:

It appends `/Local Storage/leveldb` to each target directory path to focus on the specific subdirectories where the tokens and MFA keys might be stored.

4. Compile Regular Expressions:

It compiles two regular expressions:

- `token_regex`: Matches tokens in the format `xxxxxxxxxxxxxxxxxxxxxx.xxxxxx.xxxxxxxxxxxxxxxxxxxxxxxxxxx`.
- `mfa_regex`: Matches MFA keys in the format `mfa.xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx`.

5. Search and Extract Tokens:

It iterates over each target directory, checking if the directory exists.
For each file in the directory with a `.log` or `.ldb` extension, it reads the file content and searches for tokens and MFA keys using the compiled regular expressions.
It accumulates the found tokens and MFA keys.

6. Output Results:

It prints the found tokens and MFA keys to the console.

---

## Detailed Code Explanation

- `has_ending`: Checks if a string ends with a given substring.
- `path_exists`: Checks if a given path exists.
- `search_tokens`: Reads a file and searches for matches to a given regular expression, returning the matches.
- `grab_path`: Generates a list of potential directories to search based on the operating system.
- `main`: The entry point of the script. It orchestrates the entire process of path generation, file scanning, token extraction, and result output.

---

## Example Output

The script outputs the found tokens and MFA keys, color-coded for readability:

```bash
Operating System detected: linux
Looking for tokens in: /home/.discord/Local Storage/leveldb
Tokens found:
abcdefghijklmnopqrstuvwxyz.xxxxxx.yyyyyyyyyyyyyyyyyyyyyyyyyyyyy
MFA found:
mfa.xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
```
