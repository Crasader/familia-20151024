#include "HelloWorldScene.h"
#include <random>


USING_NS_CC;
USING_NS_CC_EXT;


int _sts_sprite1;
int _sts_sprite2;
int _emo_sprite1;
int _emo_sprite2;
bool _reserveReturne;
std::string _temp_indoor;
std::string _temp_outdoor;
std::string _temp_air;
std::string _pos_sprite1;
std::string _pos_sprite2;
bool _sts_btle_equipment;
bool _sts_hems_service;
std::string FullName;

bool CardSprite::init()
{
    if (!Sprite::init())
    {
        return false;
    }

    card_type_name =
    {
        "まちの情報",
        "料理\n外食サイト",
        "家族伝言板",
        "ニュース",
        "書籍情報",
        "ビデオ\nメッセージ",
        "家のこと\nお知らせ",
        "住宅情報",
        "ヘルスケア",
        "蓄電情報",
        "消費電力\nモード",
        "リモコン",
        "まとめて\n戸締り",
        "帰宅支援\nGood\nTiming",
        "玄関カギ"
    };
    
    return true;
}

void CardSprite::onEnter()
{
    Sprite::onEnter();

    //画像の表示
    setTexture("card_back.png");
    
    //カードの位置とタグを指定
    setTag(_posIndex.x + _posIndex.y * 5 + 1);
}

std::string CardSprite::getFileName(CardType cardType)
{
    
    std::random_device device;
    
    std::mt19937 mt(device());
    std::default_random_engine _engine = std::default_random_engine(mt());
    
    //取り出す値を設定(int型)
    std::discrete_distribution<int>  distForNumbers = std::discrete_distribution<int>{0,1,2,3};
    //実際に利用
    int index = distForNumbers(_engine);

    //ファイル名の取得
    std::string filename;
    switch (index)
    {
        case Clubs: filename = "card_clubs.png"; break;
        case Diamonds: filename = "card_diamonds.png"; break;
        case Hearts: filename = "card_hearts.png"; break;
        default: filename = "card_spades.png"; break;
    }
    
    return filename;
}

void CardSprite::showNumber()
{
    //表示する数字の取得
    std::string numberString;
    int temp_num = 0;
    
    switch (_card.number)
    {
        case 1:
        switch (_card.type) {
            case 0: temp_num = 0; break;
            case 1: temp_num = 13; break;
            case 2: temp_num = 26; break;
            case 3: temp_num = 39; break;
            }
            break;
        case 2:
            switch (_card.type) {
                case 0: temp_num = 1; break;
                case 1: temp_num = 14; break;
                case 2: temp_num = 27; break;
                case 3: temp_num = 40; break;
            }
            break;
        case 3:
            switch (_card.type) {
                case 0: temp_num = 2; break;
                case 1: temp_num = 15; break;
                case 2: temp_num = 28; break;
                case 3: temp_num = 41; break;
            }
            break;
        case 4:
            switch (_card.type) {
                case 0: temp_num = 3; break;
                case 1: temp_num = 16; break;
                case 2: temp_num = 29; break;
                case 3: temp_num = 42; break;
            }
            break;
        case 5:
            switch (_card.type) {
                case 0: temp_num = 4; break;
                case 1: temp_num = 17; break;
                case 2: temp_num = 30; break;
                case 3: temp_num = 43; break;
            }
            break;
        case 6:
            switch (_card.type) {
                case 0: temp_num = 5; break;
                case 1: temp_num = 18; break;
                case 2: temp_num = 31; break;
                case 3: temp_num = 44; break;
            }
            break;
        case 7:
            switch (_card.type) {
                case 0: temp_num = 6; break;
                case 1: temp_num = 19; break;
                case 2: temp_num = 32; break;
                case 3: temp_num = 45; break;
            }
            break;
        case 8:
            switch (_card.type) {
                case 0: temp_num = 7; break;
                case 1: temp_num = 20; break;
                case 2: temp_num = 33; break;
                case 3: temp_num = 46; break;
            }
            break;
        case 9:
            switch (_card.type) {
                case 0: temp_num = 8; break;
                case 1: temp_num = 21; break;
                case 2: temp_num = 34; break;
                case 3: temp_num = 47; break;
            }
            break;
        case 10:
            switch (_card.type) {
                case 0: temp_num = 9; break;
                case 1: temp_num = 22; break;
                case 2: temp_num = 35; break;
                case 3: temp_num = 48; break;
            }
            break;
        case 11:
            switch (_card.type) {
                case 0: temp_num = 10; break;
                case 1: temp_num = 23; break;
                case 2: temp_num = 36; break;
                case 3: temp_num = 49; break;
            }
            break;
        case 12:
            switch (_card.type) {
                case 0: temp_num = 11; break;
                case 1: temp_num = 24; break;
                case 2: temp_num = 37; break;
                case 3: temp_num = 50; break;
            }
            break;
        case 13:
            switch (_card.type) {
                case 0: temp_num = 12; break;
                case 1: temp_num = 25; break;
                case 2: temp_num = 38; break;
                case 3: temp_num = 51; break;
            }
            break;
    }

    numberString = card_type_name[temp_num];
    
    //ラベルの生成
    auto number = Label::createWithSystemFont(numberString, "Arial", 24);
    number->setPosition(Point(getContentSize() / 2));
    number->setTextColor((Color4B)Color4B::BLACK);
    addChild(number);
}

