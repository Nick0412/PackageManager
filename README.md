# C++ Package Manager

This is a package manager for managing packages in C++.

## APIs

We support five different APIs: `CreatePackage`, `InstallPackage`, `UninstallPackage`, `DescribePackage`, and `ListPackages`.

For each API, we have a different message type. Each message type has a different format for the message contents but the message header is the same.

| Field                    | Size    | Example |
| ------------------------ | ------- | ------- |
| Message Size             | 4 Bytes | 303 KB  |
| Message Type             | 4 Bytes | create  |
| Message Protocol Version | 4 Bytes | v1      |

For the sample messages, we assume we have the following directory structure.

```txt
- include
  - foo.h
  - bar.h
- static-lib
  - mystatic.a
- shared-lib
  - myshared.so
```

### CreatePackage

```term
$ cpm create \
  --package-name <my_package_name> \
  --package-version <my_package_version> \
  --include-dir <my_include_dir> \
  --static-dir <my_static_dir> \
  --shared-dir <my_shared_dir>
```

| Field                    | Size    | Example     |
| ------------------------ | ------- | ----------- |
| Package Name Length      | 4 Bytes | 23          |
| Package Name             | ? Bytes | myPackage   |
| Package Version          | 4 Bytes | 1.1         |
|                          |         |             |
| # Header Files           | 4 Bytes | 2           |
| # Static Lib Files       | 4 Bytes | 1           |
| # Shared Lib Files       | 4 Bytes | 1           |
|                          |         |             |
| Header 1 Name Length     | 4 Bytes | 5           |
| Header 1 Name            | ? Bytes | foo.h       |
| Header 1 Size            | 4 Bytes | 40 KB       |
| Header 1 Contents        | ? Bytes |             |
|                          |         |             |
| Header 2 Name Length     | 4 Bytes | 5           |
| Header 2 Name            | ? Bytes | bar.h       |
| Header 2 Size            | 4 Bytes | 72 KB       |
| Header 2 Contents        | ? Bytes |             |
|                          |         |             |
| Static Lib 1 Name Length | 4 Bytes | 10          |
| Static Lib 1 Name        | ? Bytes | mystatic.a  |
| Static Lib 1 Size        | 4 Bytes | 95 KB       |
| Static Lib 1 Contents    | ? Bytes |             |
|                          |         |             |
| Shared Lib 1 Name Length | 4 Bytes | 11          |
| Shared Lib 1 Name        | ? Bytes | myshared.so |
| Shared Lib 1 Size        | 4 Bytes | 66 KB       |
| Shared Lib 1 Contents    | ? Bytes |             |

### InstallPackage

```term
$ cpm install \
  --package-name <my_package_name> \
  --package-version <my_package_version>
```

| Field                    | Size    | Example     |
| ------------------------ | ------- | ----------- |
| Package Name Length      | 4 Bytes | 23          |
| Package Name             | ? Bytes | myPackage   |
| Package Version          | 4 Bytes | 1.1         |

### UninstallPackage

```term
$ cpm uninstall \
  --package-name <my_package_name> \
  --package-version <my_package_version>
```

| Field                    | Size    | Example     |
| ------------------------ | ------- | ----------- |
| Package Name Length      | 4 Bytes | 23          |
| Package Name             | ? Bytes | myPackage   |
| Package Version          | 4 Bytes | 1.1         |

### DescribePackage

```term
$ cpm info \
  --package-name <my_package_name>
```

| Field                    | Size    | Example     |
| ------------------------ | ------- | ----------- |
| Package Name Length      | 4 Bytes | 23          |
| Package Name             | ? Bytes | myPackage   |
| Package Version          | 4 Bytes | 1.1         |

### ListPackages

```term
$ cpm list
```

There are no additional message contents for this API.

## Notes

- Start server
  - Open socket on address and port
  - Start message handlers
- Messages include
  - Upload package and version
    - Upload files including headers, static libs (.a), and/or shared libs (.so)
      - Starting with just static libs to begin
  - Download package and version
- Client
  - Client creates local cache directories like (/Users/nick/.CppCache)
  - Cache should have similar directories e.g. include, static libs, shared libs
