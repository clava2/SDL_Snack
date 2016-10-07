#include "SDL_Game.h"

CGame::CGame(string Title, int X, int Y, int Width, int Height)
{
    m_StartImage = NULL;
	m_Quit = false;
	m_QuitGame = false;
	m_Window = NULL;
	m_Renderer = NULL;
    m_Level = 1;
    m_Score = 0;

	m_MainTimer.Start();
}

bool CGame::InitWindow(string title, int X, int Y, int Width, int Height, SDL_WindowFlags Flag)
{
	if ((SDL_Init(SDL_INIT_VIDEO)) < 0)
	{
#ifdef _SDL_DEBUG
		cout << "初始化SDL_INIT_VIDEO子系统失败！SDL_Error:" << SDL_GetError() << endl;
#endif
		return false;
	}

	m_Window = SDL_CreateWindow(title.c_str(), X, Y, Width, Height, Flag);

	if (m_Window == NULL)
	{
#ifdef _SDL_DEBUG
		cout << "SDL创建窗口失败！SDL_Error:" << SDL_GetError() << endl;
#endif
		return false;
	}

	SDL_GetWindowSize(m_Window, &m_Width, &m_Height);

	m_Renderer = SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_ACCELERATED);

	if (m_Renderer == NULL)
	{
#ifdef _SDL_DEBUG
		cout << "创建渲染器失败！SDL_Error:" << SDL_GetError() << endl;
#endif
		return false;
	}

	//成员变量设置窗口

	return true;
}

bool CGame::LoadMedia ()
{

	SDL_Surface* TempSurface = IMG_Load("Start.jpg");
	if (!TempSurface)
	{
#ifdef _SDL_DEBUG
		cout << "SDL_Game.cpp	CGame	bool CGame::LoadMedia()" << endl;
		cout << "从文件加载开始页面的图片失败！" << endl;
		cout << "Path = " << "Start.jpg" << endl;
		cout << "TempSurface" << TempSurface << endl;
		cout << "SDL_GetError() = " << SDL_GetError() << endl << endl << endl;
#endif
		return false;
	}
	m_StartImage = SDL_CreateTextureFromSurface(m_Renderer, TempSurface);
	SDL_FreeSurface(TempSurface);
	if (!m_StartImage)
	{
#ifdef _SDL_DEBUG
		cout << "SDL_Game.cpp	CGame	bool CGame::LoadMedia()" << endl;
		cout << "从表面创建纹理失败！" << endl;
		cout << "m_Renderer = " << m_Renderer << endl;
		cout << "TempSurface = " << TempSurface << endl;
		cout << "SDL_GetError() = " << SDL_GetError() << endl;
#endif
		return false;
	}

    m_Font = TTF_OpenFont("font.ttf",20);
    if(!m_Font)
    {
#ifdef _SDL_DEBUG
        cout << "failed in loading font" << endl;
        cout << "fontPath = font.ttf" << endl;
        cout << "SDL_GetError() = " << SDL_GetError() << endl << endl << endl;
#endif
    }

	return true;
}

