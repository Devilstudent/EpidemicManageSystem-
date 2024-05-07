#include "EpidemicDraw.h"

//窗口大小
int g_width = 1200, g_height = 800;
//背景图像
const char g_strbackground[] = ".\\res\\background.png";
//按钮通用大小
int g_buttonW = 150;
int g_buttonH = 45;

int g_labelW = 150;
int g_labelH = 45;

void EpidemicDraw::initWindow()
{
    //初始化窗口
    initgraph(g_width, g_height, SHOWCONSOLE);
    setbkcolor(WHITE);
    cleardevice();
    system("title 校园疫情管理系统");

    loadbk();

    m_system = new EpidemicSystem();
    m_currStudent = NULL;
    m_currTeacher = NULL;
    m_currEpidemic = NULL;

    m_wndState = EnumWndState::wndLogin;

    loadWndLogin();
    loadWndMain();
    loadWndEpidemic();

    m_exit = false;
}

void EpidemicDraw::closeWindow()
{
    delete m_system;
    //关闭窗口
    closegraph();
}

void EpidemicDraw::loadbk()
{
    m_background = new IMAGE();
    setbkmode(TRANSPARENT);
    loadimage(m_background, g_strbackground, g_width, g_height);
}

void EpidemicDraw::loadWndLogin()
{
    Rect wndRect(0, 0, g_width, g_height);
    int left = (g_width - g_buttonW) / 2.0;
    int top = g_height * 2.0 / 3;
    m_btnLogin = new Button(Rect(left, top, left + g_buttonW, top + g_buttonH));

    m_btnLogin->text = "登 录 系 统";

    top += g_buttonH + 30;
    m_btnExit = new Button(Rect(left, top, left + g_buttonW, top + g_buttonH));
    m_btnExit->text = "  退  出  ";
}

void EpidemicDraw::loadWndMain()
{
    Rect wndRect(0, 0, g_width, g_height);

    //学生信息界面
    int left = (g_width - g_labelW) / 6.0 * 0;
    int top = 5;

    m_labelHeadStuId = new Label(Rect(left, top, left + g_labelW, top + g_labelH));
    m_labelHeadStuId->text = "  学  号  ";

    left += g_labelW + 15;
    m_labelHeadCollege = new Label(Rect(left, top, left + g_labelW, top + g_labelH));
    m_labelHeadCollege->text = "  学  院  ";

    left += g_labelW + 15;
    m_labelHeadInSchoolTime = new Label(Rect(left, top, left + g_labelW, top + g_labelH));
    m_labelHeadInSchoolTime->text = "入 学 时 间";

    left = (g_width - g_labelW) / 6.0 * 0;
    top = 50;
    m_listViewStudent = new listView(Rect(left, top, left + g_labelW * 3, top + 400));
    m_listViewStudent->init(40);

    top = 500;

    m_labelStuId = new Label(Rect(left, top, left + g_labelW, top + g_labelH));
    m_labelStuId->text = "  学  号  ";

    top += g_labelH + 20;

    m_labelCollege = new Label(Rect(left, top, left + g_labelW, top + g_labelH));
    m_labelCollege->text = "  学  院  ";

    top += g_labelH + 20;

    m_labelInSchoolTime = new Label(Rect(left, top, left + g_labelW, top + g_labelH));
    m_labelInSchoolTime->text = "入 学 时 间";


    left = (g_width - g_buttonW) / 6.0 * 1;
    top = 500;

    m_btnStuId = new Button(Rect(left, top, left + g_buttonW, top + g_buttonH));
    m_btnStuId->text = "0001";

    top += g_buttonH + 20;
    m_btnCollege = new Button(Rect(left, top, left + g_buttonW, top + g_buttonH));
    m_btnCollege->text = "理学院";

    top += g_buttonH + 20;
    m_btnInSchoolTime = new Button(Rect(left, top, left + g_buttonW, top + g_buttonH));
    m_btnInSchoolTime->text = "20230902";

    top += g_buttonH + 20;
    left = (g_width - g_buttonW) / 6.0 * 0 + 5;

    int btnW = g_buttonW / 3.0 * 2 - 3;
    m_btnAddStu = new Button(Rect(left, top, left + btnW, top + g_buttonH));
    m_btnAddStu->text = "增加学生";

    left += btnW + 15;
    m_btnFindStu= new Button(Rect(left, top, left + btnW, top + g_buttonH));
    m_btnFindStu->text = "查找学生";

    left += btnW + 15;
    m_btnModifyStu = new Button(Rect(left, top, left + btnW, top + g_buttonH));
    m_btnModifyStu->text = "修改学生";

    left = (g_width - g_buttonW) / 6.0 * 0 + 5;
    top += g_buttonH + 10;
    left += btnW + 15;
    m_btnDelStu = new Button(Rect(left, top, left + btnW, top + g_buttonH));
    m_btnDelStu->text = "删除学生";

    left += btnW + 15;
    m_btnCancelStu = new Button(Rect(left, top, left + btnW, top + g_buttonH));
    m_btnCancelStu->text = "取消学生";
    

    //学生信息界面===================================================================

    //教师信息界面===================================================================
    left = (g_width - g_labelW) / 6.0 * 3;
    top = 5;

    m_labelHeadTeachId = new Label(Rect(left, top, left + g_labelW, top + g_labelH));
    m_labelHeadTeachId->text = "  工  号  ";

    left += g_labelW + 15;
    m_labelHeadDepartment = new Label(Rect(left, top, left + g_labelW, top + g_labelH));
    m_labelHeadDepartment->text = "  部  门  ";

    left += g_labelW + 15;
    m_labelHeadJob = new Label(Rect(left, top, left + g_labelW, top + g_labelH));
    m_labelHeadJob->text = "  职  位  ";

    left += g_labelW + 15;
    m_labelHeadJobTime = new Label(Rect(left, top, left + g_labelW, top + g_labelH));
    m_labelHeadJobTime->text = " 入 职 时 间 ";

    left = (g_width - g_labelW) / 6.0 * 3;
    top = 50;
    m_listViewTeacher = new listView(Rect(left, top, left + g_labelW * 4, top + 400));
    m_listViewTeacher->init(40);

    top = 460;

    m_labelTeachId = new Label(Rect(left, top, left + g_labelW, top + g_labelH));
    m_labelTeachId->text = "  工  号  ";

    top += g_labelH + 20;
    m_labelDepartment = new Label(Rect(left, top, left + g_labelW, top + g_labelH));
    m_labelDepartment->text = "  部  门  ";

    top += g_labelH + 20;
    m_labelJob = new Label(Rect(left, top, left + g_labelW, top + g_labelH));
    m_labelJob->text = "  职  位  ";

    top += g_labelH + 20;
    m_labelJobTime = new Label(Rect(left, top, left + g_labelW, top + g_labelH));
    m_labelJobTime->text = " 入 职 时 间 ";

    top = 460;
    left = (g_width - g_buttonW) / 6.0 * 4;
    m_btnTeacherId = new Button(Rect(left, top, left + g_buttonW, top + g_buttonH));
    m_btnTeacherId->text = "JS001";

    top += g_buttonH + 20;
    m_btnDepartment = new Button(Rect(left, top, left + g_buttonW, top + g_buttonH));
    m_btnDepartment->text = "理学院教学组";

    top += g_buttonH + 20;
    m_btnJob = new Button(Rect(left, top, left + g_buttonW, top + g_buttonH));
    m_btnJob->text = "计算机教师";

    top += g_buttonH + 20;
    m_btnJobTime = new Button(Rect(left, top, left + g_buttonW, top + g_buttonH));
    m_btnJobTime->text = "20230707";

    top += g_buttonH + 20;
    left = (g_width - g_buttonW) / 6.0 * 3;

    btnW = g_buttonW / 3.0 * 2 - 3;
    m_btnAddTeacher = new Button(Rect(left, top, left + btnW, top + g_buttonH));
    m_btnAddTeacher->text = "增加教师";

    left += btnW + 15;
    m_btnFindTeacher = new Button(Rect(left, top, left + btnW, top + g_buttonH));
    m_btnFindTeacher->text = "查找教师";

    left += btnW + 15;
    m_btnModifyTeacher = new Button(Rect(left, top, left + btnW, top + g_buttonH));
    m_btnModifyTeacher->text = "修改教师";

    left += btnW + 15;
    m_btnDelTeacher = new Button(Rect(left, top, left + btnW, top + g_buttonH));
    m_btnDelTeacher->text = "删除教师";

    left += btnW + 15;
    m_btnCancelTeacher = new Button(Rect(left, top, left + btnW, top + g_buttonH));
    m_btnCancelTeacher->text = "取消教师";

    //教师信息界面===================================================================

    left += btnW + 15;
    m_btnGotoWndEpidemic = new Button(Rect(left, top, left + btnW, top + g_buttonH));
    m_btnGotoWndEpidemic->text = "跳转疫情界面";
}

