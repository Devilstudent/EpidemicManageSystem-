#pragma once
#include <graphics.h>
#include "button_function.h"
#include "EpidemicSystem.h"

enum EnumWndState
{
    wndLogin = 0,            //��¼����
    wndRegister = 1,         //ע�ᴰ��
    wndMain = 2,             //������
    wndEpidemic = 3,         //������ƴ���
};

struct Area
{
    Area()
    {
        color = RGB(0, 255, 0);
        totalnum = 0;
        num = 0;
    }

    Rect rect;              //λ�ô�С
    std::string text;       //��������
    COLORREF color;         //��ɫ    //��ɫ 20�˼����ϣ���ɫ 10�˼����� ��ɫ 1-9����ɫ 0

    int totalnum;           //������
    int num;                //��Ⱦ����
    void draw()
    {
        COLORREF oldcolor = getfillcolor();
        setfillcolor(color);

        fillrectangle(rect.left, rect.top, rect.right, rect.bottom);

        int width = rect.width();
        int perH = rect.height() * 1.0 / 4;
        RECT rc = { rect.left, rect.top, rect.right, rect.top + perH };
        drawtext(text.c_str(), &rc, DT_SINGLELINE | DT_CENTER | DT_VCENTER);

        //����������
        char buff[100] = { 0 };
        sprintf(buff, "������:%d", num);
        RECT rc1 = { rect.left, rect.top + perH, rect.right, rect.top + perH * 2.0 };
        drawtext(buff, &rc1, DT_SINGLELINE | DT_CENTER | DT_VCENTER);

        //���Ƹ�Ⱦ����
        sprintf(buff, "��Ⱦ����:%d", num);
        RECT rc2 = { rect.left, rect.top + perH * 2.0, rect.right, rect.top + perH * 3.0 };
        drawtext(buff, &rc2, DT_SINGLELINE | DT_CENTER | DT_VCENTER);

        //���Ƹ�Ⱦ�ܶ�
        sprintf(buff, "��Ⱦ�ܶ�:%.2lf", num * 100.0 / totalnum);
        RECT rc3 = { rect.left, rect.top + perH * 3.0, rect.right, rect.top + perH * 4.0 };
        drawtext(buff, &rc3, DT_SINGLELINE | DT_CENTER | DT_VCENTER);

        setfillcolor(oldcolor);
    }
};

//�������
class EpidemicDraw
{
public:
    //��ʼ��
    void initWindow();
    //�ر�
    void closeWindow();
    //���ر���ͼ��
    void loadbk();
    //���ص�¼����
    void loadWndLogin();
    //����������
    void loadWndMain();
    //�������鴰��
    void loadWndEpidemic();

    //������Ϣ
    void handleMessage();
    //����
    void draw();

    //���Ʊ���
    void drawbk();
    void drawWndLogin();
    void drawWndMain();
    void drawWndEpidemic();
    //���ƴ����
    void drawBigTitle();
public:
    void doEnterSystem();
    void doExitSystem();
    void doAddStudent();
    void doFindStudent();
    void doModifyStudent();
    void doDelStudent();
    void doCancelStudent();

    void doAddTeacher();
    void doFindTeacher();
    void doModifyTeacher();
    void doDelTeacher();
    void doCancelTeacher();

    void doSetStudentId();
    void doSetStudentCollege();
    void doSetStudentInSchoolTime();

    void doSetTeacherId();
    void doSetTeacherDepartment();
    void doSetTeacherJob();
    void doSetTeacherJobTime();

    //����ѧ����Ϣ�Ƿ�����
    bool isNewStudentInfoFull();
    //������ʦ��Ϣ�Ƿ�����
    bool isNewTeacherInfoFull();
    void doEnterWndEpicdemic();

    //����������Ϣ�Ƿ�����
    bool isNewEpidemicInfoFull();
    void doSetSeqId();
    void doSetId();
    void doSetArea();
    void doSetInTime();
    void doSetOutTime();
    void doSetTemperature();
    void doSetFever();
    void doSetRetentArea();

    void doAddEpidemic();
    void doFindEpidemic();
    void doModifyEpidemic();
    void doDelEpidemic();
    void doCancelEpidemic();

    void changeAreaFever(std::string areaName, bool fever,bool add);
    void changeAreaColor(Area* area);
public:
    //���ð�ť״̬
    void resetButton(EnumButtonState state); 
    void handleButtonClick(Button* buttonClick);
public:
    //����ͼ��
    IMAGE* m_background;

    //����״̬
    EnumWndState m_wndState;

    //��¼���水ť===================================================
    //��¼
    Button* m_btnLogin;
    //�˳�
    Button* m_btnExit;
    //��¼���水ť===================================================