void CGame::MainLoop()
{
    

    BeginPage();
	while (!m_QuitGame)
	{
        srand(time(NULL));
    	SDL_Event event;

        m_Food.x = rand()%MAP_WIDTH;
        m_Food.y = rand()%MAP_HEIGHT;


        SDL_RenderClear(m_Renderer);
        SDL_RenderPresent(m_Renderer);
        m_Quit = false;

        SDL_Texture* ScoreTexture = NULL;
        SDL_Rect ScoreArea;
        SDL_Rect LevelArea;
        SDL_Texture* LevelTexture = NULL;
        m_Score = 0;
        m_Level = 0;
        m_Snack.Restart();


 		while (!m_Quit)
		{
             

			while (SDL_PollEvent(&event))
			{
				switch (event.type)
				{
				case SDL_QUIT:
					m_Quit = true;
					m_QuitGame = true;
					break;
				case SDL_KEYDOWN:
				{
					switch (event.key.keysym.sym)
					{
					case SDLK_ESCAPE:
						m_Quit = true;
						m_QuitGame = true;
						break;
                    case SDLK_DOWN:
                        m_Snack.SetDirection(1);
                        break;
                    case SDLK_UP:
                        m_Snack.SetDirection(0);
                        break;
                    case SDLK_LEFT:
                        m_Snack.SetDirection(2);
                        break;
                    case SDLK_RIGHT:
                        m_Snack.SetDirection(3);
                        break;
					}
					break;
				}
				}
			}
            SDL_SetRenderDrawColor(m_Renderer, 0xff, 0x00, 0xff, 0xff);
			SDL_RenderClear(m_Renderer);
            Render();
            
        int width = m_Width/MAP_WIDTH;
            int height = m_Height/MAP_HEIGHT;

            SDL_Rect FoodRect = {m_Food.x*width,m_Food.y*height,width,height};
            SDL_SetRenderDrawColor(m_Renderer,0xff,0x00,0x00,0xff);
            SDL_RenderFillRect(m_Renderer,&FoodRect);
            SDL_SetRenderDrawColor(m_Renderer,0xff,0x00,0xff,0xff);

            m_Snack.Render(m_Window);
            if(m_MainTimer.GetTicks() >= 300.0/pow(1.5,m_Level))
            {
               if(!m_Snack.CheckDie())
                {
                   if(m_Snack.Move(m_Food))
                   {
                       m_Score += 10;
                       if(m_Score >= (50*m_Level*m_Level+50* m_Level))
                       {
                           m_Level ++;
                       }
                       SDL_Color TextColor = {0x00,0x00,0x00,0xff};
                       m_Food.x = rand()%MAP_WIDTH;
                       m_Food.y = rand()%MAP_HEIGHT;
                        string text = "Score:";
                       char num[10] = {'\0'};
                       sprintf(num,"%d",m_Score);
                       text += num;
                       cout << text << endl;
                       SDL_Surface* TextSurface = TTF_RenderText_Solid(m_Font,text.c_str(),TextColor);
                       cout << TextSurface << endl;
                       ScoreArea = {0,0,TextSurface->w,TextSurface->h};
                       if(ScoreTexture)
                       {
                           SDL_DestroyTexture(ScoreTexture);
                       }
                       ScoreTexture = SDL_CreateTextureFromSurface(m_Renderer,TextSurface);
                       SDL_FreeSurface(TextSurface);
                       text = "Level:";
                       sprintf(num,"%d",m_Level);
                       text += num;
                       cout << text << endl;
                       TextSurface = TTF_RenderText_Solid(m_Font,text.c_str(),TextColor);
                       if(LevelTexture)
                       {
                           SDL_DestroyTexture(LevelTexture);
                       }
                       LevelTexture = SDL_CreateTextureFromSurface(m_Renderer,TextSurface);
                       LevelArea = {0,ScoreArea.h,TextSurface->w,TextSurface->h};
                       SDL_FreeSurface(TextSurface);
                       TextSurface = NULL;
                   }
                    m_MainTimer.Start();
                }
               else
               {
                   cout << "the m_Snack died" << endl;
                   EndPage();

               }
            }
		    	
            SDL_RenderCopy(m_Renderer,ScoreTexture,NULL,&ScoreArea);
            SDL_RenderCopy(m_Renderer,LevelTexture,NULL,&LevelArea);


  			SDL_RenderPresent(m_Renderer);
		}
	}
}

void CGame::Render()
{
   
}

CGame::~CGame ()
{
  if (m_Window)
    {
      SDL_DestroyWindow (m_Window);
    }
  if (m_Renderer)
    {
      SDL_DestroyRenderer (m_Renderer);
    }
  if (m_StartImage)
  {
	  SDL_DestroyTexture(m_StartImage);
  }
}

