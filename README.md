# Compress File
Use C language to compress file as .gz  

## Overview

- Language: C
- Compiler: GCC v13.1.0

## Run

### Generate exe
```
gcc compress-file.c compressor.c -o compress-file -lz
```


### Compress file

```
.\compress-file.exe {filePath} compressed-file.gz
```