#pragma once
#include <graphics.h>
#include <string>
#include <list>

class Point
{
public:
    Point()
        :x(0), y(0)
    {}
    Point(int x1, int y1)
        :x(x1), y(y1)
    {}

    int x;
    int y;

};

struct Rect
{
    Rect()
    {
        left = 0;
        top = 0;
        right = 0;
        bottom = 0;
    }
    Rect(int l, int t, int r, int b)
    {
        left = l;
        top = t;
        right = r;
        bottom = b;
    }
    int left, right, top, bottom;

    int width() {
        return right - left;
    }
    int height() {
        return bottom - top;
    }

    void offset(int x, int y) {
        left += x;
        right += x;
        top += y;
        bottom += y;
    }

    Rect inflate(int x, int y) {
        left += x;
        right -= x;
        top += y;
        bottom -= y;

        return *this;
    }

    void setRect(int l, int t, int r, int b) 
    {
        left = l;
        top = t;
        right = r;
        bottom = b;
    }

    bool ptInRect(Point pt) {
        if (pt.x >= left && pt.x <= right
            && pt.y >= top && pt.y <= bottom)
        {
            return true;
        }
        return false;
    }
};


enum EnumButtonState
{
    btnNormal =0,
    btnHover =1,
    btnPress =2,
};

struct Button
{
    Button()
    {
        state = btnNormal;
    }

    Button(Rect rect)
    {
        this->rect = rect;
        state = btnNormal;
    }

    Rect rect;          //��ť��С
    int id;             //��ťid
    std::string text;   //��ť����
    int state;          //��ť״̬   EnumButtonState

    bool ptInRect(Point pt)
    {
        return rect.ptInRect(pt);
    }
    void draw()
    {
        COLORREF color;
        switch (state)
        {
        case btnNormal:
            color = RGB(255, 255, 221);
            break;
        case btnHover:
            color = RGB(255, 187, 119);
            break;
        case btnPress:
            color = RGB(185, 147, 39);
            break;
        default:
            break;
        }
        COLORREF oldcolor = getfillcolor();
        setfillcolor(color);

        fillrectangle(rect.left, rect.top, rect.right, rect.bottom);

        RECT rc = { rect.left, rect.top, rect.right, rect.bottom };
        drawtext(text.c_str(), &rc, DT_SINGLELINE | DT_CENTER | DT_VCENTER);

        setfillcolor(oldcolor);
    }
};

struct Label
{
    Label()
    {
        id = 0;
        color = RGB(0, 0, 0);
    }
    
    Label(Rect rect)
    {
        this->rect = rect;
        id = 0;
        color = RGB(0, 0, 0);
    }

    Rect rect;              //��ǩ��С
    int id;                 //��ǩid
    std::string text;       //��ǩ����
    COLORREF color;         //��ǩ��ɫ
    void draw()
    {
        COLORREF oldcolor = gettextcolor();
        settextcolor(color);
        setbkmode(TRANSPARENT);
        RECT rc = { rect.left, rect.top, rect.right, rect.bottom };
        drawtext(text.c_str(), &rc, DT_SINGLELINE | DT_CENTER | DT_VCENTER);

        settextcolor(oldcolor);
    }

};

struct listItem
{
    Rect rect;

    Label* labels[20];  //����label
    int labelCnt;
    void* userData;     //�û����� ���ڱȽ�ɾ��
    void draw()
    {
        for (int i = 0; i < labelCnt; i++)
        {
            labels[i]->draw();
        }
    }
    Label* addLabel() 
    {
        Label* label = new Label();
        labels[labelCnt++] = label;
        return label;
    }

    Label* getLabelByIdx(int idx)
    {
        if (idx < 0 || idx >= labelCnt)
            return NULL;

        return labels[idx];
    }
};

struct listItemList : public std::list<listItem*>
{
public:
    listItem* at(int idx)
    {
        int size = this->size();
        if (idx < 0 || idx >= size)
            return nullptr;

        listItemList::iterator it = this->begin();
        int i = 0;
        for (; i < idx; it++, i++)
        { 
        }

        return *it;
    }

    bool removeValue(listItem* item)
    {
        listItemList::iterator it = this->begin();

        for (; it != this->end(); it++)
        {
            listItem* tmpItem = *it;
            if (*it == item)
            {
                this->erase(it);
                return true;
            }
        }

        return false;
    }
};
//�б�ؼ�
struct listView
{
    listView()
    {
        itemHeight = 0;
        roll = 0;
    }
    listView(Rect rect)
    {
        this->rect = rect;
        itemHeight = 0;
        roll = 0;
    }
    Rect rect;

    int itemHeight;             //�б���߶�
    listItemList items;         //�б�����������
    int roll;                   //�б������ֵ
    HRGN hrgn;                  //�б��ü���Χ


    //��ʼ��
    void init(int height)
    {
        itemHeight = height;
        roll = 0;
        hrgn = CreateRectRgn(rect.left, rect.top, rect.right, rect.bottom);
    }
    void draw()
    {
        //���òü���Χ

        setcliprgn(hrgn);

        setfillcolor(RGB(45, 45, 45));
        fillrectangle(rect.left, rect.top, rect.right, rect.bottom);
        for (int i = 0; i < items.size(); i++)
        {
            setorigin(rect.left, rect.top + i * itemHeight + roll);
            items.at(i)->draw();
        }
        setorigin(0, 0);
        setcliprgn(NULL);
    }
    //�����ִ���
    void mouseRoll(int delta)
    {
        //�б����ܸ߶�С�ڵ����б�߶� ����Ҫ ����
        int subHeight = itemHeight * items.size() - (rect.bottom - rect.top);
        if (subHeight < 0)
        {
            return;
        }

        //�߶Ȳ�ֵ

        if (delta > 0)
        {
            roll += itemHeight / 2;
            if (roll > 0)
                roll = 0;
        }
        else
        {
            //�������£� �б�����
            roll -= itemHeight / 2;
            if (roll < -subHeight)
                roll = -subHeight;
        }
    }
    //���һ���б���
    listItem* addItem()
    {
        listItem* item = new listItem();

        items.push_back(item);
        return item;
    }
    //��ȡ�б���
    listItem* getItemByIdx(int idx)
    {
        return items.at(idx);
    }

    //��ȡ�б���
    listItem* getItemByUserData(void* userData)
    {
        for (int i = 0; i < items.size(); i++)
        {
            if (items.at(i)->userData == userData)
            {
                return items.at(i);
            }
        }

        return nullptr;
    }

    //ɾ���б���
    void removeItem(listItem* item)
    {
        items.removeValue(item);
    }

    //ɾ���б���
    void removeItemByUserData(void* userData)
    {
        for (int i = 0; i < items.size(); i++)
        {
            listItem* item = items.at(i);
            if (item->userData == userData)
            {
                items.remove(item);
            }
        }
    }
};