void EpidemicDraw::loadWndEpidemic()
{
    int perW = g_width / 4;
    int perH = g_height / 4;
    

    int top = perH * 2;
    int left = 10;
    m_area[0].text = "宿舍区";
    m_area[0].rect = Rect(0, top, perW, top + perH).inflate(20, 20);

    m_area[1].text = "教学区";
    m_area[1].rect = Rect(perW, top, perW * 2, top + perH).inflate(20, 20);

    m_area[2].text = "图书馆";
    m_area[2].rect = Rect(0, top + perH, perW, top + perH * 2).inflate(20, 20);

    m_area[3].text = "体育场";
    m_area[3].rect = Rect(perW, top + perH, perW * 2, top + perH * 2).inflate(20, 20);

    top = 10;
    left = 10;
    m_labelHeadSeqId = new Label(Rect(left, top, left + g_labelW, top + g_labelH));
    m_labelHeadSeqId->text = "登记流水号";

    left += g_labelW;
    m_labelHeadId = new Label(Rect(left, top, left + g_labelW, top + g_labelH));
    m_labelHeadId->text = "学号(工号)";

    left += g_labelW;
    m_labelHeadArea = new Label(Rect(left, top, left + g_labelW, top + g_labelH));
    m_labelHeadArea->text = "进入区域";

    left += g_labelW;
    m_labelHeadInTime = new Label(Rect(left, top, left + g_labelW, top + g_labelH));
    m_labelHeadInTime->text = "进入时间";

    left += g_labelW;
    m_labelHeadOutTime = new Label(Rect(left, top, left + g_labelW, top + g_labelH));
    m_labelHeadOutTime->text = "离开时间";

    left += g_labelW;
    m_labelHeadTemperature = new Label(Rect(left, top, left + g_labelW, top + g_labelH));
    m_labelHeadTemperature->text = "体温";

    left += g_labelW;
    m_labelHeadFever = new Label(Rect(left, top, left + g_labelW, top + g_labelH));
    m_labelHeadFever->text = "是否发热";

    left += g_labelW;
    m_labelHeadRetentArea = new Label(Rect(left, top, left + g_labelW, top + g_labelH));
    m_labelHeadRetentArea->text = "滞留地区列表";

    left = 10;
    top += g_labelH;
    m_listViewEpidemic = new listView(Rect(left, top, g_width - 20, g_height / 2));
    m_listViewEpidemic->init(45);


    left = 10 + perW * 2;
    top = 10 + perH * 2;

    m_labelSeqId = new Label(Rect(left, top, left + g_labelW, top + g_labelH));
    m_labelSeqId->text = "登记流水号";

    top += g_labelH;
    m_labelId = new Label(Rect(left, top, left + g_labelW, top + g_labelH));
    m_labelId->text = "学号(工号)";

    top += g_labelH;
    m_labelArea = new Label(Rect(left, top, left + g_labelW, top + g_labelH));
    m_labelArea->text = "进入区域";

    top += g_labelH;
    m_labelInTime = new Label(Rect(left, top, left + g_labelW, top + g_labelH));
    m_labelInTime->text = "进入时间";

    top += g_labelH;
    m_labelOutTime = new Label(Rect(left, top, left + g_labelW, top + g_labelH));
    m_labelOutTime->text = "离开时间";

    top += g_labelH;
    m_labelTemperature = new Label(Rect(left, top, left + g_labelW, top + g_labelH));
    m_labelTemperature->text = "体温";

    top += g_labelH;
    m_labelFever = new Label(Rect(left, top, left + g_labelW, top + g_labelH));
    m_labelFever->text = "是否发热";

    top += g_labelH;
    m_labelRetentArea = new Label(Rect(left, top, left + g_labelW, top + g_labelH));
    m_labelRetentArea->text = "滞留地区列表";

    left = 10 + perW * 2 + g_labelW + 10;
    top = 10 + perH * 2;
    m_btnSeqId = new Button(Rect(left, top, left + g_buttonW, top + g_buttonH));

    top += g_labelH;
    m_btnId = new Button(Rect(left, top, left + g_buttonW, top + g_buttonH));
    top += g_labelH;
    m_btnArea = new Button(Rect(left, top, left + g_buttonW, top + g_buttonH));
    top += g_labelH;
    m_btnInTime = new Button(Rect(left, top, left + g_buttonW, top + g_buttonH));
    top += g_labelH;
    m_btnOutTime = new Button(Rect(left, top, left + g_buttonW, top + g_buttonH));
    top += g_labelH;
    m_btnTemperature = new Button(Rect(left, top, left + g_buttonW, top + g_buttonH));
    top += g_labelH;
    m_btnFever = new Button(Rect(left, top, left + g_buttonW, top + g_buttonH));
    top += g_labelH;
    m_btnRetentArea = new Button(Rect(left, top, left + g_buttonW, top + g_buttonH));


    left = 10 + perW * 2 + g_labelW * 2 + 10;
    top = 10 + perH * 2;
    m_btnAddEpidemic = new Button(Rect(left, top, left + g_buttonW, top + g_buttonH));
    m_btnAddEpidemic->text = "增加疫情信息";
    top += g_labelH;
    m_btnFindEpidemic = new Button(Rect(left, top, left + g_buttonW, top + g_buttonH));
    m_btnFindEpidemic->text = "查询疫情信息";
    top += g_labelH;
    m_btnModifyEpidemic = new Button(Rect(left, top, left + g_buttonW, top + g_buttonH));
    m_btnModifyEpidemic->text = "修改疫情信息";
    top += g_labelH;
    m_btnDelEpidemic = new Button(Rect(left, top, left + g_buttonW, top + g_buttonH));
    m_btnDelEpidemic->text = "删除疫情信息";
    top += g_labelH;
    m_btnCancelEpidemic = new Button(Rect(left, top, left + g_buttonW, top + g_buttonH));
    m_btnCancelEpidemic->text = "取消疫情信息";

    left = 1085;
    top = 720;
    int btnW = g_buttonW / 3.0 * 2 - 3;
    m_btnGotoWndMain = new Button(Rect(left, top, left + btnW, top + g_buttonH));
    m_btnGotoWndMain->text = "跳转到主界面";
}

