## Overview

Some game information and / or game media is region-based. Skyscraper provides several ways of configuring these for your convenience. But most importantly; it supports region auto-detection directly from the file names. Read on for more information about how regions are handled by Skyscraper.

## Scraping modules that support regions

-   screenscraper (pretty much all game information and media)
-   igdb (only release date)
-   mobygames (only cover artwork)

Below follows a general list of supported regions. Please note that not all regions are supported by all modules (support is noted inside the parenthesis for each country or region).

When configuring regions be sure to use the short-names as shown (eg. 'fr' for France).

## List of supported regions

| Region Key | Country/Region (supported by scraping site)  |
| :--------: | -------------------------------------------- |
|    ame     | American continent (screenscraper)           |
|    asi     | Asia (screenscraper, igdb)                   |
|     au     | Australia (screenscraper, igdb, mobygames)   |
|     bg     | Bulgaria (screenscraper, mobygames)          |
|     br     | Brazil (screenscraper, mobygames)            |
|     ca     | Canada (screenscraper, mobygames)            |
|     cl     | Chile (screenscraper, mobygames)             |
|     cn     | China (screenscraper, igdb, mobygames)       |
|    cus     | Custom (screenscraper)                       |
|     cz     | Czech republic (screenscraper, mobygames)    |
|     de     | Germany (screenscraper, mobygames)           |
|     dk     | Denmark (screenscraper, mobygames)           |
|     eu     | Europe (screenscraper, igdb)                 |
|     fi     | Finland (screenscraper, mobygames)           |
|     fr     | France (screenscraper, mobygames)            |
|     gr     | Greece (screenscraper, mobygames)            |
|     hu     | Hungary (screenscraper, mobygames)           |
|     il     | Israel (screenscraper, mobygames)            |
|     it     | Italy (screenscraper, mobygames)             |
|     jp     | Japan (screenscraper, igdb, mobygames)       |
|     kr     | Korea (screenscraper, mobygames)             |
|     kw     | Kuwait (screenscraper)                       |
|    mor     | Middle East (screenscraper)                  |
|     nl     | Netherlands (screenscraper, mobygames)       |
|     no     | Norway (screenscraper, mobygames)            |
|     nz     | New Zealand (screenscraper, igdb, mobygames) |
|    oce     | Oceania (screenscraper)                      |
|     pe     | Peru (screenscraper)                         |
|     pl     | Poland (screenscraper, mobygames)            |
|     pt     | Portugal (screenscraper, mobygames)          |
|     ru     | Russia (screenscraper, mobygames)            |
|     se     | Sweden (screenscraper, mobygames)            |
|     sk     | Slovakia (screenscraper, mobygames)          |
|     sp     | Spain (screenscraper, mobygames)             |
|     ss     | ScreenScraper (screenscraper)                |
|     tr     | Turkey (screenscraper, mobygames)            |
|     tw     | Taiwan (screenscraper, mobygames)            |
|     uk     | United Kingdom (screenscraper, mobygames)    |
|     us     | USA (screenscraper, igdb, mobygames)         |
|    wor     | World (screenscraper, igdb, mobygames)       |

### Region auto-detection

Skyscraper will try to auto-detect the region from the file name. It will look for designations such as `(Europe)` or `(e)` and set the region accordingly. This currently works for the following regions and / or countries:

-   asi, au, br, ca, cn
-   de, dk, eu, fr, it
-   jp, kr, nl, se, sp
-   tw, us, wor

So if your files are named like `Game Name (Europe).zip`, there's no need to configure regions manually. Skyscraper will recognize `Europe` and add it to the top of the internal region priority list. If info or media isn't found for the auto-detected region, it will move down the list and check the next region on the list until it finds one that has data for the requested resource.

### Default Region Prioritization

Skyscraper's default internal region priority list is as follows. Topmost region has highest priority and so forth.

-   User-specified region set with `--region REGION` (command line) or `region="REGION"` (config.ini)
-   If no user-specified region is set, the [auto-detected](REGIONS.md#region-auto-detection) region will be added here
-   eu
-   us
-   ss
-   uk
-   wor
-   jp
-   au
-   ame
-   de
-   cus
-   cn
-   kr
-   asi
-   br
-   sp
-   fr
-   gr
-   it
-   no
-   dk
-   nz
-   nl
-   pl
-   ru
-   se
-   tw
-   ca

## Configuring Region Manually

If you insist, of course you can configure the region manually. You can either do this on command-line or through `/home/<USER>/.skyscraper/config.ini`. It is recommended to set it in `config.ini` for a permanent setup.

### config.ini

Read [this](CONFIGINI.md#region) and [this](CONFIGINI.md#regionprios).

### Command line

Read [this](CLIHELP.md#-region-code).
