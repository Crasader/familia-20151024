//
//  UserStatus.cpp
//  Card13
//
//  Created by Hiroki Ariji on 2015/10/04.
//
//

#include "UserStatus.hpp"


int _user1_status;
int _user1_emotion;
int _user2_status;
int _user2_emotion;

void UserStatusController::setUser1Status(int type)
{
    _user1_status = type;
}

int UserStatusController::getUser1Status()
{
    return _user1_status;
}

void UserStatusController::setUser1Emotion(int type)
{
    _user2_status = type;
}

int UserStatusController::getUser1Emotion()
{
    return _user2_status;
}