void EpidemicDraw::handleMessage()
{
    ExMessage msg;
    while (peekmessage(&msg, EM_KEY | EM_MOUSE))
    {
        //鼠标移动，检查是否在按钮上
        if (msg.message == WM_MOUSEMOVE)
        {
            resetButton(btnNormal);

            Point pt(msg.x, msg.y);
            if (m_wndState == wndLogin)
            {
                if (m_btnLogin->ptInRect(pt))
                    m_btnLogin->state = btnHover;
                else if (m_btnExit->ptInRect(pt))
                    m_btnExit->state = btnHover;
            }
            else if (m_wndState == wndMain)
            {
                if (m_btnStuId->ptInRect(pt))
                    m_btnStuId->state = btnHover;
                else if (m_btnCollege->ptInRect(pt))
                    m_btnCollege->state = btnHover;
                else if (m_btnInSchoolTime->ptInRect(pt))
                    m_btnInSchoolTime->state = btnHover;
                else if (m_btnAddStu->ptInRect(pt))
                    m_btnAddStu->state = btnHover;
                else if (m_btnFindStu->ptInRect(pt))
                    m_btnFindStu->state = btnHover;
                else if (m_btnModifyStu->ptInRect(pt))
                    m_btnModifyStu->state = btnHover;
                else if (m_btnDelStu->ptInRect(pt))
                    m_btnDelStu->state = btnHover;
                else if (m_btnCancelStu->ptInRect(pt))
                    m_btnCancelStu->state = btnHover;
                else if (m_btnTeacherId->ptInRect(pt))
                    m_btnTeacherId->state = btnHover;
                else if (m_btnDepartment->ptInRect(pt))
                    m_btnDepartment->state = btnHover;
                else if (m_btnJob->ptInRect(pt))
                    m_btnJob->state = btnHover;
                else if (m_btnJobTime->ptInRect(pt))
                    m_btnJobTime->state = btnHover;
                else if (m_btnAddTeacher->ptInRect(pt))
                    m_btnAddTeacher->state = btnHover;
                else if (m_btnFindTeacher->ptInRect(pt))
                    m_btnFindTeacher->state = btnHover;
                else if (m_btnModifyTeacher->ptInRect(pt))
                    m_btnModifyTeacher->state = btnHover;
                else if (m_btnDelTeacher->ptInRect(pt))
                    m_btnDelTeacher->state = btnHover;
                else if (m_btnCancelTeacher->ptInRect(pt))
                    m_btnCancelTeacher->state = btnHover;
                else if (m_btnGotoWndEpidemic->ptInRect(pt))
                    m_btnGotoWndEpidemic->state = btnHover;
            }
            else if (m_wndState == EnumWndState::wndEpidemic)
            {
                if (m_btnSeqId->ptInRect(pt))
                    m_btnSeqId->state = btnHover;
                else if (m_btnId->ptInRect(pt))
                    m_btnId->state = btnHover;
                else if (m_btnArea->ptInRect(pt))
                    m_btnArea->state = btnHover;
                else if (m_btnInTime->ptInRect(pt))
                    m_btnInTime->state = btnHover;
                else if (m_btnOutTime->ptInRect(pt))
                    m_btnOutTime->state = btnHover;
                else if (m_btnTemperature->ptInRect(pt))
                    m_btnTemperature->state = btnHover;
                else if (m_btnFever->ptInRect(pt))
                    m_btnFever->state = btnHover;
                else if (m_btnRetentArea->ptInRect(pt))
                    m_btnRetentArea->state = btnHover;
                else if (m_btnAddEpidemic->ptInRect(pt))
                    m_btnAddEpidemic->state = btnHover;
                else if (m_btnFindEpidemic->ptInRect(pt))
                    m_btnFindEpidemic->state = btnHover;
                else if (m_btnModifyEpidemic->ptInRect(pt))
                    m_btnModifyEpidemic->state = btnHover;
                else if (m_btnDelEpidemic->ptInRect(pt))
                    m_btnDelEpidemic->state = btnHover;
                else if (m_btnCancelEpidemic->ptInRect(pt))
                    m_btnCancelEpidemic->state = btnHover;
                else if (m_btnGotoWndMain->ptInRect(pt))
                    m_btnGotoWndMain->state = btnHover;
            }
        }
        else if (msg.message == WM_LBUTTONDOWN)
        {
            resetButton(btnNormal);

            Point pt(msg.x, msg.y);
            if (m_wndState == wndLogin)
            {
                if (m_btnLogin->ptInRect(pt))
                    m_btnLogin->state = btnPress;
                else if (m_btnExit->ptInRect(pt))
                    m_btnExit->state = btnPress;
            }
            else if (m_wndState == wndMain)
            {
                if (m_btnStuId->ptInRect(pt))
                    m_btnStuId->state = btnPress;
                else if (m_btnCollege->ptInRect(pt))
                    m_btnCollege->state = btnPress;
                else if (m_btnInSchoolTime->ptInRect(pt))
                    m_btnInSchoolTime->state = btnPress;
                else if (m_btnAddStu->ptInRect(pt))
                    m_btnAddStu->state = btnPress;
                else if (m_btnFindStu->ptInRect(pt))
                    m_btnFindStu->state = btnPress;
                else if (m_btnModifyStu->ptInRect(pt))
                    m_btnModifyStu->state = btnPress;
                else if (m_btnDelStu->ptInRect(pt))
                    m_btnDelStu->state = btnPress;
                else if (m_btnCancelStu->ptInRect(pt))
                    m_btnCancelStu->state = btnPress;
                else if (m_btnTeacherId->ptInRect(pt))
                    m_btnTeacherId->state = btnPress;
                else if (m_btnDepartment->ptInRect(pt))
                    m_btnDepartment->state = btnPress;
                else if (m_btnJob->ptInRect(pt))
                    m_btnJob->state = btnPress;
                else if (m_btnJobTime->ptInRect(pt))
                    m_btnJobTime->state = btnPress;
                else if (m_btnAddTeacher->ptInRect(pt))
                    m_btnAddTeacher->state = btnPress;
                else if (m_btnFindTeacher->ptInRect(pt))
                    m_btnFindTeacher->state = btnPress;
                else if (m_btnModifyTeacher->ptInRect(pt))
                    m_btnModifyTeacher->state = btnPress;
                else if (m_btnDelTeacher->ptInRect(pt))
                    m_btnDelTeacher->state = btnPress;
                else if (m_btnCancelTeacher->ptInRect(pt))
                    m_btnCancelTeacher->state = btnPress;
                else if (m_btnGotoWndEpidemic->ptInRect(pt))
                    m_btnGotoWndEpidemic->state = btnPress;
            }
            else if (m_wndState == EnumWndState::wndEpidemic)
            {
                if (m_btnSeqId->ptInRect(pt))
                    m_btnSeqId->state = btnPress;
                else if (m_btnId->ptInRect(pt))
                    m_btnId->state = btnPress;
                else if (m_btnArea->ptInRect(pt))
                    m_btnArea->state = btnPress;
                else if (m_btnInTime->ptInRect(pt))
                    m_btnInTime->state = btnPress;
                else if (m_btnOutTime->ptInRect(pt))
                    m_btnOutTime->state = btnPress;
                else if (m_btnTemperature->ptInRect(pt))
                    m_btnTemperature->state = btnPress;
                else if (m_btnFever->ptInRect(pt))
                    m_btnFever->state = btnPress;
                else if (m_btnRetentArea->ptInRect(pt))
                    m_btnRetentArea->state = btnPress;
                else if (m_btnAddEpidemic->ptInRect(pt))
                    m_btnAddEpidemic->state = btnPress;
                else if (m_btnFindEpidemic->ptInRect(pt))
                    m_btnFindEpidemic->state = btnPress;
                else if (m_btnModifyEpidemic->ptInRect(pt))
                    m_btnModifyEpidemic->state = btnPress;
                else if (m_btnDelEpidemic->ptInRect(pt))
                    m_btnDelEpidemic->state = btnPress;
                else if (m_btnCancelEpidemic->ptInRect(pt))
                    m_btnCancelEpidemic->state = btnPress;
                else if (m_btnGotoWndMain->ptInRect(pt))
                    m_btnGotoWndMain->state = btnPress;
            }
        }
        else if (msg.message == WM_LBUTTONUP)
        {
            Point pt(msg.x, msg.y);
            Button* buttonClick = NULL;

            if (m_wndState == wndLogin)
            {
                if (m_btnLogin->ptInRect(pt))
                    buttonClick =m_btnLogin;
                else if (m_btnExit->ptInRect(pt))
                    buttonClick = m_btnExit;
            }
            else if (m_wndState == wndMain)
            {
                if (m_btnStuId->ptInRect(pt))
                    buttonClick = m_btnStuId;
                else if (m_btnCollege->ptInRect(pt))
                    buttonClick = m_btnCollege;
                else if (m_btnInSchoolTime->ptInRect(pt))
                    buttonClick = m_btnInSchoolTime;
                else if (m_btnAddStu->ptInRect(pt))
                    buttonClick = m_btnAddStu;
                else if (m_btnFindStu->ptInRect(pt))
                    buttonClick = m_btnFindStu;
                else if (m_btnModifyStu->ptInRect(pt))
                    buttonClick = m_btnModifyStu;
                else if (m_btnDelStu->ptInRect(pt))
                    buttonClick = m_btnDelStu;
                else if (m_btnCancelStu->ptInRect(pt))
                    buttonClick = m_btnCancelStu;
                else if (m_btnTeacherId->ptInRect(pt))
                    buttonClick = m_btnTeacherId;
                else if (m_btnDepartment->ptInRect(pt))
                    buttonClick = m_btnDepartment;
                else if (m_btnJob->ptInRect(pt))
                    buttonClick = m_btnJob;
                else if (m_btnJobTime->ptInRect(pt))
                    buttonClick = m_btnJobTime;
                else if (m_btnAddTeacher->ptInRect(pt))
                    buttonClick = m_btnAddTeacher;
                else if (m_btnFindTeacher->ptInRect(pt))
                    buttonClick = m_btnFindTeacher;
                else if (m_btnModifyTeacher->ptInRect(pt))
                    buttonClick = m_btnModifyTeacher;
                else if (m_btnDelTeacher->ptInRect(pt))
                    buttonClick = m_btnDelTeacher;
                else if (m_btnCancelTeacher->ptInRect(pt))
                    buttonClick = m_btnCancelTeacher;
                else if (m_btnGotoWndEpidemic->ptInRect(pt))
                    buttonClick = m_btnGotoWndEpidemic;
            }
            else if (m_wndState == wndEpidemic)
            {
                if (m_btnSeqId->ptInRect(pt))
                    buttonClick = m_btnSeqId;
                else if (m_btnId->ptInRect(pt))
                    buttonClick = m_btnId;
                else if (m_btnArea->ptInRect(pt))
                    buttonClick = m_btnArea;
                else if (m_btnInTime->ptInRect(pt))
                    buttonClick = m_btnInTime;
                else if (m_btnOutTime->ptInRect(pt))
                    buttonClick = m_btnOutTime;
                else if (m_btnTemperature->ptInRect(pt))
                    buttonClick = m_btnTemperature;
                else if (m_btnFever->ptInRect(pt))
                    buttonClick = m_btnFever;
                else if (m_btnRetentArea->ptInRect(pt))
                    buttonClick = m_btnRetentArea;
                else if (m_btnAddEpidemic->ptInRect(pt))
                    buttonClick = m_btnAddEpidemic;
                else if (m_btnFindEpidemic->ptInRect(pt))
                    buttonClick = m_btnFindEpidemic;
                else if (m_btnModifyEpidemic->ptInRect(pt))
                    buttonClick = m_btnModifyEpidemic;
                else if (m_btnDelEpidemic->ptInRect(pt))
                    buttonClick = m_btnDelEpidemic;
                else if (m_btnCancelEpidemic->ptInRect(pt))
                    buttonClick = m_btnCancelEpidemic;
                else if (m_btnGotoWndMain->ptInRect(pt))
                    buttonClick = m_btnGotoWndMain;
            }

            if (buttonClick != NULL)
            {
                buttonClick->state = btnHover;
                handleButtonClick(buttonClick);
            }
        }
        else if (msg.message == WM_MOUSEWHEEL)
        {
            if (m_wndState == wndMain)
            {
                m_listViewStudent->mouseRoll(msg.wheel);
            }
        }
    }
}

