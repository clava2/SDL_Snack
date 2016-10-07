#include "SDL_Timer.h"

CTimer::CTimer()
{
	if (SDL_WasInit(SDL_INIT_TIMER))
	{
		m_Paused = false;
		m_Started = false;
		
		m_StartTicks = 0;
		m_PauseTicks = 0;
	}
	else
	{
#ifdef _SDL_DEBUG
		cout << "��ʱ����ϵͳΪ��ʼ����SDL_Error:" << SDL_GetError() << endl;
		return;
#endif
	}
}

void CTimer::Start()
{
	if (SDL_WasInit(SDL_INIT_TIMER))
	{
		m_Paused = false;
		m_Started = true;
		m_StartTicks = SDL_GetTicks();
		m_PauseTicks = 0;
	}
	else
	{
#ifdef _SDL_DEBUG
		cout << "��ʱ����ϵͳΪ��ʼ����SDL_Error:" << SDL_GetError() << endl;
		return;
#endif
	}
}

void CTimer::Pause()
{
	if (!m_Paused&&m_Started)
	{
		m_Paused = true;
		m_PauseTicks = SDL_GetTicks() - m_StartTicks;
		m_Started = true;
	}
#ifdef _SDL_DEBUG
	else
	{
		cout << "��ʱ����û�п��������Ѿ���ͣ." << endl;
	}
#endif
}

void CTimer::Stop()
{
	if (m_Started)
	{
		m_Started = false;
		m_Paused = false;
		m_PauseTicks = 0;
		m_StartTicks = 0;
	}

#ifdef _SDL_DEBUG
	else
	{
		cout << "��ʱ����û�п�ʼ��ʱ���޷�ֹͣ��" << endl;
	}
#endif
}

void CTimer::Unpause()
{
	if (m_Paused)
	{
		m_Paused = false;
		m_Started = true;
		m_PauseTicks = 0;
	}
#ifdef _SDL_DEBUG
	else
	{
		cout << "��ʱ����û����ͣ��" << endl;
	}
#endif
}

Uint32 CTimer::GetTicks()
{
	if (m_Started && !m_Paused)
	{
		return SDL_GetTicks() - m_StartTicks;
	}
	else if (m_Started)
	{
#ifdef _SDL_DEBUG
		cout << "��ʱ���Ѿ���ͣ������ֵΪ��ͣʱ�䣡" << endl;
#endif
		return m_PauseTicks;
	}
#ifdef _SDL_DEBUG
	else
	{
		cout << "��ʱ����δ����������ͣ��" << endl;
	}
#endif
	return 0;
}

