/*************************************************************************
	> File Name: SDL_Snack.h
	> Author: zhengcong
	> Mail: 1142052012@qq.com
	> Created Time: 2016年10月04日 星期二 10时40分48秒
 ************************************************************************/

#ifndef SDL_SNACK_H
#define SDL_SNACK_H

#define _SDL_DEBUG

                                                //变量注释位置标记
                                    //函数参数注释位置标记

#include <SDL2/SDL.h>                           //SDL头文件
#include <vector>

using std::vector;


#ifdef _SDL_DEBUG
#include <iostream>                             //调试用头文件
using std::cout;
using std::endl;

#endif
    
const int MAP_WIDTH = 80;                  //窗口一共被分为多少列
const int MAP_HEIGHT = 45;                 //窗口一共被分为多少行

class CSnack
{
private:

   vector<SDL_Point> m_Snack;                   //蛇 

    int m_Direction;                            //蛇的移动方向
    
    bool BiteSelf(SDL_Point point);
public:

    /*
    * 构造函数
    * 参数int Length = 10           :蛇的初始长度
    *
    * 无返回值
    */
    CSnack(int Length = 10);


    /*
    * 移动蛇
    * 无参数
    * 无返回值
    */
    bool Move(SDL_Point food);


    /*
    * 判断蛇是否已经死亡
    * 无参数
    * bool die                      :死亡返回true，否则返回false
    */
    bool CheckDie();

    /*重新开始
     *无参数
    *无返回值
    **/
    void Restart();

    /*
    * 设置方向
    * 参数int direction             :方向，0上，1下，2左，3右
    * 返回值                        ：设置成功返回true,否则返回false;
    */
    bool SetDirection(int direction);

    void Render(SDL_Window* window);
};


#endif
