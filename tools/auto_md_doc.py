"""
A script that goes into ../bija.h, parses the library for documentation tags and
creates a file called bija_doc.md within a docs/ directory. If bija_doc.md is 
already created then the script will destroy the existing file and create a new
bija_doc.md file. 

The custom tag that the script parses are the following, 
    1. <Name> - the name of the function.
    2. <Param> - the parameters the function takes in.
    3. <Description> - a one sentence description of what the function does.
    4. <Return> - what the function returns.
"""

from dataclasses import dataclass
from enum import StrEnum
from pathlib import Path
import pprint

BIJA_FILE_PATH = "../bija.h"

class TAGS(StrEnum):
    NAME  = "<Name>"
    PARAM = "<Param>"
    DESC  = "<Description>"
    RET   = "<Return>"

@dataclass
class Doc:
    """Class for keeping track of documentation for bija.h functions."""
    name  : str
    param : list[str]
    desc  : str
    ret   : str

def create_doc(doc_str: str) -> Doc | None:
    if len(doc_str) == 0:
        return None
    
    result = Doc(name="", param=[], desc="", ret="")
    lines = doc_str.split("\n")
    lines.pop(0)
    lines.pop()
    lines.pop()

    for idx in range(len(lines)):
        stripped_line = lines[idx].strip()
        tag = stripped_line[2 : ]
        tag = tag[ : tag.find(" ")]
        content = stripped_line[len(tag) + 2: ] 

        match tag:
            case TAGS.NAME:
                result.name = content.strip()
            case TAGS.PARAM:
                result.param = content.split(",")
            case TAGS.DESC:
                result.desc = content.strip()
            case TAGS.RET:
                result.ret = content.strip()

    return result

def parse() -> dict[str, Doc]:
    doc_block = ""
    doc_db = {}
    enter_doc_block = False

    with open(BIJA_FILE_PATH, "r") as code:
        for line in code:
            stripped_line = line.strip()

            if stripped_line == "/**" or enter_doc_block:
                enter_doc_block = True
                doc_block += (stripped_line + '\n')

            if stripped_line == "*/" and enter_doc_block:
                enter_doc_block = False
                doc = create_doc(doc_block)
                doc_db[doc.name] = doc
                doc_block = ""
                                
    return doc_db

def build_doc(doc_blocks: dict[str, Doc]) -> bool:
    dir_path = Path("../docs/")
    dir_path.mkdir(parents=True, exist_ok=True)

    with open("../docs/bija_docs.md", "w") as file:
        file.write("# Bija Documentation\n")

        file.write("\n This is the official documentation for Bija, a linear algebra"
        " library that supports small vectors and matrices allocated on the stack.\n")

        for func_doc in doc_blocks:
            file.write(f"# {doc_blocks[func_doc].name}\n")
            file.write(f"\n**Description**: {doc_blocks[func_doc].desc}\n")    
            file.write("\n **Parameters**:")        
            for param_idx in range(len(doc_blocks[func_doc].param)):
                if param_idx == len(doc_blocks[func_doc].param) - 1:
                    file.write(f"{doc_blocks[func_doc].param[param_idx]}")
                    continue

                file.write(f"{doc_blocks[func_doc].param[param_idx]} | ")

            file.write("\n")
            file.write(f"\n**Return**: {doc_blocks[func_doc].ret}\n")
            

if __name__ == '__main__':
    doc_db = parse()
    build_doc(doc_db)