    //�����水ť=====================================================
    //ѧ��label
    Label* m_labelHeadStuId;
    //ѧԺlabel
    Label* m_labelHeadCollege;
    //��ѧʱ��label
    Label* m_labelHeadInSchoolTime;
    //ѧ����Ϣ�б�
    listView* m_listViewStudent;

    //ѧ��label
    Label* m_labelStuId;
    //ѧԺlabel
    Label* m_labelCollege;
    //��ѧʱ��label
    Label* m_labelInSchoolTime;

    //ѧ��Button
    Button* m_btnStuId;
    //ѧԺButton
    Button* m_btnCollege;
    //��ѧʱ��Button
    Button* m_btnInSchoolTime;

    //����ѧ��btn
    Button* m_btnAddStu;
    //��ѯѧ��Btn
    Button* m_btnFindStu;
    //�޸�ѧ��btn
    Button* m_btnModifyStu;
    //ɾ��ѧ��btn
    Button* m_btnDelStu;
    //ȡ��ѧ��btn
    Button* m_btnCancelStu;


    //����label
    Label* m_labelHeadTeachId;
    //����label
    Label* m_labelHeadDepartment;
    //ְ��label
    Label* m_labelHeadJob;
    //��ְʱ��label
    Label* m_labelHeadJobTime;
    //ѧ����Ϣ�б�
    listView* m_listViewTeacher;
    //����label
    Label* m_labelTeachId;
    //����label
    Label* m_labelDepartment;
    //ְ��label
    Label* m_labelJob;
    //��ְʱ��label
    Label* m_labelJobTime;

    //����btn
    Button* m_btnTeacherId;
    //����btn
    Button* m_btnDepartment;
    //ְ��btn
    Button* m_btnJob;
    //��ְʱ��btn
    Button* m_btnJobTime;

    //���ӽ�ʦbtn
    Button* m_btnAddTeacher;
    //��ѯ��ʦBtn
    Button* m_btnFindTeacher;
    //�޸Ľ�ʦbtn
    Button* m_btnModifyTeacher;
    //ɾ����ʦbtn
    Button* m_btnDelTeacher;
    //ȡ����ʦbtn
    Button* m_btnCancelTeacher;

    //��ת������ͳ�ƽ���
    Button* m_btnGotoWndEpidemic;
    //�����水ť=====================================================


    //����ͳ�ƽ��水ť===============================================

    Label* m_labelHeadSeqId;            //�Ǽ���ˮ��
    Label* m_labelHeadId;               //ѧ�� �� ����
    Label* m_labelHeadArea;             //��������
    Label* m_labelHeadInTime;           //����ʱ��
    Label* m_labelHeadOutTime;          //�뿪ʱ��
    Label* m_labelHeadTemperature;      //����
    Label* m_labelHeadFever;            //�Ƿ���
    Label* m_labelHeadRetentArea;       //���������б�

    listView* m_listViewEpidemic;       //����ͳ���б�

    Label* m_labelSeqId;                //�Ǽ���ˮ��
    Label* m_labelId;                   //ѧ�� �� ����
    Label* m_labelArea;                 //��������
    Label* m_labelInTime;               //����ʱ��
    Label* m_labelOutTime;              //�뿪ʱ��
    Label* m_labelTemperature;          //����
    Label* m_labelFever;                //�Ƿ���
    Label* m_labelRetentArea;           //���������б�


    Button* m_btnSeqId;                 //�Ǽ���ˮ��
    Button* m_btnId;                    //ѧ�� �� ����
    Button* m_btnArea;                  //��������
    Button* m_btnInTime;                //����ʱ��
    Button* m_btnOutTime;               //�뿪ʱ��
    Button* m_btnTemperature;           //����
    Button* m_btnFever;                 //�Ƿ���
    Button* m_btnRetentArea;            //���������б�

    
    Button* m_btnAddEpidemic;            //����������Ϣbtn
    Button* m_btnFindEpidemic;           //��ѯ������ϢBtn
    Button* m_btnModifyEpidemic;         //�޸�������Ϣbtn
    Button* m_btnDelEpidemic;            //ɾ��������Ϣbtn
    Button* m_btnCancelEpidemic;         //ȡ��������Ϣbtn

    Button* m_btnGotoWndMain;           //��ת��ѧ����ʦ������

    //У������  ����������ѧ����ͼ��ݣ�������
    Area m_area[4];
    //����ͳ�ƽ��水ť===============================================

    bool m_exit;

    EpidemicSystem* m_system;

    StudentInfo* m_currStudent;

    TeacherInfo* m_currTeacher;

    EpidemicRegisterInfo* m_currEpidemic;
};