void CardSprite::moveBackToInitPos()
{
    //移動アニメーションの作成
    float posX = CARD_1_POS_X + CARD_DISTANCE_X * _posIndex.x;
    float posY = CARD_1_POS_Y + CARD_DISTANCE_Y * _posIndex.y;
    auto move = MoveTo::create(MOVING_TIME, Point(posX, posY));
    
    //アニメーションの実行
    runAction(move);
}

void CardSprite::moveToTrash()
{
    //移動アニメーションの作成
    float posX = CARD_1_POS_X + CARD_DISTANCE_X * 4;
    float posY = CARD_1_POS_Y - CARD_DISTANCE_Y;
    auto move = MoveTo::create(MOVING_TIME, Point(posX, posY));
    
    //アニメーション後に呼び出す関数の作成
    auto func = CallFunc::create([&](){
        this->setTag(TAG_TRUSH_CARD);
    });
    
    //アクションの直列結合
    auto seq = Sequence::create(move, func, nullptr);
    
    //アニメーションの実行
    runAction(seq);
}

void CardSprite::moveToInitPos()
{
    //移動アニメーションの作成
    float posX = CARD_1_POS_X + CARD_DISTANCE_X * _posIndex.x;
    float posY = CARD_1_POS_Y + CARD_DISTANCE_Y * _posIndex.y;
    auto move = MoveTo::create(MOVING_TIME, Point(posX, posY));
    
    //カード回転アニメーションの作成
    auto scale1 = ScaleTo::create(MOVING_TIME / 2, 0, 1);
    auto func1 = CallFunc::create([&](){
        //画像の表示
        setTexture(getFileName(_card.type));
        
        //数字の表示
        showNumber();
    });
    auto scale2 = ScaleTo::create(MOVING_TIME / 2, 1, 1);
    auto seq1 = Sequence::create(scale1, func1, scale2, nullptr);
    
    //アクションの並列結合
    auto spawn = Spawn::create(move, seq1, nullptr);
    
    //アニメーションの実行
    runAction(spawn);
}

Scene* HelloWorld::scene()
{
    //シーンを生成する
    auto scene = Scene::create();
    
    //HelloWorldクラスのレイヤーを生成する
    auto layer = HelloWorld::create();
    
    //シーンに対してレイヤーを追加する
    scene->addChild(layer);
    
    //シーンを返す
    return scene;
}

