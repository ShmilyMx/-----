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
	//����13*10�ľ���
	void createBox();
	//���洴���ľ���
	LayerColor **m_box;

	//��Ŵ����Ķ���
	LayerColor **m_tetris;
	void createTetris();

	//��Ų�����tetris
	Vector<LayerColor *>m_vecboxs;

	//�ж��Ƿ��Ƶ���������
	bool isDown;
	bool isUpdate;

	//��Ų�����������tetris
	int TetrisNumber;

	//��������任����
	int changeNumber;



};