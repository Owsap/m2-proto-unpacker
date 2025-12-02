# M2 Proto Unpacker
M2 Proto Unpacker is a standalone tool that loads binary **item_proto** and **mob_proto** files, optionally decrypts them using **[TEA]** (*Tiny Encryption Algorithm*), decompresses them with the **[Snappy]** codec, parses their internal structures, and exports the decoded data into human-readable `.txt` tables.

[TEA]: https://en.wikipedia.org/wiki/Tiny_Encryption_Algorithm
[Snappy]: https://en.wikipedia.org/wiki/Snappy_(compression)

---

## TEA Decryption (Optional)
If the input is encrypted, the tool decrypts it using user-provided keys from `tea-keys.json`.

Example template:
```json
{
	"item_proto": [],
	"mob_proto": []
}
```
You must insert your own TEA keys, none are provided with the tool.

## Supported Decompression
- Snappy

## Build Instructions
### Requirements
- C++20 compiler (MSVC)
- Visual Studio

### 3rd Party Libraries (included in vendor/)
- [neargye/magic_enum](https://github.com/Neargye/magic_enum)
- [google/snappy](https://github.com/google/snappy)
- [gabime/spdlog](https://github.com/gabime/spdlog)
- [nlohmann/json](https://github.com/nlohmann/json)

## Legal Notes
This project **does not** include:
- Game files
- Encryption keys
- Decompiled source code
- Proprietary assets

Users must provide data files and TEA keys.

Reverse-engineered file formats are used purely for interoperability.