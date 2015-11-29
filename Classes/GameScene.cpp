#include "GameScene.h"
#include "ui/CocosGUI.h"

using namespace ui;


#define vSize Director::getInstance()->getVisibleSize()


GameScene::GameScene()
{
	auto size = sizeof(LayerColor *) * 13 * 10;
	m_box = (LayerColor **)malloc(size);
	memset(m_box, 0, size);

	auto tetris = sizeof(LayerColor *) * 4 * 4;
	m_tetris = (LayerColor **)malloc(tetris);
	memset(m_tetris, 0, tetris);
	this->isDown = false;
	this->isUpdate = true;
	this->TetrisNumber = 0;
	this->changeNumber = 0;
}
GameScene::~GameScene()
{
	CC_SAFE_FREE(m_box);
}

Scene *GameScene::createScene()
{
	auto scene = Scene::create();
	auto layer = GameScene::create();
	scene->addChild(layer);
	return scene;
}

bool GameScene::init()
{
	do
	{
		CC_BREAK_IF(!Layer::init());
		//添加背景颜色
		auto bg = LayerColor::create(Color4B::YELLOW);
		this->addChild(bg);
		
		createBox();
		createTetris();

		//左移
		auto btleft = Button::create("move.png", "move.png");
		btleft->setPosition(Vec2(100, 100));
		this->addChild(btleft);
		btleft->addClickEventListener([=](Ref *){
			log("========");
			//遍历每一个看是否到边界了
			for (auto tetris : m_vecboxs)
			{
				if (tetris->getPositionX() <= 1 || isDown == true) return;
			}

			for (auto tetris : m_vecboxs)
			{
				tetris->setPositionX(tetris->getPositionX() - 41);
				
			}
			
		});

		//右移
		auto btright = Button::create("move.png", "move.png");
		btright->setPosition(Vec2(300, 100));
		this->addChild(btright);
		btright->addClickEventListener([=](Ref *){
			log("========");
			//遍历每一个看是否到边界了
			for (auto tetris : m_vecboxs)
			{
				if (tetris->getPositionX() >= 360 || isDown==true) return;
			}
			
			for (auto tetris:m_vecboxs)
			{
				tetris->setPositionX(tetris->getPositionX() + 41);
			}
			
		});

		//变换形状
		auto btchange = Button::create("move.png", "move.png");
		btchange->setPosition(Vec2(200, 100));
		this->addChild(btchange);
		btchange->addClickEventListener([=](Ref *){
			
			int colcnt = m_vecboxs.front()->getPositionX() / 41;
			if (colcnt > 6 && TetrisNumber == 1) return;		
			if (colcnt > 7) return;
			switch (TetrisNumber)
			{
				unschedule(schedule_selector(GameScene::updatedown));
				m_vecboxs.clear();
			case 1: //产生竖起一条
			{
				
				auto number = changeNumber % 2;
				if (number == 0)
				{
					/*for (auto i = 0; i < 4; i++)
					{
						if (i == 0)
						{
							m_vecboxs.pushBack(m_tetris[0]);
						}
						if (i != 0)
						{
							this->removeChild(m_tetris[i * 4]);
							m_tetris[i * 4] = nullptr;

							auto tetris = LayerColor::create(Color4B::ORANGE, 40, 40);
							tetris->setPosition(41 + 41 * i, m_tetris[0]->getPositionY());
							m_tetris[i] = tetris;
							m_vecboxs.pushBack(tetris);
							this->addChild(tetris);
						}

					}*/
					auto tt = m_tetris[0];
					for (auto i = 0; i < 4 * 4; i++)
					{
						this->removeChild(m_tetris[i]);
						m_tetris[i] = nullptr;

					}
					for (auto i = 0; i < 4; i++)
					{
						auto tetris = LayerColor::create(Color4B::ORANGE, 40, 40);
						tetris->setPosition(tt->getPositionX() + i * 41, tt->getPositionY());
						m_tetris[i] = tetris;
						m_vecboxs.pushBack(tetris);
						this->addChild(tetris);
					}
					changeNumber++;
				}
				if (number == 1)
				{
					/*for (auto i = 0; i < 4; i++)
					{
						if (i == 0)
						{
							m_vecboxs.pushBack(m_tetris[0]);
						}
						if (i != 0)
						{
							this->removeChild(m_tetris[i]);
							m_tetris[i] = nullptr;

							auto tetris = LayerColor::create(Color4B::ORANGE, 40, 40);
							tetris->setPosition(41, m_tetris[0]->getPositionY()+41*i);
							m_tetris[i*4] = tetris;
							m_vecboxs.pushBack(tetris);
							this->addChild(tetris);
						}

					}*/
					auto tt = m_tetris[0];
					for (auto i = 0; i < 4 * 4; i++)
					{
						this->removeChild(m_tetris[i]);
						m_tetris[i] = nullptr;

					}
					for (auto i = 0; i < 4; i++)
					{
						auto tetris = LayerColor::create(Color4B::ORANGE, 40, 40);
						tetris->setPosition(tt->getPositionX() , tt->getPositionY()+ i * 41);
						m_tetris[i*4] = tetris;
						m_vecboxs.pushBack(tetris);
						this->addChild(tetris);
					}
					changeNumber++;
				}
				break;
			}
			case 2: //产生正方形
			{	
				break;
			}			//  *
			case 3: //产生* * *
			{
				auto number = changeNumber % 4;
				if (number==0)
				{
					auto tt = m_tetris[0];
					for (auto i = 0; i < 4*4; i++)
					{
						if (m_tetris[i])
						{
							this->removeChild(m_tetris[i]);
							m_tetris[i] = nullptr;
						}

					}
					for (auto row = 0; row < 3; row++)
					{
						for (auto col = 0; col < 2; col++)
						{
							if (row==0)
							{
								if (col==1)
								{
									auto tetris = LayerColor::create(Color4B::ORANGE, 40, 40);
									tetris->setPosition(tt->getPositionX() + col * 41, tt->getPositionY() + row * 41);
									m_tetris[row * 4+col] = tetris;
									m_vecboxs.pushBack(tetris);
									this->addChild(tetris);

								}
							}
							if (row==1)
							{
								auto tetris = LayerColor::create(Color4B::ORANGE, 40, 40);
								tetris->setPosition(tt->getPositionX() + col * 41,tt->getPositionY()+row*41);
								m_tetris[row * 4 + col] = tetris;
								m_vecboxs.pushBack(tetris);
								this->addChild(tetris);
							}
							if (row==2)
							{
								if (col == 1)
								{
									auto tetris = LayerColor::create(Color4B::ORANGE, 40, 40);
									tetris->setPosition(tt->getPositionX() + col * 41, tt->getPositionY() + row * 41);
									m_tetris[row * 4 + col] = tetris;
									m_vecboxs.pushBack(tetris);
									this->addChild(tetris);

								}
							}
						}
					}
					changeNumber++;
				}
				if (number==1)
				{
					auto tt = m_tetris[1];
					for (auto i = 0; i < 4 * 4; i++)
					{
						if (m_tetris[i])
						{
							this->removeChild(m_tetris[i]);
							m_tetris[i] = nullptr;
						}

					}
					for (auto row = 0; row < 2; row++)
					{
						for (auto col = 0; col < 3; col++)
						{
							if (row==0)
							{
								if (col==1)
								{
									auto tetris = LayerColor::create(Color4B::ORANGE, 40, 40);
									tetris->setPosition(tt->getPositionX(), tt->getPositionY());
									m_tetris[row * 4 + col] = tetris;
									m_vecboxs.pushBack(tetris);
									this->addChild(tetris);
								}
							}
							if (row==1)
							{
								auto tetris = LayerColor::create(Color4B::ORANGE, 40, 40);
								tetris->setPosition(tt->getPositionX()+(col-1)*41, tt->getPositionY()+row*41);
								m_tetris[row * 4 + col] = tetris;
								m_vecboxs.pushBack(tetris);
								this->addChild(tetris);
							}
						}
					}
					changeNumber++;
				}
				
				if (number==2)
				{
					auto tt = m_tetris[1];
					for (auto i = 0; i < 4 * 4; i++)
					{
						if (m_tetris[i])
						{
							this->removeChild(m_tetris[i]);
							m_tetris[i] = nullptr;
						}

					}
					for (auto row = 0; row < 3; row++)
					{
						for (auto col = 0; col < 2; col++)
						{
							if (row==0)
							{
								if (col==0)
								{
									auto tetris = LayerColor::create(Color4B::ORANGE, 40, 40);
									tetris->setPosition(tt->getPositionX() -41, tt->getPositionY());
									m_tetris[row * 4 + col] = tetris;
									m_vecboxs.pushBack(tetris);
									this->addChild(tetris);
								}
							}
							if (row==1)
							{
								auto tetris = LayerColor::create(Color4B::ORANGE, 40, 40);
								tetris->setPosition(tt->getPositionX() +(col-1)* 41, tt->getPositionY()+row*41);
								m_tetris[row * 4 + col] = tetris;
								m_vecboxs.pushBack(tetris);
								this->addChild(tetris);
							}
							if (row==2)
							{
								if (col==0)
								{
									auto tetris = LayerColor::create(Color4B::ORANGE, 40, 40);
									tetris->setPosition(tt->getPositionX() + (col - 1) * 41, tt->getPositionY() + row * 41);
									m_tetris[row * 4 + col] = tetris;
									m_vecboxs.pushBack(tetris);
									this->addChild(tetris);
								}
							}
						}
					}
					changeNumber++;
				}
				if (number==3)
				{
					auto tt = m_tetris[0];
					for (auto i = 0; i < 4 * 4; i++)
					{
						if (m_tetris[i])
						{
							this->removeChild(m_tetris[i]);
							m_tetris[i] = nullptr;
						}

					}
					for (auto row = 0; row < 2; row++)
					{
						for (auto col = 0; col < 3; col++)
						{
							if (row==0)
							{
								auto tetris = LayerColor::create(Color4B::ORANGE, 40, 40);
								tetris->setPosition(tt->getPositionX() + col * 41, tt->getPositionY());
								m_tetris[row * 4 + col] = tetris;
								m_vecboxs.pushBack(tetris);
								this->addChild(tetris);
							}
							if (row==1)
							{
								if (col==1)
								{
									auto tetris = LayerColor::create(Color4B::ORANGE, 40, 40);
									tetris->setPosition(tt->getPositionX() + col * 41, tt->getPositionY()+row*41);
									m_tetris[row * 4 + col] = tetris;
									m_vecboxs.pushBack(tetris);
									this->addChild(tetris);
								}
							}
						}
					}
					changeNumber++;
				}
				break;

			}			//    *
			case 4: //产生  * *
			{			//  *	
				
				auto number = changeNumber % 2;
				if (number==0)
				{
					auto tt = m_tetris[0];
					for (auto i = 0; i < 4 * 4; i++)
					{
						if (m_tetris[i])
						{
							this->removeChild(m_tetris[i]);
							m_tetris[i] = nullptr;
						}

					}
					for (auto row = 0; row < 2; row++)
					{
						for (auto col = 0; col < 3; col++)
						{
							if (row==1)
							{
								if (col==0 || col==1)
								{
									auto tetris = LayerColor::create(Color4B::ORANGE, 40, 40);
									tetris->setPosition(tt->getPositionX() + col * 41, tt->getPositionY()+row*41);
									m_tetris[row * 4 + col] = tetris;
									m_vecboxs.pushBack(tetris);
									this->addChild(tetris);
								}
							}
							if (row==0)
							{
								if (col==1 || col==2)
								{
									auto tetris = LayerColor::create(Color4B::ORANGE, 40, 40);
									tetris->setPosition(tt->getPositionX() + col * 41, tt->getPositionY()+row*41);
									m_tetris[row * 4 + col] = tetris;
									m_vecboxs.pushBack(tetris);
									this->addChild(tetris);
								}
							}
						}
					}
					changeNumber++;
				}
				if (number==1)
				{
					auto tt = m_tetris[1];
					for (auto i = 0; i < 4 * 4; i++)
					{
						if (m_tetris[i])
						{
							this->removeChild(m_tetris[i]);
							m_tetris[i] = nullptr;
						}

					}
					for (auto row = 0; row < 3; row++)
					{
						for (auto col = 0; col < 2; col++)
						{
							if (row==0)
							{
								if (col==0)
								{
									auto tetris = LayerColor::create(Color4B::ORANGE, 40, 40);
									tetris->setPosition(tt->getPositionX() + (col-1) * 41, tt->getPositionY() + row * 41);
									m_tetris[row * 4 + col] = tetris;
									m_vecboxs.pushBack(tetris);
									this->addChild(tetris);
								}
							}
							if (row==1)
							{
								auto tetris = LayerColor::create(Color4B::ORANGE, 40, 40);
								tetris->setPosition(tt->getPositionX() + (col-1) * 41, tt->getPositionY() + row * 41);
								m_tetris[row * 4 + col] = tetris;
								m_vecboxs.pushBack(tetris);
								this->addChild(tetris);
							}
							if (row==2)
							{
								if (col==1)
								{
									auto tetris = LayerColor::create(Color4B::ORANGE, 40, 40);
									tetris->setPosition(tt->getPositionX() + (col-1) * 41, tt->getPositionY() + row * 41);
									m_tetris[row * 4 + col] = tetris;
									m_vecboxs.pushBack(tetris);
									this->addChild(tetris);
								}
							}
						}
					}
					changeNumber++;
				}


				break;
			}		   // *
			case 5://产生 * *
			{			//  *
				auto number = changeNumber % 2;
				if (number == 0)
				{
					auto tt = m_tetris[1];
					for (auto i = 0; i < 4 * 4; i++)
					{
						if (m_tetris[i])
						{
							this->removeChild(m_tetris[i]);
							m_tetris[i] = nullptr;
						}

					}
					for (auto row = 0; row < 2; row++)
					{
						for (auto col = 0; col < 3; col++)
						{
							if (row == 0)
							{
								if (col == 0 || col == 1)
								{
									auto tetris = LayerColor::create(Color4B::ORANGE, 40, 40);
									tetris->setPosition(tt->getPositionX() + (col - 1) * 41, tt->getPositionY());
									m_tetris[row * 4 + col] = tetris;
									m_vecboxs.pushBack(tetris);
									this->addChild(tetris);
								}
							}
							if (row == 1)
							{
								if (col == 1 || col == 2)
								{
									auto tetris = LayerColor::create(Color4B::ORANGE, 40, 40);
									tetris->setPosition(tt->getPositionX() + (col - 1) * 41, tt->getPositionY() + row * 41);
									m_tetris[row * 4 + col] = tetris;
									m_vecboxs.pushBack(tetris);
									this->addChild(tetris);
								}
							}
						}
					}
					changeNumber++;
				}
				if (number == 1)
				{
					auto tt = m_tetris[0];
					for (auto i = 0; i < 4 * 4; i++)
					{
						if (m_tetris[i])
						{
							this->removeChild(m_tetris[i]);
							m_tetris[i] = nullptr;
						}

					}
					for (auto row = 0; row < 3; row++)
					{
						for (auto col = 0; col < 2; col++)
						{
							if (row == 0)
							{
								if (col == 1)
								{
									auto tetris = LayerColor::create(Color4B::ORANGE, 40, 40);
									tetris->setPosition(tt->getPositionX() + col * 41, tt->getPositionY() + row * 41);
									m_tetris[row * 4 + col] = tetris;
									m_vecboxs.pushBack(tetris);
									this->addChild(tetris);
								}
							}
							if (row == 1)
							{
								auto tetris = LayerColor::create(Color4B::ORANGE, 40, 40);
								tetris->setPosition(tt->getPositionX() + col * 41, tt->getPositionY() + row * 41);
								m_tetris[row * 4 + col] = tetris;
								m_vecboxs.pushBack(tetris);
								this->addChild(tetris);
							}
							if (row == 2)
							{
								if (col == 0)
								{
									auto tetris = LayerColor::create(Color4B::ORANGE, 40, 40);
									tetris->setPosition(tt->getPositionX() + col * 41, tt->getPositionY() + row * 41);
									m_tetris[row * 4 + col] = tetris;
									m_vecboxs.pushBack(tetris);
									this->addChild(tetris);
								}
							}
						}
					}
					changeNumber++;
				}

				break;

			}			// *
			case 6:// 产生 *
			{			// *  *
				auto number = changeNumber % 4;
				if (number==0)
				{
					auto tt = m_tetris[0];
					for (auto i = 0; i < 4 * 4; i++)
					{
						if (m_tetris[i])
						{
							this->removeChild(m_tetris[i]);
							m_tetris[i] = nullptr;
						}
					}
					for (auto row = 0; row < 2; row++)
					{
						for (auto col = 0; col < 3; col++)
						{
							if (row==0)
							{
								auto tetris = LayerColor::create(Color4B::ORANGE, 40, 40);
								tetris->setPosition(tt->getPositionX() + col * 41, tt->getPositionY() + row * 41);
								m_tetris[row * 4 + col] = tetris;
								m_vecboxs.pushBack(tetris);
								this->addChild(tetris);
							}
							if (row==1)
							{
								if (col==2)
								{
									auto tetris = LayerColor::create(Color4B::ORANGE, 40, 40);
									tetris->setPosition(tt->getPositionX() + col * 41, tt->getPositionY() + row * 41);
									m_tetris[row * 4 + col] = tetris;
									m_vecboxs.pushBack(tetris);
									this->addChild(tetris);
								}
							}
						}
					}
					changeNumber++;
				}
				if (number == 1)
				{
					auto tt = m_tetris[0];
					for (auto i = 0; i < 4 * 4; i++)
					{
						if (m_tetris[i])
						{
							this->removeChild(m_tetris[i]);
							m_tetris[i] = nullptr;
						}
					}
					for (auto row = 0; row < 3; row++)
					{
						for (auto col = 0; col < 2; col++)
						{
							if (row==0 || row == 1)
							{
								if (col==1)
								{
									auto tetris = LayerColor::create(Color4B::ORANGE, 40, 40);
									tetris->setPosition(tt->getPositionX() + col * 41, tt->getPositionY() + row * 41);
									m_tetris[row * 4 + col] = tetris;
									m_vecboxs.pushBack(tetris);
									this->addChild(tetris);
								}
							}
						
							if (row==2)
							{
								auto tetris = LayerColor::create(Color4B::ORANGE, 40, 40);
								tetris->setPosition(tt->getPositionX() + col * 41, tt->getPositionY() + row * 41);
								m_tetris[row * 4 + col] = tetris;
								m_vecboxs.pushBack(tetris);
								this->addChild(tetris);
							}
						}
					}
					changeNumber++;
				}
				if (number == 2)
				{
					auto tt = m_tetris[1];
					for (auto i = 0; i < 4 * 4; i++)
					{
						if (m_tetris[i])
						{
							this->removeChild(m_tetris[i]);
							m_tetris[i] = nullptr;
						}

					}
					for (auto row = 0; row < 2; row++)
					{
						for (auto col = 0; col < 3; col++)
						{
							if (row==0)
							{
								if (col==0)
								{
									auto tetris = LayerColor::create(Color4B::ORANGE, 40, 40);
									tetris->setPosition(tt->getPositionX() +(col-1) * 41, tt->getPositionY() + row * 41);
									m_tetris[row * 4 + col] = tetris;
									m_vecboxs.pushBack(tetris);
									this->addChild(tetris);
								}
							}
							if (row==1)
							{
								auto tetris = LayerColor::create(Color4B::ORANGE, 40, 40);
								tetris->setPosition(tt->getPositionX() + (col - 1) * 41, tt->getPositionY() + row * 41);
								m_tetris[row * 4 + col] = tetris;
								m_vecboxs.pushBack(tetris);
								this->addChild(tetris);
							}
						}
					}
					changeNumber++;

				}
				if (number == 3)
				{
					auto tt = m_tetris[0];
					for (auto i = 0; i < 4 * 4; i++)
					{
						if (m_tetris[i])
						{
							this->removeChild(m_tetris[i]);
							m_tetris[i] = nullptr;
						}

					}
					for (auto row = 0; row < 3; row++)
					{
						for (auto col = 0; col < 2; col++)
						{
							if (row==0)
							{
								auto tetris = LayerColor::create(Color4B::ORANGE, 40, 40);
								tetris->setPosition(tt->getPositionX() + col * 41, tt->getPositionY() + row * 41);
								m_tetris[row * 4 + col] = tetris;
								m_vecboxs.pushBack(tetris);
								this->addChild(tetris);
							}
							if (row==1 || row==2)
							{
								if (col==0)
								{
									auto tetris = LayerColor::create(Color4B::ORANGE, 40, 40);
									tetris->setPosition(tt->getPositionX() + col * 41, tt->getPositionY() + row * 41);
									m_tetris[row * 4 + col] = tetris;
									m_vecboxs.pushBack(tetris);
									this->addChild(tetris);
								}
							}
						}
					}
					changeNumber++;
				}
					
				break;
			}			// *
			case 7://产生  *
			{		//   * * 
				
				auto number = changeNumber % 4;
				if (number==0)
				{
					auto tt = m_tetris[0];
					for (auto i = 0; i < 4 * 4; i++)
					{
						if (m_tetris[i])
						{
							this->removeChild(m_tetris[i]);
							m_tetris[i] = nullptr;
						}
					}
					for (auto row = 0; row < 2; row++)
					{
						for (auto col = 0; col < 3; col++)
						{
							if (row==1)
							{
								auto tetris = LayerColor::create(Color4B::ORANGE, 40, 40);
								tetris->setPosition(tt->getPositionX() + col * 41, tt->getPositionY() + row * 41);
								m_tetris[row * 4 + col] = tetris;
								m_vecboxs.pushBack(tetris);
								this->addChild(tetris);
							}
							if (row==0)
							{
								if (col==2)
								{
									auto tetris = LayerColor::create(Color4B::ORANGE, 40, 40);
									tetris->setPosition(tt->getPositionX() + col * 41, tt->getPositionY() + row * 41);
									m_tetris[row * 4 + col] = tetris;
									m_vecboxs.pushBack(tetris);
									this->addChild(tetris);
								}
							}
							
						}
					}
					changeNumber++;
				}
				if (number == 1)
				{
					auto tt = m_tetris[2];
					for (auto i = 0; i < 4 * 4; i++)
					{
						if (m_tetris[i])
						{
							this->removeChild(m_tetris[i]);
							m_tetris[i] = nullptr;
						}
					}
					for (auto row = 0; row < 3; row++)
					{
						for (auto col = 0; col < 2; col++)
						{
							if (row==0 || row==1)
							{
								if (col==0)
								{
									auto tetris = LayerColor::create(Color4B::ORANGE, 40, 40);
									tetris->setPosition(tt->getPositionX() + (col-2) * 41, tt->getPositionY() + row * 41);
									m_tetris[row * 4 + col] = tetris;
									m_vecboxs.pushBack(tetris);
									this->addChild(tetris);
								}
							}
							if (row==2)
							{
								auto tetris = LayerColor::create(Color4B::ORANGE, 40, 40);
								tetris->setPosition(tt->getPositionX() + (col - 2) * 41, tt->getPositionY() + row * 41);
								m_tetris[row * 4 + col] = tetris;
								m_vecboxs.pushBack(tetris);
								this->addChild(tetris);
							}
						}
					}
					changeNumber++;
				}
				if (number == 2)
				{
					auto tt = m_tetris[0];
					for (auto i = 0; i < 4 * 4; i++)
					{
						if (m_tetris[i])
						{
							this->removeChild(m_tetris[i]);
							m_tetris[i] = nullptr;
						}
					}
					for (auto row = 0; row < 2; row++)
					{
						for (auto col = 0; col < 3; col++)
						{
							if (row==0)
							{
								auto tetris = LayerColor::create(Color4B::ORANGE, 40, 40);
								tetris->setPosition(tt->getPositionX() + col * 41, tt->getPositionY() + row * 41);
								m_tetris[row * 4 + col] = tetris;
								m_vecboxs.pushBack(tetris);
								this->addChild(tetris);
							}
							if (row==1)
							{
								if (col==0)
								{
									auto tetris = LayerColor::create(Color4B::ORANGE, 40, 40);
									tetris->setPosition(tt->getPositionX() + col * 41, tt->getPositionY() + row * 41);
									m_tetris[row * 4 + col] = tetris;
									m_vecboxs.pushBack(tetris);
									this->addChild(tetris);
								}
							}
						}
					}
					changeNumber++;
				}
				if (number == 3)
				{
					auto tt = m_tetris[0];
					for (auto i = 0; i < 4 * 4; i++)
					{
						if (m_tetris[i])
						{
							this->removeChild(m_tetris[i]);
							m_tetris[i] = nullptr;
						}
					}
					for (auto row = 0; row < 3; row++)
					{
						for (auto col = 0; col < 2; col++)
						{
							if (row==0)
							{
								auto tetris = LayerColor::create(Color4B::ORANGE, 40, 40);
								tetris->setPosition(tt->getPositionX() + col * 41, tt->getPositionY() + row * 41);
								m_tetris[row * 4 + col] = tetris;
								m_vecboxs.pushBack(tetris);
								this->addChild(tetris);
							}
							if (row==1 || row==2)
							{

								if (col==1)
								{
									auto tetris = LayerColor::create(Color4B::ORANGE, 40, 40);
									tetris->setPosition(tt->getPositionX() + col * 41, tt->getPositionY() + row * 41);
									m_tetris[row * 4 + col] = tetris;
									m_vecboxs.pushBack(tetris);
									this->addChild(tetris);
								}
							}
						}
					}
					changeNumber++;
				}
				break;
			}
			default:
				break;
			}
			schedule(schedule_selector(GameScene::updatedown), 0.7f);
		});

		schedule(schedule_selector(GameScene::updatedown),0.7f);

		return true;
	} while (0);
	return false;
}


