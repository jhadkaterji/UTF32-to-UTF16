# UTF32-to-UTF16
This program reads a file containing UTF32 encodings, decodes to determine the Unicode Characters, and then writes the decoded characters to UTF-16

-Takes 2 args: name of input file as first, name of output file as second. -output file is written with the same endian-ness as the input file -program returns a status of -1 if an error is encountered; otherwise it will return a status of 0.
