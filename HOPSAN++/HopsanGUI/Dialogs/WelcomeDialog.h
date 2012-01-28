/*-----------------------------------------------------------------------------
 This source file is part of Hopsan NG

 Copyright (c) 2011 
    Mikael Axin, Robert Braun, Alessandro Dell'Amico, Björn Eriksson,
    Peter Nordin, Karl Pettersson, Petter Krus, Ingo Staack

 This file is provided "as is", with no guarantee or warranty for the
 functionality or reliability of the contents. All contents in this file is
 the original work of the copyright holders at the Division of Fluid and
 Mechatronic Systems (Flumes) at Linköping University. Modifying, using or
 redistributing any part of this file is prohibited without explicit
 permission from the copyright holders.
-----------------------------------------------------------------------------*/

//!
//! @file   WelcomeDialog.h
//! @author Robert Braun <robert.braun@liu.se>
//! @date   2010-XX-XX
//!
//! @brief Contains a class for the Welcome dialog
//!
//$Id$

#ifndef WELCOMEDIALOG_H
#define WELCOMEDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QCheckBox>
#include <QListWidget>
#include <QWebView>
#include <QProgressBar>
#include <QVBoxLayout>

class MainWindow;

class WelcomeDialog : public QDialog
{
    Q_OBJECT

public:
    WelcomeDialog(MainWindow *parent = 0);

    QString mpUpdateLink;

protected:
    virtual void mouseMoveEvent(QMouseEvent *);
    virtual bool focusNextPrevChild(bool next);

private slots:
    void createNewModel();
    void loadExistingModel();
    void loadLastSession();
    void openRecentModel();
    void showNews(bool loadedSuccesfully);
    void updateLoadingWebProgressBar();
    void urlClicked(const QUrl &link);
    void openDownloadPage();

private:
    void updateGraphics();

    QLabel *mpHeading;
    QLabel *mpActionText;

    QPushButton *mpNew;
    QPushButton *mpOpen;
    QPushButton *mpLastSession;

    QIcon *mpNewIcon;
    QIcon *mpOpenIcon;
    QIcon *mpLastSessionIcon;

    QIcon *mpNewActiveIcon;
    QIcon *mpOpenActiveIcon;
    QIcon *mpLastSessionActiveIcon;

    QListWidget *mpRecentList;
    QStringList mModelList;

    QCheckBox *mpDontShowMe;
    QCheckBox *mpPopupHelpCheckBox;

    QPushButton *mpNewVersionButton;
    QMenu *mpNewVersionMenu;
    QAction *mpAutoUpdateAction;
    QAction *mpGoToDownloadPageAction;
    QLabel *mpNewsLabel;
    QProgressBar *mpLoadingWebProgressBar;
    QLabel *mpLoadingWebLabel;
    QTimer *mpLoadingWebProgressBarTimer;
    QVBoxLayout *mpLoadingWebLayout;
    QWidget *mpLoadingWebWidget;
    QWebView *mpWeb;
};

#endif // WELCOMEDIALOG_H