void GameScene::updatedown(float)
{
	//判断是否死亡
	for (auto col = 0; col < 10; col++)
	{
		auto number = 0;
		for (auto row = 0; row < 13; row++)
		{
			if (m_box[row*10+col])
			{
				number = number>row ? number : row;
			}
		}
		if (number>=12)
		{
			log("======gameover");
			unschedule(schedule_selector(GameScene::updatedown));
			Director::getInstance()->replaceScene(GameScene::createScene());
		}
	}

	if (isUpdate==false)
	{
		isUpdate = true;
		isDown = true;	
		unschedule(schedule_selector(GameScene::updatedown));
		/*for (auto tetris:m_vecboxs)
		{
			int col = tetris->getPositionX() / 41;
			int row = (tetris->getPositionY()-149) / 41;
			log("%f,%f", tetris->getPositionX(), tetris->getPositionY() - 149);
			m_box[row * 10 + col] = tetris;
		}*/
		for (auto i = 0; i < 16; i++)
		{
			if (m_tetris[i])
			{
				int col = m_tetris[i]->getPositionX() / 41;
				int row = (m_tetris[i]->getPositionY() - 149) / 41;
				log("%f,%f", m_tetris[i]->getPositionX(), m_tetris[i]->getPositionY() - 149);
				m_box[row * 10 + col] = m_tetris[i];
			}
		}
		createTetris();
		return;
	}
	
	for (auto tetris :m_vecboxs)
	{
		
		tetris->setPositionY(tetris->getPositionY() - 41);
	}
	/*for (auto te : m_vecboxs)
	{
		if (te->getTag() == 1)
		{
			int col = te->getPositionX() / 41;
			int row = (te->getPositionY() - 149) / 41;
			if (row==0)
			{
				
				isUpdate = false;
			}
			if (row != 0 && m_box[(row - 1) * 10 + col])
			{			
				isUpdate = false;
				return;
			}
		}
	}*/
	/*for (auto i = 0; i < 4; i++)
	{
		if (!m_tetris[i]) continue;
		log("%f,%f", m_tetris[i]->getPositionX(), m_tetris[i]->getPositionY() - 149);
		int col = m_tetris[i]->getPositionX() / 41;
		int row = (m_tetris[i]->getPositionY() - 149) / 41;
		if (row == 0)
		{
			isUpdate = false;
		}
		if (row != 0 && m_box[(row - 1) * 10 + col])
		{
			isUpdate = false;
			return;
		}
	}*/

	for (auto col = 0; col < 4; col++)
	{
		for (auto row = 0; row < 4; row++)
		{
			if (!m_tetris[row * 4 + col]) continue;
			int c = m_tetris[row * 4 + col]->getPositionX() / 41;
			int r = (m_tetris[row * 4 + col]->getPositionY() - 149) / 41;
			if (r==0)
			{
				isUpdate = false;
				return;
			}
			if ((r != 0) && (m_box[(r - 1) * 10 + c]!=nullptr))
			{
				isUpdate = false;
				return;
			}
			break;
		}
	}
	

	//消除某一行
	auto cnt = 0;
	for (auto row = 0; row < 13; row++)
	{
		auto number = 0;		
		for (auto col = 0; col < 10; col++)
		{
			
			if (m_box[row * 10 + col])
			{
				number++;
			}
			if (number == 10)
			{
				for (auto col = 0; col < 10; col++)
				{
					this->removeChild(m_box[row * 10 + col]);
					m_box[row * 10 + col] = nullptr;
				}
				cnt++;
			}
			else if (cnt>0 && number < 10)
			{
				auto tetris = m_box[row * 10 + col];
				if (!tetris) continue;
				auto newRow = row - cnt;
				m_box[newRow * 10 + col] = tetris;
				m_box[row * 10 + col] = nullptr;
				//tetris->setPositionY(tetris->getPositionY() - cnt * 41);
				auto newPos = m_box[newRow*10+col]->getPosition()-Vec2(0,cnt*41);
				auto oldPos = tetris->getPosition();
				
				auto time = (oldPos - newPos).y / vSize.height;
				tetris->runAction(MoveTo::create(time, newPos));
				
			}
		}		
	}
}
void GameScene::createBox()
{
	for (auto col = 0; col < 10; col++)
	{
		for (auto row = 0; row < 13; row++)
		{
			auto box = LayerColor::create(Color4B::GRAY,40,40);
			box->setPosition((box->getContentSize().width+1)*col, (box->getContentSize().height+1)*row+150);
			box->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
			this->addChild(box);
		}
	}
}