void EpidemicDraw::draw()
{
    //绘制背景
    drawbk();

    if (m_wndState == EnumWndState::wndLogin)
    {
        drawWndLogin();
    }
    else if (m_wndState == EnumWndState::wndMain)
    {
        drawWndMain();
    }
    else if (m_wndState == EnumWndState::wndEpidemic)
    {
        drawWndEpidemic();
    }

    //刷新批量绘制
    FlushBatchDraw();
}

void EpidemicDraw::drawbk()
{
    //旧颜色
    COLORREF oldClr = getfillcolor();

    setfillcolor(RGB(233, 233, 233));
    //绘制背景
    fillrectangle(0, 0, g_width, g_height);
    //恢复旧颜色
    setfillcolor(oldClr);


    //绘制背景图
    putimage(0, 0, m_background);
}

void EpidemicDraw::drawWndLogin()
{
    //绘制大标题
    drawBigTitle();

    COLORREF oldcolor = gettextcolor();
    LOGFONT oldstyle;
    gettextstyle(&oldstyle);

    settextcolor(RGB(40, 40, 40));
    settextstyle(33, 12, _T("微软雅黑"));

    m_btnLogin->draw();
    m_btnExit->draw();

    settextcolor(oldcolor);
    settextstyle(&oldstyle);
}

void EpidemicDraw::drawWndMain()
{
    m_labelHeadStuId->draw();
    m_labelHeadCollege->draw();
    m_labelHeadInSchoolTime->draw();

    m_listViewStudent->draw();

    m_labelStuId->draw();
    m_labelCollege->draw();
    m_labelInSchoolTime->draw();


    COLORREF oldcolor = gettextcolor();
    LOGFONT oldstyle;
    gettextstyle(&oldstyle);

    settextcolor(RGB(40, 40, 40));
    m_btnStuId->draw();
    m_btnCollege->draw();
    m_btnInSchoolTime->draw();

    m_btnAddStu->draw();
    m_btnFindStu->draw();
    m_btnModifyStu->draw();
    m_btnDelStu->draw();
    m_btnCancelStu->draw();

    settextcolor(oldcolor);
    settextstyle(&oldstyle);

    m_labelHeadTeachId->draw();
    m_labelHeadDepartment->draw();
    m_labelHeadJob->draw();
    m_labelHeadJobTime->draw();

    m_listViewTeacher->draw();

    m_labelTeachId->draw();
    m_labelDepartment->draw();
    m_labelJob->draw();
    m_labelJobTime->draw();
    gettextstyle(&oldstyle);

    settextcolor(RGB(40, 40, 40));

    m_btnTeacherId->draw();
    m_btnDepartment->draw();
    m_btnJob->draw();
    m_btnJobTime->draw();

    m_btnAddTeacher->draw();
    m_btnFindTeacher->draw();
    m_btnModifyTeacher->draw();
    m_btnDelTeacher->draw();
    m_btnCancelTeacher->draw();

    m_btnGotoWndEpidemic->draw();

    settextcolor(oldcolor);
    settextstyle(&oldstyle);
}

