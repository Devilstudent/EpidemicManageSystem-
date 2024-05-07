#include "EpidemicSystem.h"

EpidemicSystem::EpidemicSystem()
{

}

EpidemicSystem::~EpidemicSystem()
{

}

void EpidemicSystem::initialize()
{

}

void EpidemicSystem::uninitialize()
{

}

bool EpidemicSystem::addTeacherInfo(TeacherInfo* teacherInfo)
{
    if (m_teacherList.valueAt(teacherInfo->m_id) != nullptr)
    {
        //不允许重复添加
        return false;
    }

    m_teacherList.push_back(teacherInfo);
    return true;
}

TeacherInfo* EpidemicSystem::findTeacherInfo(std::string teacherId)
{
    return m_teacherList.valueAt(teacherId);
}

bool EpidemicSystem::modifyTeacherInfo(TeacherInfo* teacherInfo)
{
    TeacherInfo* tmpInfo = m_teacherList.valueAt(teacherInfo->m_id);
    if (tmpInfo == nullptr)
    {
        //没有对应数据
        return false;
    }

    tmpInfo->m_job = teacherInfo->m_job;
    tmpInfo->m_jobTime = teacherInfo->m_jobTime;
    tmpInfo->m_department = teacherInfo->m_department;

    return true;
}

bool EpidemicSystem::delTeacherInfo(TeacherInfo* teacherInfo)
{
    TeacherInfo* tmpInfo = m_teacherList.valueAt(teacherInfo->m_id);

    if (tmpInfo == nullptr)
        return false;

    m_teacherList.removeValue(teacherInfo);
    return true;
}

bool EpidemicSystem::addStudentInfo(StudentInfo* studentInfo)
{
    if (m_studentList.valueAt(studentInfo->m_id) != nullptr)
    {
        //不允许重复添加
        return false;
    }

    m_studentList.push_back(studentInfo);
    return true;

}

StudentInfo* EpidemicSystem::findStudentInfo(std::string studentId)
{
    return m_studentList.valueAt(studentId);
}

bool EpidemicSystem::modifyStudentInfo(StudentInfo* studentInfo)
{
    StudentInfo* tmpInfo = m_studentList.valueAt(studentInfo->m_id);
    if (tmpInfo == nullptr)
    {
        //没有对应数据
        return false;
    }

    tmpInfo->m_inSchoolTime = studentInfo->m_inSchoolTime;
    tmpInfo->m_college = studentInfo->m_college;
    return true;
}

bool EpidemicSystem::delStudentInfo(StudentInfo* studentInfo)
{
    StudentInfo* tmpInfo = m_studentList.valueAt(studentInfo->m_id);
    if (tmpInfo == nullptr)
        return false;

    m_studentList.removeValue(tmpInfo);
    return true;
}

bool EpidemicSystem::addEpidemicRegisterInfo(EpidemicRegisterInfo* info)
{
    if (m_list.valueAt(info->m_seqId) != nullptr)
    {
        //不要添加重复数据
        return false;
    }

    m_list.push_back(info);
    return true;
}

EpidemicRegisterInfo* EpidemicSystem::findEpidemicRegisterInfo(std::string seqId)
{
    return m_list.valueAt(seqId);
}

bool EpidemicSystem::modifyEpidemicRegisterInfo(EpidemicRegisterInfo* info)
{
    EpidemicRegisterInfo* tmpInfo = m_list.valueAt(info->m_seqId);
    if (tmpInfo == nullptr)
    {
        //没有对应数据
        return false;
    }

    //tmpInfo->m_seqId = info->m_seqId;
    tmpInfo->m_id = info->m_id;
    tmpInfo->m_inTime = info->m_inTime;
    tmpInfo->m_outTime = info->m_outTime;
    tmpInfo->m_temperature = info->m_temperature;
    tmpInfo->m_fever = info->m_fever;
    tmpInfo->m_retentAeraList = info->m_retentAeraList;

    return true;
}

bool EpidemicSystem::delEpidemicRegisterInfo(EpidemicRegisterInfo* info)
{
    EpidemicRegisterInfo* tmpInfo = m_list.valueAt(info->m_seqId);
    if (tmpInfo == nullptr)
    {
        //没有对应数据
        return false;
    }

    m_list.removeValue(tmpInfo);
    return true;
}
