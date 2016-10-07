#ifndef SDL_TIMER_H
#define SDL_TIMER_H

#define _SDL_DEBUG

#include <SDL2/SDL.h>

#ifdef _SDL_DEBUG
#include <iostream>

using std::endl;
using std::cout;

#endif


class CTimer
{
private:

//ʱ���¼����

	Uint32 m_StartTicks;							//�洢��ʼʱ��
	Uint32 m_PauseTicks;							//�洢��ͣʱ��

//��ʱ��״̬����

	bool m_Paused;									//�洢�Ƿ���ͣ
	bool m_Started;									//�洢�Ƿ�ʼ��ʱ

public:

//���캯����


	/**���캯��
	*���Ա��					:δ����
	*/
	CTimer();


//��ز���



	/**��ʼ��ʱ
	*���Ա��					:δ����
	*/
	void Start();

	/**ֹͣ��ʱ��
	*���Ա��					:δ����
	*/
	void Stop();

	/**��ͣ��ʱ��
	*���Ա��					:δ����
	*/
	void Pause();

	/**��ͣ�����¿�ʼ��ʱ��
	*���Ա��					:δ����
	*/
	void Unpause();
	
	/**�õ���ǰʱ��
	*����ֵ						:�Ӽ�ʱ����ʼ�����ڵ�ʱ�䣻
	*���Ա��					:δ����
	*/
	Uint32 GetTicks();


//�ڲ�������ȡ��


	/**�жϵ�ǰ��ʱ���Ƿ�ʼ
	*����ֵ						:��ʼ����true;���򷵻�false;
	*/
	bool IsStarted()
	{
		return m_Started;
	}

	/**�жϵ�ǰ��ʱ���Ƿ���ͣ
	*����ֵ						:��ͣ����true;���򷵻�false;
	*/
	bool IsPaused()
	{
		return m_Paused;
	}
};




#endif