void EpidemicDraw::drawWndEpidemic()
{
    COLORREF oldcolor = gettextcolor();
    LOGFONT oldstyle;
    gettextstyle(&oldstyle);

    m_labelHeadSeqId->draw();
    m_labelHeadId->draw();
    m_labelHeadArea->draw();
    m_labelHeadInTime->draw();
    m_labelHeadOutTime->draw();
    m_labelHeadTemperature->draw();
    m_labelHeadFever->draw();
    m_labelHeadRetentArea->draw();

    m_listViewEpidemic->draw();

    m_labelSeqId->draw();
    m_labelId->draw();
    m_labelArea->draw();
    m_labelInTime->draw();
    m_labelOutTime->draw();
    m_labelTemperature->draw();
    m_labelFever->draw();
    m_labelRetentArea->draw();

    settextcolor(RGB(40, 40, 40));

    m_btnSeqId->draw();
    m_btnId->draw();
    m_btnArea->draw();
    m_btnInTime->draw();
    m_btnOutTime->draw();
    m_btnTemperature->draw();
    m_btnFever->draw();
    m_btnRetentArea->draw();

    m_btnAddEpidemic->draw();
    m_btnFindEpidemic->draw();
    m_btnModifyEpidemic->draw();
    m_btnDelEpidemic->draw();
    m_btnCancelEpidemic->draw();

    m_btnGotoWndMain->draw();

    m_area[0].draw();
    m_area[1].draw();
    m_area[2].draw();
    m_area[3].draw();

    settextcolor(oldcolor);
    settextstyle(&oldstyle);
}

void EpidemicDraw::drawBigTitle()
{
    COLORREF oldcolor = gettextcolor();
    LOGFONT oldstyle;
    gettextstyle(&oldstyle);

    //设置文字颜色
    settextcolor(RGB(50, 50, 250));
    //设置字体 用大字体
    settextstyle(200, 60, _T("微软雅黑"));

    //窗口大小
    Rect wndRect(0, 0, getwidth(), getheight());

    Rect titleRect = wndRect;
    int w = titleRect.width();
    int h = titleRect.height();

    titleRect.bottom = titleRect.bottom / 2;

    RECT rc = { titleRect.left,titleRect.top,titleRect.right,titleRect.bottom };
    for (int i = 0; i < 7; i++)
    {
        titleRect.offset(1, 1);
        rc = { titleRect.left,titleRect.top,titleRect.right,titleRect.bottom };
        drawtext("校园疫情管理系统", &rc, DT_CENTER | DT_SINGLELINE | DT_VCENTER);
    }


    settextcolor(RGB(178, 202, 2));
    titleRect.offset(1, 1);
    rc = { titleRect.left,titleRect.top,titleRect.right,titleRect.bottom };
    drawtext("校园疫情管理系统", &rc, DT_CENTER | DT_SINGLELINE | DT_VCENTER);

    settextcolor(oldcolor);
    settextstyle(&oldstyle);
}

void EpidemicDraw::doEnterSystem()
{
    m_wndState = wndMain;
}

void EpidemicDraw::doExitSystem()
{
    m_exit = true;
}

void EpidemicDraw::doAddStudent()
{
    if (isNewStudentInfoFull() == false)
    {
        ::MessageBox(GetHWnd(), "请将新增信息填写完整", "校园疫情管理系统", MB_OK);
        return;
    }

    StudentInfo* stuInfo = new StudentInfo();
    stuInfo->m_id = m_btnStuId->text;
    stuInfo->m_college = m_btnCollege->text;
    stuInfo->m_inSchoolTime = m_btnInSchoolTime->text;
    if (m_system->addStudentInfo(stuInfo) == false)
    {
        delete stuInfo;
        ::MessageBox(GetHWnd(), "学号信息已存在，重复添加", "校园疫情管理系统", MB_OK);
        return;
    }

    m_currStudent = stuInfo;
    //添加到listview

    int perW = m_listViewStudent->rect.width() / 3;
    int perH = 40;

    listItem* item = m_listViewStudent->addItem();
    item->userData = (void*)stuInfo;

    COLORREF labelcolor = RGB(74, 128, 216);
    Label* labelStudentId = item->addLabel();
    Label* labelStudentCollege = item->addLabel();
    Label* labelInSchoolTime = item->addLabel();

    labelStudentId->color = labelcolor;
    labelStudentCollege->color = labelcolor;
    labelInSchoolTime->color = labelcolor;

    labelStudentId->text = stuInfo->m_id;
    labelStudentCollege->text = stuInfo->m_college;
    labelInSchoolTime->text = stuInfo->m_inSchoolTime;

    labelStudentId->rect.setRect(perW * 0, 0, perW * 0 + g_labelW, g_labelH);
    labelStudentCollege->rect.setRect(perW * 1, 0, perW * 1 + g_labelW, g_labelH);
    labelInSchoolTime->rect.setRect(perW * 2, 0, perW * 2 + g_labelW, g_labelH);
}

void EpidemicDraw::doFindStudent()
{
    if (m_btnStuId->text.empty())
    {
        ::MessageBox(GetHWnd(), "请输入学号", "校园疫情管理系统", MB_OK);
        return;
    }

    StudentInfo* info = m_system->findStudentInfo(m_btnStuId->text);
    if (info == nullptr)
    {
        ::MessageBox(GetHWnd(), "没有该学号的学生信息", "校园疫情管理系统", MB_OK);
        return;
    }

    //当前学生信息
    m_currStudent = info;

    m_btnCollege->text = info->m_college;
    m_btnInSchoolTime->text = info->m_inSchoolTime;
}

void EpidemicDraw::doModifyStudent()
{
    if (m_btnStuId->text.empty())
    {
        ::MessageBox(GetHWnd(), "请先查询学号", "校园疫情管理系统", MB_OK);
        return;
    }
    if (m_currStudent == nullptr)
    {
        ::MessageBox(GetHWnd(), "请先查询学号", "校园疫情管理系统", MB_OK);
        return;
    }


    if (m_currStudent->m_id != m_btnStuId->text)
    {
        ::MessageBox(GetHWnd(), "学号不允许修改，已重置", "校园疫情管理系统", MB_OK);
        m_btnStuId->text = m_currStudent->m_id;
    }

    m_currStudent->m_college = m_btnCollege->text;
    m_currStudent->m_inSchoolTime = m_btnInSchoolTime->text;

    m_system->modifyStudentInfo(m_currStudent);

}

void EpidemicDraw::doDelStudent()
{
    if (m_btnStuId->text.empty())
    {
        ::MessageBox(GetHWnd(), "请先查询学号", "校园疫情管理系统", MB_OK);
        return;
    }

    if (m_currStudent == nullptr)
    {
        ::MessageBox(GetHWnd(), "请先查询学号", "校园疫情管理系统", MB_OK);
        return;
    }

    if (m_system->delStudentInfo(m_currStudent)==false)
    {
        ::MessageBox(GetHWnd(), "没有该学号的学生信息", "校园疫情管理系统", MB_OK);
        return;
    }

    m_listViewStudent->removeItemByUserData(m_currStudent);

    doCancelStudent();
}

void EpidemicDraw::doCancelStudent()
{
    m_currStudent = nullptr;

    m_btnStuId->text.clear();
    m_btnCollege->text.clear();
    m_btnInSchoolTime->text.clear();

}

