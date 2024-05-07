#pragma once

#include <iostream>
#include <list>

//教师信息
struct TeacherInfo
{
    std::string m_id;                           //教师Id
    std::string m_department;                   //部门
    std::string m_job;                          //职务
    std::string m_jobTime;                      //入职时间
};

//学生信息
struct StudentInfo
{
    std::string m_id;                           //学生id
    std::string m_college;                      //学院
    std::string m_inSchoolTime;                 //入学时间
};

//疫情登记信息
struct EpidemicRegisterInfo
{
public:
    std::string m_seqId;                        //登记流水号
    std::string m_id;                           //学号或者工号
    std::string m_area;                         //进入区域
    std::string m_inTime;                       //进门时间
    std::string m_outTime;                      //出门时间
    std::string m_temperature;                  //体温
    bool  m_fever;                              //7日是否发热
    std::list<std::string> m_retentAeraList;    //滞留地区列表
};

//教师列表类
class TeacherList : public std::list<TeacherInfo*>
{
public:
    //查询info 是否在列表
    bool isContain(TeacherInfo* teacherInfo)
    {
        TeacherList::iterator it = this->begin();
        for (; it != this->end(); it++)
        {
            TeacherInfo* tempInfo = *it;
            if (teacherInfo->m_id == tempInfo->m_id)
            {
                return true;
            }
        }

        return false;
    }
    //按id查询 教师数据
    TeacherInfo* valueAt(std::string id)
    {
        TeacherInfo* info = nullptr;

        TeacherList::iterator it = this->begin();
        for (; it != this->end(); it++)
        {
            TeacherInfo* tempInfo = *it;
            if (id == tempInfo->m_id)
            {
                info = tempInfo;
                break;
            }
        }

        return info;
    }

    //按id 删除
    bool removeValue(TeacherInfo* info)
    {
        TeacherList::iterator it = this->begin();
        for (; it != this->end(); it++)
        {
            TeacherInfo* tempInfo = *it;
            if (info->m_id == tempInfo->m_id)
            {
                //删除对应数据
                this->erase(it);
                return true;
            }
        }
        return false;
    }

};

//学生列表类
class StudentList : public std::list<StudentInfo*>
{
public:
    //查询info 是否在列表
    bool isContain(StudentInfo* studentInfo)
    {
        StudentList::iterator it = this->begin();
        for (; it != this->end(); it++)
        {
            StudentInfo* tempInfo = *it;
            if (studentInfo->m_id == tempInfo->m_id)
            {
                return true;
            }
        }

        return false;
    }
    //按id查询 学生数据
    StudentInfo* valueAt(std::string id)
    {
        StudentInfo* info = nullptr;

        StudentList::iterator it = this->begin();
        for (; it != this->end(); it++)
        {
            StudentInfo* tempInfo = *it;
            if (id == tempInfo->m_id)
            {
                info = tempInfo;
                break;
            }
        }

        return info;
    }

    //按id 删除
    bool removeValue(StudentInfo* info)
    {
        StudentList::iterator it = this->begin();
        for (; it != this->end(); it++)
        {
            StudentInfo* tempInfo = *it;
            if (info->m_id == tempInfo->m_id)
            {
                //删除对应数据
                this->erase(it);
                return true;
            }
        }

        return false;
    }
};

//登记信息列表
class EpidemicRegisterList : public std::list<EpidemicRegisterInfo*>
{
public:
    //查询info 是否在列表
    bool isContain(EpidemicRegisterInfo* epidemicRegisterInfo)
    {
        EpidemicRegisterList::iterator it = this->begin();
        for (; it != this->end(); it++)
        {
            EpidemicRegisterInfo* tempInfo = *it;
            if (epidemicRegisterInfo->m_id == tempInfo->m_id)
            {
                return true;
            }
        }

        return false;
    }
    EpidemicRegisterInfo* valueAt(std::string seqId)
    {
        EpidemicRegisterList::iterator it = this->begin();
        for (; it != this->end(); it++)
        {
            EpidemicRegisterInfo* info = *it;
            if (info->m_seqId == seqId)
            {
                return info;
            }
        }
        return nullptr;
    }

    //按seqId 删除
    bool removeValue(EpidemicRegisterInfo* info)
    {
        EpidemicRegisterList::iterator it = this->begin();
        for (; it != this->end(); it++)
        {
            EpidemicRegisterInfo* tempInfo = *it;
            if (info->m_seqId == tempInfo->m_seqId)
            {
                //删除对应数据
                this->erase(it);
                return true;
            }
        }

        return false;
    }

};

//按日期数据
struct DateEpidemicRegisterInfo
{
    std::string m_date;                         //日期
    EpidemicRegisterList  m_list;               //登记信息列表
};

class DateEpidemicRegisterList : public std::list<DateEpidemicRegisterInfo*>
{
public:
    //查询info 是否在列表
    bool isContain(DateEpidemicRegisterInfo* dateEpidemicRegisterInfo)
    {
        DateEpidemicRegisterList::iterator it = this->begin();
        for (; it != this->end(); it++)
        {
            DateEpidemicRegisterInfo* tempInfo = *it;
            if (dateEpidemicRegisterInfo->m_date == tempInfo->m_date)
            {
                return true;
            }
        }
        return false;
    }

    //查询某日期的 登记数据
    DateEpidemicRegisterInfo* valueAt(std::string date)
    {
        DateEpidemicRegisterInfo* info = nullptr;

        DateEpidemicRegisterList::iterator it = this->begin();
        for (; it != this->end(); it++)
        {
            DateEpidemicRegisterInfo* tempInfo = *it;
            if (date == tempInfo->m_date)
            {
                //找到了某日期 数据
                info = tempInfo;
                break;
            }
        }

        return info;
    }
};



//疫情管理系统
class EpidemicSystem
{
public:
    EpidemicSystem();
    ~EpidemicSystem();

    //初始化
    void initialize();
    //返初始化
    void uninitialize();
    //增加教师
    bool addTeacherInfo(TeacherInfo* teacherInfo);
    //查找教师
    TeacherInfo* findTeacherInfo(std::string teacherId);
    //修改教师
    bool modifyTeacherInfo(TeacherInfo* teacherInfo);
    //删除教师
    bool delTeacherInfo(TeacherInfo* teacherInfo);


    //增加学生
    bool addStudentInfo(StudentInfo* studentInfo);
    //查找学生
    StudentInfo* findStudentInfo(std::string studentId);
    //修改学生
    bool modifyStudentInfo(StudentInfo* studentInfo);
    //删除学生
    bool delStudentInfo(StudentInfo* studentInfo);

    //按日期 登记信息
    bool addEpidemicRegisterInfo(EpidemicRegisterInfo* info);
    //查找 疫情登记信息
    EpidemicRegisterInfo* findEpidemicRegisterInfo(std::string seqId);
    //修改 疫情登记信息
    bool modifyEpidemicRegisterInfo(EpidemicRegisterInfo* info);
    //删除 疫情登记信息
    bool delEpidemicRegisterInfo(EpidemicRegisterInfo* info);
protected:
    TeacherList m_teacherList;                                  //教师列表
    StudentList m_studentList;                                  //学生列表

    EpidemicRegisterList m_list;                                //登记信息列表

    //不需要如下功能
    //DateEpidemicRegisterList m_dateEpidemicRegisterList;        //日期，登记信息列表
};

