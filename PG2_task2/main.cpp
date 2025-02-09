#include <Novice.h>
#include<math.h>
#define USE_MATH_DEFINES
#include"Player.h"
#include"Enemy.h"
#include<stdlib.h>
#include<time.h>
const char kWindowTitle[] = "LC1D_21_マスダ_アキヒロ_タイトル";







// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };



	int title = Novice::LoadTexture("./Resources/images/Title.png");
	int gameclear = Novice::LoadTexture("./Resources/images/GameClear.png");
	int gameover = Novice::LoadTexture("./Resources/images/GameOver.png");




	unsigned int currentTime = (unsigned int)time(nullptr);
	srand(currentTime);




	int score = 0;





	enum SCENE
	{
		TITLE,
		GAME,
		CLEAR,
		OVER
	};
	int scene = TITLE;

	





	Player* player = new Player();

	const int ENEMY_MAX = 3;


	Enemy* enemy[ENEMY_MAX];


	for (int i = 0; i < ENEMY_MAX; i++)
	{
		enemy[i] = new Enemy(i + 4);
	}


	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0)
	{
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);


		switch (scene)
		{
		case TITLE:


			///
			/// ↓更新処理ここから
			///



			if (keys[DIK_SPACE] && preKeys[DIK_SPACE] == 0)
			{
				scene = GAME;
				score = 0;
				player->Init();
				for (int i = 0; i < ENEMY_MAX; i++)
				{
					enemy[i]->Init();
				}
			}
			///
			/// ↑更新処理ここまで
			///

			///
			/// ↓描画処理ここから
			///
			Novice::DrawSprite(0, 0, title, 1.0f, 1.0f, 0.0f, WHITE);
			///
			/// ↑描画処理ここまで
			///

			break;

		case GAME:

			///
			/// ↓更新処理ここから
			///

			


			player->Update(keys, preKeys);

			for (int i = 0; i < ENEMY_MAX; i++)
			{
				enemy[i]->Update();
			}


			//敵と弾が当たっている時
			for (int i = 0; i < ENEMY_MAX; i++)
			{
				int distanceX = (player->bullet->GetPosX() - enemy[i]->GetPosX());

				int distanceY = (player->bullet->GetPosY() - enemy[i]->GetPosY());

				int distanceXY =
					static_cast<int>(sqrt(distanceX * distanceX + distanceY * distanceY));

				//敵と弾が当たっている時の距離
				int r = player->bullet->GetRadius() + enemy[i]->GetRadius();
				//敵と弾が当たっている時

				if (distanceXY <= r)
				{
					enemy[i]->SetAlive(false);
					score += 100;
				}

			}

			//敵と自機が当たっている時
			for (int i = 0; i < ENEMY_MAX; i++)
			{
				int distanceX = (player->GetPosX() - enemy[i]->GetPosX());

				int distanceY = (player->GetPosY() - enemy[i]->GetPosY());

				int distanceXY =
					static_cast<int>(sqrt(distanceX * distanceX + distanceY * distanceY));

				//敵と弾が当たっている時の距離
				int r = player->GetRadius() + enemy[i]->GetRadius();
				//敵と弾が当たっている時

				if (distanceXY <= r)
				{
					player->SetAlive(false);
					scene = OVER;
				}
			}


			if (score >= 2000)
			{
				scene = CLEAR;
			}


			///
			/// ↑更新処理ここまで
			///


			///
			/// ↓描画処理ここから
			///


			


			for (int i = 0; i < ENEMY_MAX; i++)
			{
				enemy[i]->Draw();
			}

			player->Draw();


			if (keys[DIK_SPACE] && preKeys[DIK_SPACE])
			{
				Novice::DrawBox(605, 650, 70, 30, 0.0f, RED, kFillModeSolid);
			}

			if (keys[DIK_W])
			{
				Novice::DrawBox(60, 610, 30, 30, 0.0f, RED, kFillModeSolid);
			}
			if (keys[DIK_A])
			{
				Novice::DrawBox(20, 650, 30, 30, 0.0f, RED, kFillModeSolid);
			}
			if (keys[DIK_S])
			{
				Novice::DrawBox(60, 650, 30, 30, 0.0f, RED, kFillModeSolid);
			}
			if (keys[DIK_D])
			{
				Novice::DrawBox(100, 650, 30, 30, 0.0f, RED, kFillModeSolid);
			}


			Novice::DrawBox(60, 610, 30, 30, 0.0f, WHITE, kFillModeWireFrame);
			Novice::ScreenPrintf(70, 615, "W");

			Novice::DrawBox(20, 650, 30, 30, 0.0f, WHITE, kFillModeWireFrame);
			Novice::ScreenPrintf(30, 655, "A");

			Novice::DrawBox(60, 650, 30, 30, 0.0f, WHITE, kFillModeWireFrame);
			Novice::ScreenPrintf(70, 655, "S");

			Novice::DrawBox(100, 650, 30, 30, 0.0f, WHITE, kFillModeWireFrame);
			Novice::ScreenPrintf(110, 655, "D");


			Novice::DrawBox(605, 650, 70, 30, 0.0f, WHITE, kFillModeWireFrame);
			Novice::ScreenPrintf(620, 655, "SHOT");



			Novice::ScreenPrintf(10, 10, "%5d", score);


			///
			/// ↑描画処理ここまで
			///

			break;
		case CLEAR:

			///
			/// ↓更新処理ここから
			///


			if (keys[DIK_SPACE] && preKeys[DIK_SPACE] == 0)
			{
				scene = TITLE;

			}
			///
			/// ↑更新処理ここまで
			///

			///
			/// ↓描画処理ここから
			///
			Novice::DrawSprite(0, 0, gameclear, 1.0f, 1.0f, 0.0f, WHITE);
			Novice::ScreenPrintf(620, 385, "%5d", score);
			///
			/// ↑描画処理ここまで
			///

			break;
		case OVER:

			///
			/// ↓更新処理ここから
			///




			if (keys[DIK_SPACE] && preKeys[DIK_SPACE] == 0)
			{
				scene = TITLE;

			}

			///
			/// ↑更新処理ここまで
			///

			///
			/// ↓描画処理ここから
			///
			Novice::DrawSprite(0, 0, gameover, 1.0f, 1.0f, 0.0f, WHITE);
			Novice::ScreenPrintf(620, 385, "%5d", score);
			///
			/// ↑描画処理ここまで
			///


			break;


		}


		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0)
		{
			break;
		}
	}


	for (int i = 0; i < ENEMY_MAX; i++)
	{
		delete enemy[i];
	}

	
	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
