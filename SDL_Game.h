/************************************************************************
*****�ļ���				:SDL_Game.h									*****
*****����				:CGame										*****
*****�汾��				:ver 0.2									*****
*****����޸���			:֣��										*****
*************************************************************************/



#ifndef CGAME_H
#define CGAME_H

#define _SDL_DEBUG


																//��Ա����ע��λ�ñ��
									//��������ע��λ�ñ��

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "SDL_Timer.h"
#include "SDL_Snack.h"
#include <ctime>

#ifdef _SDL_DEBUG

#include <iostream>

using std::cout;
using std::cin;
using std::endl;

#endif

using std::string;


class CGame
{
private:
	//�������ݿ�
	int m_Width	;												//��ǰ���ڵĿ��
	int m_Height;												//��ǰ���ڵĸ߶�

	//��Ϸ���ƿ�
	bool m_Quit;												//�Ƿ��Ƴ�������Ϸ
	bool m_QuitGame;											//�Ƿ��Ƴ������Ϸ

	//���ں���Ⱦ��
	SDL_Window* m_Window;										//��Ϸ����Ҫ����
	SDL_Renderer* m_Renderer;									//���ڵ���Ⱦ��

	SDL_Texture* m_StartImage;									//��Ϸ��ʼʱ��ʾ��ͼƬ

	CTimer m_MainTimer;											//��ʱ��

    int m_Level;                                                //��ҵļ���

    int m_Score;                                                //

    TTF_Font* m_Font;                                             //����

    
    CSnack m_Snack;

    SDL_Point m_Food;

	//��������
public:
	//���캯������������

	/**���캯��
	*����string Title = ""			:��������ʱ�ı��⣬Ĭ��Ϊ�ձ���
	*����int X = 100				:��������ʱ�ĺ����꣬Ĭ��Ϊ100
	*����int Y = 100				:��������ʱ�������꣬Ĭ��Ϊ100
	*����int Width = 500			:��������ʱ�Ŀ�ȣ�Ĭ��Ϊ500
	*����int Height = 500			:��������ʱ�ĸ߶ȣ�Ĭ��Ϊ500
	*����SDL_WindowFlags Flag = SDL_WINDOW_SHOWN	:��������ʱ�����ԣ�Ĭ������ʾ״̬����������Ϊ����֮һ��
	*											SDL_WINDOW_ALLOW_HIGHDPI		:���������DPI�Ĵ���
	*											SDL_WINDOW_BORDERLESS			:�����ޱ߿�Ĵ���
	*											SDL_WINDOW_FOREIGN				:�����ⲿ����
	*											SDL_WINDOW_FULLSCREEN			:��ȫ��ģʽ�������ڣ���ȫ�������С��Ļ�ķֱ��ʣ�
	*											SDL_WINDOW_FULLSCREEN_DESKTOP	:��ȫ��ģʽ�������ڣ���ȫ���������С��Ļ�ֱ��ʣ�
	*											SDL_WINDOW_HIDDEN				:����ʱ���ش���
	*											SDL_WINDOW_INPUT_FOCUS			:����ʱ����۽�
	*											SDL_WINDOW_INPUT_GRABBED		:����ʱץȡ����
	*											SDL_WINDOW_MAXIMIZED			:����ʱ��󻯴���
	*											SDL_WINDOW_MINIMIZED			:����ʱ��С������
	*											SDL_WINDOW_MOUSE_CAPTURE		:�����������
	*											SDL_WINDOW_OPENGL				:����������OpenGL�Ĵ���
	*											SDL_WINDOW_SHOWN				:����ʱ��ʾ����
	*											SDL_WINDOW_RESIZABLE			:�����ɵ�����С�Ĵ���
	*											SDL_WINDOW_MOUSE_FOCUS			:����ʱ���۽��ڴ˴���
	*�޷���ֵ
	*����									:����������ڳɹ����ͽ�����ָ��ָ��δ��ڣ����Զ�����Ⱦ��ָ��ָ��ô��ڶ�Ӧ����Ⱦ��
	*������									:�ô���ָ��ָ��һ�����ڣ�����Ⱦ��ָ��ָ�򴰿ڶ�Ӧ����Ⱦ��
	*���Ա��								:δ����
	*/
	CGame(string Title = "", int X = 100, int Y = 100, int Width = 500, int Height = 500);

	/**��������
	*�޲���
	*�޷���ֵ
	*����									:�������ָ�벻Ϊ�գ������ٴ��ڣ������Ⱦ��ָ�벻Ϊ�գ���������Ⱦ��
	*������									:���ٴ��ڣ�������ָ��ָ��գ�������Ⱦ����������ָ��ָ���
	*���Ա��								:δ����
	*/
	~CGame();


	//��ʼǰ׼����

	/**��ʼ�����ں���
	*����									:ͬ���캯��
	*����ֵ									:�����ɹ�����true,һ�����ִ��󣬷���false;
	*����									:ͬ���캯��
	*������									:ͬ���캯��
	*���Ա��								:δ����
	*/
	bool InitWindow(string title = "", int X = 0, int Y = 0, int Width = 100, int Height = 100, SDL_WindowFlags Flag = SDL_WINDOW_SHOWN);

	/**���ļ�����ý���ļ�
	*�޲���
	*����ֵ									:���سɹ�����true,���򷵻�false;
	*����									:���ļ�����ý��,�Ӿ����������
	*������									:�Ӿ����ļ�����
	*���Ա��								:δ����
	*/
	bool LoadMedia();


	//ѭ����

	/**�¼�����ѭ��
	*�޲���
	*�޷���ֵ								:����ʱ��ѭ����ֻ�е�m_QuitGame��m_QuitͬʱΪtrueʱ���Ƴ�
	*�޷���ֵ
	*����									:ѭ������ʱ�䣬ֱ�������������˳�ѭ��
	*������									:ռ��һ������Ĵ����ʱ��
	*���Ա��								:δ����
	*/
	void MainLoop();

	/**�ڴ�������Ⱦ
	*�޲���
	*�޷���ֵ
	*����									:�ڴ����л�ͼ
	*������									:��ͼ
	*���Ա��								:δ����
	*/
	void Render();

	/**��ʼҳ
	*�޲���
	*�޷���ֵ
	*����									:������ʼҳ��ֱ��ʱ��ﵽ�����������������Ǿ��������
	*������									:�Ӿ������
	*���Ա��								:δ����
	*/
	void BeginPage();

	/**��ɫ����ʱ�����ҳ��
	*�޲���
	*�޷���ֵ
	*����									:�������ҳ��һ��ʱ�䣬ʱ�䵽����Զ��˳�
	*������									:�Ӿ������
	*���Ա��								:δ����
	*/
	void EndPage();

	/**�����ѡ����ͣʱ��ҳ��
	*�޲���
	*�޷���ֵ
	*����									:����˵�ҳ�棬ֱ������ĳ�������ߵ��ĳ����ť(�Ӿ��������
	*������									:�Ǿ������
	*���Ա��								:δ����
	*/
	void Menu();

	/**�жϵ�ǰ��Ϸ�Ƿ�Ӧ�ý���
	*�޲���
	*����ֵ									:Ӧ�ý�������true,���򷵻�false
	*����									:�жϵ�ǰ��Ϸ�Ƿ�ý���
	*������									:��
	*���Ա��								:δ����
	*/
	bool CheckEnd() const;
};


void InCallBack(void* Param, void* Result);

#endif