//HelloWorldクラスのレイヤーの初期化処理を行う
bool HelloWorld::init()
{
    if (!Layer::init())
    {
        return false;
    }

    emotion_status =
    {
        "sumairu.png", // スマイル（通常）
        "akuma.png", // 怒り
        "ase.png",  // 汗（緊張）
        "kiran.png", // キラーん（やる気）
        "komaru.png", // 困り（トラブル）
        "naki.png", // 泣き
        "tehehe.png", // てへへ（いたずらしちゃった）
        "tenshi.png", // 天使　（絶好調）
        "tere.png", // てれる
        "yattane.png" // やったね！
    };
    family_menber =
    {
        "mother.png",
        "grandmother.png",
        "boy.png",
        "brother.png",
        "randfather.png"
    };
    countCard = 0;
    char commnad_name[1024];
    getHouseInfo(commnad_name);

    
    //シングルタップイベント取得
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(_swallowsTouches);
    
    //イベント関数の割り当て
    listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(HelloWorld::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);
    listener->onTouchCancelled = CC_CALLBACK_2(HelloWorld::onTouchCancelled, this);
    
    //イベントを追加する
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    //ゲームを初期化する
    initGame();


    return true;
}

void HelloWorld::initCards()
{
    //ゲームカードのクリア
    _cards.clear();
    countCard=0;
    
    //4種類 x 13枚分のループ
    for (int type = 0; type < CARD_TYPE_NUM; type++)
    {
        for (int number = 1; number <= CARD_NUM; number++)
        {
            //カード情報の作成
            Card card;
            card.number = number;
            card.type = (CardType)type;
            
            //カードを追加する
            _cards.push_back(card);
        }
    }
}

Card HelloWorld::getCard()
{
    //カードの数値を取得する
    if(countCard>14){
        countCard = 0;
    }
    auto card = _cards[countCard];
    countCard++;
    
    return card;
}

void HelloWorld::createCard(PosIndex posIndex)
{
    float posX = CARD_1_POS_X;
    float posY = CARD_1_POS_Y - CARD_DISTANCE_Y;

    //新しいカードを作成する
    auto card = CardSprite::create();
    card->setCard(getCard());
    card->setPosition(posX, posY);
    card->setPosIndex(posIndex);
    card->moveToInitPos();
    addChild(card, ZORDER_SHOW_CARD);
}

void HelloWorld::showInitCards()
{
    for (int tag = 1; tag <= 10; tag++)
    {
        auto card = getChildByTag(tag);
        if (card)
        {
            //カードが残っている場合は、削除する
            card->removeFromParent();
        }
    }
    
    //5列 x 2行分のループ
    for (int x = 0; x < 5; x++)
    {
        for (int y = 0; y < 3; y++)
        {
            PosIndex posIndex;
            posIndex.x = x;
            posIndex.y = y;
            
            //カードの生成
            createCard(posIndex);
        }
    }
}

