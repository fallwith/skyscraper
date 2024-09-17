#! /usr/bin/env python3

# Generate a Skyscraper compatible mame ROM filename to ROM full name CSV.
# You usually don't need to run this script.

# (c) 2023 Gemba @ GitHub
# SPDX-License-Identifier: GPL-3.0-or-later

from pathlib import Path
import csv
import pandas as pd
import requests


URL = (
    "https://raw.githubusercontent.com/"
    "RetroPie/EmulationStation/master/resources/mamenames.xml"
)

OUTFILE = Path(__file__).parent.resolve() / "../../mameMap.csv"

req = requests.get(URL)
lines = req.text.split("\n")
hdr = lines[0].replace("<!--", "").replace("-->", "").strip()
print(f"[+] File info: {hdr}")
lines[0] = "<root>"
lines.append("</root>")
df = pd.read_xml("".join(lines), xpath="//root/*")

if len(df):
    print(f"[+] Found {len(df)} ROM names")

    with open(OUTFILE, "w") as csvoutfile:
        csvoutfile.write(f"# {hdr}\n")
        csvoutfile.write(f"# yarked from: {URL}\n")

    df.to_csv(
        OUTFILE, index=False, header=False, sep=";", quoting=csv.QUOTE_ALL, mode="a"
    )
    print(f"[+] Written to {OUTFILE}")
else:
    print("[!] Ran into an error")
