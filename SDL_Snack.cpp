/*************************************************************************
	> File Name: SDL_Snack.cpp
	> Author:zhengcong 
	> Mail: 1142052012@qq.com
	> Created Time: 2016年10月04日 星期二 11时12分29秒
 ************************************************************************/
#include "SDL_Snack.h"

                                                    //变量注释位置标记
                                    //函数参数注释位置标记

CSnack::CSnack(int Length)
{
    m_Snack.resize(Length); 
    for(int i = 0;i != Length;i++)
    {
        m_Snack[Length-i-1].x = 0;
        m_Snack[Length-i-1].y = i;
    }
    m_Direction = 1;
}

bool CSnack::Move(SDL_Point food)
{
    SDL_Point Temp = m_Snack[0];
    switch(m_Direction)
    {
        case 0:
            Temp.y--;
            m_Snack.insert(m_Snack.begin(),Temp);
            break;
        case 1:
            Temp.y++;
            m_Snack.insert(m_Snack.begin(),Temp);
            break;
        case 2:
            Temp.x --;
            m_Snack.insert(m_Snack.begin(),Temp);
            break;
        case 3:
            Temp.x ++;
            m_Snack.insert(m_Snack.begin(),Temp);
            break;
    }
    if((Temp.x == food.x)&&(Temp.y == food.y))
    {
        return true;
    }
    m_Snack.pop_back();
    return false;
}

bool CSnack::BiteSelf(SDL_Point point)
{
    for(int i = 0;i != m_Snack.size();i++)
    {
        if((m_Snack[i].x == point.x)&&(m_Snack[i].y == point.y))
        {
#ifdef _SDL_DEBUG
            cout << "bite point = " << i  << endl;
            cout << "m_Snack[i] = " << m_Snack[i].x << "," << m_Snack[i].y << endl;
            cout << "point = " << point.x << "." << point.y << endl << endl << endl;
#endif
            return true;
        }
    }
    return false;
}

bool CSnack::CheckDie()
{
    SDL_Point temp = m_Snack[0];
    switch(m_Direction)
    {
        case 0:
            temp.y--;
            if((temp.y < 0)||BiteSelf(temp))
            {
#ifdef _SDL_DEBUG
                cout << "the snack died" << endl;
                cout << "m_Direction = " << m_Direction << endl;
                cout << "m_Snack[0] = " << m_Snack[0].x << "," << m_Snack[0].y << endl;
                cout << "BiteSelf(temp) = " << BiteSelf(temp) << endl;
                cout << "temp = " << temp.x  << "," << temp.y << endl << endl << endl;
#endif
                return true;
            }
            break;
        case 1:
            temp.y ++;
            if((temp.y >= MAP_HEIGHT)||BiteSelf(temp))
            {
#ifdef _SDL_DEBUG
                cout << "the snack died" << endl;
                cout << "m_Direction = " << m_Direction << endl;
                cout << "m_Snack[0] = " << m_Snack[0].x << "," << m_Snack[0].y << endl;
                cout << "BiteSelf(temp) =  " << BiteSelf(temp) << endl;
                cout << "temp = " << temp.x << "," << temp.y << endl << endl << endl;
#endif
                return true;
            }
            break;
        case 2:
            temp.x --;
            if((temp.x < 0)||BiteSelf(temp))
            {
#ifdef _SDL_DEBUG
                cout << "the snack died" << endl;
                cout << "m_Direction = " << m_Direction << endl;
                cout << "m_Snack[0] = " << m_Snack[0].x << "," << m_Snack[0].y << endl;
                cout << "BiteSelf(temp) = " << BiteSelf(temp) << endl;
                cout << BiteSelf(temp) << endl;
                cout << (temp.x < 0) << endl;
                cout << "temp = " << temp.x << "," << temp.y << endl << endl << endl;
#endif
                return true;
            }
            break;
        case 3:
            temp.x ++;
            if((temp.x >= MAP_WIDTH)||BiteSelf(temp))
            {
#ifdef _SDL_DEBUG
                cout << "the snack died" << endl;
                cout << "m_Direction = " << m_Direction << endl;
                cout << "m_Snack[0] = " << m_Snack[0].x << "," << m_Snack[0].y << endl;
                cout << "BiteSelf(temp) = " << BiteSelf(temp) << endl;
                cout << "temp = " << temp.x << "," << temp.y << endl << endl << endl;
#endif
                return true;
            }
            break;
    }
    return false;
}

bool CSnack::SetDirection(int direction)
{
    if(((m_Direction == 0)&&(direction == 1))||((m_Direction == 2)&&(direction == 3))||((m_Direction == 1)&&(direction == 0))||((m_Direction == 3)&&(direction == 2)))
    {
#ifdef _SDL_DEBUG
        cout << "cann't change the direction" << endl;
        cout << "m_Direction = " << m_Direction << endl;
        cout << "direction = " << direction << endl << endl << endl;
#endif
        return false;
    }
    m_Direction = direction;
    return true;
}

void CSnack::Render(SDL_Window* window)
{
    int width = 0;
    int height = 0;
    SDL_GetWindowSize(window,&width,&height);
    width /= MAP_WIDTH;
    height /= MAP_HEIGHT;
    SDL_Renderer* renderer = SDL_GetRenderer(window);
    SDL_SetRenderDrawColor(renderer,0xff,0xff,0xff,0xff);
    for(int i = 0;i != m_Snack.size();i++)
    {
        SDL_Rect rect = {m_Snack[i].x*width,m_Snack[i].y*height,width,height};
        SDL_RenderFillRect(renderer,&rect);
    }
}

void CSnack::Restart()
{
    m_Snack.resize(10);
    for(int i = 0;i != 10;i++)
    {
        m_Snack[10-i-1] = {0,i};
    }
    m_Direction = 1;
}
