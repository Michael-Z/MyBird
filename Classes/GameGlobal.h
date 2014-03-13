//
//  GameGlobal.h
//  testShao3
//
//  Created by shaozhen on 14-2-20.
//
//

#ifndef testShao3_GameGlobal_h
#define testShao3_GameGlobal_h

const bool GameShowShop = true;

const int GameReady = 1;
const int GameRun = 2;
const int GameEnd = 3;

const float SpeedLand = 120;
const float SpeedPipe = SpeedLand;
const float SpeedBirdDie = 300;

const int PipeWidth = 52;
const int LandMoreWidth = 32;

const int ActionTagBirdFall = 11;
const int ActionTagBirdFly = 12;
const int ActionTagPipeMove = 13;
const int ActionTagLandMove = 14;
const int ActionTagBirdUpDown = 15;
const int ActionTagBirdBlink = 16;

const int KMenuRestart = 1;
const int KMenuRecord = 2;
const int KMenuSaveClose = 3;
const int KMenuSaveOk = 4;
const int KMenuShopOne = 5;
const int KMenuShopTwo = 6;
const int KMenuShopThree = 7;
const int KMenuShopClose = 8;
const int KMenuShop = 9;

const int KLayerTagPopupResult = 1;
const int KLayerTagPopupStart = 2;
const int KLayerTagPopupSave = 3;
const int KLayerTagPopupShop = 4;
const int KLayerTagGameUI = 5;

const int KLayerOrderGame = 1;
const int KLayerOrderPopupStart = 2;
const int KLayerOrderPopupSave = 8;
const int KLayerOrderPopupShop = 9;
const int KLayerOrderPopupResult = 10;
const int KLayerOrderGameUI = 11;

const int KShopOne = 20;
const int KShopTwo = 50;
const int KShopThree = 150;

const int KShopCostOne = 1;
const int KShopCostTwo = 2;
const int KShopCostThree = 5;
#endif
