Format of Obfuscator Files

The Obfuscator file format consists generally of metadata and content
or payload data.  Metadata are information about the encoding or about
the content.  In unciphered form, metadata are of fixed size, while
content data are of variable size.  The obfuscator cipher can produce
variably-sized output from fixed-size input, so in an obfuscated data
stream, metadata may be either of fixed size or of variable size.

Data, whether metadata or payload data, are obfuscated by encoding the
data on a bit-by-bit basis as the case of an alphabetic character.
Lower case corresponds to a binary zero (0), while upper case
corresponds to a binary one (1).  Data are encoded four bits at a
time, into alphabetic characters.  Characters in the obfuscated output
are grouped into words, with words separated by whitespace (tab 0x09
'\t', space 0x20 ' ', newline 0x0a '\n').  Each word of obfuscated
output encodes at most one four-bit nibble of data.  Punctuation does
not divide words; only whitespace divides words.

In the obfuscated data stream, words which have fewer than four
characters do not encode data.  For example, none of "a", "the", "an",
"and", "her", or "his" encode data.  Words which have four or more
characters, but for which fewer than four characters are capable of
case variation, do not encode data.  For example, none of "_one",
"tw_o", "ma-n", "dog_", "h.e-", or "-she" encode data.  Words which
have at least four characters that are capable of case variation
encode data in the first four such case-capable characters.
Characters within the word which follow the fourth case-capable
character are not used to encode data, even if any such character is
also case-capable.  For example, in the word "abandon", only the first
four characters "aban" would encode data; the trailing characters
"don" could be set to any case by an encoder, and would be ignored by
a decoder.

Case-capable characters within a word encode data bits in the order in
which they appear in the word.  Of the four data-encoding characters,
the first encodes the most significant bit of the nibble, the second
encodes the next most significant bit, the third encodes the next most
significant bit, and the fourth encodes the least significant bit of
the nibble.  For example, the word "aBandon" encodes the binary data
"0100", while the word "AbAndon" encodes the binary data "1010".
(Recall that trailing characters after the first four case-capable
characters are ignored.)

To encode one byte of binary data, the high nibble is encoded first,
then the low nibble is encoded.  At least two words of output are
necessary to encode one byte of input.  For example, the binary data
"11110000" could be encoded as "DOGS cats ".  The same binary data
"11110000" could also be encoded as "TwO CATS aNd No dogs "; recall
that words not containing four case-capable characters do not encode
data, and are ignored. 

Multiple versions of the Obfuscator file format exist, which vary each
from the other in what metadata are stored and where that metadata is
located.  Specific details of various versions follow below. 

[Version 01.01: CRC in header](01_01.md)

[Version 01.02: MD5 in header](01_02.md)

[Version 01.03: SHA-2 in header](01_03.md)

[Version 02.01: CRC follows content](02_01.md)

[Version 02.02: MD5 follows content](02_02.md)

[Version 02.03: SHA-2 follows content](02_03.md)