void HelloWorld::playBGM()
{
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("music/bgm.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.1f);
    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("music/bgm.mp3",true);
}

void HelloWorld::stopBGM()
{
    CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
}

void HelloWorld::playEffect()
{
    std::vector<std::string> effect_sounds = {
        "music/blackout_harp1.mp3",
        "music/small_footsteps.mp3"
    };
    
    std::random_device device;
    
    std::mt19937 mt(device());
    std::default_random_engine _engine = std::default_random_engine(mt());
    
    //取り出す値を設定(int型)
    std::discrete_distribution<int>  distForNumbers = std::discrete_distribution<int>{0,1};
    //実際に利用
    int index = distForNumbers(_engine);
    
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(effect_sounds[index].c_str());
    CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume(0.5f);
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(effect_sounds[index].c_str());
//    CocosDenshion::SimpleAudioEngine::getInstance()->unloadEffect(effect_sounds[index].c_str());
}


void HelloWorld::initGame()
{
    Size winSize = Director::getInstance()->getVisibleSize();
    playBGM();
    
    auto _bg2 = LayerColor::create(Color4B(0,0x33,0xFF,0x99), winSize.width, winSize.height);
    this->addChild(_bg2);
    
    Sprite* sprite;
    sprite = Sprite::create("mother.png");
    sprite->setScale(2.5f);
    sprite->setPosition(Vec2(winSize.width/2, winSize.height*4/5));
    addChild(sprite);
    cocos2d::Label* label = Label::createWithSystemFont("この端末のオーナー\n"+FullName, "Marker Felt.ttf", 30);
    label->setScale(2.0f);
    label->setPosition(Vec2(winSize.width/2, winSize.height*8/9));
    this->addChild(label);
    
    if(_sts_hems_service){
        //CCSpriteクラスで画像を設定します。
        _sts_sprite1 = 0;
        _sts_sprite2 = 0;
        _sprite1 = Sprite::create("boy.png");
        _sprite1_emotion = Sprite::create(emotion_status[_sts_sprite1]);
        _sprite1->setScale(2.5f);
        _sprite1->setPosition(Vec2(winSize.width*1/4, winSize.height/8));
        _sprite1->setTag(TAG_BOY);
        addChild(_sprite1);
        _sprite1_emotion->setScale(2.0f);
        _sprite1_emotion->setPosition(Vec2(winSize.width*1/4-80, winSize.height/8+70));
        addChild(_sprite1_emotion);
        _sprite2 = Sprite::create("grandmother.png");
        _sprite2_emotion = Sprite::create(emotion_status[_sts_sprite2]);
        _sprite2->setScale(3.0f);
        _sprite2->setPosition(Vec2(winSize.width*3/4, winSize.height/8));
        _sprite2->setTag(TAG_GRANDMOTHER);
        addChild(_sprite2, 0);
        _sprite2_emotion->setScale(2.0f);
        _sprite2_emotion->setPosition(Vec2(winSize.width*3/4-80, winSize.height/8+70));
        addChild(_sprite2_emotion, 0);
    
        _label1 = Label::createWithSystemFont("検索中", "Marker Felt.ttf", 30);
        _label1->setScale(2.0f);
        _label1->setPosition(Vec2(winSize.width*1/4, winSize.height/12));
        this->addChild(_label1);

        _label2 = Label::createWithSystemFont("検索中", "Marker Felt.ttf", 30);
        _label2->setScale(2.0f);
        _label2->setPosition(Vec2(winSize.width*3/4, winSize.height/12));
        this->addChild(_label2);

        _label3 = Label::createWithSystemFont("- - -", "Marker Felt.ttf", 14);
        _label3->setScale(2.0f);
        _label3->setPosition(Vec2(winSize.width/2, winSize.height/25));
        this->addChild(_label3);
    
        this->schedule(schedule_selector(HelloWorld::Action01), 3.0f);
        this->schedule(schedule_selector(HelloWorld::Action02), 3.0f);
    }else{
        _label3 = Label::createWithSystemFont("現在サービス利用停止中です", "Marker Felt.ttf", 24);
        _label3->setScale(2.0f);
        _label3->setPosition(Vec2(winSize.width/2, winSize.height/12));
        this->addChild(_label3);
    }

    //裏向いているカードを表示する
    showBackCards();
    
    //時間を表示する
    showTimerLabel();
    
    //ボタンを表示する
    // showButton();

    //update関数の呼び出しを停止
    unscheduleUpdate();
    
    //カードを初期化する
    initCards();
    
    //カードを表示する
    showInitCards();
    
    //カードの山を表示する
    showBackCards();
    
    //ゴミ箱を初期化する
    initTrash();
    
    //時間を表示する
    showTimerLabel();
    
    //update関数の呼び出しを開始
    scheduleUpdate();

}

void HelloWorld::Sequence1(int status)
{
    float time;
    float num;
    switch (status) {
        case 0:
            time = 1.8f;
            num = 0.3f;
            break;
        case 1:
            time = 1.8f;
            num = 3.0f;
            break;
            
        default:
            time = 1.0f;
            num = 1.0f;
            break;
    }
    // 大きさ（縮小）アクションを適用 1.0秒 0倍
    auto scaleTo1 = ScaleTo::create(time, num);
    //callbackでの消去処理
    auto removeSprite1 = CallFunc::create([this](){
//        this->removeChild(_sprite1);
    });
    // 縮小、消去アクションを適用
    auto sequence1 = Sequence::create(scaleTo1, removeSprite1, NULL);
    // 縮小、消去runアクションを適用
    _sprite1->runAction(sequence1);
}

void HelloWorld::Sequence2(int status)
{
    float time;
    float num;
    switch (status) {
        case 0:
            time = 1.8f;
            num = 0.2f;
            break;
        case 1:
            time = 1.8f;
            num = 4.2f;
            break;
            
        default:
            time = 1.0f;
            num = 1.0f;
            break;
    }
    // 大きさ（縮小）アクションを適用 2.5秒 0倍
    auto scaleTo2 = ScaleTo::create(time, num);
    //callbackでの画像消去処理
    auto removeSprite2 = CallFunc::create([this](){
//        this->removeChild(_sprite2);
    });
    // 縮小、消去アクションを適用
    auto sequence2 = Sequence::create(scaleTo2, removeSprite2, NULL);
    // 縮小、消去runアクションを適用
    _sprite2->runAction(sequence2);
}

void HelloWorld::getHouseEquipmentStatus(char* result)
{
    const char *post_command;
    post_command = "http://127.0.0.1:3000/get_message?type=2";
    std::string recv = Get_data(post_command);
    
    Json* json = Json_create(recv.c_str());
    if (json) {
        int eq_sts = Json_getInt(json, "equipment", 0);
        
        if (_sts_hems_service==true && eq_sts!=3 && _sts_btle_equipment==false) {
            // 異常警報！ 開けっ放しでお出かけとか、不審侵入とか異常検知
            //  最終的にはコメントアウトは外す（今は、環境ができていないので常に異常事態になってしまうので。）
             CocosDenshion::SimpleAudioEngine::getInstance()->stopAllEffects();
             CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("music/emargency_calling.mp3");
             CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume(0.5f);
             CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music/emargency_calling.mp3");
        }
    }

    return;
}

std::vector<std::string> split(const std::string &str, char sep)
{
    std::vector<std::string> v;        // 分割結果を格納するベクター
    auto first = str.begin();              // テキストの最初を指すイテレータ
    while( first != str.end() ) {         // テキストが残っている間ループ
        auto last = first;                      // 分割文字列末尾へのイテレータ
        while( last != str.end() && *last != sep )       // 末尾 or セパレータ文字まで進める
            ++last;
        v.push_back(std::string(first, last));       // 分割文字を出力
        if( last != str.end() )
            ++last;
        first = last;          // 次の処理のためにイテレータを設定
    }
    return v;
}

void HelloWorld::getTargetStatus(char* result)
{
    const char *post_command;
    post_command = "http://127.0.0.1:3000/get_message?type=3";
    std::string recv = Get_data(post_command);
    Json* json = Json_create(recv.c_str());
    if (json) {
        _sts_sprite1 = Json_getInt(json, "sts1", 0);
        _emo_sprite1 = Json_getInt(json, "emo1", 0);
        _sts_sprite2 = Json_getInt(json, "sts2", 0);
        _emo_sprite2 = Json_getInt(json, "emo2", 0);
        _pos_sprite1 = Json_getString(json, "desc1", "");
        _pos_sprite2 = Json_getString(json, "desc2", "");

    }
    post_command = "http://127.0.0.1:3000/get_message?type=12";
    recv = Get_data(post_command);
    json = Json_create(recv.c_str());
    if (json) {
        _temp_indoor = Json_getString(json, "indor_temp", "");
        _temp_outdoor = Json_getString(json, "out_temp", "");
        _temp_air = Json_getString(json, "elec_temp", "");
    }

    return;
}

int estateType;
void HelloWorld::getHouseInfo(char* result)
{
    const char *post_command;
    post_command = "http://127.0.0.1:3000/get_message?type=1";
    std::string recv = Get_data(post_command);
    Json* json = Json_create(recv.c_str());
    if (json) {
        _sts_hems_service = true;
        FullName = Json_getString(json, "firstname", "");
        FullName += Json_getString(json, "lastname", "");
        std::string buildtype = Json_getString(json, "buildtype", "");
        std::string ownership = Json_getString(json, "ownership", "");
        
        if (ownership == "持家") {
            if (buildtype=="戸建") {
                estateType = 1;
            }else{
                estateType = 2;
            }
        }else{
            if (buildtype=="戸建") {
                estateType = 10;
            }else{
                estateType = 11;
            }
        }
        
        std::string latitude = Json_getString(json, "latitude", "");
        std::string longitude = Json_getString(json, "longitude", "");

        float val_latitude = std::stof(latitude);	// 10.5f
        float val_longitude = std::stof(longitude); // -10.5f
        NativeLauncher::set_TargetLocationInfo_lati(val_latitude);
        NativeLauncher::set_TargetLocationInfo_longi(val_longitude);

    }else {
        _sts_hems_service = false;
    }

    return;
}

//  文字列を置換する
std::string HelloWorld::Replace( std::string String1, std::string String2, std::string String3 )
{
    std::string::size_type  Pos( String1.find( String2 ) );
    
    while( Pos != std::string::npos )
    {
        String1.replace( Pos, String2.length(), String3 );
        Pos = String1.find( String2, Pos + String3.length() );
    }
    
    return String1;
}

void HelloWorld::setTargetStatus(int val1, int emo1, int val2, int emo2)
{
    _sts_sprite1 = val1;
    _sts_sprite2 = emo1;
    _sts_sprite1 = val1;
    _sts_sprite2 = emo2;
}

void HelloWorld::BTLEAction()
{
    _sts_btle_equipment = true;
}

// １番目画像Runアクションメソッド
void HelloWorld::Action01(float frame)
{
    _sprite1_emotion->setTexture(emotion_status[_sts_sprite1]);

    _label1->setString(_pos_sprite1);
}

// ２番目画像Runアクションメソッド
void HelloWorld::Action02(float frame)
{
    _sprite2_emotion->setTexture(emotion_status[_sts_sprite2]);
    _label2->setString(_pos_sprite2);

    std::ostringstream stream1;
    std::ostringstream stream2;
    std::ostringstream stream3;
    stream1 << _temp_indoor;
    stream2 << _temp_outdoor;
    stream3 << _temp_air;
    std::string temp = "室内：" + stream1.str() + "度：室外：" + stream2.str() + "度設定温度：" + stream2.str() + "度";
    _label3->setString(temp);
}

CardSprite* HelloWorld::getTouchCard(Touch *touch)
{
    for (int tag = 1; tag <= 15; tag++)
    {
        //表示されているカードを取得する
        auto card = (CardSprite*)getChildByTag(tag);
        if (card &&
            card != _firstCard &&
            card->getBoundingBox().containsPoint(touch->getLocation()))
        {
            //タップされたカードの場合は、そのカードを返す
            return card;
        }
    }
    
    return nullptr;
}

bool HelloWorld::onTouchBegan(Touch *touch, Event *unused_event)
{
    //タップされたカードを取得する
    _firstCard = getTouchCard(touch);
    if (_firstCard)
    {
        //場に出ているカードがタップされた場合
        
        //Zオーダーを変更する
        _firstCard->setLocalZOrder(ZORDER_MOVING_CARD);
        
        playEffect();
        return true;
    }
    
    
    auto sprite1 = this->getChildByTag(TAG_BOY);
    if (sprite1 &&
        sprite1->getBoundingBox().containsPoint(touch->getLocation()))
    {
        showModal(1);
        return false;
    }
    auto sprite2 = this->getChildByTag(TAG_GRANDMOTHER);
    if (sprite2 &&
        sprite2->getBoundingBox().containsPoint(touch->getLocation()))
    {
        showModal(1);
        return false;
    }

    
    return false;
}

void HelloWorld::onTouchMoved(Touch *touch, Event *unused_event)
{
    //スワイプしているカードの位置を変更
    _firstCard->setPosition(_firstCard->getPosition() + touch->getDelta());
}

void HelloWorld::menuStartCallback(Ref* Sender)
{
    MenuItem* menuItem = (MenuItem*)Sender;
    log("%d",menuItem->getTag());
    switch(menuItem->getTag()){
        case 1:
            break;
        case 2:
            break;
    }
    dialogClose();
}
void HelloWorld::dialogClose()
{
    UIDialog* dialog = static_cast<UIDialog*>(getChildByTag(30));
    dialog->close();
}

void HelloWorld::showModal(int type)
{
    std::string title;
    std::string content1;
    std::string content2;
    switch (type) {
        case 0:
            title = "他の機能を利用する";
            content1 = "お知らせです";
            content2 = "この機能は現在利用できません\n運用が開始されるまでお待ち下さい※";
            break;
        case 1:
            title = "メインへ戻る";
            content1 = "工事中";
            content2 = "遷移先の機能は現在利用できません\n運用が開始されるまでお待ち下さい※";
            break;
            
        default:
            break;
    }
    cocos2d::ccMenuCallback action = CC_CALLBACK_1(HelloWorld::menuStartCallback,this);
    std::vector<UIDialogButton*> buttons = {
        new UIDialogButton(title,action,1),
    };
    auto* dialog = UIDialog::create(content1,content2, buttons);
    addChild(dialog,31,30);
}

void HelloWorld::onTouchEnded(Touch *touch, Event *unused_event)
{
    auto sprite1 = this->getChildByTag(TAG_BOY);
    if (sprite1 &&
        sprite1->getBoundingBox().containsPoint(touch->getLocation()))
    {
        return;
    }
    auto sprite2 = this->getChildByTag(TAG_GRANDMOTHER);
    if (sprite2 &&
        sprite2->getBoundingBox().containsPoint(touch->getLocation()))
    {
        return;
    }
    
    
    int indetifier = 0;
    int indetifier_sub = 0;
    
    //タップしたカードの取得
    auto _secondSprite = getTouchCard(touch);
    indetifier = _firstCard->getCard().number;
    if (_secondSprite)
    {
        indetifier_sub = _secondSprite->getCard().number;
    }

    
    indetifier = _firstCard->getCard().type*13 + indetifier;
    
    
    
    
    //新しいカードを配置する
    if ((int)_cards.size() > 0)
    {
        createCard(_firstCard->getPosIndex());
    }
        
    //カードを捨てる
    _firstCard->moveToTrash();
        
    if (_secondSprite)
    {
        //もう1枚の新しいカードを配置する
        if ((int)_cards.size() > 0)
        {
            createCard(_secondSprite->getPosIndex());
        }
            
        //カードを捨てる
        _secondSprite->moveToTrash();
    }
        
    if ((int)_cards.size() <= 0)
    {
        //カードの山を削除する
        removeChildByTag(TAG_BACK_CARD);
    }
    
    //タップしているカードの指定を外す
    _firstCard = nullptr;

    switch(indetifier){
    case 1: // 自治体
            // ToDo 今回はしんどいので実装しない
            CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(2.0f,
                                                                                SmartCityController::scene(),
                                                                                ccc3(0, 0, 0)));
            
        break;
    case 2: // 料理、外食サイト
        CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(2.0f,
                                                                            CookingController::scene(),
                                                                            ccc3(0, 0, 0)));
        break;
    case 3: // 家族からのお知らせ
            // ToDo 今回はしんどいので実装しない
            showModal(0);
/*
        CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(2.0f,
                                                                            FamiliaController::scene(),
                                                                            ccc3(0, 0, 0)));
 */
        break;
    case 4: // ニュース
        CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(2.0f,
                                                                            InfoController::scene(),
                                                                            ccc3(0, 0, 0)));
        break;
    case 5: // 書籍情報
        CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(2.0f,
                                                                            ServiceController::scene(),
                                                                            ccc3(0, 0, 0)));
        break;
    case 6: // ビデオメッセージ
        stopBGM();
        CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(2.0f,
                                                                            MediaController::scene(),
                                                                            ccc3(0, 0, 0)));
        break;
    case 7: // メッセージ　運営事務からの
        CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(2.0f,
                                                                            HomeInfoController::scene(),
                                                                            ccc3(0, 0, 0)));

        break;
    case 8: // 住宅情報　プロジぎょしゃへの送客
        CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(2.0f,
                                                                            EstateController::scene(estateType),
                                                                            ccc3(0, 0, 0)));
        break;
    case 9: // 万歩計スタート & ストップ　行動履歴を取得するため
        CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(2.0f,
                                                                            MotionController::scene(),
                                                                            ccc3(0, 0, 0)));
        break;
    case 10: // 蓄電情報　エネルギー情報を見る
        CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(2.0f,
                                                                            ComsumeController::scene(),
                                                                            ccc3(0, 0, 0)));
        break;
    case 11: // 消費電力を行う　微妙に設定値を節電方向にする
        CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(2.0f,
                                                                            PowersaveController::scene(),
                                                                            ccc3(0, 0, 0)));
        break;
    case 12: // 設備機器　設備機器の状態と制御ができるようにする
        CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(2.0f,
                                                                            EquipmentController::scene(),
                                                                            ccc3(0, 0, 0)));
        break;
    case 13: // お出かけ\nまとめ処理
        CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(2.0f,
                                                                            OutgoingController::scene(),
                                                                            ccc3(0, 0, 0)));
        break;
    case 14: // 帰宅予約
        CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(2.0f,
                                                                            ReserveRetunrHomeController::scene(),
                                                                            ccc3(0, 0, 0)));
        break;
    case 15: // 玄関ドアの開閉
        CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(2.0f,
                                                                            SecurityController::scene(),
                                                                            ccc3(0, 0, 0)));
        break;
    default:
        CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(2.0f,
                                                                            SecurityController::scene(),
                                                                            ccc3(0, 0, 0)));
        break;
    }

}

