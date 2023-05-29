/****************************************************************************
** CopyRight(c) 2019,　北京知行新能科技有限公司
** All rights reserved
**
** 文件名称: keyboraddlg.cpp
** 摘要: "键盘输入"对话框
** 当前版本: 1.0.0.0
** 作者:  聂晓波
** 完成日期: 2019.02.23
**
** 取代版本:
** 作者:
** 完成日期：
**
** 历史修改记录:　
** 作者　　　　修改时间　　版本　　　修改版本
** 聂晓波      2019.02.23   V1.0      创建
**
****************************************************************************/
#include"keyboarddlg.h"
#include <QDebug>
CKeyBoardDlg::CKeyBoardDlg()
{
	m_pUi= new Ui::keyBoardDialog;
	m_pUi->setupUi(this);
    this->setModal(true);
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setObjectName("mykeyboard");
    this->setStyleSheet("CKeyBoardDlg#mykeyboard{border-image:url(:/png/empty_background.jpg)}");
	init();
	//keyboardLangChange();
}
CKeyBoardDlg::~CKeyBoardDlg()
{
}
void CKeyBoardDlg::init()
{
	//信号与槽
	connect(m_pUi->okBtn,SIGNAL(clicked()),this,SLOT(okBtn_clicked()));
	connect(m_pUi->cancelBtn,SIGNAL(clicked()),this,SLOT(cancelBtn_clicked()));
	connect(m_pUi->clearBtn,SIGNAL(clicked()),this,SLOT(clearBtn_clicked()));

	//pushButton_0
	connect(m_pUi->pushButton_0,SIGNAL(clicked()),this,SLOT(pushButton0_clicked()));
	//pushButton_1
	connect(m_pUi->pushButton_1,SIGNAL(clicked()),this,SLOT(pushButton1_clicked()));
	//pushButton_2
	connect(m_pUi->pushButton_2,SIGNAL(clicked()),this,SLOT(pushButton2_clicked()));
	//pushButton_3
	connect(m_pUi->pushButton_3,SIGNAL(clicked()),this,SLOT(pushButton3_clicked()));
	//pushButton_4
	connect(m_pUi->pushButton_4,SIGNAL(clicked()),this,SLOT(pushButton4_clicked()));
	//pushButton_5
	connect(m_pUi->pushButton_5,SIGNAL(clicked()),this,SLOT(pushButton5_clicked()));
	//pushButton_6
	connect(m_pUi->pushButton_6,SIGNAL(clicked()),this,SLOT(pushButton6_clicked()));
	//pushButton_7
	connect(m_pUi->pushButton_7,SIGNAL(clicked()),this,SLOT(pushButton7_clicked()));
	//pushButton_8
	connect(m_pUi->pushButton_8,SIGNAL(clicked()),this,SLOT(pushButton8_clicked()));
	//pushButton_9
	connect(m_pUi->pushButton_9,SIGNAL(clicked()),this,SLOT(pushButton9_clicked()));

	connect(m_pUi->pointBtn,SIGNAL(clicked()),this,SLOT(pointBtn_clicked()));
	connect(m_pUi->nagBtn,SIGNAL(clicked()),this,SLOT(nagBtn_clicked()));

	m_fInputValue=0.0;
	m_ok=false;

}
//确定-槽函数
void CKeyBoardDlg::okBtn_clicked()
{

	m_ok=false;
	QString strInputText=m_pUi->lineEdit_input->text();
    m_fInputValue=strInputText.toFloat(&m_ok);
//    m_fInputValue = strInputText.toFloat();
    emit Ok_button_clicked();
//    m_pUi->lineEdit_input->setText("");
	this->close();
}
//取消-槽函数
void CKeyBoardDlg::cancelBtn_clicked()
{
	QString strInputText=m_pUi->lineEdit_input->text();
	if(strInputText.length()>=1)
	{
		strInputText.chop(1);//删除最后一个字符
	}
	m_pUi->lineEdit_input->setText(strInputText);
}
//清除-槽函数
void CKeyBoardDlg::clearBtn_clicked()
{
	QString strInputText=m_pUi->lineEdit_input->text();
	if(!(strInputText.isEmpty()))
	{
		//非空则清空
		m_pUi->lineEdit_input->clear();
	}	
}
//获取输入值
bool CKeyBoardDlg::getInputValue(float &fValue)
{
	fValue=m_fInputValue;
//    qDebug()<<"m_fInputValue="<<m_fInputValue;
	return m_ok;
}
//"数字键0"槽函数
void CKeyBoardDlg::pushButton0_clicked()
{
	getDigitalKeyboardText(m_pUi->pushButton_0);
}
//"数字键1"槽函数
void CKeyBoardDlg::pushButton1_clicked()
{
	getDigitalKeyboardText(m_pUi->pushButton_1);
}
//"数字键2"槽函数
void CKeyBoardDlg::pushButton2_clicked()
{
	getDigitalKeyboardText(m_pUi->pushButton_2);
}
//"数字键3"槽函数
void CKeyBoardDlg::pushButton3_clicked()
{
	getDigitalKeyboardText(m_pUi->pushButton_3);
}
//"数字键4"槽函数
void CKeyBoardDlg::pushButton4_clicked()
{
	getDigitalKeyboardText(m_pUi->pushButton_4);
}
//"数字键5"槽函数
void CKeyBoardDlg::pushButton5_clicked()
{
	getDigitalKeyboardText(m_pUi->pushButton_5);
}
//"数字键6"槽函数
void CKeyBoardDlg::pushButton6_clicked()
{
	getDigitalKeyboardText(m_pUi->pushButton_6);
}
//"数字键7"槽函数
void CKeyBoardDlg::pushButton7_clicked()
{
	getDigitalKeyboardText(m_pUi->pushButton_7);
}
//"数字键8"槽函数
void CKeyBoardDlg::pushButton8_clicked()
{
	getDigitalKeyboardText(m_pUi->pushButton_8);
}
//"数字键9"槽函数
void CKeyBoardDlg::pushButton9_clicked()
{
	getDigitalKeyboardText(m_pUi->pushButton_9);
}
//"小数点"槽函数
void CKeyBoardDlg::pointBtn_clicked()
{
	getDigitalKeyboardText(m_pUi->pointBtn);
}
//"负数"槽函数
void CKeyBoardDlg::nagBtn_clicked()
{
	getDigitalKeyboardText(m_pUi->nagBtn);
}
//获取数字键盘
void CKeyBoardDlg::getDigitalKeyboardText(QPushButton *pushButton)
{
	bool editFlag=false;
	editFlag=m_pUi->lineEdit_input->hasAcceptableInput ();
	if (editFlag)
	{
		m_pUi->lineEdit_input->insert(pushButton->text());
	}
	
}
//禁止点号和负号按钮
void CKeyBoardDlg::disablePointAndNagBtn()
{
	m_pUi->pointBtn->setEnabled(false);
	m_pUi->nagBtn->setEnabled(false);
}
void CKeyBoardDlg::keyboardLangChange()
{
	if(g_iLangChange==1)
	{
//		setWindowTitle(QApplication::translate("keyBoardDialog", "\346\225\260\345\255\227\351\224\256\347\233\230", 0, QApplication::UnicodeUTF8));
//		m_pUi->label->setText(QApplication::translate("keyBoardDialog", "\350\276\223\345\205\245\345\200\274", 0, QApplication::UnicodeUTF8));
//		m_pUi->okBtn->setText(QApplication::translate("keyBoardDialog", "\347\241\256 \345\256\232", 0, QApplication::UnicodeUTF8));
//        m_pUi->cancelBtn->setText(QApplication::translate("keyBoardDialog", "\345\217\226 \346\266\210", 0, QApplication::UnicodeUTF8));
//        m_pUi->clearBtn->setText(QApplication::translate("keyBoardDialog", "\346\270\205 \351\231\244", 0, QApplication::UnicodeUTF8));
    }
	else
	{
		setWindowTitle("Digital keyboard");
		m_pUi->label->setText("Input value");
		m_pUi->okBtn->setText("OK");
        m_pUi->cancelBtn->setText("Cancel");
        m_pUi->clearBtn->setText("Clear");
	}
}

void CKeyBoardDlg::display_lineedit()
{
    m_pUi->lineEdit_input->setText(str_display);
}
