Obfuscator encodes arbitrary binary data into the case of words in an
output text stream.  The first four letters of each word are used for
encoding; remaining letters in each word, if any, are not significant
in the encoding.  Words in the word list which are shorter than four
letters may appear in the output, but are not used in the encoding.
The total output is a whitespace-delimited list of words, within which
the case of letters varies without regard to grammatical standards or
common usage norms.  

An encoding program may select and sequence words for output without
regard to grammatical or syntactical sense of those words as
linguistic text.  Encoding programs may create "word salads" from
internal word lists, create words from random letter sequences, use
base text documents or multi-word text fragments, or some other
method resulting in whitespace-delimited words containing at least
four characters capable of case variation to carry the obfuscated
data.

[File Format Description](doc/FileFormat.txt)

