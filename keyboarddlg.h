#ifndef KEY_BOARD_DLG_H
#define KEY_BOARD_DLG_H

#include <QObject>
#include <QDialog>
#include <QPushButton>
#include "ui_keyboard.h"
//#include "commmacro.h"

namespace Ui
{
	class keyBoardDialog;
}
class CKeyBoardDlg:public QDialog
{
	Q_OBJECT
public:
	CKeyBoardDlg();
	~CKeyBoardDlg();
    int g_iLangChange;
    float m_fInputValue;   //输入值
    QString str_display;

signals:
    void Ok_button_clicked(void);

public Q_SLOTS:
	void okBtn_clicked();     //确定-槽函数
	void cancelBtn_clicked(); //取消-槽函数
	void clearBtn_clicked();  //清除-槽函数
	

	void pushButton0_clicked();//"数字键0"槽函数
	void pushButton1_clicked();//"数字键1"槽函数
	void pushButton2_clicked();//"数字键2"槽函数
	void pushButton3_clicked();//"数字键3"槽函数
	void pushButton4_clicked();//"数字键4"槽函数
	void pushButton5_clicked();//"数字键5"槽函数
	void pushButton6_clicked();//"数字键6"槽函数
	void pushButton7_clicked();//"数字键7"槽函数
	void pushButton8_clicked();//"数字键8"槽函数
	void pushButton9_clicked();//"数字键9"槽函数
	void pointBtn_clicked();   //"小数点"槽函数
	void nagBtn_clicked();     //"负数"槽函数

    void display_lineedit();

public:
	bool getInputValue(float &fValue);//获取输入值
	int setDatatype(int nDatatype);   //设置数据类型
	void disablePointAndNagBtn();     //禁用点号和负号按钮
	void keyboardLangChange();
private:
	void init();
	void getDigitalKeyboardText(QPushButton *pushButton);
private:
   QString m_strFriendlytips;//友情提示语
//     float m_fInputValue;   //输入值
	 bool m_ok;
private:
	Ui::keyBoardDialog  *m_pUi;

};
#endif //KEY_BOARD_DLG_H
