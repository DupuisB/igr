#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "drawwindow.h"

#include <QMenuBar>
#include <QToolBar>
#include <QTextEdit>
#include <QAction>
#include <QFileDialog>
#include <QDir>
#include <QFile>
#include <QMessageBox>
#include <QCloseEvent>
#include <QSlider>
#include <QLabel>
#include <QActionGroup>
#include <QComboBox>
#include <QBrush>

void MainWindow::selectColor(int index)
{
    QColor color;

    // Set the color based on the index of the dropdown
    switch(index)
    {
    case 0: color = QColor(Qt::black); break;
    case 1: color = QColor(Qt::red); break;
    case 2: color = QColor(Qt::green); break;
    case 3: color = QColor(Qt::blue); break;
    case 4: color = QColor(Qt::yellow); break;
    }

    qDebug() << "Color selected:" << color;
    DrawWindow *drawWindow = (DrawWindow *)this->centralWidget();
    drawWindow->currentColor = color;
}

void MainWindow::selectStyle(int index)
{
    qDebug() << "Style changed to " << index;
    DrawWindow *drawWindow = (DrawWindow *)this->centralWidget();
    drawWindow->currentStyle = index;
}

void MainWindow::changeThickness(int value)
{
    qDebug() << "Thickness changed to " << value;
    DrawWindow *drawWindow = (DrawWindow *)this->centralWidget();
    drawWindow->currentThickness = value;

    QLabel *thicknessLabel = (QLabel *)this->findChild<QLabel *>();
    thicknessLabel->setText(QString::number(value));
}

void MainWindow::quit()
{
    this->close();
}

void MainWindow::open()
{
    qDebug() << "Opening file.";
}

void MainWindow::save()
{
    qDebug() << "Saving file.";
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    //Create actions for the menu. Has images and shortcuts
    QAction *openAction = new QAction(QIcon(":/assets/open.png"), tr("&Open ..."), this);
    QAction *saveAction = new QAction(QIcon(":/assets/save.png"), tr("&Save ..."), this);
    QAction *quitAction = new QAction(QIcon(":/assets/quit.png"), tr("&Quit ..."), this);

    //Define what happens when the actions are triggered
    connect(openAction, SIGNAL(triggered()), this, SLOT(open()));
    connect(saveAction, SIGNAL(triggered()), this, SLOT(save()));
    connect(quitAction, SIGNAL(triggered()), this, SLOT(quit()));

    //Set shortcuts
    openAction->setShortcut(tr("Ctrl+O"));
    saveAction->setShortcut(tr("Ctrl+S"));
    quitAction->setShortcut(tr("Ctrl+Q"));

    QMenuBar *menuBar = this->menuBar();
    QMenu *menu = menuBar->addMenu(tr("&File"));
    menu->addAction(openAction);
    menu->addAction(saveAction);
    menu->addAction(quitAction);

    // Create a toolbar
    QToolBar *toolBar = this->addToolBar(tr("Toolbar"));

    // Add color dropdown (QComboBox)
    this->colorComboBox = new QComboBox(this);
    this->colorComboBox->addItem(tr("Black"));
    this->colorComboBox->addItem(tr("Red"));
    this->colorComboBox->addItem(tr("Green"));
    this->colorComboBox->addItem(tr("Blue"));
    this->colorComboBox->addItem(tr("Yellow"));

    this->colorComboBox->setItemData(0, QColor(Qt::black), Qt::DecorationRole);
    this->colorComboBox->setItemData(1, QColor(Qt::red), Qt::DecorationRole);
    this->colorComboBox->setItemData(2, QColor(Qt::green), Qt::DecorationRole);
    this->colorComboBox->setItemData(3, QColor(Qt::blue), Qt::DecorationRole);
    this->colorComboBox->setItemData(4, QColor(Qt::yellow), Qt::DecorationRole);

    toolBar->addWidget(new QLabel(tr("Color: "), this));
    toolBar->addWidget(this->colorComboBox);

    // Connect color combo box to the selectColor slot
    connect(this->colorComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(selectColor(int)));

    toolBar->addSeparator();

    // Add a thickness slider to the toolbar
    this->thicknessSlider = new QSlider(Qt::Horizontal, this);
    this->thicknessSlider->setMinimum(1);
    this->thicknessSlider->setMaximum(10);
    this->thicknessSlider->setValue(1);
    this->thicknessSlider->setFixedWidth(200);
    toolBar->addWidget(new QLabel(tr("Thickness: "), this));
    toolBar->addWidget(thicknessSlider);

    this->thicknessLabel = new QLabel(tr("1"), this);
    this->thicknessLabel->setFixedWidth(20);
    this->thicknessLabel->setAlignment(Qt::AlignCenter);
    toolBar->addWidget(this->thicknessLabel);

    // Connect the slider to a slot
    connect(thicknessSlider, SIGNAL(valueChanged(int)), this, SLOT(changeThickness(int)));

    toolBar->addSeparator();

    // Add style dropdown (QComboBox)
    this->styleComboBox = new QComboBox(this);
    this->styleComboBox->addItem(tr("Cursor"));
    this->styleComboBox->addItem(tr("Line"));
    this->styleComboBox->addItem(tr("Rectangle"));
    this->styleComboBox->addItem(tr("Ellipse"));
    this->styleComboBox->addItem(tr("Brush"));
    toolBar->addWidget(new QLabel(tr("Style: "), this));
    toolBar->addWidget(this->styleComboBox);

    // Connect style combo box to the selectStyle slot
    connect(this->styleComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(selectStyle(int)));

    // Add a text edit widget
    QTextEdit *textEdit = new QTextEdit(this);
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

    if (confirm == QMessageBox::Yes)
    {
        event->accept();
    }
    else
    {
        event->ignore();
    }
}
