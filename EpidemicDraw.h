#pragma once
#include <graphics.h>
#include "button_function.h"
#include "EpidemicSystem.h"

enum EnumWndState
{
    wndLogin = 0,            //登录窗口
    wndRegister = 1,         //注册窗口
    wndMain = 2,             //主窗口
    wndEpidemic = 3,         //疫情绘制窗口
};

struct Area
{
    Area()
    {
        color = RGB(0, 255, 0);
        totalnum = 0;
        num = 0;
    }

    Rect rect;              //位置大小
    std::string text;       //区域名称
    COLORREF color;         //颜色    //红色 20人及以上，橙色 10人及以上 黄色 1-9，绿色 0

    int totalnum;           //总人数
    int num;                //感染人数
    void draw()
    {
        COLORREF oldcolor = getfillcolor();
        setfillcolor(color);

        fillrectangle(rect.left, rect.top, rect.right, rect.bottom);

        int width = rect.width();
        int perH = rect.height() * 1.0 / 4;
        RECT rc = { rect.left, rect.top, rect.right, rect.top + perH };
        drawtext(text.c_str(), &rc, DT_SINGLELINE | DT_CENTER | DT_VCENTER);

        //绘制总人数
        char buff[100] = { 0 };
        sprintf(buff, "总人数:%d", num);
        RECT rc1 = { rect.left, rect.top + perH, rect.right, rect.top + perH * 2.0 };
        drawtext(buff, &rc1, DT_SINGLELINE | DT_CENTER | DT_VCENTER);

        //绘制感染人数
        sprintf(buff, "感染人数:%d", num);
        RECT rc2 = { rect.left, rect.top + perH * 2.0, rect.right, rect.top + perH * 3.0 };
        drawtext(buff, &rc2, DT_SINGLELINE | DT_CENTER | DT_VCENTER);

        //绘制感染密度
        sprintf(buff, "感染密度:%.2lf", num * 100.0 / totalnum);
        RECT rc3 = { rect.left, rect.top + perH * 3.0, rect.right, rect.top + perH * 4.0 };
        drawtext(buff, &rc3, DT_SINGLELINE | DT_CENTER | DT_VCENTER);

        setfillcolor(oldcolor);
    }
};

//疫情绘制
class EpidemicDraw
{
public:
    //初始化
    void initWindow();
    //关闭
    void closeWindow();
    //加载背景图像
    void loadbk();
    //加载登录窗口
    void loadWndLogin();
    //加载主窗口
    void loadWndMain();
    //加载疫情窗口
    void loadWndEpidemic();

    //处理消息
    void handleMessage();
    //绘制
    void draw();

    //绘制背景
    void drawbk();
    void drawWndLogin();
    void drawWndMain();
    void drawWndEpidemic();
    //绘制大标题
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

    //新增学生信息是否完整
    bool isNewStudentInfoFull();
    //新增教师信息是否完整
    bool isNewTeacherInfoFull();
    void doEnterWndEpicdemic();

    //新增疫情信息是否完整
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
    //重置按钮状态
    void resetButton(EnumButtonState state); 
    void handleButtonClick(Button* buttonClick);
public:
    //背景图像
    IMAGE* m_background;

    //窗口状态
    EnumWndState m_wndState;

    //登录界面按钮===================================================
    //登录
    Button* m_btnLogin;
    //退出
    Button* m_btnExit;
    //登录界面按钮===================================================

    //主界面按钮=====================================================
    //学号label
    Label* m_labelHeadStuId;
    //学院label
    Label* m_labelHeadCollege;
    //入学时间label
    Label* m_labelHeadInSchoolTime;
    //学生信息列表
    listView* m_listViewStudent;

    //学号label
    Label* m_labelStuId;
    //学院label
    Label* m_labelCollege;
    //入学时间label
    Label* m_labelInSchoolTime;

    //学号Button
    Button* m_btnStuId;
    //学院Button
    Button* m_btnCollege;
    //入学时间Button
    Button* m_btnInSchoolTime;

    //增加学生btn
    Button* m_btnAddStu;
    //查询学生Btn
    Button* m_btnFindStu;
    //修改学生btn
    Button* m_btnModifyStu;
    //删除学生btn
    Button* m_btnDelStu;
    //取消学生btn
    Button* m_btnCancelStu;


    //工号label
    Label* m_labelHeadTeachId;
    //部门label
    Label* m_labelHeadDepartment;
    //职务label
    Label* m_labelHeadJob;
    //入职时间label
    Label* m_labelHeadJobTime;
    //学生信息列表
    listView* m_listViewTeacher;
    //工号label
    Label* m_labelTeachId;
    //部门label
    Label* m_labelDepartment;
    //职务label
    Label* m_labelJob;
    //入职时间label
    Label* m_labelJobTime;

    //工号btn
    Button* m_btnTeacherId;
    //部门btn
    Button* m_btnDepartment;
    //职务btn
    Button* m_btnJob;
    //入职时间btn
    Button* m_btnJobTime;

    //增加教师btn
    Button* m_btnAddTeacher;
    //查询教师Btn
    Button* m_btnFindTeacher;
    //修改教师btn
    Button* m_btnModifyTeacher;
    //删除教师btn
    Button* m_btnDelTeacher;
    //取消教师btn
    Button* m_btnCancelTeacher;

    //跳转到疫情统计界面
    Button* m_btnGotoWndEpidemic;
    //主界面按钮=====================================================


    //疫情统计界面按钮===============================================

    Label* m_labelHeadSeqId;            //登记流水号
    Label* m_labelHeadId;               //学号 或 工号
    Label* m_labelHeadArea;             //进入区域
    Label* m_labelHeadInTime;           //进入时间
    Label* m_labelHeadOutTime;          //离开时间
    Label* m_labelHeadTemperature;      //体温
    Label* m_labelHeadFever;            //是否发热
    Label* m_labelHeadRetentArea;       //滞留地区列表

    listView* m_listViewEpidemic;       //疫情统计列表

    Label* m_labelSeqId;                //登记流水号
    Label* m_labelId;                   //学号 或 工号
    Label* m_labelArea;                 //进入区域
    Label* m_labelInTime;               //进入时间
    Label* m_labelOutTime;              //离开时间
    Label* m_labelTemperature;          //体温
    Label* m_labelFever;                //是否发热
    Label* m_labelRetentArea;           //滞留地区列表


    Button* m_btnSeqId;                 //登记流水号
    Button* m_btnId;                    //学号 或 工号
    Button* m_btnArea;                  //进入区域
    Button* m_btnInTime;                //进入时间
    Button* m_btnOutTime;               //离开时间
    Button* m_btnTemperature;           //体温
    Button* m_btnFever;                 //是否发热
    Button* m_btnRetentArea;            //滞留地区列表

    
    Button* m_btnAddEpidemic;            //增加疫情信息btn
    Button* m_btnFindEpidemic;           //查询疫情信息Btn
    Button* m_btnModifyEpidemic;         //修改疫情信息btn
    Button* m_btnDelEpidemic;            //删除疫情信息btn
    Button* m_btnCancelEpidemic;         //取消疫情信息btn

    Button* m_btnGotoWndMain;           //跳转到学生教师主界面

    //校内区域  宿舍区，教学区，图书馆，体育场
    Area m_area[4];
    //疫情统计界面按钮===============================================

    bool m_exit;

    EpidemicSystem* m_system;

    StudentInfo* m_currStudent;

    TeacherInfo* m_currTeacher;

    EpidemicRegisterInfo* m_currEpidemic;
};