void GameScene::createTetris()
{
	m_vecboxs.clear();
	changeNumber = 0;
	schedule(schedule_selector(GameScene::updatedown), 0.7f);
	for (auto i = 0; i < 16; i++)
	{
		m_tetris[i] = nullptr;

	}
	isDown = false;
	////产生竖起一条
	//for (auto i = 0; i < 4; i++)
	//{
	//	auto tetris = LayerColor::create(Color4B::ORANGE, 40, 40);
	//	tetris->setPosition(41,(tetris->getContentSize().height+1)*i+641);
	//	this->addChild(tetris);
	//	m_vecboxs.pushBack(tetris);
	//}

	TetrisNumber = random(1, 7);
	 auto pos = random(0, 6);
	//TetrisNumber = 5;
	 switch (TetrisNumber)
	{		
	case 1: //产生竖起一条
	{
		
		for (auto i = 0; i < 4; i++)
		{
			
			auto tetris = LayerColor::create(Color4B::ORANGE, 40, 40);
			tetris->setPosition(41*pos,(tetris->getContentSize().height+1)*i+682);
			this->addChild(tetris);
			m_vecboxs.pushBack(tetris);
			m_tetris[i * 4] = tetris;
			if (i==0)
			{
				tetris->setTag(1);
			}
		}
		break;
	}
	case 2: //产生正方形
	{
		for (auto row = 0; row < 2; row++)
		{
			for (auto col = 0; col < 2; col++)
			{
				auto tetris = LayerColor::create(Color4B::ORANGE, 40, 40);
				tetris->setPosition(41*(pos+col + 1), (tetris->getContentSize().height + 1)*row + 682);
				this->addChild(tetris);
				m_vecboxs.pushBack(tetris);
				m_tetris[row * 4 + col] = tetris;
				if (row == 0)
				{
					tetris->setTag(1);
				}
			}
		}
		break;
	}			//  *
	case 3: //产生* * *
	{
		for (auto row = 0; row < 2; row++)
		{
			for (auto col = 0; col < 3; col++)
			{
				if (row==0)
				{
					auto tetris = LayerColor::create(Color4B::ORANGE, 40, 40);
					tetris->setPosition(41  * (col + 1+ pos), (tetris->getContentSize().height + 1)*row + 682);
					this->addChild(tetris);
					m_vecboxs.pushBack(tetris);
					m_tetris[row * 4 + col] = tetris;
					tetris->setTag(1);
				}
				if (row==1)
				{
					if (col==1)
					{
						auto tetris = LayerColor::create(Color4B::ORANGE, 40, 40);
						tetris->setPosition(41  * (col + 1+ pos), (tetris->getContentSize().height + 1)*row + 682);
						this->addChild(tetris);
						m_vecboxs.pushBack(tetris);
						m_tetris[row * 4 + col] = tetris;
					}
				}
			}
		}
		break;

	}			//    *
	case 4: //产生  * *
	{			//  *	
		for (auto row = 0; row < 3; row++)
		{
			for (auto col = 0; col < 2; col++)
			{
				if (row==0)
				{
					if (col==0)
					{
						auto tetris = LayerColor::create(Color4B::ORANGE, 40, 40);
						tetris->setPosition(41  * (col + 1+ pos), (tetris->getContentSize().height + 1)*row + 682);
						this->addChild(tetris);
						m_vecboxs.pushBack(tetris);
						m_tetris[0] = tetris;
						tetris->setTag(1);
					}
				}
				else if (row==1)
				{
					auto tetris = LayerColor::create(Color4B::ORANGE, 40, 40);
					tetris->setPosition(41  * (col + 1+ pos), (tetris->getContentSize().height + 1)*row + 682);
					this->addChild(tetris);
					m_vecboxs.pushBack(tetris);
					m_tetris[row * 4 + col] = tetris;
				}
				else
				{
					if (col==1)
					{
						auto tetris = LayerColor::create(Color4B::ORANGE, 40, 40);
						tetris->setPosition(41  * (col + 1+ pos), (tetris->getContentSize().height + 1)*row + 682);
						this->addChild(tetris);
						m_tetris[row * 4 + col] = tetris;
						m_vecboxs.pushBack(tetris);
					}
				}
			}
		}
		break;
	}		   // *
	case 5://产生 * *
	{			//  *
		for (auto row = 0; row < 3; row++)
		{
			for (auto col = 0; col < 2; col++)
			{
				if (row == 0)
				{
					if (col == 1)
					{
						auto tetris = LayerColor::create(Color4B::ORANGE, 40, 40);
						tetris->setPosition(41  * (col + 1+ pos), (tetris->getContentSize().height + 1)*row + 682);
						this->addChild(tetris);
						m_vecboxs.pushBack(tetris);
						m_tetris[row*4+col] = tetris;
						tetris->setTag(1);
					}
				}
				else if (row == 1)
				{
					auto tetris = LayerColor::create(Color4B::ORANGE, 40, 40);
					tetris->setPosition(41 * (col + 1 + pos), (tetris->getContentSize().height + 1)*row + 682);
					this->addChild(tetris);
					m_vecboxs.pushBack(tetris);
					m_tetris[row * 4 + col] = tetris;
				}
				else
				{
					if (col == 0)
					{
						auto tetris = LayerColor::create(Color4B::ORANGE, 40, 40);
						tetris->setPosition(41  * (col + 1+ pos), (tetris->getContentSize().height + 1)*row + 682);
						this->addChild(tetris);
						m_tetris[row * 4 + col] = tetris;
						m_vecboxs.pushBack(tetris);
					}
				}
			}
		}
		break;
		
	}			// *
	case 6:// 产生 *
	{			// *  *
		for (auto row = 0; row < 3; row++)
		{
			for (auto col = 0; col < 2; col++)
			{
				if (row==0)
				{
					auto tetris = LayerColor::create(Color4B::ORANGE, 40, 40);
					tetris->setPosition(41  * (col + 1+ pos), (tetris->getContentSize().height + 1)*row + 682);
					this->addChild(tetris);
					m_vecboxs.pushBack(tetris);
					m_tetris[row * 4 + col] = tetris;
					tetris->setTag(1);
				}
				else
				{
					if (col==0)
					{
						auto tetris = LayerColor::create(Color4B::ORANGE, 40, 40);
						tetris->setPosition(41  * (col + 1+ pos), (tetris->getContentSize().height + 1)*row + 682);
						this->addChild(tetris);
						m_tetris[row * 4 + col] = tetris;
						m_vecboxs.pushBack(tetris);
					}
				}
			}
		}
		break;
	}			// *
	case 7://产生  *
	{		//   * * 
		for (auto row = 0; row < 3; row++)
		{
			for (auto col = 0; col < 2; col++)
			{
				if (row == 0)
				{
					auto tetris = LayerColor::create(Color4B::ORANGE, 40, 40);
					tetris->setPosition(41  * (col + 1+ pos), (tetris->getContentSize().height + 1)*row + 682);
					this->addChild(tetris);
					m_vecboxs.pushBack(tetris);
					m_tetris[row * 4 + col] = tetris;
					tetris->setTag(1);
				}
				else
				{
					if (col == 1)
					{
						auto tetris = LayerColor::create(Color4B::ORANGE, 40, 40);
						tetris->setPosition(41  * (col + 1+ pos), (tetris->getContentSize().height + 1)*row + 682);
						this->addChild(tetris);
						m_tetris[row * 4 + col] = tetris;
						m_vecboxs.pushBack(tetris);
					}
				}
			}
		}
		break;
	}
	default:
		break;
	}
}