#pragma once

//текстуры
#define MAIN_TEXTURE "GameRes\\Textures\\EntityTiles.png" // картинка со всеми тайлами
#define MAIN_MENU_BACKGROUND "GameRes\\Textures\\pixel-bg.png" // задний фон главного меню
#define PROJECTILES "GameRes\\Textures\\Projectiles.png" // снаряды

#define WASD "GameRes\\Textures\\wasd.png" 
#define ARROWS "GameRes\\Textures\\arrows.png" 
#define SHOOT "GameRes\\Textures\\leftButton.png"
#define ESC "GameRes\\Textures\\esc.png"


//карта
#define GROUND_LAYER "GameRes\\TextData\\Map\\ground-layer.txt" // нижний слой
#define COLLISION_LAYER "GameRes\\TextData\\Map\\collision-layer.txt" // слой с твердыми объектами
#define SPIKES_LAYER "GameRes\\TextData\\Map\\spikes-layer.txt" // слой с шипами
#define TILE_TYPES "GameRes\\TextData\\Map\\types.txt" // виды тайлов

//шрифты
#define PIXEL_FONT "GameRes\\Fonts\\pixelcyr_normal.ttf" // шрифт

//информация об игроке
#define PLAYER_INFO "GameRes\\TextData\\Player\\player-info.txt"
//настройки
#define SETTINGS "GameRes\\TextData\\Settings\\settings.txt"
//рекорды
#define SCORES "GameRes\\TextData\\Records\\best-scores.txt"


//музыка
#define MENU_MUSIC "GameRes\\Music\\Menu\\main-menu.ogg"
#define IN_GAME_MUSIC_1 "GameRes\\Music\\InGame\\ingame.ogg"
//звуковые эффекты
#define FIREBALL_SOUND "GameRes\\Music\\SFX\\fireball.wav"
#define ENEMY_DAMAGE_SOUND "GameRes\\Music\\SFX\\EnemyDeath1.wav"
#define POTION_SOUND "GameRes\\Music\\SFX\\potion.wav"