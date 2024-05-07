// EpidemicManage.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <graphics.h>
#include "EpidemicDraw.h"

int main()
{
    EpidemicDraw epidemicDraw;

    epidemicDraw.initWindow();

    //批量绘制开始
    BeginBatchDraw();
    clock_t begin = clock();

    while (!epidemicDraw.m_exit)
    {
        //1.首先处理消息
        epidemicDraw.handleMessage();

        clock_t now = clock();
        clock_t delta = now - begin;
        //人眼接受的1秒 24帧  
        //40毫秒绘制一次 相当于1秒28帧，刚好
        if (delta < 40)
        {
            continue;
        }
        begin = now;
        //绘制draw
        epidemicDraw.draw();
    }

    //结束批量绘制
    EndBatchDraw();

    epidemicDraw.closeWindow();
    return 0;
}
