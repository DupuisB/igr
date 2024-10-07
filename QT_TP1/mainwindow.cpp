#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMenuBar>
#include <QToolBar>
#include <QTextEdit>
#include <QAction>
#include <QFileDialog>
#include <QDir>
#include <QFile>
#include <QMessageBox>
#include <QCloseEvent>

#include <iostream>

void MainWindow::quit()
{
    this->close();
}

void MainWindow::open()
{
    qDebug() << "Opening file.";
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), QDir::homePath(), tr("HTML Files (*.html)"));
    std::cout << "File name: " << fileName.toStdString() << std::endl;

    QFile file(fileName);
    file.open(QIODevice::ReadOnly);

    QTextEdit * textEdit = this->findChild<QTextEdit *>();
    textEdit->clear();
    textEdit->setHtml(file.readAll());

    file.close();
    qDebug() << "File opened.";
}

void MainWindow::save()
{
    qDebug() << "Saving file.";
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"), QDir::homePath(), tr("HTML Files (*.html)"));
    std::cout << "File name: " << fileName.toStdString() << std::endl;

    QFile file(fileName);
    file.open(QIODevice::WriteOnly);

    QTextEdit * textEdit = this->findChild<QTextEdit *>();
    file.write(textEdit->toHtml().toUtf8());

    file.close();
    qDebug() << "File saved.";

}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    //Create actions for the menu. HAs images and shortcuts
    QAction * openAction = new QAction(QIcon(":/assets/open.png"), tr("&Open ..."), this);
    QAction * saveAction = new QAction(QIcon(":/assets/save.png"), tr("&Save ..."), this);
    QAction * quitAction = new QAction(QIcon(":/assets/quit.png"), tr("&Quit ..."), this);

    //Define what happens when the actions are triggered
    connect(openAction, SIGNAL(triggered()), this, SLOT(open()));
    connect(saveAction, SIGNAL(triggered()), this, SLOT(save()));
    connect(quitAction, SIGNAL(triggered()), this, SLOT(quit()));

    //Set shortcuts
    openAction->setShortcut(tr("Ctrl+O"));
    saveAction->setShortcut(tr("Ctrl+S"));
    quitAction->setShortcut(tr("Ctrl+Q"));


    QMenuBar * menuBar = this->menuBar();
    QMenu * menu = menuBar->addMenu(tr("&File"));
    menu->addAction(openAction);
    menu->addAction(saveAction);
    menu->addAction(quitAction);

    //Same commands in a toolbar
    QToolBar * toolBar = this->addToolBar(tr("File"));
    toolBar->addAction(openAction);
    toolBar->addAction(saveAction);
    toolBar->addAction(quitAction);

    //Add a text edit widget
    QTextEdit * textEdit = new QTextEdit(this);
    this->setCentralWidget(textEdit);

    //ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// Same as quit()
void MainWindow::closeEvent(QCloseEvent *event)
{
    QMessageBox::StandardButton confirm = QMessageBox::question(this, "Quit", "Are you sure you want to quit?", QMessageBox::Yes | QMessageBox::No);

    if(confirm == QMessageBox::Yes)
    {
        event->accept();
    }
    else
    {
        event->ignore();
    }
}
