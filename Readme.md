# Readable structure from single lines

## Overview

The program allows you to convert a compressed file, such as a Json file contained in a single line, into an easily readable file.

## Input example

``` json
{"glossary": {"title": "example glossary","GlossDiv": {"title": "S","GlossList": {"GlossEntry": {"ID": "SGML","SortAs": "SGML","GlossTerm": "Standard Generalized Markup Language","Acronym": "SGML","Abbrev": "ISO 8879:1986","GlossDef": {"para": "A meta-markup language, used to create markup languages such as DocBook.","GlossSeeAlso": ["GML","XML"]},"GlossSee": "markup"}}}}}
```

## Output example

``` json

{
    "glossary": 
    {
        "title": "example glossary",
        "GlossDiv": 
        {
            "title": "S",
            "GlossList": 
            {
                "GlossEntry": 
                {
                    "ID": "SGML",
                    "SortAs": "SGML",
                    "GlossTerm": "Standard Generalized Markup Language",
                    "Acronym": "SGML",
                    "Abbrev": "ISO 8879:1986",
                    "GlossDef": 
                    {
                        "para": "A meta-markup language,
                         used to create markup languages such as DocBook.",
                        "GlossSeeAlso": 
                        [
                            "GML",
                            "XML"
                        ]
                    },
                    "GlossSee": "markup"
                }
            }
        }
    }
}
```