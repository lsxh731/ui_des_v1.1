#ifndef MESDIALOG_H
#define MESDIALOG_H

#include <QDialog>

namespace Ui {
class Mesdialog;
}

class Mesdialog : public QDialog
{
    Q_OBJECT

public:
    explicit Mesdialog(QWidget *parent = 0);
    ~Mesdialog();

    void ToShowChinese();
    void ToShowEnglish();

    bool which_Mesdialog; //true:reboot_dialog,false:save_log_dialog

    void ShowOkButton();
    void ShowOkAndCancelButton();


public slots:
    void CancelPressed();
    void OkPressed();

private:
    Ui::Mesdialog *ui;

signals:
    void OkButtonPressed();


};

#endif // MESDIALOG_H