void HelloWorld::onTouchCancelled(Touch *touch, Event *unused_event)
{
    //タップ終了と同じ処理を行う
    onTouchEnded(touch, unused_event);
}

void HelloWorld::showButton()
{
    //ボタンを作成する
    auto button = ControlButton::create(Scale9Sprite::create("button.png"));
    
    //画像を引き延ばさない設定
    button->setAdjustBackgroundImage(false);
    
    //ボタンの位置設定
    button->setPosition(BUTTON_POS_X, BUTTON_POS_Y);
    
    //ボタンをタップしたときに呼び出す関数の設定
    button->addTargetWithActionForControlEvents(this,
                                                cccontrol_selector(HelloWorld::onTapButton),
                                                Control::EventType::TOUCH_UP_INSIDE);
    
    //ボタンに表示する文字
    button->setTitleForState("Start", Control::State::NORMAL);
    
    //画面に追加する
    addChild(button);
}

void HelloWorld::initTrash()
{
    while (true)
    {
        //ゴミカードがなくなるまでループする
        auto card = getChildByTag(TAG_TRUSH_CARD);
        if (card)
        {
            //ゴミカードが見つかったら削除する
            card->removeFromParent();
        }
        else
        {
            break;
        }
    }
}

void HelloWorld::showBackCards()
{
    return;
/*
    auto backCards = getChildByTag(TAG_BACK_CARD);
    if (!backCards)
    {
        //表示されていない場合
        
        float posX = CARD_1_POS_X;
        float posY = CARD_1_POS_Y - CARD_DISTANCE_Y;
        
        //カードの山を表示する
        backCards = Sprite::create("card_back.png");
        backCards->setPosition(posX, posY);
        backCards->setTag(TAG_BACK_CARD);
        addChild(backCards);
    }
*/
}

