# M2 Proto Unpacker
M2 Proto Unpacker is a standalone tool that loads binary **item_proto** and **mob_proto** files, optionally decrypts them using **[TEA]** (*Tiny Encryption Algorithm*),
decompresses them with **[Snappy]** or **[LZO]** codec, parses their internal structures, and exports the decoded data into `.txt` tables.

---

## Features
- Load and decode `item_proto` and `mob_proto` binary files
- Optional **[TEA]** decryption via `tea-keys.json`
- **[Snappy]** and **[LZO]** decompression
- Export decoded data to `.txt` tables
- Optional `mob_proto` overwrite system using a reference **[TSV]** (*tab-separated values*) file
- Flexible **[CLI]** with verbosity, silent mode, and custom paths

---

## TEA Decryption (Optional)
If the input files are encrypted, the tool decrypts them using user-provided TEA keys from `tea-keys.json`.

Example template:
```json
{
	"item_proto": [],
	"mob_proto": []
}
```
> ⚠️ You must insert your own TEA keys, none are provided with the tool.

---

## Supported Decompressions
- **[Snappy]**
- **[LZO]**

---

## Proto Reference Overwrite
The tool supports **overwriting** specific **fields** at dump time using a tab-separated reference file (`.txt`).

This is useful for:
- Restoring values from another proto version.
- Applying batch fixes (gold, skills, folder, etc.)
- Merging data from spreadsheets or Excel exports.

> ⚠️ This feature is currently available **only for** `mob_proto`

### Supported Fields (Reference File)
The reference table may include:
- `Folder`
- `MinGold`, `MaxGold`
- `ResurrectionVnum`
- `PolymorphItem`
- Skill levels and vnums
- Special points (berserk, stoneskin, etc.)
- `HitRange`

Only fields present in the reference file are applied. All other values remain unchanged.

### Usage
`m2-proto-unpacker --overwrite-mob-proto`
> You may also specify a custom reference file.

### Notes
- The reference file must be **tab-separated**.
- The overwrite is applied **only during dumping**, original binaries are not modified

---

## Command Line Usage
`m2-proto-unpacker [options]`

### Common Defaults
If no arguments are provided, the tool searches the current directory for:
```
item_proto
mob_proto
tea-keys.json
```

### CLI Options
| Option                         | Description                                                                                                         |
|--------------------------------|---------------------------------------------------------------------------------------------------------------------|
| `--item_proto [path]`          | Directory or full path to `item_proto`                                                                              |
| `--mob_proto [path]`           | Directory or full path to `mob_proto`                                                                               |
| `--keys [path]`                | Path to `tea-keys.json`                                                                                             |
| `--out [path]`                 | Output directory for dumped `.txt` files                                                                            |
| `--overwrite-mob-proto [path]` | Enable `mob_proto` overwrite using reference table. If `[path]` is omitted, `mob_proto_ref.txt` is used by default. |
| `--verbose`                    | Enable detailed debug logging                                                                                       |
| `--silent`                     | Only show errors                                                                                                    |
| `--help`                       | Show help                                                                                                           |
| `--version`                    | Show version                                                                                                        |

---

## Requirements
- C++20 Compiler
- MSVC (Visual Studio)

---

## Third-Party Libraries (included in vendor/)
- [neargye/magic_enum](https://github.com/Neargye/magic_enum)
- [google/snappy](https://github.com/google/snappy)
- [google/lzo](https://www.oberhumer.com/opensource/lzo/)
- [gabime/spdlog](https://github.com/gabime/spdlog)
- [nlohmann/json](https://github.com/nlohmann/json)
- [vincentlaucsb/csv-parser](https://github.com/vincentlaucsb/csv-parser)

---

## Legal Notes
This project **does not include**:
- Game files.
- Encryption keys.
- Decompiled source code.
- Proprietary assets.

Users must provide data files and TEA keys.  
Reverse-engineered file formats are used purely for interoperability.

[TEA]: https://en.wikipedia.org/wiki/Tiny_Encryption_Algorithm
[Snappy]: https://en.wikipedia.org/wiki/Snappy_(compression)
[LZO]: https://en.wikipedia.org/wiki/Lempel%E2%80%93Ziv%E2%80%93Oberhumer
[CLI]: https://en.wikipedia.org/wiki/Command-line_interface
[TSV]: https://en.wikipedia.org/wiki/Tab-separated_values