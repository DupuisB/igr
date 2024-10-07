#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCloseEvent>
#include <QSlider>
#include <QComboBox>
#include <QLabel>
#include <QToolBar>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QComboBox *colorComboBox;
    QComboBox *styleComboBox;
    QSlider *thicknessSlider;
    QLabel *thicknessLabel;



private:
    Ui::MainWindow *ui;

public slots:
    void open();
    void save();
    void quit();
    void closeEvent(QCloseEvent *event);

    // Updated slots to match the QComboBox index changes
    void selectColor(int index);
    void selectStyle(int index);

    void changeThickness(int value);
};

#endif // MAINWINDOW_H
