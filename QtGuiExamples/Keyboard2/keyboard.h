#ifndef KEYBOARD_H
#define KEYBOARD_H

#define LETTER      0
#define HANZI       1
#define NUMBER      2
#define CAP_LETTER  3

#ifdef RUN_ON_LINUX
#define FILE_ZI_KU      "data/ziku.dat"
#else
#define FILE_ZI_KU      "data/ziku.dat"  //汉字库路径
#endif
#include <QMainWindow>
#include <QPushButton>
namespace Ui {
class Keyboard;
}

class Keyboard : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit Keyboard(QWidget *parent = 0,bool num = false);
    ~Keyboard();
private:
    QStringList m_srf;
    QString     m_CurPY;    //在使用汉字输入时 用于存放当前输入框中的值
    int         m_Page;     //当前页
    int         m_Page_A;   //总页数  此变量和上一个变量用于汉字输入模式时  因为汉字显示页面 每一页显示10个汉字所以需要  翻页

    bool    FindChinese(QString PinYin, QString &Chinese);

    bool    m_MouseDown;
    QPoint  m_DragPos;
    void mouseMoveEvent(QMouseEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);

private:
//    QString Qk_letter;
    char k_letter[7];
    char k_letter_index;
    int  Flag_InputMode; //用于标识输入的模式，如英语字母、汉字拼音、大小写等。
    int  Flag_Mid_Mode;

    void get_key_letter(QString letter);
    void Input_letter_to_linEdit(const QString letter);//将输入的字母 显示在输入框内
    void InitKeyBoard();//初始化
    void Key_Init_ALL(void);
    void hanzi_zk_set();
    //字库需求定义
    //   const char* str_translate_to_hz(void);//字符串翻译成汉字
    void clean_piy_and_hanzi_while_clicked(void);

    void KeyBoardStartMode(int mode);   //进入键盘初始输入法
    void KeyBoardHanziMode();           //键盘输入汉字模式
    void KeyBoardNumMode();             //键盘输入数字模式
    void KeyBoardLetterMode();              //键盘输入小写字母模式
    void KeyBoadrCapMode();             //键盘输入大写字母模式

    void Draw3dFrame(QRect &r, QPainter &dc);
protected:
    void paintEvent(QPaintEvent *);

private slots:
    void on_pushButton_Enter_clicked();
    void on_pushButton_space_clicked();
    void on_pushButton_sign_tan_clicked();
    void on_pushButton_sign_wen_clicked();
    void on_pushButton_sign_fen_clicked();
    void on_pushButton_sign_ju_clicked();
    void on_pushButton_sign_dou_clicked();

    void on_pushButton_cap_clicked();
    void on_pushButton_del_clicked();
    void on_pushButton_pre_clicked();
    void on_pushButton_next_clicked();

    void on_hz_1_clicked();
    void on_hz_2_clicked();
    void on_hz_3_clicked();
    void on_hz_4_clicked();
    void on_hz_5_clicked();
    void on_hz_6_clicked();
    void on_hz_7_clicked();
    void on_hz_8_clicked();
    void on_hz_9_clicked();
    void on_hz_10_clicked();//hz1-10

    void on_pushButton_q_clicked();
    void on_pushButton_w_clicked();
    void on_pushButton_e_clicked();
    void on_pushButton_r_clicked();
    void on_pushButton_t_clicked();
    void on_pushButton_y_clicked();
    void on_pushButton_u_clicked();
    void on_pushButton_i_clicked();
    void on_pushButton_o_clicked();
    void on_pushButton_p_clicked();
    void on_pushButton_a_clicked();
    void on_pushButton_s_clicked();
    void on_pushButton_d_clicked();
    void on_pushButton_f_clicked();
    void on_pushButton_g_clicked();
    void on_pushButton_h_clicked();
    void on_pushButton_j_clicked();
    void on_pushButton_k_clicked();
    void on_pushButton_l_clicked();
    void on_pushButton_z_clicked();
    void on_pushButton_x_clicked();
    void on_pushButton_c_clicked();
    void on_pushButton_v_clicked();
    void on_pushButton_b_clicked();
    void on_pushButton_n_clicked();
    void on_pushButton_m_clicked();//a-z

    void on_pushButton_en_ch_clicked();
    void on_pushButton_esc_clicked();
private:
    Ui::Keyboard *ui;
    QPushButton *m_Display[10];
    QPushButton *m_letter_a_z[26];
};

#endif // KEYBOARD_H
