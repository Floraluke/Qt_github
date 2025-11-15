#ifndef QWMAINWIND_H
#define QWMAINWIND_H

#include <QMainWindow>

namespace Ui {
class QWMainWind;
}

class QWMainWind : public QMainWindow
{
    Q_OBJECT

public:
    explicit QWMainWind(QWidget *parent = nullptr);
    ~QWMainWind();

private slots:
    void on_txtEdit_copyAvailable(bool b);
    void on_actOpen_triggered();
    void on_actFont_triggered();
    void on_actNew_triggered();
    void on_spinBoxFontSize_valueChanged(int aFontSize);
    void on_comboFont_currentIndexChanged(const QString &arg1);
    void on_actToolbarLab_triggered(bool checked);
    void on_actFontBold_triggered(bool checked);
    void on_actFontItalic_triggered(bool checked);
    void on_actFontUnder_triggered(bool checked);
    void on_txtEdit_selectionChanged();
    void on_toolButtonAbout_clicked(); // 添加About按钮的槽函数声明

private:
    Ui::QWMainWind *ui;
    void iniUI();
    void iniSignalSlots();
    void updateCurFile(QString aFile);

    // 其他私有成员变量...
    QString fCurFileName;
    class QLabel *fLabCurFile;
    class QProgressBar *progressBar1;
    class QSpinBox *spinFontSize;
    class QFontComboBox *comboFont;
};

#endif // QWMAINWIND_H
