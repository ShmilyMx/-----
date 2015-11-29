#include "cocos2d.h"

USING_NS_CC;

class GameScene :public Layer
{
public:
	GameScene();
	~GameScene();
	static Scene *createScene();
	bool init();
	CREATE_FUNC(GameScene);
	
	void updatedown(float);

private:
	//创建13*10的矩阵
	void createBox();
	//保存创建的矩阵
	LayerColor **m_box;

	//存放创建的东西
	LayerColor **m_tetris;
	void createTetris();

	//存放产生的tetris
	Vector<LayerColor *>m_vecboxs;

	//判断是否移到最下面了
	bool isDown;
	bool isUpdate;

	//存放产生的是哪种tetris
	int TetrisNumber;

	//存放我所变换的数
	int changeNumber;



};