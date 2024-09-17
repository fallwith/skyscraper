/***************************************************************************
 *            skyscraper.h
 *
 *  Wed Jun 7 12:00:00 CEST 2017
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

#ifndef SKYSCRAPER_H
#define SKYSCRAPER_H

#include "abstractfrontend.h"
#include "cache.h"
#include "netcomm.h"
#include "netmanager.h"
#include "platform.h"
#include "scraperworker.h"
#include "settings.h"

#include <QCommandLineParser>
#include <QElapsedTimer>
#include <QFile>
#include <QObject>

class Skyscraper : public QObject {
    Q_OBJECT

public:
    Skyscraper(const QCommandLineParser &parser, const QString &currentDir);
    ~Skyscraper();
    QSharedPointer<Queue> queue;
    QSharedPointer<NetManager> manager;
    enum OpMode { SINGLE, NO_INTR, CACHE_EDIT, THREADED };
    int state = SINGLE;

public slots:
    void run();

signals:
    void finished();

private slots:
    void entryReady(const GameEntry &entry, const QString &output,
                    const QString &debug);
    void checkThreads();

private:
    Settings config;
    void loadConfig(const QCommandLineParser &parser);
    QString secsToString(const int &seconds);
    void checkForFolder(QDir &folder, bool create = true);
    void showHint();
    void prepareScraping();
    void prepareFileQueue();
    void updateWhdloadDb(NetComm &netComm, QEventLoop &q);
    void prepareIgdb(NetComm &netComm, QEventLoop &q);
    void prepareScreenscraper(NetComm &netComm, QEventLoop &q);
    void loadAliasMap();
    void loadMameMap();
    void loadWhdLoadMap();
    void setRegionPrios();
    void setLangPrios();
    QString normalizePath(QFileInfo fileInfo);
    // void migrate(QString filename);
    const inline QString platformFileExtensions() {
        return Platform::get().getFormats(config.platform, config.extensions,
                                          config.addExtensions);
    }
    void setFolder(const bool doCacheScraping, QString &outFolder,
                   const bool createMissingFolder = true);

    AbstractFrontend *frontend;

    QSharedPointer<Cache> cache;

    QList<GameEntry> gameEntries;
    QList<QString> cliFiles;
    QMutex entryMutex;
    QMutex checkThreadMutex;
    QElapsedTimer timer;
    QString gameListFileString;
    QString skippedFileString;
    int doneThreads;
    int notFound;
    int found;
    int avgSearchMatch;
    int avgCompleteness;
    int currentFile;
    int totalFiles;
    bool cacheScrapeMode; // config.scraper == "cache"
    bool doCacheScraping; // cacheScrapeMode && pretend == false
};

#endif // SKYSCRAPER_H