void CGame::BeginPage()
{
	SDL_SetRenderDrawColor(m_Renderer,0xff, 0xff, 0xff, 0xff);

	SDL_RenderCopy(m_Renderer, m_StartImage, NULL, NULL);

	SDL_RenderPresent(m_Renderer);
    SDL_Delay(1000);
}


bool CGame::CheckEnd() const
{
	return true;
}

void CGame::EndPage()
{
#ifdef _SDL_DEBUG
    cout << "enter the die page!" << endl << endl << endl << endl;
#endif
    SDL_Event e;
    bool quit = false;
    SDL_Color TextColor = {0x00,0x00,0x00,0xff};
    SDL_Surface* message = TTF_RenderText_Solid(m_Font,"Game Over!   (Press Enter To Restart,ESC To Quit)",TextColor);
    if(!message)
    {
#ifdef _SDL_DEBUG
        cout << "failed in creating the text surface " << endl;
        cout << "text = Game Over" << endl;
        cout << "font = " << m_Font << endl;
        cout << "message = " << message << endl;
        cout << "SDL_GetError()  = " << SDL_GetError() << endl << endl << endl;
#endif
        return;
    }
    SDL_Texture* MessageTexture = SDL_CreateTextureFromSurface(m_Renderer,message);
    int width = message->w;
    int height = message->h;
    SDL_Rect TextArea = {m_Width/2 - width/2,m_Height/2 - height/2,width,height};
    SDL_FreeSurface(message);
    message = NULL;
    if(!MessageTexture)
    {
#ifdef _SDL_DEBUG
        cout << "failed in creating texture from surface!" <<endl;
        cout << "message = " << message << endl;
        cout << "MessageTexture = " << MessageTexture << endl;
        cout << "m_Renderer = " << m_Renderer << endl ;
        cout << "SDL_GetError() = " << SDL_GetError() << endl << endl << endl;
#endif
    }

    SDL_SetRenderDrawColor(m_Renderer,0x00,0xff,0xff,0xff);
    SDL_GetWindowSize(m_Window,&m_Width,&m_Height);
#ifdef _SDL_DEBUG
    cout << m_Width << "  " << m_Height << endl;
#endif
    SDL_Rect MessageArea = {m_Width/2-width/2 - 100,m_Height/2-height/2 - 100,width + 200,height + 200};
    SDL_RenderFillRect(m_Renderer,&MessageArea);
        
    while(!quit)
    {
        while(SDL_PollEvent(&e))
        {
            if(e.type == SDL_KEYDOWN)
            {
                if((e.key.keysym.sym == SDLK_RETURN))
                {
                    quit = true;
                    m_Quit = true;
                }
                if(e.key.keysym.sym == SDLK_ESCAPE)
                {
                    quit = true;
                    m_Quit = true;
                    m_QuitGame = true;
                }
            }
        }
        SDL_RenderCopy(m_Renderer,MessageTexture,NULL, &TextArea);
        SDL_RenderPresent(m_Renderer);
    }
    SDL_DestroyTexture(MessageTexture);
    MessageTexture = NULL;
}

void CGame::Menu()
{
	SDL_Event e;
	bool quit = false;
	while (!quit)
	{
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_KEYDOWN)
			{
				if (e.key.keysym.sym == SDLK_ESCAPE)
				{
					m_QuitGame = true;
					quit = true;
					m_Quit = true;
				}
			}
			if (e.type == SDL_QUIT)
			{
				m_QuitGame = true;
				quit = true;
				m_Quit = true;
			}
		}
		SDL_RenderPresent(m_Renderer);
	}
}


void InCallBack(void* Param, void* Result)
{
	cout << "SDL_Game.cpp	void InCallBack(void* Param,void* Reault)" << endl;
	cout << "进入按钮的回调函数调用！" << endl << endl << endl;
}
