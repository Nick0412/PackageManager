# PackageManager

// - Start Server
//   - Open socket on address and port
//   - start message handlers
// - Messages include
//   - Upload package and version
//     - Upload files including headers, static libs (.a), and/or shared libs (.so) [starting with just static libs to begin]
//   - Download package and version
// - Client
//   - Client creates local cache directories like (/Users/nick/.CppCache)
//   - Cache should have similar directories such as Include, Static Libraries, Shared Libs


include
  - a.h
  - b.h
  - 1.h
  - 2.h
static-lib
  - mylib.a

upload-library --package-name myPackage --version 2 --include /bla/include --static /bla/static-lib --shared /bla/shared-lib

(for all messages)
| Message Header | Message Contents | 

(Message Header, for all messages)
| Message Total Size | Message Type | Message Protocol Version |

(Upload Library Message v1)
Message Total Size                  4 Bytes 
Message Type (upload_library)       4 Bytes 
Message Protocol Version (v1)       4 Bytes 
Package Name Length                 4 Bytes
Package Name                        X Bytes
Version Number of Package (1)       4 Bytes 

Number of header files              4 Bytes (10)
Number of static lib files          4 Bytes 
Number of shared lib files          4 Bytes 

Header 1 Name Length                4 Bytes ("Bla/mycoolheader.h") -> (14)
Header 1 Name                       X Bytes (B, l, a, /, m, y, c, o, o, l ...)
Header 1 Size                       4 Bytes (40 KB)
Header 1                            X Bytes 

Static lib 1 Name Length                4 Bytes ("Bla/mycoolheader.h") -> (14)
Static lib 1 Name                       X Bytes (B, l, a, /, m, y, c, o, o, l ...)
Static lib 1 Size                       4 Bytes (40 KB)
Static lib 1                            X Bytes 

Static lib 2 Name Length                4 Bytes ("Bla/mycoolheader.h") -> (14)
Static lib 2 Name                       X Bytes (B, l, a, /, m, y, c, o, o, l ...)
Static lib 2 Size                       4 Bytes (40 KB)
Static lib 2                            X Bytes 

Shared lib 1 Name Length                4 Bytes ("Bla/mycoolheader.h") -> (14)
Shared lib 1 Name                       X Bytes (B, l, a, /, m, y, c, o, o, l ...)
Shared lib 1 Size                       4 Bytes (40 KB)
Shared lib 1                            X Bytes 


(Download Library Message)

(List Packages)

(Describe Package)

Describe

CRUDL