void EpidemicDraw::doAddTeacher()
{
    if (isNewTeacherInfoFull() == false)
    {
        ::MessageBox(GetHWnd(), "请将新增信息填写完整", "校园疫情管理系统", MB_OK);
        return;
    }

    TeacherInfo* info = new TeacherInfo();
    info->m_id = m_btnTeacherId->text;
    info->m_department = m_btnDepartment->text;
    info->m_job = m_btnJob->text;
    info->m_jobTime = m_btnJobTime->text;

    if (m_system->addTeacherInfo(info) == false)
    {
        delete info;
        ::MessageBox(GetHWnd(), "工号信息已存在，重复添加", "校园疫情管理系统", MB_OK);
        return;
    }

    m_currTeacher = info;

    int perW = m_listViewTeacher->rect.width() / 4;
    int perH = 40;

    listItem* item = m_listViewTeacher->addItem();
    item->userData = (void*)info;

    COLORREF labelcolor = RGB(74, 128, 216);
    Label* labelTeacherId = item->addLabel();
    Label* labelDepartment = item->addLabel();
    Label* labelJob = item->addLabel();
    Label* labelJobTime = item->addLabel();

    labelTeacherId->color = labelcolor;
    labelDepartment->color = labelcolor;
    labelJob->color = labelcolor;
    labelJobTime->color = labelcolor;

    labelTeacherId->text = info->m_id;
    labelDepartment->text = info->m_department;
    labelJob->text = info->m_job;
    labelJobTime->text = info->m_jobTime;

    labelTeacherId->rect.setRect(perW * 0, 0, perW * 0 + g_labelW, g_labelH);
    labelDepartment->rect.setRect(perW * 1, 0, perW * 1 + g_labelW, g_labelH);
    labelJob->rect.setRect(perW * 2, 0, perW * 2 + g_labelW, g_labelH);
    labelJobTime->rect.setRect(perW * 3, 0, perW * 3 + g_labelW, g_labelH);

}

void EpidemicDraw::doFindTeacher()
{
    if (m_btnTeacherId->text.empty())
    {
        ::MessageBox(GetHWnd(), "请输入工号", "校园疫情管理系统", MB_OK);
        return;
    }

    TeacherInfo* info = m_system->findTeacherInfo(m_btnTeacherId->text);
    if (info == nullptr)
    {
        ::MessageBox(GetHWnd(), "没有该工号的教师信息", "校园疫情管理系统", MB_OK);
        return;
    }

    m_currTeacher = info;

    m_btnTeacherId->text = info->m_id;
    m_btnDepartment->text = info->m_department;
    m_btnJob->text = info->m_job;
    m_btnJobTime->text = info->m_jobTime;
}

void EpidemicDraw::doModifyTeacher()
{
    if (m_btnTeacherId->text.empty())
    {
        ::MessageBox(GetHWnd(), "请输入工号", "校园疫情管理系统", MB_OK);
        return;
    }
    
    if (m_currTeacher->m_id != m_btnTeacherId->text)
    {
        ::MessageBox(GetHWnd(), "工号不允许修改，已重置", "校园疫情管理系统", MB_OK);
        m_btnTeacherId->text = m_currTeacher->m_id;
    }

    m_currTeacher->m_department = m_btnDepartment->text;
    m_currTeacher->m_job = m_btnJob->text;
    m_currTeacher->m_jobTime = m_btnJobTime->text;

}

void EpidemicDraw::doDelTeacher()
{
    if (m_btnTeacherId->text.empty())
    {
        ::MessageBox(GetHWnd(), "请输入工号", "校园疫情管理系统", MB_OK);
        return;
    }

    if (m_currTeacher == nullptr)
    {
        ::MessageBox(GetHWnd(), "请输入工号", "校园疫情管理系统", MB_OK);
        return;
    }

    if (m_system->delTeacherInfo(m_currTeacher) == false)
    {
        ::MessageBox(GetHWnd(), "没有该工号的教师信息", "校园疫情管理系统", MB_OK);
        return;
    }

    m_listViewTeacher->removeItemByUserData(m_currTeacher);

    doCancelTeacher();
}

void EpidemicDraw::doCancelTeacher()
{
    m_currTeacher = nullptr;

    m_btnTeacherId->text.clear();
    m_btnDepartment->text.clear();
    m_btnJob->text.clear();
    m_btnJobTime->text.clear();
}

void EpidemicDraw::doSetStudentId()
{
    char str[100] = {0};
    if (InputBox(str, 100, "输入学号","校园疫情管理系统",m_btnStuId->text.c_str()))
        m_btnStuId->text = str;
}

void EpidemicDraw::doSetStudentCollege()
{
    char str[100] = { 0 };
    if (InputBox(str, 100, "输入学院", "校园疫情管理系统", m_btnCollege->text.c_str()))
        m_btnCollege->text = str;
}

void EpidemicDraw::doSetStudentInSchoolTime()
{
    char str[100] = { 0 };
    if (InputBox(str, 100, "输入入学时间", "校园疫情管理系统", m_btnInSchoolTime->text.c_str()))
        m_btnInSchoolTime->text = str;
}

void EpidemicDraw::doSetTeacherId()
{
    char str[100] = { 0 };
    if (InputBox(str, 100, "输入工号", "校园疫情管理系统", m_btnTeacherId->text.c_str()))
        m_btnTeacherId->text = str;
}

void EpidemicDraw::doSetTeacherDepartment()
{
    char str[100] = { 0 };
    if (InputBox(str, 100, "输入部门", "校园疫情管理系统", m_btnDepartment->text.c_str()))
        m_btnDepartment->text = str;
}

void EpidemicDraw::doSetTeacherJob()
{
    char str[100] = { 0 };
    if (InputBox(str, 100, "输入职务", "校园疫情管理系统", m_btnJob->text.c_str()))
        m_btnJob->text = str;
}

void EpidemicDraw::doSetTeacherJobTime()
{
    char str[100] = { 0 };
    if (InputBox(str, 100, "输入入职时间", "校园疫情管理系统", m_btnJobTime->text.c_str()))
        m_btnJobTime->text = str;
}

bool EpidemicDraw::isNewStudentInfoFull()
{
    if (m_btnStuId->text.empty())
        return false;
    if (m_btnCollege->text.empty())
        return false;
    if (m_btnInSchoolTime->text.empty())
        return false;

    return true;
}

bool EpidemicDraw::isNewTeacherInfoFull()
{
    if (m_btnTeacherId->text.empty())
        return false;
    if (m_btnDepartment->text.empty())
        return false;
    if (m_btnJob->text.empty())
        return false;
    if (m_btnJobTime->text.empty())
        return false;

    return true;
}

void EpidemicDraw::doEnterWndEpicdemic()
{
    m_wndState = EnumWndState::wndEpidemic;
}

bool EpidemicDraw::isNewEpidemicInfoFull()
{
    if (m_btnSeqId->text.empty())
        return false;
    if (m_btnId->text.empty()) 
        return false;
    if (m_btnArea->text.empty())
        return false;
    if (m_btnInTime->text.empty())
        return false;
    if (m_btnOutTime->text.empty())
        return false;
    if (m_btnTemperature->text.empty())
        return false;
    if (m_btnFever->text.empty())
        return false;
    if (m_btnRetentArea->text.empty())
        return false;

    return true;
}

void EpidemicDraw::doSetSeqId()
{
    char str[100] = { 0 };
    if (InputBox(str, 100, "输入流水号", "校园疫情管理系统", m_btnSeqId->text.c_str()))
        m_btnSeqId->text = str;
}

void EpidemicDraw::doSetId()
{
    char str[100] = { 0 };
    if (InputBox(str, 100, "输入学号（工号）", "校园疫情管理系统", m_btnId->text.c_str()))
        m_btnId->text = str;
}