void HelloWorld::onTapButton(Ref* sender, Control::EventType controlEvent)
{
    //update関数の呼び出しを停止
    unscheduleUpdate();
    
    //カードを初期化する
    initCards();
    
    //カードを表示する
    showInitCards();
    
    //カードの山を表示する
    showBackCards();
    
    //ゴミ箱を初期化する
    initTrash();
    
    //時間を表示する
    showTimerLabel();
    
    //update関数の呼び出しを開始
    scheduleUpdate();
}

void HelloWorld::showTimerLabel()
{
    _timer = 0;
/*
    auto timerLabel = (Label*)getChildByTag(TAG_TIMER_LABEL);
    if (!timerLabel)
    {
        //時間のラベルを表示する
        timerLabel = Label::createWithSystemFont("", "Arial", 48);
        timerLabel->setPosition(TIMER_LABEL_POS_X, TIMER_LABEL_POS_Y);
        timerLabel->setTag(TAG_TIMER_LABEL);
        addChild(timerLabel);
    }
*/
//    timerLabel->setString(StringUtils::format("%0.2fs", _timer));
}

#define ONE 1
#define TWO 2

void HelloWorld::update(float dt)
{
    char commnad_name[1024];
    _timer += dt;
    //時間の積算
    if (_timer > 6){
        _timer=0;
        getHouseEquipmentStatus(commnad_name);
        getTargetStatus(commnad_name);
    }
}
