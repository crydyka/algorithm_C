import string

charlists = (string.digits, string.ascii_uppercase, string.ascii_lowercase)
dictChars = []

for charlist in charlists:
    for i, c in enumerate(charlist):
        sep = ("" if (c == '0') else ", ") + ("" if (i % 5) else "\\\n\t")
        dictChars.append(f"{sep}DICT_ITEM(\'{c}\')")

with open("charList.h", "w") as f:
    f.write(
        "#pragma once\n\n"
        f"#define DICT_ITEM(c) {{c, 0}}\n"
        f"#define DICT_CHARS_LIST {{ {''.join(dictChars)} \\\n}}\n"
    )