void EpidemicDraw::doSetArea()
{
    char str[100] = { 0 };
    if (InputBox(str, 100, "进入区域(宿舍区，教学区，图书馆，体育场)", "校园疫情管理系统", m_btnArea->text.c_str()))
        m_btnArea->text = str;
}

void EpidemicDraw::doSetInTime()
{
    char str[100] = { 0 };
    if (InputBox(str, 100, "进入时间", "校园疫情管理系统", m_btnInTime->text.c_str()))
        m_btnInTime->text = str;
}

void EpidemicDraw::doSetOutTime()
{
    char str[100] = { 0 };
    if (InputBox(str, 100, "离开时间", "校园疫情管理系统", m_btnOutTime->text.c_str()))
        m_btnOutTime->text = str;
}

void EpidemicDraw::doSetTemperature()
{
    char str[100] = { 0 };
    if (InputBox(str, 100, "体温", "校园疫情管理系统", m_btnTemperature->text.c_str()))
        m_btnTemperature->text = str;
}

void EpidemicDraw::doSetFever()
{
    char str[100] = { 0 };
    if (InputBox(str, 100, "是否发热", "校园疫情管理系统", m_btnFever->text.c_str()))
        m_btnFever->text = str;
}

void EpidemicDraw::doSetRetentArea()
{
    char str[100] = { 0 };
    if (InputBox(str, 100, "滞留地区列表", "校园疫情管理系统", m_btnRetentArea->text.c_str()))
        m_btnRetentArea->text = str;
}

void EpidemicDraw::doAddEpidemic()
{
    if (isNewEpidemicInfoFull() == false)
    {
        ::MessageBox(GetHWnd(), "请将新增信息填写完整", "校园疫情管理系统", MB_OK);
        return;
    }

    if (m_btnId->text.find("JS") != -1)//教师工号 JS***
    {
        if (m_system->findTeacherInfo(m_btnId->text) == nullptr)
        {
            ::MessageBox(GetHWnd(), "请输入正确学号或工号", "校园疫情管理系统", MB_OK);
            return;
        }
    }
    else
    {
        if (m_system->findStudentInfo(m_btnId->text) == nullptr)
        {
            ::MessageBox(GetHWnd(), "请输入正确学号或工号", "校园疫情管理系统", MB_OK);
            return;
        }
    }
    if (m_btnArea->text != "宿舍区"
        && m_btnArea->text != "教学区"
        && m_btnArea->text != "图书馆"
        && m_btnArea->text != "体育场")
    {
        ::MessageBox(GetHWnd(), "请输入正确区域（宿舍区，教学区，图书馆，体育场）", "校园疫情管理系统", MB_OK);
        return;
    }

    EpidemicRegisterInfo* info = new EpidemicRegisterInfo();
    info->m_seqId = m_btnSeqId->text;
    info->m_id = m_btnId->text;
    info->m_area = m_btnArea->text;
    info->m_inTime = m_btnInTime->text;
    info->m_outTime = m_btnOutTime->text;
    info->m_temperature = m_btnTemperature->text;
    info->m_fever = m_btnFever->text == "发热" ? true : false;
    info->m_retentAeraList.push_back(m_btnRetentArea->text);

    if (m_system->addEpidemicRegisterInfo(info) == false)
    {
        delete info;
        ::MessageBox(GetHWnd(), "流水号信息已存在，重复添加", "校园疫情管理系统", MB_OK);
        return;
    }

    m_currEpidemic = info;

    int perW = m_listViewEpidemic->rect.width() / 8;
    int perH = 40;

    listItem* item = m_listViewEpidemic->addItem();
    item->userData = (void*)info;

    COLORREF labelcolor = RGB(74, 128, 216);
    Label* labelSeqId = item->addLabel();
    Label* labelId = item->addLabel();
    Label* labelArea = item->addLabel();
    Label* labelInTime = item->addLabel();
    Label* labelOutTime = item->addLabel();
    Label* labelTemperature = item->addLabel();
    Label* labelFever = item->addLabel();
    Label* labelRetentArea = item->addLabel();

    labelSeqId->color = labelcolor;
    labelId->color = labelcolor;
    labelArea->color = labelcolor;
    labelInTime->color = labelcolor;
    labelOutTime->color = labelcolor;
    labelTemperature->color = labelcolor;
    labelFever->color = labelcolor;
    labelRetentArea->color = labelcolor;

    labelSeqId->text = info->m_seqId;
    labelId->text = info->m_id;
    labelArea->text = info->m_area;
    labelInTime->text = info->m_inTime;
    labelOutTime->text = info->m_outTime;
    labelTemperature->text = info->m_temperature;
    labelFever->text = info->m_fever ? "发热" : "正常";
    labelRetentArea->text = info->m_retentAeraList.begin()->c_str();

    labelSeqId->rect.setRect(perW * 0, 0, perW * 0 + g_labelW, g_labelH);
    labelId->rect.setRect(perW * 1, 0, perW * 1 + g_labelW, g_labelH);
    labelArea->rect.setRect(perW * 2, 0, perW * 2 + g_labelW, g_labelH);
    labelInTime->rect.setRect(perW * 3, 0, perW * 3 + g_labelW, g_labelH);
    labelOutTime->rect.setRect(perW * 4, 0, perW * 4 + g_labelW, g_labelH);
    labelTemperature->rect.setRect(perW * 5, 0, perW * 5 + g_labelW, g_labelH);
    labelFever->rect.setRect(perW * 6, 0, perW * 6 + g_labelW, g_labelH);
    labelRetentArea->rect.setRect(perW * 7, 0, perW * 7 + g_labelW, g_labelH);

    //同步每个区域感染情况
    changeAreaFever(m_currEpidemic->m_area, m_currEpidemic->m_fever, true);

}

void EpidemicDraw::doFindEpidemic()
{
    if (m_btnSeqId->text.empty())
    {
        ::MessageBox(GetHWnd(), "请输入流水号", "校园疫情管理系统", MB_OK);
        return;
    }

    EpidemicRegisterInfo* info = m_system->findEpidemicRegisterInfo(m_btnSeqId->text);

    if (info == nullptr)
    {
        ::MessageBox(GetHWnd(), "没有该流水号的疫情登记信息", "校园疫情管理系统", MB_OK);
        return;
    }

    m_currEpidemic = info;

    m_btnSeqId->text = info->m_seqId;
    m_btnId->text = info->m_id;
    m_btnArea->text = info->m_area;
    m_btnInTime->text = info->m_inTime;
    m_btnOutTime->text = info->m_outTime;
    m_btnTemperature->text = info->m_temperature;
    m_btnFever->text = info->m_fever ? "发热" : "正常";
    m_btnRetentArea->text = info->m_retentAeraList.begin()->c_str();

}

void EpidemicDraw::doModifyEpidemic()
{
    if (m_btnSeqId->text.empty())
    {
        ::MessageBox(GetHWnd(), "请输入流水号", "校园疫情管理系统", MB_OK);
        return;
    }

    if (m_currEpidemic == nullptr)
    {
        ::MessageBox(GetHWnd(), "请输入流水号", "校园疫情管理系统", MB_OK);
        return;
    }

    std::string oldArea = m_currEpidemic->m_area;
    bool oldFever = m_currEpidemic->m_fever;

    m_currEpidemic->m_seqId = m_btnSeqId->text;
    m_currEpidemic->m_id = m_btnId->text;
    m_currEpidemic->m_area = m_btnArea->text;
    m_currEpidemic->m_inTime = m_btnInTime->text;
    m_currEpidemic->m_outTime = m_btnOutTime->text;
    m_currEpidemic->m_temperature = atof(m_btnTemperature->text.c_str());
    m_currEpidemic->m_fever = m_btnOutTime->text == "发热" ? true : false;
    m_currEpidemic->m_retentAeraList.push_back(m_btnRetentArea->text);


    if (m_system->modifyEpidemicRegisterInfo(m_currEpidemic))
    {
        changeAreaFever(oldArea, oldFever, false);
        changeAreaFever(m_currEpidemic->m_area, m_currEpidemic->m_fever, true);
    }
}

