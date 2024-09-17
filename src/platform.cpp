/***************************************************************************
 *            platform.cpp
 *
 *  Sat Dec 23 10:00:00 CEST 2017
 *  Copyright 2017 Lars Muldjord
 *  muldjordlars@gmail.com
 ****************************************************************************/
/*
 *  This file is part of skyscraper.
 *
 *  skyscraper is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
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

#include "platform.h"

#include <QByteArray>
#include <QDebug>
#include <QDir>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QProcess>
#include <QSet>
#include <QString>
#include <QStringList>
#include <iostream>

Platform &Platform::get() {
    static Platform platform;
    return platform;
}

QStringList Platform::getPlatforms() const { return platforms; }

// If user provides no scraping source with '-s' this sets the default for the
// platform
QString Platform::getDefaultScraper() const { return "cache"; }

bool Platform::loadConfig() {
    clearConfigData();

    QString fn = "peas.json";
    QFile configFile(fn);
    if (!configFile.open(QIODevice::ReadOnly)) {
        printf("\033[1;31mFile not found '%s'. Now quitting...\033[0m\n",
               fn.toUtf8().constData());
        return false;
    }

    QByteArray saveData = configFile.readAll();
    QJsonDocument json(QJsonDocument::fromJson(saveData));

    if (json.isNull() || json.isEmpty()) {
        printf("\033[1;31mFile '%s' empty or no JSON format. Now "
               "quitting...\033[0m\n",
               fn.toUtf8().constData());
        return false;
    }

    QJsonObject jObj = json.object();
    peas = jObj.toVariantMap();

    for (auto piter = jObj.constBegin(); piter != jObj.constEnd(); piter++) {
        platforms.push_back(piter.key());
    }

    platforms.sort();

    if (!loadPlatformsIdMap()) {
        return false;
    }
    return true;
}

void Platform::clearConfigData() {
    platforms.clear();
    platformIdsMap.clear();
}

QStringList Platform::getScrapers(QString platform) const {
    QStringList scrapers = peas[platform].toHash()["scrapers"].toStringList();
    // Always add 'cache' as the last one
    scrapers.append("cache");

    return scrapers;
}

QString Platform::getFormats(QString platform, QString extensions,
                             QString addExtensions) const {
    if (!extensions.isEmpty() && extensions.contains("*.")) {
        return extensions;
    }

    QSet<QString> formats({"*.zip", "*.7z", "*.ml"});
    QStringList addExts;

#if QT_VERSION >= 0x050e00
    addExts = addExtensions.split(" ", Qt::SkipEmptyParts);
#else
    addExts = addExtensions.split(" ", QString::SkipEmptyParts);
#endif
    for (auto f : addExts) {
        if (f.startsWith("*.")) {
            formats << f;
        }
    }

    QStringList myFormats = peas[platform].toHash()["formats"].toStringList();
    for (auto f : myFormats) {
        if (f.trimmed().startsWith("*.")) {
            formats << f.trimmed();
        }
    }

    QList<QString> l = formats.values();
    std::sort(l.begin(), l.end());
    QString ret = l.join(" ");
    qDebug() << "getFormats()" << ret;
    return ret;
}

// This contains all known platform aliases as listed on each of the scraping
// source sites
QStringList Platform::getAliases(QString platform) const {
    QStringList aliases;
    // Platform name itself is always appended as the first alias
    aliases.append(platform);
    aliases.append(peas[platform].toHash()["aliases"].toStringList());
    qDebug() << "getAliases():" << aliases;
    return aliases;
}

bool Platform::loadPlatformsIdMap() {
    QString fn = "platforms_idmap.csv";
    QFile configFile(fn);
    if (!configFile.open(QIODevice::ReadOnly)) {
        printf("\033[1;31mFile not found '%s'. Now quitting...\033[0m\n",
               fn.toUtf8().constData());
        return false;
    }
    while (!configFile.atEnd()) {
        QString line = QString(configFile.readLine()).trimmed();
        if (line.isEmpty() || line.startsWith("#") ||
            line.startsWith("folder,")) {
            continue;
        }
        QStringList parts = line.split(',');
        if (parts.length() != 4) {
            printf("\033[1;31mFile '%s', line '%s' has not four columns, but "
                   "%d. Please fix. Now quitting...\033[0m\n",
                   fn.toUtf8().constData(),
                   parts.join(',').toUtf8().constData(), parts.length());
            configFile.close();
            return false;
        }
        QString pkey = parts[0].trimmed();
        if (pkey.isEmpty()) {
            printf(
                "\033[1;31mFile '%s', line '%s' has empty folder/platform. "
                "Ignoring this line. Please fix to mute this warning.\033[0m\n",
                fn.toUtf8().constData(), parts.join(',').toUtf8().constData());
            configFile.close();
            return false;
        }
        parts.removeFirst();
        QVector<int> ids(QVector<int>(3));
        int i = 0;
        for (QString id : parts) {
            id = id.trimmed();
            ids[i] = -1;
            if (!id.isEmpty()) {
                bool ok;
                int tmp = id.toInt(&ok);
                if (ok) {
                    ids[i] = (tmp == 0) ? -1 : tmp;
                } else {
                    printf(
                        "\033[1;33mFile '%s', line '%s,%s' has unparsable int "
                        "value (use -1 for unknown platform id). Assumming -1 "
                        "for now, please fix to mute this warning.\033[0m\n",
                        fn.toUtf8().constData(), pkey.toUtf8().constData(),
                        parts.join(',').toUtf8().constData());
                }
            }
            i++;
        }
        platformIdsMap.insert(pkey, ids);
    }
    configFile.close();
    return true;
}

int Platform::getPlatformIdOnScraper(const QString platform,
                                     const QString scraper) const {
    int id = -1;
    if (platformIdsMap.contains(platform)) {
        QVector<int> ids = platformIdsMap[platform];
        qDebug() << "platform ids" << ids;
        if (scraper == "screenscraper") {
            id = ids[0];
        } else if (scraper == "mobygames") {
            id = ids[1];
        } else if (scraper == "thegamesdb") {
            id = ids[2];
        }
    }
    qDebug() << "Got platform id" << id << "for platform" << platform
             << "and scraper" << scraper;
    return id;
}

// --- Console colors ---
// Black        0;30     Dark Gray     1;30
// Red          0;31     Light Red     1;31
// Green        0;32     Light Green   1;32
// Brown/Orange 0;33     Yellow        1;33
// Blue         0;34     Light Blue    1;34
// Purple       0;35     Light Purple  1;35
// Cyan         0;36     Light Cyan    1;36
// Light Gray   0;37     White         1;37
