#include "PlayerMovementSubjectObserver.h"

/*--------------------------------------------------------------------------------------------------------------------*/
void PlayerMovementSubject::registerPlayerMovementObserver(PlayerMovementObserver *observer)
{
  observers_.insert(observer);
}

/*--------------------------------------------------------------------------------------------------------------------*/
void PlayerMovementSubject::unregisterPlayerMovementObserver(PlayerMovementObserver *observer)
{
  observers_.erase(observer);
}

/*--------------------------------------------------------------------------------------------------------------------*/
void PlayerMovementSubject::notifyPlayerMovementObservers()
{
  for(auto observer : observers_)
    observer->notify();
}

/*--------------------------------------------------------------------------------------------------------------------*/
void PlayerMovementObserver::notify()
{

}