void EpidemicDraw::doDelEpidemic()
{
    if (m_btnSeqId->text.empty())
    {
        ::MessageBox(GetHWnd(), "请输入流水号", "校园疫情管理系统", MB_OK);
        return;
    }

    if (m_currEpidemic == nullptr)
    {
        ::MessageBox(GetHWnd(), "请输入流水号", "校园疫情管理系统", MB_OK);
        return;
    }

    bool oldFever = m_currEpidemic->m_fever;
    std::string oldArea = m_currEpidemic->m_area;
    if (m_system->delEpidemicRegisterInfo(m_currEpidemic))
    {
        changeAreaFever(oldArea, oldFever, false);

        m_listViewEpidemic->removeItemByUserData(m_currEpidemic);
        m_currEpidemic = nullptr;
    }
}

void EpidemicDraw::doCancelEpidemic()
{
    m_btnSeqId->text.clear();
    m_btnId->text.clear();
    m_btnArea->text.clear();
    m_btnInTime->text.clear();
    m_btnOutTime->text.clear();
    m_btnTemperature->text.clear();
    m_btnFever->text.clear();
    m_btnRetentArea->text.clear();

    m_currEpidemic = nullptr;
}

void EpidemicDraw::changeAreaFever(std::string areaName, bool fever, bool add)
{
    //同步每个区域感染情况
    if (areaName == "宿舍区")
    {
        if (add)
            m_area[0].totalnum++;
        else
            m_area[0].totalnum--;


        if (fever)
        {
            if(add)
                m_area[0].num++;
            else
                m_area[0].num--;
            changeAreaColor(&m_area[0]);
        }
    }
    else if (m_currEpidemic->m_area == "教学区")
    {
        if (add)
            m_area[1].totalnum++;
        else
            m_area[1].totalnum--;


        if (fever)
        {
            if (add)
                m_area[1].num++;
            else
                m_area[1].num--;
            changeAreaColor(&m_area[1]);
        }
    }
    else if (m_currEpidemic->m_area == "图书馆")
    {
        if (add)
            m_area[2].totalnum++;
        else
            m_area[2].totalnum--;


        if (fever)
        {
            if (add)
                m_area[2].num++;
            else
                m_area[2].num--;
            changeAreaColor(&m_area[2]);
        }
    }
    else if (m_currEpidemic->m_area == "体育场")
    {
        if (add)
            m_area[3].totalnum++;
        else
            m_area[3].totalnum--;


        if (fever)
        {
            if (add)
                m_area[3].num++;
            else
                m_area[3].num--;
            changeAreaColor(&m_area[3]);
        }
    }
}

void EpidemicDraw::changeAreaColor(Area* area)
{
    if (area->num >= 3)
        area->color = RGB(255, 0, 0);
    else if (area->num >= 2)
        area->color = RGB(255, 128, 0);
    else if (area->num >= 1)
        area->color = RGB(255, 255, 0);
    else
        area->color = RGB(0, 255, 0);
}

void EpidemicDraw::resetButton(EnumButtonState state)
{
    m_btnLogin->state = state;
    m_btnExit->state = state;

    m_btnStuId->state = state;
    m_btnCollege->state = state;
    m_btnInSchoolTime->state = state;

    m_btnAddStu->state = state;
    m_btnFindStu->state = state;
    m_btnModifyStu->state = state;
    m_btnDelStu->state = state;
    m_btnCancelStu->state = state;

    m_btnTeacherId->state = state;
    m_btnDepartment->state = state;
    m_btnJob->state = state;
    m_btnJobTime->state = state;

    m_btnAddTeacher->state = state;
    m_btnFindTeacher->state = state;
    m_btnModifyTeacher->state = state;
    m_btnDelTeacher->state = state;
    m_btnFindTeacher->state = state;
    m_btnCancelTeacher->state = state;

    m_btnGotoWndEpidemic->state = state;

    m_btnSeqId->state = state;
    m_btnId->state = state;
    m_btnArea->state = state;
    m_btnInTime->state = state;
    m_btnOutTime->state = state;
    m_btnTemperature->state = state;
    m_btnFever->state = state;
    m_btnRetentArea->state = state;

    m_btnAddEpidemic->state = state;
    m_btnFindEpidemic->state = state;
    m_btnModifyEpidemic->state = state;
    m_btnDelEpidemic->state = state;
    m_btnCancelEpidemic->state = state;

    m_btnGotoWndMain->state = state;
}

void EpidemicDraw::handleButtonClick(Button* buttonClick)
{
    if (buttonClick == m_btnLogin)
        doEnterSystem();
    else if (buttonClick == m_btnExit)
        doExitSystem();
    else if (buttonClick == m_btnStuId)
        doSetStudentId();
    else if (buttonClick == m_btnCollege)
        doSetStudentCollege();
    else if (buttonClick == m_btnInSchoolTime)
        doSetStudentInSchoolTime();
    else if (buttonClick == m_btnAddStu)
        doAddStudent();
    else if (buttonClick == m_btnFindStu)
        doFindStudent();
    else if (buttonClick == m_btnModifyStu)
        doModifyStudent();
    else if (buttonClick == m_btnDelStu)
        doDelStudent();
    else if (buttonClick == m_btnCancelStu)
        doCancelStudent();
    else if (buttonClick == m_btnTeacherId)
        doSetTeacherId();
    else if (buttonClick == m_btnDepartment)
        doSetTeacherDepartment();
    else if (buttonClick == m_btnJob)
        doSetTeacherJob();
    else if (buttonClick == m_btnJobTime)
        doSetTeacherJobTime();
    else if (buttonClick == m_btnAddTeacher)
        doAddTeacher();
    else if (buttonClick == m_btnFindTeacher)
        doFindTeacher();
    else if (buttonClick == m_btnModifyTeacher)
        doModifyTeacher();
    else if (buttonClick == m_btnDelTeacher)
        doDelTeacher();
    else if (buttonClick == m_btnCancelTeacher)
        doCancelTeacher();
    else if (buttonClick == m_btnGotoWndEpidemic)
        doEnterWndEpicdemic();
    else if (buttonClick == m_btnSeqId)
        doSetSeqId();
    else if (buttonClick == m_btnId)
        doSetId();
    else if (buttonClick == m_btnArea)
        doSetArea();
    else if (buttonClick == m_btnInTime)
        doSetInTime();
    else if (buttonClick == m_btnOutTime)
        doSetOutTime();
    else if (buttonClick == m_btnTemperature)
        doSetTemperature();
    else if (buttonClick == m_btnFever)
        doSetFever();
    else if (buttonClick == m_btnRetentArea)
        doSetRetentArea();
    else if (buttonClick == m_btnGotoWndMain)
        doEnterSystem();
    else if (buttonClick == m_btnAddEpidemic)
        doAddEpidemic();
    else if (buttonClick == m_btnFindEpidemic)
        doFindEpidemic();
    else if (buttonClick == m_btnModifyEpidemic)
        doModifyEpidemic();
    else if (buttonClick == m_btnDelEpidemic)
        doDelEpidemic();
    else if (buttonClick == m_btnCancelEpidemic)
        doCancelEpidemic();
}
