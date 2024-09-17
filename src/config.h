/*
 *  This file is part of skyscraper.
 *  Copyright 2023 Gemba @ GitHub
 *
 *  skyscraper is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  skyscraper is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with skyscraper; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA.
 */

#ifndef CONFIG_H
#define CONFIG_H

#include <QString>

namespace Config {
    enum class FileOp { KEEP, OVERWRITE, CREATE_DIST };

    void copyFile(const QString &src, const QString &dest,
                  FileOp fileOp = FileOp::OVERWRITE);
    void setupUserConfig();
    void checkLegacyFiles();
    QString getSupportedPlatforms();
} // namespace Config

#endif // CONFIG_H