#include "strtools.h"

#include <QDebug>

int main() {

    QMap<QString, QPair<QString, QString>> tests = {
        {"do not multbang",
         QPair<QString, QString>("I am sentence one!!  I am sentence two.\nI "
                                 "am sentence three!!!!!!!!!",
                                 "I am sentence one!! I am sentence two.\nI am "
                                 "sentence three!!!!!!!!!")},
        {"itemize bullet",
         QPair<QString, QString>(
             "bla bla\n  ●  item 1\n* item2\nfoo bar baz\n* item 1b\n●  item "
             "2b",
             "bla bla\n- item 1\n- item2\nfoo bar baz\n- item 1b\n- item 2b")},
        {"itemize star 2", QPair<QString, QString>(
                               "bla bla\n  *  item 1\n* item2\nfoo bar baz\n* "
                               "item 1b\n*  item 2b\n  *  item 3b  \n\n\nbaz",
                               "bla bla\n- item 1\n- item2\nfoo bar baz\n- "
                               "item 1b\n- item 2b\n- item 3b\n\n\nbaz")},
        {"itemize star",
         QPair<QString, QString>(
             "bla bla\n  *  item 1\n* item2\nfoo bar baz\n* item 1b\n*  item "
             "2b",
             "bla bla\n- item 1\n- item2\nfoo bar baz\n- item 1b\n- item 2b")},
        {"multbang",
         QPair<QString, QString>(
             "I am sentence one!!  I am sentence two.\nI am sentence "
             "three!!!!!!!!!",
             "I am sentence one! I am sentence two.\nI am sentence three!")},
        {"multispaces", QPair<QString, QString>("bla bla!    \n\n\nblubb",
                                                "bla bla!\n\n\nblubb")},
        {"replace ellipsis",
         QPair<QString, QString>("bla …bla  \n  …efefef efefef…\n  \n  ",
                                 "bla ...bla\n...efefef efefef...\n\n")},
        {"sentence spacing",
         QPair<QString, QString>(
             "I am sentence one.  I am sentence two.\nI am sentence three.",
             "I am sentence one. I am sentence two.\nI am sentence three.")},
        {"single star 2",
         QPair<QString, QString>("bla bla  \n  *  efefef efefef\nefef",
                                 "bla bla\n*  efefef efefef\nefef")},
        {"single star", QPair<QString, QString>("bla bla  \n  *  efefef efefef",
                                                "bla bla\n*  efefef efefef")},
        {"trim lines",
         QPair<QString, QString>("bla bla  \n  efefef efefef\n  \n  ",
                                 "bla bla\nefefef efefef\n\n")},
    };

    qInfo() << "";
    int pass = 0;
    for (auto t : tests.keys()) {
        QString input = tests.value(t).first;
        QString exp = tests.value(t).second;
        QString out =
            StrTools::tidyText(input, t == "do not multbang" ? true : false);
        if (out == exp) {
            qInfo() << "  Pass: " << t;
            pass++;
        } else {
            qWarning() << "Failed: " << t << "\nExp: " << exp
                       << "\nGot: " << out << "\n";
        }
    }
    qInfo() << "\nTests passed: " << pass << "/" << tests.keys().size();
}