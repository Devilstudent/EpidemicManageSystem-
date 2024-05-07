#pragma once

#include <iostream>
#include <list>

//��ʦ��Ϣ
struct TeacherInfo
{
    std::string m_id;                           //��ʦId
    std::string m_department;                   //����
    std::string m_job;                          //ְ��
    std::string m_jobTime;                      //��ְʱ��
};

//ѧ����Ϣ
struct StudentInfo
{
    std::string m_id;                           //ѧ��id
    std::string m_college;                      //ѧԺ
    std::string m_inSchoolTime;                 //��ѧʱ��
};

//����Ǽ���Ϣ
struct EpidemicRegisterInfo
{
public:
    std::string m_seqId;                        //�Ǽ���ˮ��
    std::string m_id;                           //ѧ�Ż��߹���
    std::string m_area;                         //��������
    std::string m_inTime;                       //����ʱ��
    std::string m_outTime;                      //����ʱ��
    std::string m_temperature;                  //����
    bool  m_fever;                              //7���Ƿ���
    std::list<std::string> m_retentAeraList;    //���������б�
};

//��ʦ�б���
class TeacherList : public std::list<TeacherInfo*>
{
public:
    //��ѯinfo �Ƿ����б�
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
    //��id��ѯ ��ʦ����
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

    //��id ɾ��
    bool removeValue(TeacherInfo* info)
    {
        TeacherList::iterator it = this->begin();
        for (; it != this->end(); it++)
        {
            TeacherInfo* tempInfo = *it;
            if (info->m_id == tempInfo->m_id)
            {
                //ɾ����Ӧ����
                this->erase(it);
                return true;
            }
        }
        return false;
    }

};

//ѧ���б���
class StudentList : public std::list<StudentInfo*>
{
public:
    //��ѯinfo �Ƿ����б�
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
    //��id��ѯ ѧ������
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

    //��id ɾ��
    bool removeValue(StudentInfo* info)
    {
        StudentList::iterator it = this->begin();
        for (; it != this->end(); it++)
        {
            StudentInfo* tempInfo = *it;
            if (info->m_id == tempInfo->m_id)
            {
                //ɾ����Ӧ����
                this->erase(it);
                return true;
            }
        }

        return false;
    }
};

//�Ǽ���Ϣ�б�
class EpidemicRegisterList : public std::list<EpidemicRegisterInfo*>
{
public:
    //��ѯinfo �Ƿ����б�
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

    //��seqId ɾ��
    bool removeValue(EpidemicRegisterInfo* info)
    {
        EpidemicRegisterList::iterator it = this->begin();
        for (; it != this->end(); it++)
        {
            EpidemicRegisterInfo* tempInfo = *it;
            if (info->m_seqId == tempInfo->m_seqId)
            {
                //ɾ����Ӧ����
                this->erase(it);
                return true;
            }
        }

        return false;
    }

};

//����������
struct DateEpidemicRegisterInfo
{
    std::string m_date;                         //����
    EpidemicRegisterList  m_list;               //�Ǽ���Ϣ�б�
};

class DateEpidemicRegisterList : public std::list<DateEpidemicRegisterInfo*>
{
public:
    //��ѯinfo �Ƿ����б�
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

    //��ѯĳ���ڵ� �Ǽ�����
    DateEpidemicRegisterInfo* valueAt(std::string date)
    {
        DateEpidemicRegisterInfo* info = nullptr;

        DateEpidemicRegisterList::iterator it = this->begin();
        for (; it != this->end(); it++)
        {
            DateEpidemicRegisterInfo* tempInfo = *it;
            if (date == tempInfo->m_date)
            {
                //�ҵ���ĳ���� ����
                info = tempInfo;
                break;
            }
        }

        return info;
    }
};



//�������ϵͳ
class EpidemicSystem
{
public:
    EpidemicSystem();
    ~EpidemicSystem();

    //��ʼ��
    void initialize();
    //����ʼ��
    void uninitialize();
    //���ӽ�ʦ
    bool addTeacherInfo(TeacherInfo* teacherInfo);
    //���ҽ�ʦ
    TeacherInfo* findTeacherInfo(std::string teacherId);
    //�޸Ľ�ʦ
    bool modifyTeacherInfo(TeacherInfo* teacherInfo);
    //ɾ����ʦ
    bool delTeacherInfo(TeacherInfo* teacherInfo);


    //����ѧ��
    bool addStudentInfo(StudentInfo* studentInfo);
    //����ѧ��
    StudentInfo* findStudentInfo(std::string studentId);
    //�޸�ѧ��
    bool modifyStudentInfo(StudentInfo* studentInfo);
    //ɾ��ѧ��
    bool delStudentInfo(StudentInfo* studentInfo);

    //������ �Ǽ���Ϣ
    bool addEpidemicRegisterInfo(EpidemicRegisterInfo* info);
    //���� ����Ǽ���Ϣ
    EpidemicRegisterInfo* findEpidemicRegisterInfo(std::string seqId);
    //�޸� ����Ǽ���Ϣ
    bool modifyEpidemicRegisterInfo(EpidemicRegisterInfo* info);
    //ɾ�� ����Ǽ���Ϣ
    bool delEpidemicRegisterInfo(EpidemicRegisterInfo* info);
protected:
    TeacherList m_teacherList;                                  //��ʦ�б�
    StudentList m_studentList;                                  //ѧ���б�

    EpidemicRegisterList m_list;                                //�Ǽ���Ϣ�б�

    //����Ҫ���¹���
    //DateEpidemicRegisterList m_dateEpidemicRegisterList;        //���ڣ��Ǽ���Ϣ�б�
};

